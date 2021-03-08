#ifndef NWL_EVENT_H
#define NWL_EVENT_H
#include <nwl_core.hpp>
#include "io_switch.h"
namespace NWL
{
	/// abstract event struct
	/// interface:
	/// -> create in the event_proc callback function -> set the event data
	/// -> dispatch to different listeners;
	/// description:
	struct NWL_API a_event
	{
	public:
		bit is_handled = false;
		event_types type = EVT_DEFAULT;
	public:
		a_event(event_types event_type);
		// --predicates
		inline bit is_in_category(event_categories event_category) { return (type & event_category); }
	};
	using event_callback = std::function<void(a_event&)>;
}
namespace NWL
{
	/// cursor_event struct
	struct NWL_API cursor_event : public a_event
	{
	public:
		cursor_codes code = CRS_0;
		f64 val_x = 0.0, val_y = 0.0;
	public:
		// mouse_move_event or mouse_scroll_event
		cursor_event(event_types event_type, f64 coord_or_scroll_x, f64 coord_or_scroll_y);
		// mouse_buttevent_proc
		cursor_event(event_types event_type, cursor_codes button_code,
			f64 coord_or_scroll_x = 0.0, f64 coord_or_scroll_y = 0.0);
	};
	/// keyboard_event struct
	struct NWL_API keyboard_event : public a_event
	{
	public:
		union {
			keyboard_codes code = KC_SPACE;
			union { schar nrow; wchar wide; } character;
		};
		ui32 nof_repeats = 0;
	public:
		// release_key_event
		keyboard_event(event_types event_type, keyboard_codes code_or_char);
		// press_key_event
		keyboard_event(event_types event_type, keyboard_codes code_or_char, ui32 repeat_count);
	};
	/// window_event struct
	struct NWL_API window_event : public a_event
	{
	public:
		si32 val_x = 0, val_y = 0;
	public:
		// window_close_event or window_focus_event
		window_event(event_types event_type);
		// window_resize_event
		window_event(event_types event_type, si32 width_or_x, si32 height_or_y);
	};
}
#endif	//NW_AEVENT_H