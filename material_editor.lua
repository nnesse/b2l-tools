local capi = require 'material_editor_capi'
local lgi = require 'lgi'
local Gtk = lgi.require('Gtk')
local Gdk = lgi.require('Gdk')
local GdkX11 = lgi.require('GdkX11')
local GObject = lgi.require('GObject')
local GLib = lgi.require('GLib')
local GdkPixbuf = lgi.require('GdkPixbuf')
local pprint = require 'pprint'

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

b2l_data = false
current_scene = false
current_object = false

controls = {}
settings_expanders = {}
settings_grids = {}
materials = {}
frame_start = 0
frame_end = 0
frame_delta = 1
playing_animation = false
shutdown = false

local window_main = Gtk.Window {
   title = 'B2L Material Editor',
   on_destroy = function()
	   shutdown = true
   end,
   width_request = 250,
   on_realize = function (window)
	   capi.create_glwin(window:get_window():get_xid())
   end,
}

vbox_settings = Gtk.VBox {
	hexpand = true
}

function queue_render()
	capi:need_redraw()
end

function setting_changed()
	save_toolbutton.sensitive = true
end

function update_controls(uniforms)
	if not b2l_data then
		return
	end
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

	--Remove references to controls this shader doesn't need
	for k, v in pairs(controls) do
		if not uniforms[k] then
			controls[k].widget = nil
		end
	end

	-- Remove all expanders
	for k, v in pairs(settings_expanders) do
		vbox_settings:remove(v)
	end

	settings_grids = {}
	settings_expanders = {}

	local grids_pos = {}

	for i, k in ipairs(uniforms) do
		local datatype = uniforms[k].datatype
		local tag = uniforms[k].tag
		if not tag then
			tag = "Misc"
		end
		local id = k
		if not active_material.params[k] then
			active_material.params[k] = {}
		end

		if active_material.params[k].datatype ~= datatype then
			active_material.params[k].datatype = datatype
			active_material.params[k].value = nil
		end

		active_material.params[k].tag = tag

		if not controls[k] then
			controls[k] = {datatype = v}
		end

		controls[k].tag = tag

		local value = active_material.params[k].value
		if datatype == "float" then
			if not value then
				value = 0.5
			end
			active_material.params[k].value = value
			local widget = Gtk.Scrollbar {
				orientation = "HORIZONTAL",
				adjustment = Gtk.Adjustment {
					lower = 0,
					upper = 1,
				},
				hexpand = true,
				on_value_changed = function(self)
					if active_material.params[k].value ~= self:get_value() then
						setting_changed()
					end
					active_material.params[k].value = self:get_value()
					queue_render()
				end
			}
			controls[k].widget = widget
			controls[k].widget:set_value(value)
		elseif datatype == "vec3" then
			if not value then
				value = {1, 1, 1}
			end
			active_material.params[k].value = value
			local widget = Gtk.ColorButton {
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
			controls[k].widget = widget
			controls[k].widget:set_rgba(Gdk.RGBA {red = value[1], green = value[2], blue = value[3], alpha = 1})
		elseif datatype == "bool" then
			if value == nil then
				value = false
			end
			active_material.params[k].value = value
			controls[k] = {}
			local widget = Gtk.CheckButton {
				label = "",
				on_toggled = function(self)
					if active_material.params[k].value ~= self.active then
						setting_changed()
					end
					active_material.params[k].value = self.active
					queue_render()
				end
			}
			controls[k].widget = widget
			controls[k].widget:set_active(value)
		elseif datatype == "sampler2D" then
			if value ~= nil then
				active_material.params[k].value = value
			end
			controls[k] = { }
			local widget = Gtk.FileChooserButton {
				title = id,
				action = "OPEN",
				on_selection_changed = function(chooser)
					local abs_filename = chooser:get_filename()
					local filename = b2l_relative_path(chooser:get_filename())
					if filename and active_material.params[k].value ~= filename then
						setting_changed()
					end
					if filename then
						local pbuf,err = GdkPixbuf.Pixbuf.new_from_file(abs_filename)
						if pbuf then
							active_material.params[k].value = filename
							active_material.params[k]._pbuf = pbuf
							active_material.params[k]._texture = nil
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
			controls[k].widget = widget
			if value ~= nil then
				controls[k].widget:set_filename(b2l_absolute_path(value))
			end
		end

		if controls[k].widget then
			local grid = settings_grids[tag]
			if not grid then
				grid = Gtk.Grid {
					row_spacing = 5,
					margin_start = 30,
				}
				local expander = Gtk.Expander {
					label = tag,
					expanded = true,
					grid
				}
				vbox_settings:pack_end(expander, false, false, 5)
				settings_grids[tag] = grid
				settings_expanders[tag] = expander
				grids_pos[tag] = 0
			end
			controls[k].widget.margin_start = 30
			grid:attach(Gtk.Label { label = k, xalign = 0 } , 0, grids_pos[tag], 1, 1)
			grid:attach(controls[k].widget, 1, grids_pos[tag], 1, 1)
			grids_pos[tag] = grids_pos[tag] + 1
		end

	end
	vbox_settings:show_all()
	queue_render()
end

function b2l_dir()
	return capi.directory_name(b2l_filename)
end

function b2l_relative_path(file)
	return capi.make_path_relative(b2l_dir(), file)
end

function b2l_absolute_path(file)
	return b2l_dir() .. file
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

scenes_store = Gtk.ListStore.new {
	[1] = GObject.Type.STRING
}

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

uv_layer_store = Gtk.ListStore.new {
	[1] = GObject.Type.STRING,
}

function load_b2l_file(filename)
	local lua_name = filename

	if lua_name then
		local bin_name = lua_name .. ".bin"
		local mat_name = lua_name .. ".mat"
		b2l_data = (loadfile(lua_name))()

		capi.set_b2l_file(bin_name)

		local material_fn = loadfile(mat_name)
		if material_fn then
			materials = material_fn()
		else
			materials = {}
		end

		for k, v in pairs(materials) do
			if v.shaders.fs_filename then
				local abs_filename = b2l_absolute_path(v.shaders.fs_filename)
				local text, err = GLib.file_get_contents(abs_filename)
				if text then
					v.shaders['_fs_text_org'] = text
					v.shaders['_fs_text'] = capi.filter_shader_text(text)
				end
			end
			if v.shaders.vs_filename then
				local abs_filename = b2l_absolute_path(v.shaders.vs_filename)
				local text, err = GLib.file_get_contents(abs_filename)
				if text then
					v.shaders['_vs_text_org'] = text
					v.shaders['_vs_text'] = capi.filter_shader_text(text)
				end
			end
		end

		scenes_store:clear()
		for k, v in pairs(b2l_data.scenes) do
			scenes_store:append {
				[1] = k
			}
		end
		scene_combo:set_active_iter(scenes_store:get_iter_first())
		Gtk.main_iteration_do(false)
		save_toolbutton.sensitive = false
	end
end

b2l_file_button = Gtk.FileChooserButton {
	title = "BRT File",
	action = "OPEN",
	filter = b2l_filter,
	hexpand = true,
	on_selection_changed = function(chooser)
		b2l_filename = chooser:get_filename()
		load_b2l_file(b2l_filename)
	end,
}

if b2l_filename then
	b2l_file_button:set_filename(b2l_filename)
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
			local abs_filename = chooser:get_filename()
			local filename = b2l_relative_path(chooser:get_filename())
			if filename and active_material.shaders['fs_filename'] ~= filename then
				setting_changed()
			end
			if filename then
				local text, err = GLib.file_get_contents(abs_filename)
				if text then
					active_material.shaders['fs_filename'] = filename
					active_material.shaders['_fs_text_org'] = text
					active_material.shaders['_fs_text'] = capi.filter_shader_text(text)
					local fs_text = active_material.shaders['_fs_text_org']
					local vs_text = active_material.shaders['_vs_text_org']
					if fs_text and vs_text then
						local uniforms = capi.get_shader_uniforms(vs_text, fs_text)
						if uniforms then
							update_controls(uniforms)
						end
					end
				end
				fs_edit_button.sensitive = true
			else
				fs_edit_button.sensitive = false
			end

		end,
	}


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
		local abs_filename = chooser:get_filename()
		local filename = b2l_relative_path(chooser:get_filename())
		if filename then
			local text, err = GLib.file_get_contents(abs_filename)
			if text then
				setting_changed()
				active_material.shaders['vs_filename'] = filename
				active_material.shaders['_vs_text_org'] = text
				active_material.shaders['_vs_text'] = capi.filter_shader_text(text)
				local fs_text = active_material.shaders['_fs_text_org']
				local vs_text = active_material.shaders['_vs_text_org']
				if fs_text and vs_text then
					local uniforms = capi.get_shader_uniforms(vs_text, fs_text)
					if uniforms then
						update_controls(uniforms)
					end
				end
			end
			vs_edit_button.sensitive = true
		else
			vs_edit_button.sensitive = false
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
		b2l_file_button:set_filename(chooser:get_filename())
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
		str = str .. "\n"
		GLib.file_set_contents(b2l_filename .. ".mat", str)
		button.sensitive = false
	end,
}

