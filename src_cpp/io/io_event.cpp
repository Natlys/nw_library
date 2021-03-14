#include <nwl_pch.hpp>
#include "io_event.h"
namespace NW
{
	a_event::a_event(event_types event_type) : type(event_type), is_handled(false) { }

	mouse_event::mouse_event(event_types event_type, f64 coord_or_scroll_x, f64 coord_or_scroll_y) :
		a_event(event_type), val_x(coord_or_scroll_x), val_y(coord_or_scroll_y) {}
	mouse_event::mouse_event(event_types event_type, mouse_codes button_code,
		f64 coord_or_scroll_x, f64 coord_or_scroll_y) :
		a_event(event_type), code(button_code), val_x(coord_or_scroll_x), val_y(coord_or_scroll_y) {}

	keyboard_event::keyboard_event(event_types event_type, keyboard_codes code_or_char) :
		a_event(event_type), code(code_or_char), nof_repeats(0) { }
	keyboard_event::keyboard_event(event_types event_type, keyboard_codes code_or_char, ui32 repeat_count) :
		a_event(event_type), code(code_or_char), nof_repeats(repeat_count) { }

	window_event::window_event(event_types event_type) : a_event(event_type) {}
	window_event::window_event(event_types event_type, si32 width_or_x, si32 height_or_y) :
		a_event(event_type), val_x(width_or_x), val_y(height_or_y) {}
}