#include <nwl_pch.hpp>
#include "io_device.h"
namespace NWL
{
	keyboard_state::keyboard_state()
	{
	}
	// --setters
	void keyboard_state::set_mode(modes mode){
	}
	// --core_methods
	void keyboard_state::update()
	{
		for (auto& ibtn : m_buttons) {
			switch (ibtn.state) {
			case BS_FREE:
				ibtn.nof_repeats = 0;
				break;
			case BS_HELD:
				ibtn.nof_repeats += 1;
				break;
			case BS_PRESSED:
				ibtn.nof_repeats = 0;
				ibtn.state = BS_HELD;
				break;
			case BS_RELEASED:
				ibtn.nof_repeats = 0;
				ibtn.state = BS_FREE;
				break;
			}
		}
	}
	void keyboard_state::event_proc(evt& kbd_evt)
	{
		auto& rbtn = m_buttons[kbd_evt.code];
		switch (kbd_evt.type) {
		case EVT_KEYBOARD_PRESSED:
			rbtn.state = BS_PRESSED;
			break;
		case EVT_KEYBOARD_RELEASED:
			rbtn.state = BS_RELEASED;
			break;
		case EVT_KEYBOARD_CHAR:
			rbtn.character.wide = kbd_evt.character.wide;
			rbtn.character.nrow = kbd_evt.character.nrow;
			break;
		}
	}
}
namespace NWL
{
	cursor_state::cursor_state()
	{
	}
	// --setters
	void cursor_state::set_mode(modes mode) {
		switch (mode) {
		case CRS_CAPTURED: {
			HWND wnd_handle = GetFocus();
			RECT wnd_rect = { 0, 0, 0, 0 };
			SetCapture(wnd_handle);
			GetWindowRect(wnd_handle, &wnd_rect);
			ClipCursor(&wnd_rect);
			ShowCursor(FALSE);
			break;
		}
		case CRS_HIDDEN: {
			ShowCursor(FALSE);
			break;
		}
		default: {
			ShowCursor(TRUE);
			ClipCursor(NULL);
			ReleaseCapture();
			break;
		}
		}
		m_mode = mode;
	}
	// --core_methods
	void cursor_state::update()
	{
		m_move_delta_x = 0.0;
		m_move_delta_y = 0.0;
		m_scroll_delta_x = 0.0;
		m_scroll_delta_y = 0.0;
	}
	void cursor_state::event_proc(evt& crs_evt)
	{
		switch (crs_evt.type) {
		case EVT_CURSOR_MOVE:
			m_move_delta_x = crs_evt.val_x - m_move_x;
			m_move_delta_y = crs_evt.val_y - m_move_y;
			m_move_x = crs_evt.val_x;
			m_move_y = crs_evt.val_y;
			for (auto& ibtn : m_buttons) {
				switch (ibtn.state) {
				case BS_FREE:
					ibtn.free_delta_x = crs_evt.val_x - ibtn.free_x;
					ibtn.free_delta_y += crs_evt.val_y - ibtn.free_y;
				case BS_HELD:
					ibtn.held_delta_x = crs_evt.val_x - ibtn.held_x;
					ibtn.held_delta_y += crs_evt.val_y - ibtn.held_y;
				case BS_RELEASED:
					ibtn.free_x = m_move_x;
					ibtn.free_y = m_move_y;
					ibtn.state = BS_FREE;
					ibtn.held_delta_x = 0.0;
					ibtn.held_delta_y = 0.0;
				case BS_PRESSED:
					ibtn.held_x = m_move_x;
					ibtn.held_y = m_move_y;
					ibtn.state = BS_HELD;
					ibtn.free_delta_x = 0.0;
					ibtn.free_delta_y = 0.0;
					break;
				}
			}
			break;
		case EVT_CURSOR_SCROLL:
			m_scroll_delta_x += crs_evt.val_x;
			m_scroll_delta_y += crs_evt.val_y;
			break;
		case EVT_CURSOR_PRESSED:
			m_buttons[crs_evt.code].state = BS_PRESSED;
			break;
		case EVT_CURSOR_RELEASED:
			m_buttons[crs_evt.code].state = BS_RELEASED;
			break;
		}
	}
}