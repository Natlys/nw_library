#include <nwl_pch.hpp>
#include "io_device.h"
namespace NWL
{
	keyboard_state::keyboard_state() {}
	// --core_methods
	void keyboard_state::on_event(keyboard_event& kbd_evt)
	{
		auto& key = m_buttons[kbd_evt.code];
		switch (kbd_evt.type) {
		case EVT_KEYBOARD_HELD: {
			key.state = BS_HELD;
			break;
		}
		case EVT_KEYBOARD_FREE: {
			key.state = BS_FREE;
			key.nof_repeats = 0;
		}
		case EVT_KEYBOARD_CHAR: {
			key.character.wide = kbd_evt.character.wide;
			key.character.nrow = kbd_evt.character.nrow;
			break;
		}
		}
	}
}
namespace NWL
{
	cursor_state::cursor_state() {}
	void cursor_state::set_mode(cursor_modes crs_mode) { m_mode = crs_mode; }
	// --core_methods
	void cursor_state::on_event(cursor_event& crs_evt)
	{
		switch (crs_evt.type) {
		case EVT_CURSOR_MOVE: {
			m_move_delta_x = crs_evt.val_x - m_move_x;
			m_move_delta_x = crs_evt.val_y - m_move_y;
			m_move_x = crs_evt.val_x;
			m_move_y = crs_evt.val_y;
			if (get_held(crs_evt.code)) {
				m_buttons[crs_evt.code].held_delta_x = m_move_x - m_buttons[crs_evt.code].held_y;
				m_buttons[crs_evt.code].held_delta_y = m_move_y - m_buttons[crs_evt.code].held_y;
			}
			break;
		}
		case EVT_CURSOR_SCROLL:
			m_scroll_delta_x = crs_evt.val_x;
			m_scroll_delta_y = crs_evt.val_y;
			break;
		case EVT_CURSOR_HELD: {
			auto& btn = m_buttons[crs_evt.code];
			btn.state = BS_HELD;
			btn.held_x = m_move_x;
			btn.held_y = m_move_y;
			break;
		}
		case EVT_CURSOR_FREE: {
			auto& btn = m_buttons[crs_evt.code];
			btn.state = BS_FREE;
			btn.held_delta_x = 0.0;
			btn.held_delta_y = 0.0;
			break;
		}
		default: break;
		}
	}
}