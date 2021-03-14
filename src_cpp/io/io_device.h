#ifndef NW_IO_DEVICE_H
#define NW_IO_DEVICE_H
#include <nwl_core.hpp>
#include "io_switch.h"
#include "io_event.h"
#if (defined NW_OS)
namespace NW
{
	/// keyboard_button struct
	struct NW_API keyboard_button
	{
	public:
		button_states state = BS_FREE;
		ui16 nof_repeats = 0;
		union { schar nrow = ' '; wchar wide; } character;
	};
	/// keyboard_state class
	class NW_API keyboard_state
	{
	public:
		using evt = keyboard_event;
		using btn = keyboard_button;
		using codes = keyboard_codes;
	public:
		keyboard_state();
		// --getters
		inline ui16 get_repeats(codes code) const		{ return m_buttons[code].nof_repeats; }
		// --predicates
		inline bit is_free(codes code) const			{ return m_buttons[code].state == BS_FREE; }
		inline bit is_held(codes code) const			{ return m_buttons[code].state == BS_HELD; }
		inline bit is_released(codes code) const		{ return m_buttons[code].state == BS_RELEASED; }
		inline bit is_pressed(codes code) const			{ return m_buttons[code].state == BS_PRESSED; }
		// --operators
		inline btn& operator[](codes code)				{ return m_buttons[code]; }
		inline const btn& operator[](codes code) const	{ return m_buttons[code]; }
		// --core_methods
		void update();
		void event_proc(evt& kbd_evt);
	private:
		keyboard_button m_buttons[KBC_COUNT];
	};
}
namespace NW
{
	/// mouse_button struct
	struct NW_API mouse_button
	{
	public:
		button_states state = BS_FREE;
		f32 free_coord_x = 0.0, free_coord_y = 0.0;
		f32 free_delta_x = 0.0, free_delta_y = 0.0;
		f32 held_coord_x = 0.0, held_coord_y = 0.0;
		f32 held_delta_x = 0.0, held_delta_y = 0.0;
	};
	/// mouse_state class
	class NW_API mouse_state
	{
	public:
		using evt = mouse_event;
		using btn = mouse_button;
		using codes = mouse_codes;
	public:
		mouse_state();
		// --getters
		inline f64 get_free_coord_x(codes code) const	{ return m_buttons[code].free_coord_x; }
		inline f64 get_free_coord_y(codes code) const	{ return m_buttons[code].free_coord_y; }
		inline f64 get_free_delta_x(codes code) const	{ return m_buttons[code].free_delta_x; }
		inline f64 get_free_delta_y(codes code) const	{ return m_buttons[code].free_delta_y; }
		inline f64 get_held_coord_x(codes code) const	{ return m_buttons[code].held_coord_x; }
		inline f64 get_held_coord_y(codes code) const	{ return m_buttons[code].held_coord_y; }
		inline f64 get_held_delta_x(codes code) const	{ return m_buttons[code].held_delta_x; }
		inline f64 get_held_delta_y(codes code) const	{ return m_buttons[code].held_delta_y; }
		inline f64 get_move_coord_x() const				{ return m_move_coord_x; }
		inline f64 get_move_coord_y() const				{ return m_move_coord_y; }
		inline f64 get_move_delta_x() const				{ return m_move_delta_x; }
		inline f64 get_move_delta_y() const				{ return m_move_delta_y; }
		inline f64 get_scroll_delta_x() const			{ return m_scroll_delta_x; }
		inline f64 get_scroll_delta_y() const			{ return m_scroll_delta_y; }
		// --setters
		void set_cursor_enabled(bit enable_cursor);
		// --predicates
		inline bit is_free(codes code) const			{ return m_buttons[code].state == BS_FREE; }
		inline bit is_held(codes code) const			{ return m_buttons[code].state == BS_HELD; }
		inline bit is_released(codes code) const		{ return m_buttons[code].state == BS_RELEASED; }
		inline bit is_pressed(codes code) const			{ return m_buttons[code].state == BS_PRESSED; }
		inline bit is_cursor_enabled() const			{ return m_is_cursor_enabled; }
		// --operators
		inline btn& operator[](codes code)				{ return m_buttons[code]; }
		inline const btn& operator[](codes code)const	{ return m_buttons[code]; }
		// --core_methods
		void update();
		void event_proc(evt& ms_evt);
	private:
		btn m_buttons[MSC_COUNT];
		f64 m_move_coord_x, m_move_coord_y;
		f64 m_move_delta_x, m_move_delta_y;
		f64 m_scroll_delta_x, m_scroll_delta_y;
		bit m_is_cursor_enabled;
	};
}
#endif	// NW_OS
#endif	// NW_IO_DEVICE_H