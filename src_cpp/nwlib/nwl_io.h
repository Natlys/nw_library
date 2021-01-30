#ifndef NWL_IO_H
#define NWL_IO_H

#include <nwl_core.hpp>

#include <iostream>
#include <fstream>

namespace NWL
{
	using InStream = std::istream;
	using OutStream = std::ostream;
	using IOStream = std::iostream;
	using InFStream = std::ifstream;
	using OutFStream = std::ofstream;
	using IOFStream = std::fstream;
}

namespace NWL
{
	enum KeyCodes : Char16 {
		KC_NONE = 0,
		KC_BELL = '\a', KC_BACKSPACE = 8, KC_HTAB = 9, KC_ENTER = 10, KC_VTAB = 11,
		KC_LSHIFT, KC_RSHIFT,
		KC_LCTRL, KC_RCTRL,
		KC_PAUSE, KC_CAPS_LOCK, KC_ESCAPE = 27,
		KC_SPACE = 32, KC_EXCLAIM = 33, KC_HASH = 35,
		KC_LEFT = 37, KC_UP = 38, KC_RIGHT = 39, KC_DOWN = 40,
		KC_INSERT = 45, KC_DEL = 46, KC_HOME,
		KC_K0 = 48, KC_K1 = 49, KC_K2 = 50, KC_K3 = 51, KC_K4 = 52,
		KC_K5 = 53, KC_K6 = 54, KC_K7 = 55, KC_K8 = 56, KC_K9 = 57,
		KC_COLON, KC_SEMICOLON, KC_LESSER = 60, KC_EQUAL = 61, KC_GREATER = 62,
		KC_A = 65, KC_B, KC_C, KC_D,
		KC_E, KC_F, KC_G, KC_H, KC_I,
		KC_J, KC_K, KC_L, KC_M, KC_N,
		KC_O, KC_P, KC_Q, KC_R, KC_S,
		KC_T, KC_U, KC_V, KC_W, KC_X,
		KC_Y, KC_Z,
		KC_a = 'a', KC_b, KC_c, KC_d, KC_e, KC_f, KC_g, KC_h, KC_i, KC_j, KC_k, KC_l, KC_m, KC_n, KC_o, KC_p = 112,
		KC_q = 113, KC_r, KC_s, KC_t, KC_u, KC_v, KC_w, KC_x, KC_y, KC_z = 'z',
		KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
		KC_RECT_DITHER = 177, KC_QUAD = 254,
		KC_PGUP, KC_PGDN,
		KC_RETURN, KC_SCROLL,
		KC_NP_MUL, KC_NP_DIV, KC_NP_ADD, KC_NP_SUB, KC_NP_DECIMAL, KC_PERIOD,
		KC_COUNT = 255
	};
	enum InputModes : UInt32 {
		IM_CURSOR_NORMAL = 0, IM_CURSOR_DISABLED, IM_CURSOR_HIDDEN,
		IM_KEYBOARD_NORMAL, IM_KEYBOARD_STICK, IM_KEYBOARD_LOCK
	};
	enum MouseButtons : UInt32 {
		MSB_LEFT = 0x0, MSB_RIGHT = 0x1,
		MSB_0 = 0x0, MSB_1 = 0x1, MSB_2 = 0x2,
		MSB_3 = 0x3, MSB_4 = 0x4, MSB_5 = 0x5,
		MSB_6 = 6, MSB_7 = 0x07,
		MSB_COUNT = 7
	};
}
namespace NWL
{
	struct NWL_API ButtonState
	{
		bool bPressed = false, bReleased = false;
		bool bHeld = false;
		bool bNew = false, bOld = false;
	};
	template<UInt16 ButtonsCount>
	struct NWL_API KeyboardState
	{
		ButtonState bsKeys[ButtonsCount]{ 0 };
		Char8 aChars[ButtonsCount]{ 0 };
		Char16 wChars[ButtonsCount]{ 0 };
		InputModes iMode = IM_KEYBOARD_NORMAL;
	};
	template<UInt16 ButtonsCount>
	struct NWL_API MouseState
	{
		double xMove = 0.0, yMove = 0.0;
		double xHeld[ButtonsCount]{ 0 }, yHeld[ButtonsCount]{ 0 };
		double xMoveDelta = 0.0, yMoveDelta = 0.0;
		double xScroll = 0.0, yScroll = 0.0;
		ButtonState bsButtons[ButtonsCount]{ 0 };
		InputModes iMode = IM_CURSOR_NORMAL;
	};
}

#endif	// NWL_IO_H