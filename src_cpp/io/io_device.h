#ifndef NWL_IO_DEVICE_H
#define NWL_IO_DEVICE_H

#include <nwl_core.hpp>

#if (defined NWL_PLATFORM_WINDOWS)
namespace NWL
{
	enum ButtonStates : Char8 {
		BS_DEFAULT = 0,
		BS_PRESSED, BS_RELEASED, BS_HELD
	};
	enum KeyCodes : Char16 {
		KC_BACKSPACE = 8, KC_VTAB = 9, KC_HTAB = 11, KC_ENTER = 13,
		KC_LSHIFT = 17,	KC_RSHIFT = 17,
		KC_LCTRL = 18,	KC_RCTRL = 18,
		KC_PAUSE = 20,	KC_CAPS_LOCK = 26,	KC_ESCAPE = 27,
		KC_LEFT = 37,	KC_UP = 38,		KC_RIGHT = 39,	KC_DOWN = 40,
		KC_INSERT = 45,	KC_DEL = 46,	KC_HOME = 47,
		// printable
		KC_SPACE = 32,	KC_EXCLAIM = 33,	KC_QUOTE = 34,	KC_HASH = 35,	KC_DOLLAR = 36,
		KC_PERCENT = 37,	KC_AMPERSAND = 38,	KC_APOSTROPHE = 39,
		KC_LBRACKET = 40,	KC_RBRACKET = 41,	KC_ASTERISK = 42,
		KC_PLUS = 43,	KC_MINUS = 45,	KC_SLASH = 47,
		KC_COMMA = 44,	KC_DOT = 46,
		KC_0 = 48,	KC_1 = 49,	KC_2 = 50,	KC_3 = 51,	KC_4 = 52,
		KC_5 = 53,	KC_6 = 54,	KC_7 = 55,	KC_8 = 56,	KC_9 = 57,
		KC_COLON = 58,	KC_SEMICOLON = 59,
		KC_LESSER = 60,	KC_EQUAL = 61,	KC_GREATER = 62,
		KC_A = 65,	KC_B = 66,	KC_C = 67,	KC_D = 68,
		KC_E = 69,	KC_F = 70,	KC_G = 71,	KC_H = 72,
		KC_I = 73,	KC_J = 74,	KC_K = 75,	KC_L = 76,
		KC_M = 77,	KC_N = 78,	KC_O = 79,	KC_P = 80,
		KC_Q = 81,	KC_R = 82,	KC_S = 83,	KC_T = 84,
		KC_U = 85,	KC_V = 86,	KC_W = 87,	KC_X = 88,
		KC_Y = 89, KC_Z = 90,
		KC_a = 97,	KC_b = 98,	KC_c = 99,	KC_d = 100,
		KC_e = 101,	KC_f = 102,	KC_g = 103,	KC_h = 104,
		KC_i = 105,	KC_j = 106,	KC_k = 107,	KC_l = 108,
		KC_m = 109,	KC_n = 110,	KC_o = 111,	KC_p = 112,
		KC_q = 113,	KC_r = 114,	KC_s = 115,	KC_t = 116,
		KC_u = 117,	KC_v = 118,	KC_w = 119,	KC_x = 120,
		KC_y = 121,	KC_z = 122,
		KC_F1,	KC_F2,	KC_F3,	KC_F4,	KC_F5,	KC_F6,
		KC_F7,	KC_F8,	KC_F9,	KC_F10,	KC_F11,	KC_F12,
		KC_RECT_DITHER = 177,	KC_QUAD = 254,
		KC_COUNT = 255
	};
	enum CursorCodes : Char16 {
		CRS_0 = 1 << 0,	CRS_1 = 1 << 1,	CRS_2 = 1 << 2,
		CRS_3 = 1 << 3, CRS_4 = 1 << 4, CRS_5 = 1 << 5,
		CRS_6 = 1 << 6, CRS_7 = 1 << 7,
		CRS_LEFT = CRS_0,	CRS_RIGHT = CRS_1,
		CRS_COUNT = CRS_7
	};
	enum CursorModes : UInt32 {
		CRS_DEFAULT = 0,
		CRS_CAPTURED, CRS_HIDDEN,
	};
	enum KeyboardModes : UInt32 {
		KBD_DEFAULT = 0,
		KBD_STICK, KBD_LOCK
	};
}
#endif
namespace NWL
{
	template<UInt16 KeyCount>
	struct NWL_API KeyboardT
	{
	public:
		struct {
			ButtonStates bState = BS_DEFAULT;
			UInt16 unRepeats = 0;
		} Keys[KeyCount];
		KeyboardModes kbdMode = KBD_DEFAULT;
	public:
		// --gettters
		inline Bit GetPressed(KeyCodes kCode) const { return Keys[kCode].bState == BS_PRESSED; }
		inline Bit GetReleased(KeyCodes kCode) const { return Keys[kCode].bState == BS_RELEASED; }
		inline Bit GetHeld(KeyCodes kCode) const { return Keys[kCode].bState == BS_HELD; }
		inline UInt16 GetRepeats(KeyCodes kCode) const { return Keys[kCode].unRepeats; }
		inline KeyboardModes GetMode() const { return kbdMode; }
	};
	template<UInt16 ButtonsCount>
	struct NWL_API CursorT
	{
	public:
		struct {
			ButtonStates bState = BS_RELEASED;
			Float64 xHeld = 0.0, yHeld = 0.0;
			Float64 xHeldDelta = 0.0, yHeldDelta = 0.0;
		} Buttons[ButtonsCount];
		CursorModes crsMode = CRS_DEFAULT;
		Float64 xMove = 0.0, yMove = 0.0;
		Float64 xMoveDelta = 0.0, yMoveDelta = 0.0;
		Float64 xScrollDelta = 0.0, yScrollDelta = 0.0;
	public:
		// --getters
		inline Bit GetPressed(UInt16 crsButton) const { return Buttons[crsButton].bState == BS_PRESSED; }
		inline Bit GetReleased(CursorCodes crsButton)	const { return Buttons[crsButton].bState == BS_RELEASED; }
		inline Bit GetHeld(CursorCodes crsButton) const { return Buttons[crsButton].bState == BS_HELD; }
		inline Float64 GetHeldX(CursorCodes crsButton) const { return Buttons[crsButton].xHeld; }
		inline Float64 GetHeldY(CursorCodes crsButton) const { return Buttons[crsButton].yHeld; }
		inline Float64 GetHeldDeltaX(CursorCodes crsButton) const { return Buttons[crsButton].xHeldDelta; }
		inline Float64 GetHeldDeltaY(CursorCodes crsButton) const { return Buttons[crsButton].yHeldDelta; }
		inline Float64 GetMoveX() const { return xMove; }
		inline Float64 GetMoveY() const { return yMove; }
		inline Float64 GetMoveDeltaX() const { return xMoveDelta; }
		inline Float64 GetMoveDeltaY() const { return yMoveDelta; }
		inline Float64 GetScrollDeltaX() const { return xScrollDelta; }
		inline Float64 GetScrollDeltaY() const { return yScrollDelta; }
		inline CursorModes GetMode() const { return crsMode; }
	};

	typedef KeyboardT<KC_COUNT> Keyboard;
	typedef CursorT<CRS_COUNT> Cursor;
}

#endif	// NWL_IO_DEVICE_H