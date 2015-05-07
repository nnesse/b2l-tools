local b2l_gl = require 'b2l_material_editor'
local lgi = require 'lgi'
local Gtk = lgi.require('Gtk')
local Gdk = lgi.require('Gdk')
local GLib = lgi.require('GLib')
local GdkPixbuf = lgi.require('GdkPixbuf')
local pprint = require 'pprint'

scene = false

local window_main = Gtk.Window {
   title = 'B2L Material Editor',
   on_destroy = Gtk.main_quit,
   width_request = 250,
}

vbox_settings = Gtk.VBox {
	hexpand = true
}

editor_env = os.getenv("EDITOR")
if editor_env then
	editor = GLib.find_program_in_path(editor_env)
end
if not editor then
	editor = GLib.find_program_in_path("gvim")
end
if not editor then
	editor = GLib.find_program_in_path("gedit")
end
if not editor then
	editor = GLib.find_program_in_path("emacs")
end

fs_text =
"#version 330\
out vec4 color;\
void main()\
{\
	color = vec4(1);\
}"

vs_text=
"#version 330\
in vec3 pos;\
void main()\
{\
	gl_Position = vec4(vec3(pos.x, pos.y, -pos.z) * 1.0, 1);\
}"

controls = {}
texture_units = {}

function queue_render()
	b2l_gl:need_redraw()
end

function setting_changed()
	save_toolbutton.sensitive = true
end

function update_shaders()
	if not scene then
		return
	end
	local uniforms = b2l_gl.set_shaders(scene.userdata, vs_text, fs_text)
	if not uniforms then
		local dialog = Gtk.MessageDialog {
			parent = window,
			message_type = 'ERROR', buttons = 'CLOSE',
			text = "Failed to parse shaders",
			on_response = Gtk.Widget.destroy
		}
		dialog:show_all()
		return
	end
	for k, v in pairs(controls) do
		if not uniforms[k] then
			if controls[k].datatype == "sampler2D" and controls[k].texunit then
				texture_units[controls[k].texunit] = false
			end
		end
		if (v.widget) then
			vbox_settings:remove(v.widget)
		end
		if not uniforms[k] then
			controls[k].widget = nil
		end
	end
	for i, k in ipairs(uniforms) do
		local v = uniforms[k]
		local value = false
		if not controls[k] then
			controls[k] = {}
		end
		if controls[k].datatype == v then
			if controls[k].mat_value ~= nil then
				value = controls[k].mat_value
				controls[k].mat_value = nil
			else
				value = controls[k].value
			end
		end
		if v == "float" then
			if controls[k].value == nil then
				value = 0.5
			end
			if not controls[k].widget then
				local widget = Gtk.Expander {
					label = k,
					expanded = true,
					Gtk.Scrollbar {
						orientation = "HORIZONTAL",
						adjustment = Gtk.Adjustment {
							lower = 0,
							upper = 1,
						},
						on_value_changed = function(self)
							if controls[k].value ~= self:get_value() then
								setting_changed()
							end
							controls[k].value = self:get_value()
							queue_render()
						end
					}
				}
				controls[k].widget = widget
			end
			controls[k].value = value
			controls[k].widget:get_child():set_value(value)
			vbox_settings:pack_end(controls[k].widget, false, false, 5)
		elseif v == "vec3" then
			if controls[k].value == nil then
				value = {1, 1, 1}
			end
			if not controls[k].widget then
				controls[k] = {}
				local widget = Gtk.Expander {
					label = k,
					expanded = true,
					Gtk.ColorButton {
						use_alpha = false,
						on_color_set = function(self)
							save_toolbutton.sensitive = true
							local value = {self.rgba.red, self.rgba.green, self.rgba.blue }
							if value[1] ~= controls[k].value[1] or
								value[2] ~= controls[k].value[2] or
								value[3] ~= controls[k].value[3] then
								setting_changed()
							end
							controls[k].value = {self.rgba.red, self.rgba.green, self.rgba.blue }
							queue_render()
						end
					}
				}
				controls[k].widget = widget
			end
			controls[k].value = value
			controls[k].widget:get_child():set_rgba(Gdk.RGBA {red = value[1], green = value[2], blue = value[3], alpha = 1})
			vbox_settings:pack_end(controls[k].widget, false, false, 5)
		elseif v == "bool" then
			if controls[k].value == nil then
				value = false
			end
			if not controls[k].widget then
				controls[k] = {}
				local widget = Gtk.CheckButton {
					label = k,
					on_toggled = function(self)
						if controls[k].value ~= self.active then
							setting_changed()
						end
						controls[k].value = self.active
						queue_render()
					end
				}
				controls[k].widget = widget
			end
			controls[k].value = value
			controls[k].widget:set_active(value)
			vbox_settings:pack_end(controls[k].widget, false, false, 5)
		elseif v == "sampler2D" then
			if controls[k].value == nil then
				value = nil
			end
			if not controls[k].widget then
				local t = 1;
				while texture_units[t] == true do
					t = t + 1
				end
				texture_units[t] = true
				controls[k] = { texunit= t }
				local widget = Gtk.Expander {
					label = k,
					expanded = true,
					Gtk.FileChooserButton {
						title = k,
						action = "OPEN",
						on_selection_changed = function(chooser)
							save_toolbutton.sensitive = true
							local filename = chooser:get_filename()
							if controls[k].value ~= filename then
								setting_changed()
							end
							if filename then
								local pbuf,err = GdkPixbuf.Pixbuf.new_from_file(filename)
								if pbuf then
									controls[k].value = filename
									controls[k].pbuf = pbuf
									controls[k].needs_upload = true
									queue_render()
								else
									local dialog = Gtk.MessageDialog {
										parent = window,
										message_type = 'ERROR', buttons = 'CLOSE',
										text = ("Failed to open image file: %s"):format(err),
										on_response = Gtk.Widget.destroy
									}
									dialog:show_all()
								end
							end
						end,
					}
				}
				controls[k].widget = widget
			end
			if value ~= nil then
				controls[k].value = value
				controls[k].widget:get_child():set_filename(value)
			end
			vbox_settings:pack_end(controls[k].widget, false, false, 5)
		end
		controls[k].value = value
		controls[k].datatype = v
	end
	vbox_settings:show_all()
	queue_render()