uv_layer_combo = Gtk.ComboBox {
	id = "UV layer",
	model = uv_layer_store,
	active = 0,
	cells = {
		{
			Gtk.CellRendererText(),
			{ text = 1 }
		}
	},
	on_changed = function(combo)
		local active = combo:get_active_iter()
		if not active then
			return
		end
		local row = combo.model[active]
		if active_material.uv_layer ~= row[1] then
			active_material.uv_layer = row[1]
			setting_changed()
			queue_render()
		end
	end
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
		local active = combo:get_active_iter()
		if not active then
			return
		end
		local row = objects_store[active]
		local object_name = row[1]
		current_object = object_name

		local obj = b2l_data.objects[current_object]
		local mesh = b2l_data.meshes[obj.data]

		uv_layer_store:clear()
		for k, v in pairs(mesh.uv_layers) do
			uv_layer_store:append {
				[1] = k,
			}
		end

		materials_store:clear()
		for i, v in ipairs(mesh.submeshes) do
			materials_store:append {
				[1] = v.material_name
			}
		end
		material_combo:set_active_iter(materials_store:get_iter_first())

		actions_store:clear()
		local armature_name = b2l_data.objects[object_name].armature_deform
		local scene = b2l_data.scenes[current_scene]
		if armature_name then
			local armature_obj = b2l_data.objects[armature_name]
			if armature_obj.nla_tracks then
				for i, track in ipairs(armature_obj.nla_tracks) do
					for j, action in ipairs(track) do
						local frame_start
						local frame_end

						frame_start = action.frame_start - scene.frame_start
						if frame_start < 0 then
							frame_start = 0
						end

						if action.frame_end > scene.frame_end then
							frame_end = scene.frame_end - scene.frame_start
						else
							frame_end = action.frame_end - scene.frame_start
						end

						if frame_start <= frame_end then
							actions_store:append {
								[1] = action.name,
								[2] = frame_start,
								[3] = frame_end - 1
							}
						end
					end
				end
			end
		end
		action_combo:set_active_iter(actions_store:get_iter_first())
		Gtk.main_iteration_do(false)
		queue_render()
	end
}

