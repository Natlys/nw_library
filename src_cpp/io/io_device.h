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
		using evt = keyboard_event;
		using btn = keyboard_button;
		using codes = keyboard_codes;
		using modes = keyboard_modes;
	public:
		keyboard_state();
		// --getters
		inline bit get_free(codes code) const			{ return m_buttons[code].state == BS_FREE; }
		inline bit get_held(codes code) const			{ return m_buttons[code].state == BS_HELD; }
		inline bit get_released(codes code) const		{ return m_buttons[code].state == BS_RELEASED; }
		inline bit get_pressed(codes code) const		{ return m_buttons[code].state == BS_PRESSED; }
		inline ui16 get_repeats(codes code) const		{ return m_buttons[code].nof_repeats; }
		inline modes get_mode() const					{ return m_mode; }
		// --setters
		void set_mode(modes mode);
		// --operators
		inline btn& operator[](codes code)				{ return m_buttons[code]; }
		inline const btn& operator[](codes code) const	{ return m_buttons[code]; }
		// --core_methods
		void update();
		void event_proc(evt& kbd_evt);
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
		using evt = cursor_event;
		using btn = cursor_button;
		using codes = cursor_codes;
		using modes = cursor_modes;
	public:
		cursor_state();
		// --getters
		inline bit get_free(codes code) const			{ return m_buttons[code].state == BS_FREE; }
		inline f64 get_free_x(codes code) const			{ return m_buttons[code].free_x; }
		inline f64 get_free_y(codes code) const			{ return m_buttons[code].free_y; }
		inline f64 get_free_delta_x(codes code) const	{ return m_buttons[code].free_delta_x; }
		inline f64 get_free_delta_y(codes code) const	{ return m_buttons[code].free_delta_y; }
		inline bit get_held(codes code) const			{ return m_buttons[code].state == BS_HELD; }
		inline f64 get_held_x(codes code) const			{ return m_buttons[code].held_x; }
		inline f64 get_held_y(codes code) const			{ return m_buttons[code].held_y; }
		inline f64 get_held_delta_x(codes code) const	{ return m_buttons[code].held_delta_x; }
		inline f64 get_held_delta_y(codes code) const	{ return m_buttons[code].held_delta_y; }
		inline bit get_released(codes code) const		{ return m_buttons[code].state == BS_RELEASED; }
		inline bit get_pressed(codes code) const		{ return m_buttons[code].state == BS_PRESSED; }
		inline f64 get_move_x() const					{ return m_move_x; }
		inline f64 get_move_y() const					{ return m_move_y; }
		inline f64 get_move_delta_x() const				{ return m_move_delta_x; }
		inline f64 get_move_delta_y() const				{ return m_move_delta_y; }
		inline f64 get_scroll_delta_x() const			{ return m_scroll_delta_x; }
		inline f64 get_scroll_delta_y() const			{ return m_scroll_delta_y; }
		inline modes get_mode() const					{ return m_mode; }
		// --setters
		void set_mode(modes mode);
		// --operators
		inline btn& operator[](codes code)				{ return m_buttons[code]; }
		inline const btn& operator[](codes code)const	{ return m_buttons[code]; }
		// --core_methods
		void update();
		void event_proc(evt& crs_evt);
	private:
		btn m_buttons[CRS_COUNT];
		modes m_mode = CRS_DEFAULT;
		f64 m_move_x = 0.0, m_move_y = 0.0;
		f64 m_move_delta_x = 0.0, m_move_delta_y = 0.0;
		f64 m_scroll_delta_x = 0.0, m_scroll_delta_y = 0.0;
	};
}

#endif	// NWL_IO_DEVICE_H