end

b2l_filter = Gtk.FileFilter {}
b2l_filter:set_name("B2L file")
b2l_filter:add_pattern("*.b2l")

vert_glsl_filter = Gtk.FileFilter {}
vert_glsl_filter:set_name("OpenGL vertex shader")
vert_glsl_filter:add_pattern("*.vert.glsl")

frag_glsl_filter = Gtk.FileFilter {}
frag_glsl_filter:set_name("OpenGL fragment shader")
frag_glsl_filter:add_pattern("*.frag.glsl")

function load_b2l_file(filename)
	local lua_name = filename
	if lua_name then
		local bin_name = lua_name .. ".bin"
		local mat_name = lua_name .. ".mat"
		scene = (loadfile(lua_name))()
		b2l_gl.parse_scene(scene, bin_name)
		local material_fn = loadfile(mat_name)
		if material_fn then
			local material = material_fn()
			if material then
				for k, v in pairs(controls) do
					v.mat_value = nil
				end
				for k, v in pairs(material.params) do
					if k ~= 'vs_filename' and k ~= 'fs_filename' then
						if controls[k] and controls[k].datatype == v.datatype then
							controls[k].mat_value = v.value
						else
							controls[k] = { ['mat_value'] = v.value, ['datatype'] = v.datatype }
						end
					end
				end
				vs_chooser:set_filename(material.shaders['vs_filename'])
				fs_chooser:set_filename(material.shaders['fs_filename'])
			end
		end
	end
	Gtk.main_iteration()
	save_toolbutton.sensitive = false
end

b2l_file_button = Gtk.FileChooserButton {
	title = "BRT File",
	action = "OPEN",
	filter = b2l_filter,
	on_selection_changed = function(chooser)
	 	local filename = chooser:get_filename()
		load_b2l_file(filename)
	end,
}

function reload_fs(filename)
	if filename then
		local fs_text_next, err = GLib.file_get_contents(filename)
		if fs_text_next then
			fs_text = fs_text_next
		end
	end
end

fs_edit_button = Gtk.Button {
		label = "Edit",
		sensitive = false,
		on_clicked = function()
			GLib.spawn_async(nil,
				{ editor, fs_chooser:get_filename() },
				nil,
				GLib.SpawnFlags {
					'SEARCH_PATH'
				},
				nil)
			end,
		}

fs_filename = nil
fs_chooser = Gtk.FileChooserButton {
		title = "Fragment shader",
		action = "OPEN",
		filter = frag_glsl_filter,
		on_selection_changed = function(chooser)
			local filename = chooser:get_filename()
			if fs_filename ~= filename then
				setting_changed()
			end
			reload_fs(filename)
			update_shaders()
			if filename then
				fs_edit_button.sensitive = true
			else
				fs_edit_button.sensitive = false
			end
		end,
	}

