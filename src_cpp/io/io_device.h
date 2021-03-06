#ifndef NWL_IO_DEVICE_H
#define NWL_IO_DEVICE_H
#include <nwl_core.hpp>
#include "io_switch.h"
#include "io_event.h"
namespace NWL
{
	/// keyboard_button struct
	struct NWL_API keyboard_button
	{
	public:
		button_states state = BS_FREE;
		ui16 nof_repeats = 0;
		union { schar nrow = ' '; wchar wide; } character;
	};
	/// keyboard_state class
	class NWL_API keyboard_state
	{
	public:
		keyboard_state();
		// --getters
		inline bit get_free(key_codes code) const		{ return m_buttons[code].state == BS_FREE; }
		inline bit get_held(key_codes code) const		{ return m_buttons[code].state == BS_HELD; }
		inline ui16 get_repeats(key_codes code) const	{ return m_buttons[code].nof_repeats; }
		inline keyboard_modes get_mode() const			{ return m_mode; }
		// --operators
		inline keyboard_button& operator[](key_codes code)	{ return m_buttons[code]; }
		// --core_methods
		void on_event(keyboard_event& kbd_evt);
	private:
		keyboard_button m_buttons[KC_COUNT];
		keyboard_modes m_mode = KBD_DEFAULT;
	};
}
namespace NWL
{
	/// cursor_button struct
	struct NWL_API cursor_button
	{
	public:
		button_states state = BS_FREE;
		f32 free_x = 0.0, free_y = 0.0;
		f32 free_delta_x = 0.0, free_delta_y = 0.0;
		f32 held_x = 0.0, held_y = 0.0;
		f32 held_delta_x = 0.0, held_delta_y = 0.0;
	};
	/// cursor_state class
	class NWL_API cursor_state
	{
	public:
		cursor_state();
		// --getters
		inline bit get_free(cursor_codes code) const		{ return m_buttons[code].state == BS_FREE; }
		inline f64 get_free_x(cursor_codes code) const		{ return m_buttons[code].free_x; }
		inline f64 get_free_y(cursor_codes code) const		{ return m_buttons[code].free_y; }
		inline f64 get_free_delta_x(cursor_codes code) const{ return m_buttons[code].free_delta_x; }
		inline f64 get_free_delta_y(cursor_codes code) const{ return m_buttons[code].free_delta_y; }
		inline bit get_held(cursor_codes code) const		{ return m_buttons[code].state == BS_HELD; }
		inline f64 get_held_x(cursor_codes code) const		{ return m_buttons[code].held_x; }
		inline f64 get_held_y(cursor_codes code) const		{ return m_buttons[code].held_y; }
		inline f64 get_held_delta_x(cursor_codes code) const{ return m_buttons[code].held_delta_x; }
		inline f64 get_held_delta_y(cursor_codes code) const{ return m_buttons[code].held_delta_y; }
		inline f64 get_move_x() const						{ return m_move_x; }
		inline f64 get_move_y() const						{ return m_move_y; }
		inline f64 get_move_delta_x() const					{ return m_move_delta_x; }
		inline f64 get_move_delta_y() const					{ return m_move_delta_y; }
		inline f64 get_scroll_delta_x() const				{ return m_scroll_delta_x; }
		inline f64 get_scroll_delta_y() const				{ return m_scroll_delta_y; }
		inline cursor_modes get_mode() const				{ return m_mode; }
		// --setters
		void set_mode(cursor_modes crs_mode);
		// --operators
		inline cursor_button& operator[](cursor_codes code) { return m_buttons[code]; }
		// --core_methods
		void on_event(cursor_event& crs_evt);
	private:
		cursor_button m_buttons[CRS_COUNT];
		cursor_modes m_mode = CRS_DEFAULT;
		f64 m_move_x = 0.0, m_move_y = 0.0;
		f64 m_move_delta_x = 0.0, m_move_delta_y = 0.0;
		f64 m_scroll_delta_x = 0.0, m_scroll_delta_y = 0.0;
	};
}

#endif	// NWL_IO_DEVICE_H