scene_combo = Gtk.ComboBox {
	id = "Scene",
	model = scenes_store,
	active = 0,
	cells = {
		{
			Gtk.CellRendererText(),
			{ text = 1 }
		}
	},
	on_changed = function (combo)
		local active = combo:get_active_iter()
		if not active then
			return
		end
		local row = scenes_store[active]
		current_scene = row[1]

		objects_store:clear()
		objects = {}
		for k, v in pairs(b2l_data.scenes[current_scene].objects) do
			local object = {}
			objects[k] = object
			obj_data = b2l_data.objects[k]
			if obj_data.nla_tracks then
				local actions = {}
				object.actions = actions
				for i, track in ipairs(obj_data.nla_tracks) do
					for j, action in ipairs(track) do
						actions[action.name] = action
					end
				end
			end
			if obj_data.type == 'MESH' then
				objects_store:append {
					[1] = k
				}
			end
		end
		object_combo:set_active_iter(objects_store:get_iter_first())
		Gtk.main_iteration_do(false)

		queue_render()
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
		local active = combo:get_active_iter()
		if not active then
			return
		end
		local row = materials_store[active]
		local material_name = row[1]
		if materials and material_name then
			active_material = materials[material_name]
			if not active_material then
				active_material = { params = {}, shaders = {}}
				materials[material_name] = active_material
			end
			if active_material.shaders['vs_filename'] then
				vs_chooser:set_filename(b2l_absolute_path(active_material.shaders['vs_filename']))
			end
			if active_material.shaders['fs_filename'] then
				fs_chooser:set_filename(b2l_absolute_path(active_material.shaders['fs_filename']))
			end

			iter = uv_layer_store:get_iter_first()
			uv_layer_combo:set_active_iter(iter)
			if active_material.uv_layer then
				while iter do
					local uv_layer_row = uv_layer_store[iter]
					if uv_layer_row[1] == active_material.uv_layer then
						uv_layer_combo:set_active_iter(iter)
					end
					iter = uv_layer_store:next(iter)
				end
			end
			Gtk.main_iteration_do(false)
		end
	end
}

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
		local active = combo:get_active_iter()
		if not active then
			return
		end
		local row = actions_store[active]
		local action_name = row[1]
		frame_start = row[2]
		frame_end = row[3]
		frame_delta = 1
		action_scale.adjustment.lower = 1
		action_scale.adjustment.upper = (frame_end - frame_start) + 1
		action_scale:set_value(1)
	end
}

