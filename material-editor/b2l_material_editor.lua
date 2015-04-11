local b2l_gl = require 'b2l_material_editor'
local lgi = require 'lgi'
local Gtk = lgi.require('Gtk')
local Gdk = lgi.require('Gdk')
local GLib = lgi.require('GLib')
local GdkPixbuf = lgi.require('GdkPixbuf')

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
			if controls[k].datatype == "sampler2D" then
				texture_units[controls[k].texunit] = false
			end
			controls[k] = nil
		end
		vbox_settings:remove(v.widget)
	end
	for i, k in ipairs(uniforms) do
		local v = uniforms[k]
		if v == "float" then
			if not controls[k] then
				controls[k] = { value = 0.5 }
				local widget = Gtk.Expander {
					label = k,
					expanded = true,
					Gtk.Scrollbar {
						orientation = "HORIZONTAL",
						adjustment = Gtk.Adjustment {
							lower = 0,
							upper = 1,
							value = controls[k].value
						},
						on_value_changed = function(self)
							controls[k].value = self:get_value()
							queue_render()
						end
					}
				}
				controls[k].widget = widget
				widget:get_child():set_value(controls[k].value)
			end
			vbox_settings:pack_end(controls[k].widget, false, false, 5)
		elseif v == "vec3" then
			if not controls[k] then
				local init_color = Gdk.RGBA {red = 1, green = 1, blue = 1, alpha = 1}
				controls[k] = { value = {init_color.red, init_color.green, init_color.blue} }
				local widget = Gtk.Expander {
					label = k,
					expanded = true,
					Gtk.ColorButton {
						rgba = init_color,
						use_alpha = false,
						on_notify = function(self)
							controls[k].value = {self.rgba.red, self.rgba.green, self.rgba.blue }
							queue_render()
						end
					}
				}
				controls[k].widget = widget
			end
			vbox_settings:pack_end(controls[k].widget, false, false, 5)
		elseif v == "bool" then
			if not controls[k] then
				controls[k] = { value = false }
				widget = Gtk.CheckButton {
					active = controls[k].value,
					label = k,
					on_notify = function(self)
						controls[k].value = self.active
						queue_render()
					end
				}
				controls[k].widget = widget
				widget:set_active(controls[k].value)
			end
			vbox_settings:pack_end(controls[k].widget, false, false, 5)
		elseif v == "sampler2D" then
			if not controls[k] then
				local t = 1;
				while texture_units[t] == true do
					t = t + 1
				end
				texture_units[t] = true
				controls[k] = { value = nil, texunit = t }
				local widget = Gtk.Expander {
					label = k,
					expanded = true,
					Gtk.FileChooserButton {
						title = k,
						action = "OPEN",
						on_selection_changed = function(chooser)
							local filename = chooser:get_filename()
							local pbuf,err = GdkPixbuf.Pixbuf.new_from_file(filename)
							if pbuf then
								controls[k].value = pbuf
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
						end,
					}
				}
				controls[k].widget = widget
			end
			vbox_settings:pack_end(controls[k].widget, false, false, 5)
		end
		if controls[k] then
			controls[k].datatype = v
		end
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
		scene = (loadfile(lua_name))()
		b2l_gl.parse_scene(scene, bin_name)
		update_shaders()
	end
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

function reload_fs()
	local filename = fs_chooser:get_filename()
	if filename then
		local fs_text_next, err = GLib.file_get_contents(filename)
		if fs_text_next then
			fs_text = fs_text_next
		end
	end
end

fs_chooser = Gtk.FileChooserButton {
		title = "Fragment shader",
		action = "OPEN",
		filter = frag_glsl_filter,
		on_selection_changed = function(chooser)
			reload_fs()
			update_shaders()
		end,
	}

function reload_vs()
	local filename = vs_chooser:get_filename()
	if filename then
		local vs_text_next, err = GLib.file_get_contents(filename)
		if vs_text_next then
			vs_text = vs_text_next
		end
	end
end

vs_chooser = Gtk.FileChooserButton {
	title = "Vertex shader",
	action = "OPEN",
	filter = vert_glsl_filter,
	on_selection_changed = function(chooser)
		reload_vs()
		update_shaders()
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
							local chooser = Gtk.FileChooserDialog {
								title = "Open Brt file",
								parent = window,
								action = 'OPEN',
								on_response = function(self, id, data)
									self:hide()
								end,
							}
							chooser:add_button('Open', Gtk.ResponseType.ACCEPT)
							chooser:add_button('Cancel', Gtk.ResponseType.CANCEL)
							chooser:add_filter(b2l_filter)
							local res = chooser:run()
							if res == Gtk.ResponseType.ACCEPT then
								local filename = chooser:get_filename()
								load_b2l_file(filename)
								b2l_file_button:set_filename(filename)
							end
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
				icon_name = "view-refresh",
				on_clicked = function()
					reload_fs()
					reload_vs()
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
				Gtk.Button {
					label = "Edit",
					on_clicked = function()
						GLib.spawn_async(nil,
							{ editor, vs_chooser:get_filename() },
							nil,
							GLib.SpawnFlags {
								'SEARCH_PATH'
							},
							nil)
					end,
				},
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
				Gtk.Button {
					label = "Edit",
					on_clicked = function()
						GLib.spawn_async(nil,
							{ editor, fs_chooser:get_filename() },
							nil,
							GLib.SpawnFlags {
								'SEARCH_PATH'
							},
							nil)
					end,
				},
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