function reload_vs(filename)
	if filename then
		local vs_text_next, err = GLib.file_get_contents(filename)
		if vs_text_next then
			vs_text = vs_text_next
		end
	end
end


vs_edit_button = Gtk.Button {
	label = "Edit",
	sensitive = false,
	on_clicked = function()
		GLib.spawn_async(nil,
			{ editor, vs_chooser:get_filename() },
			nil,
			GLib.SpawnFlags {
				'SEARCH_PATH'
			},
			nil)
	end,
}

vs_filename = nil
vs_chooser = Gtk.FileChooserButton {
	title = "Vertex shader",
	action = "OPEN",
	filter = vert_glsl_filter,
	on_selection_changed = function(chooser)
		local filename = chooser:get_filename()
		if vs_filename ~= filename then
			setting_changed()
		end
		reload_vs(filename)
		update_shaders()
		if filename then
			vs_edit_button.sensitive = true
		else
			vs_edit_button.sensitive = false
		end
		vs_filename = filename
	end,
}

function open_b2l_chooser_dialog()
	local chooser = Gtk.FileChooserDialog {
		title = "Open B2l file",
		parent = window,
		action = 'OPEN',
		on_response = function(self, id, data)
			self:hide()
		end,
	}
	chooser:add_button('Cancel', Gtk.ResponseType.CANCEL)
	chooser:add_button('Open', Gtk.ResponseType.ACCEPT)
	chooser:add_filter(b2l_filter)
	local res = chooser:run()
	if res == Gtk.ResponseType.ACCEPT then
		local filename = chooser:get_filename()
		load_b2l_file(filename)
		b2l_file_button:set_filename(filename)
	end
end

save_toolbutton = Gtk.ToolButton {
	icon_name = "document-save",
	sensitive = false,
	on_clicked = function(button)
		local params = {}
		local shaders = {}
		local material = {
			['shaders'] = shaders,
			['params'] = params
		}
		shaders['vs_filename'] = vs_chooser:get_filename()
		shaders['fs_filename'] = fs_chooser:get_filename()
		str = "return "
		local printer = function(s)
			str = str .. s
		end
		for k,v in pairs(controls) do
			if v.widget then
				params[k] = {
					datatype = v.datatype,
					value = v.value
				}
			end
		end
		pprint.pformat(material, {}, printer)
		GLib.file_set_contents(b2l_file_button:get_filename() .. ".mat", str)
		button.sensitive = false
	end,
}

-- Pack everything into the window.
local vbox_main = Gtk.VBox {
	{
		Gtk.MenuBar {
			Gtk.MenuItem {
				label = "File",
				submenu = Gtk.Menu {
					Gtk.MenuItem {
						label = "Open",
						on_activate = function()
							open_b2l_chooser_dialog()
						end,
					},
					Gtk.MenuItem {
						label = "Exit",
						on_activate = function()
							Gtk.main_quit()
						end,
					}
				}
			},
		},
		expand = false,
		fill = false
	},
	{
		Gtk.Toolbar {
			Gtk.ToolButton {
				icon_name = "document-open",
				on_clicked = function()
					open_b2l_chooser_dialog()
				end,
			},
			save_toolbutton,
			Gtk.ToolButton {
				icon_name = "view-refresh",
				on_clicked = function()
					reload_fs(fs_chooser:get_filename())
					reload_vs(vs_chooser:get_filename())
					update_shaders()
				end,
			},
		},
		expand = false,
		fill = false
	},
	{
		Gtk.Label {
			label = "B2L File"
		},
		expand = false,
		fill = false,
	},
	{
		b2l_file_button,
		expand = false,
		fill = false,
	},
	{
		Gtk.Label {
			label = "Vertex Shader"
		},
		expand = false,
		fill = false,
	},
	{
		Gtk.HBox {
			vs_chooser,
			{
				vs_edit_button,
				expand = false,
				fill = false
			},
		},
		expand = false,
		fill = false,
	},
	{
		Gtk.Label {
			label = "Fragment Shader"
		},
		expand = false,
		fill = false,
	},
	{
		Gtk.HBox {
			fs_chooser,
			{
				fs_edit_button,
				expand = false,
				fill = false
			},
		},
		expand = false,
		fill = false,
	},
	{
		vbox_settings,
		expand = false,
		fill = true
	},
}

window_main:add(vbox_main)

-- Show windows and start the loop.
window_main:show_all()
Gtk.main()
