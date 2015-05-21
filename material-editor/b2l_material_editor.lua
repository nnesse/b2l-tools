local b2l_gl = require 'b2l_material_editor'
local lgi = require 'lgi'
local Gtk = lgi.require('Gtk')
local Gdk = lgi.require('Gdk')
local GObject = lgi.require('GObject')
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
		local datatype = uniforms[k]
		if not active_material.params[k] then
			active_material.params[k] = {}
		end

		if active_material.params[k].datatype ~= datatype then
			active_material.params[k].datatype = datatype
			active_material.params[k].value = nil
		end

		if not controls[k] then
			controls[k] = {datatype = v}
		end

		local value = active_material.params[k].value
		if datatype == "float" then
			if not value then
				value = 0.5
			end
			active_material.params[k].value = value
			if not controls[k].widget then
				local control = Gtk.Scrollbar {
					orientation = "HORIZONTAL",
					adjustment = Gtk.Adjustment {
						lower = 0,
						upper = 1,
					},
					on_value_changed = function(self)
						if active_material.params[k].value ~= self:get_value() then
							setting_changed()
						end
						active_material.params[k].value = self:get_value()
						queue_render()
					end
				}
				local widget = Gtk.HBox {
					{
						Gtk.Label {
							label = k,
							hexpand = false
						},
						expand = false,
						fill = false
					},
					{
						control,
						expand = true,
						fill = true
					},
					spacing = 10,
				}
				controls[k].widget = widget
				controls[k].control = control
			end
			controls[k].control:set_value(value)
			vbox_settings:pack_end(controls[k].widget, false, false, 5)
		elseif datatype == "vec3" then
			if not value then
				value = {1, 1, 1}
			end
			active_material.params[k].value = value
			if not controls[k].widget then
				local control = Gtk.ColorButton {
					use_alpha = false,
					on_color_set = function(self)
						local value = {self.rgba.red, self.rgba.green, self.rgba.blue }
						if (not active_material.params[k].value) or
							value[1] ~= active_material.params[k].value[1] or
							value[2] ~= active_material.params[k].value[2] or
							value[3] ~= active_material.params[k].value[3] then
							setting_changed()
						end
						active_material.params[k].value = {self.rgba.red, self.rgba.green, self.rgba.blue }
						queue_render()
					end
				}
				local widget = Gtk.HBox {
					{
						Gtk.Label {
							label = k,
							hexpand = false
						},
						expand = false,
						fill = false
					},
					{
						control,
						expand = true,
						fill = true
					},
					spacing = 10,
				}
				controls[k].widget = widget
				controls[k].control = control
			end
			controls[k].control:set_rgba(Gdk.RGBA {red = value[1], green = value[2], blue = value[3], alpha = 1})
			vbox_settings:pack_end(controls[k].widget, false, false, 5)
		elseif datatype == "bool" then
			if value == nil then
				value = false
			end
			active_material.params[k].value = value
			if not controls[k].widget then
				controls[k] = {}
				local widget = Gtk.CheckButton {
					label = k,
					on_toggled = function(self)
						if active_material.params[k].value ~= self.active then
							setting_changed()
						end
						active_material.params[k].value = self.active
						queue_render()
					end
				}
				controls[k].widget = widget
			end
			controls[k].widget:set_active(value)
			vbox_settings:pack_end(controls[k].widget, false, false, 5)
		elseif datatype == "sampler2D" then
			if value ~= nil then
				active_material.params[k].value = value
			end
			if not controls[k].widget then
				local t = 1;
				while texture_units[t] == true do
					t = t + 1
				end
				texture_units[t] = true
				controls[k] = { texunit= t }
				local control = Gtk.FileChooserButton {
					title = k,
					action = "OPEN",
					on_selection_changed = function(chooser)
						local filename = chooser:get_filename()
						if active_material.params[k].value ~= filename then
							setting_changed()
						end
						if filename then
							local pbuf,err = GdkPixbuf.Pixbuf.new_from_file(filename)
							if pbuf then
								active_material.params[k].value = filename
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
				local widget = Gtk.HBox {
					{
						Gtk.Label {
							label = k,
							hexpand = false
						},
						expand = false,
						fill = false
					},
					{
						control,
						expand = true,
						fill = true
					},
					spacing = 10,
				}
				controls[k].widget = widget
				controls[k].control = control
			end
			if value ~= nil then
				controls[k].control:set_filename(value)
			end
			vbox_settings:pack_end(controls[k].widget, false, false, 5)
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

objects_store = Gtk.ListStore.new {
	[1] = GObject.Type.STRING
}

materials_store = Gtk.ListStore.new {
	[1] = GObject.Type.STRING
}

actions_store = Gtk.ListStore.new {
	[1] = GObject.Type.STRING,
	[2] = GObject.Type.INT,
	[3] = GObject.Type.INT,
}

function load_b2l_file(filename)
	local lua_name = filename

	if lua_name then
		local bin_name = lua_name .. ".bin"
		local mat_name = lua_name .. ".mat"
		scene = (loadfile(lua_name))()

		objects_store:clear()
		materials_store:clear()
		actions_store:clear()

		objects = {}
		for k, v in pairs(scene.scene.objects) do
			local object = {}
			objects[k] = object
			if v.nla_tracks then
				local actions = {}
				object.actions = actions
				for i, track in ipairs(v.nla_tracks) do
					for j, action in ipairs(track) do
						actions[action.name] = action
					end
				end
			end
			if v.type == 'MESH' then
				objects_store:append {
					[1] = k
				}
			end
		end

		for i, v in ipairs(scene.materials) do
			materials_store:append {
				[1] = v
			}
		end

		b2l_gl.parse_scene(scene, bin_name)

		local material_fn = loadfile(mat_name)
		if material_fn then
			materials = material_fn()
		else
			materials = {}
		end

		save_toolbutton.sensitive = false
		object_combo:set_active_iter(objects_store:get_iter_first())
		material_combo:set_active_iter(materials_store:get_iter_first())
	end
end

b2l_file_button = Gtk.FileChooserButton {
	title = "BRT File",
	action = "OPEN",
	filter = b2l_filter,
	hexpand = true,
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

fs_chooser = Gtk.FileChooserButton {
		title = "Fragment shader",
		action = "OPEN",
		filter = frag_glsl_filter,
		on_selection_changed = function(chooser)
			local filename = chooser:get_filename()
			if filename and active_material.shaders['fs_filename'] ~= filename then
				setting_changed()
			end
			reload_fs(filename)
			update_shaders()
			if filename then
				fs_edit_button.sensitive = true
			else
				fs_edit_button.sensitive = false
			end
			if filename then
				active_material.shaders['fs_filename'] = filename
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

vs_chooser = Gtk.FileChooserButton {
	title = "Vertex shader",
	action = "OPEN",
	filter = vert_glsl_filter,
	on_selection_changed = function(chooser)
		local filename = chooser:get_filename()
		if filename and filename ~= active_material.shaders['vs_filename'] then
			setting_changed()
		end
		reload_vs(filename)
		update_shaders()
		if filename then
			vs_edit_button.sensitive = true
		else
			vs_edit_button.sensitive = false
		end
		if filename then
			active_material.shaders.vs_filename = filename
		end
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
		str = "return "
		local printer = function(s)
			str = str .. s
		end
		pprint.pformat(materials, {}, printer)
		GLib.file_set_contents(b2l_file_button:get_filename() .. ".mat", str)
		button.sensitive = false
	end,
}

object_combo = Gtk.ComboBox {
	id = "Object",
	model = objects_store,
	active = 0,
	cells = {
		{
			Gtk.CellRendererText(),
			{ text = 1 }
		}
	},
	on_changed = function (combo)
		local row = objects_store[combo:get_active_iter()]
		local object_name = row[1]
		b2l_gl.set_object(object_name)

		actions_store:clear()

		local armature_name = scene.scene.objects[object_name].armature_deform
		if armature_name then
			local armature_obj = scene.scene.objects[armature_name]
			if armature_obj.nla_tracks then
				for i, track in ipairs(armature_obj.nla_tracks) do
					for j, action in ipairs(track) do
						actions_store:append {
							[1] = action.name,
							[2] = action.frame_start,
							[3] = action.frame_end
						}
					end
				end
			end
		end
		action_combo:set_active_iter(actions_store:get_iter_first())
	end
}

material_combo = Gtk.ComboBox {
	id = "Material",
	model = materials_store,
	active = 0,
	cells = {
		{
			Gtk.CellRendererText(),
			{ text = 1 }
		}
	},
	on_changed = function (combo)
		local row = materials_store[combo:get_active_iter()]
		local material_name = row[1]
		if materials and material_name then
			active_material = materials[material_name]
			if not active_material then
				active_material = { params = {}, shaders = {}}
				materials[material_name] = active_material
			end
			if active_material.shaders['vs_filename'] then
				vs_chooser:set_filename(active_material.shaders['vs_filename'])
			end
			if active_material.shaders['fs_filename'] then
				fs_chooser:set_filename(active_material.shaders['fs_filename'])
			end
		end
	end
}

frame_start = 1
frame_delta = 1
frame_end = 1

action_combo = Gtk.ComboBox {
	id = "Action",
	model = actions_store,
	active = 0,
	cells = {
		{
			Gtk.CellRendererText(),
			{ text = 1 }
		}
	},
	on_changed = function (combo)
		local row = actions_store[combo:get_active_iter()]
		local action_name = row[1]
		frame_start = row[2]
		frame_end = row[3]
		frame_delta = 1
		action_scale.adjustment.lower = 1
		action_scale.adjustment.upper = (frame_end - frame_start)
		action_scale:set_value(1)
	end
}

action_scale = Gtk.Scale {
	adjustment = Gtk.Adjustment {
		lower = 1,
		upper = 100,
		step_increment = 1,
		page_increment = 1,
	},
	digits = 0,
	on_value_changed = function(self)
		frame_delta = self:get_value()
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
		Gtk.Grid {
			column_spacing = 20,
			{
				Gtk.Label {
					label = "B2L File"
				},
				left_attach = 0,
				top_attach = 0,
			},
			{
				b2l_file_button,
				left_attach = 1,
				top_attach = 0,
				width = 2,
			},
			{
				Gtk.Label {
					label = "Object"
				},
				left_attach = 0,
				top_attach = 1,
			},
			{
				object_combo,
				left_attach = 1,
				top_attach = 1,
				width = 2,
			},
			{
				Gtk.Label {
					label = "Material"
				},
				left_attach = 0,
				top_attach = 2,
			},
			{
				material_combo,
				left_attach = 1,
				top_attach = 2,
				width = 2,
			},
			{
				Gtk.Label {
					label = "Action"
				},
				left_attach = 0,
				top_attach = 3,
			},
			{
				action_combo,
				left_attach = 1,
				top_attach = 3,
				width = 2,
			},
			{
				Gtk.Label {
					label = "Frame"
				},
				left_attach = 0,
				top_attach = 4,
			},
			{
				action_scale,
				left_attach = 1,
				top_attach = 4,
				width = 2,
			},
			{
				Gtk.Label {
					label = "Vertex Shader"
				},
				left_attach = 0,
				top_attach = 5,
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
				left_attach = 1,
				top_attach = 5,
				width = 2,
			},
			{
				Gtk.Label {
					label = "Fragment Shader"
				},
				left_attach = 0,
				top_attach = 6,
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
				left_attach = 1,
				top_attach = 6,
				width = 2,
			},
		},
		expand = false,
		fill = false
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
