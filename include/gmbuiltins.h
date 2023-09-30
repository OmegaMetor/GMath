#pragma once
#include <vector>
#include <string>
std::vector<std::string> stringCollection = {
    "argumVhent",
    "argument0",
    "argument1",
    "argument10",
    "argument11",
    "argument12",
    "argument13",
    "argument14",
    "argument15",
    "argument2",
    "argument3",
    "argument4",
    "argument5",
    "argument6",
    "argument7",
    "argument8",
    "argument9",
    "argument_relative",
    "background_alpha",
    "background_blend",
    "background_color",
    "background_foreground",
    "background_height",
    "background_hspeed",
    "background_htiled",
    "background_index",
    "background_showcolor",
    "background_visible",
    "background_vspeed",
    "background_vtiled",
    "background_width",
    "background_x",
    "background_xscale",
    "background_y",
    "background_yscale",
    "caption_health",
    "caption_lives",
    "caption_score",
    "current_day",
    "current_hour",
    "current_minute",
    "current_month",
    "current_second",
    "current_time",
    "current_weekday",
    "current_year",
    "cursor_sprite",
    "error_last",
    "error_occurred",
    "event_action",
    "event_number",
    "event_object",
    "event_type",
    "fps",
    "game_id",
    "health",
    "instance_count",
    "instance_id",
    "keyboard_key",
    "keyboard_lastchar",
    "keyboard_lastkey",
    "keyboard_string",
    "lives",
    "mouse_button",
    "mouse_lastbutton",
    "mouse_x",
    "mouse_y",
    "room",
    "room_caption",
    "room_first",
    "room_height",
    "room_last",
    "room_persistent",
    "room_speed",
    "room_width",
    "score",
    "secure_mode",
    "show_health",
    "show_lives",
    "show_score",
    "temp_directory",
    "transition_kind",
    "transition_steps",
    "transition_time",
    "view_angle",
    "view_current",
    "view_enabled",
    "view_hborder",
    "view_hport",
    "view_hspeed",
    "view_hview",
    "view_object",
    "view_vborder",
    "view_visible",
    "view_vspeed",
    "view_wport",
    "view_wview",
    "view_xport",
    "view_xview",
    "view_yport",
    "view_yview",
    "working_directory",
    "alarm",
    "bbox_bottom",
    "bbox_left",
    "bbox_right",
    "bbox_top",
    "depth",
    "direction",
    "friction",
    "gravity",
    "gravity_direction",
    "hspeed",
    "id",
    "image_alpha",
    "image_angle",
    "image_blend",
    "image_index",
    "image_number",
    "image_single",
    "image_speed",
    "image_xscale",
    "image_yscale",
    "mask_index",
    "object_index",
    "path_endaction",
    "path_index",
    "path_orientation",
    "path_position",
    "path_positionprevious",
    "path_scale",
    "path_speed",
    "persistent",
    "solid",
    "speed",
    "sprite_height",
    "sprite_index",
    "sprite_width",
    "sprite_xoffset",
    "sprite_yoffset",
    "timeline_index",
    "timeline_position",
    "timeline_speed",
    "visible",
    "vspeed",
    "x",
    "xprevious",
    "xstart",
    "y",
    "yprevious",
    "ystart"
};

bool isBuiltin(std::string string)
{
    auto it = std::find(stringCollection.begin(), stringCollection.end(), string);
    return it != stringCollection.end();
}