action_scale = Gtk.Scale {
	adjustment = Gtk.Adjustment {
		lower = 1,
		upper = 1,
		step_increment = 1,
		page_increment = 1,
	},
	digits = 2,
	on_value_changed = function(self)
		if not playing_animation then
			frame_delta = self:get_value() - 1
		end
		queue_render()
	end,
}

function animation_update()
	frame_delta = frame_delta + 0.3333;
	if (frame_start + frame_delta) >= frame_end then
		frame_delta = frame_delta - (frame_end - frame_start)
	end
	action_scale:set_value(frame_delta + 1)
end

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
							shutdown = true
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
					local vs_filaname = active_material.shaders['vs_filename']
					local fs_filename = active_material.shaders['fs_filename']
					if vs_filename then
						local abs_filename = b2l_absolute_path(vs_filename)
						local text, err = GLib.file_get_contents(abs_filename)
						if text then
							active_material.shaders['_vs_text_org'] = text
							active_material.shaders['_vs_text'] = capi.filter_shader_text(text)
						end
					end
					if fs_filename then
						local abs_filename = b2l_absolute_path(fs_filename)
						local text, err = GLib.file_get_contents(abs_filename)
						if text then
							active_material.shaders['_fs_text_org'] = text
							active_material.shaders['_fs_text'] = capi.filter_shader_text(text)
						end
					end

					local fs_text = active_material.shaders['_fs_text_org']
					local vs_text = active_material.shaders['_vs_text_org']
					if fs_text and vs_text then
						local uniforms = capi.get_shader_uniforms(vs_text, fs_text)
						if uniforms then
							update_controls(uniforms)
						end
					end
				end,
			},
		},
		expand = false,
		fill = false
	},
	{
		Gtk.Grid {
			margin_start = 30,
			row_spacing = 3,
			column_spacing = 30,
			{
				Gtk.Label {
					label = "B2L File",
					xalign = 0,
				},
				left_attach = 0,
				top_attach = 0,
			},
			{
				b2l_file_button,
				left_attach = 1,
				top_attach = 0,
				width = 1,
			},
			{
				Gtk.Label {
					label = "Scene",
					xalign = 0,
				},
				left_attach = 0,
				top_attach = 1,
			},
			{
				scene_combo,
				left_attach = 1,
				top_attach = 1,
				width = 1,
			},
			{
				Gtk.Label {
					label = "Object",
					xalign = 0,
				},
				left_attach = 0,
				top_attach = 2,
			},
			{
				object_combo,
				left_attach = 1,
				top_attach = 2,
				width = 1,
			},
			{
				Gtk.Label {
					label = "Material",
					xalign = 0,
				},
				left_attach = 0,
				top_attach = 3,
			},
			{
				material_combo,
				left_attach = 1,
				top_attach = 3,
				width = 1,
			},
			{
				Gtk.Label {
					label = "UV layer",
					xalign = 0,
				},
				left_attach = 0,
				top_attach = 4,
			},
			{
				uv_layer_combo,
				left_attach = 1,
				top_attach = 4,
			},
			{
				Gtk.Label {
					label = "Action",
					xalign = 0,
				},
				left_attach = 0,
				top_attach = 5,
			},
			{
				action_combo,
				left_attach = 1,
				top_attach = 5,
				width = 1,
			},
			{
				Gtk.Label {
					label = "Frame",
					xalign = 0,
				},
				left_attach = 0,
				top_attach = 6,
			},
			{
				Gtk.HBox {
					{
						Gtk.ToolButton {
							icon_name = "media-playback-start",
							on_clicked = function(button)
								if frame_start ~= frame_end then
									if button.icon_name == "media-playback-start" then
										playing_animation = true
										button.icon_name = "media-playback-stop"
									else
										playing_animation = false
										button.icon_name = "media-playback-start"
									end
								end
								queue_render()
							end,
						},
						expand = false
					},
					action_scale,
				},
				left_attach = 1,
				top_attach = 6,
				width = 1,
			},
			{
				Gtk.Label {
					label = "Vertex Shader",
					xalign = 0,
				},
				left_attach = 0,
				top_attach = 7,
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
				top_attach = 7,
				width = 1,
			},
			{
				Gtk.Label {
					label = "Fragment Shader",
					xalign = 0,
				},
				left_attach = 0,
				top_attach = 8,
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
				top_attach = 8,
				width = 1,
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
