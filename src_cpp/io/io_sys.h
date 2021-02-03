#ifndef NWL_IO_SYSTEM_H
#define NWL_IO_SYSTEM_H

#include <nwl_core.hpp>
#include <io/io_event.h>
#include <io/io_stream.h>

namespace NWL
{
	/// InputOutputSystem static class
	class NWL_API IOSys
	{
	public:
		static KeyboardState<KC_COUNT> s_Keyboard;
		static MouseState<MSB_COUNT> s_Mouse;
	public:
		// --getters
		static inline bool GetKeyPressed(UInt16 unKeyId) { return s_Keyboard.bsKeys[unKeyId].bPressed; }
		static inline bool GetKeyReleased(UInt16 unKeyId) { return s_Keyboard.bsKeys[unKeyId].bReleased; }
		static inline bool GetKeyHeld(UInt16 unKeyId) { return s_Keyboard.bsKeys[unKeyId].bHeld; }
		static inline bool GetMousePressed(UInt16 unButtonId) { return s_Mouse.bsButtons[unButtonId].bPressed; }
		static inline bool GetMousReleased(UInt16 unButtonId) { return s_Mouse.bsButtons[unButtonId].bReleased; }
		static inline bool GetMouseHeld(UInt16 unButtonId) { return s_Mouse.bsButtons[unButtonId].bHeld; }
		static inline double GetMouseScrollX() { return s_Mouse.xScroll; }
		static inline double GetMouseScrollY() { return s_Mouse.yScroll; }
		static inline double GetMouseMoveX() { return s_Mouse.xMove; }
		static inline double GetMouseMoveY() { return s_Mouse.yMove; }
		static inline double GetMouseMoveDeltaX() { return s_Mouse.xMoveDelta; }
		static inline double GetMouseMoveDeltaY() { return s_Mouse.yMoveDelta; }
		static inline double GetMouseHeldX(MouseButtons msCode) { return s_Mouse.xHeld[msCode]; }
		static inline double GetMouseHeldY(MouseButtons msCode) { return s_Mouse.yHeld[msCode]; }
		static inline InputModes GetMouseIMode() { return s_Mouse.iMode; }
		static inline InputModes GetKeyboardIMode() { return s_Keyboard.iMode; }
		// --setters
		static void SetCursorIMode(InputModes iMode);
		static void SetKeyboardIMode(InputModes iMode);

		// --core_methods
		static void Update();
	private:
		static inline void UpdateKeyboard();
		static inline void UpdateMouseButtons();
	private:
	};
}

#endif // NWL_IO_SYSTEM_H