#ifndef NWL_EVENT_H
#define NWL_EVENT_H

#include <nwl_core.hpp>
#include <io/io_device.h>

namespace NWL
{

	enum EventTypes : UInt32 {
		ET_DEFAULT = 1 << 0,
		ET_CURSOR_MOVE = 1 << 1, ET_CURSOR_SCROLL = 1 << 2, ET_CURSOR_PRESS = 1 << 3, ET_CURSOR_RELEASE = 1 << 4,
		ET_KEYBOARD_RELEASE = 1 << 8, ET_KEYBOARD_PRESS = 1 << 9, ET_KEYBOARD_CHAR = 1 << 10,
		ET_WINDOW_CLOSE = 1 << 12, ET_WINDOW_RESIZE = 1 << 13, ET_WINDOW_MOVE = 1 << 14, ET_WINDOW_FOCUS = 1 << 15, ET_WINDOW_DEFOCUS = 1 << 16
	};
	enum EventCategories : UInt32 {
		EC_DEFAULT = ET_DEFAULT,
		EC_CURSOR = ET_CURSOR_MOVE | ET_CURSOR_SCROLL | ET_CURSOR_PRESS | ET_CURSOR_RELEASE,
		EC_KEYBOARD = ET_KEYBOARD_PRESS | ET_KEYBOARD_RELEASE | ET_KEYBOARD_CHAR,
		EC_WINDOW = ET_WINDOW_CLOSE | ET_WINDOW_RESIZE | ET_WINDOW_MOVE | ET_WINDOW_FOCUS | ET_WINDOW_DEFOCUS,
	};
}

namespace NWL
{
	/// Abstract Event struct
	/// Interface:
	/// -> Create in the OnEvent callback function -> Set the event data
	/// -> Dispatch to different classes
	/// Description:
	struct NWL_API AEvent
	{
	public:
		Bit bIsHandled = false;
		EventTypes evType = ET_DEFAULT;
	public:
		AEvent(EventTypes evtType) : evType(evtType), bIsHandled(false) { }
		virtual ~AEvent() = default;
		// --predicates
		inline bool IsInCategory(EventCategories evCat) { return (evType & evCat); }
	};
	/// CursorEvent struct
	struct NWL_API CursorEvent : public AEvent
	{
	public:
		Float64 nX = 0.0, nY = 0.0;
		CursorCodes cButton = CRS_0;
	public:
		// MouseMove/Scroll-Event
		CursorEvent(EventTypes mmevtType, Float64 nCoordOrScrollX, Float64 nCoordOrScrollY) :
			AEvent(mmevtType), nX(nCoordOrScrollX), nY(nCoordOrScrollY) {}
		// MouseButtonEvent
		CursorEvent(EventTypes mbevtType, CursorCodes crsButton,
			Float64 nCrdOrScrollX = 0.0, Float64 nCrdOrScrollY = 0.0) :
			AEvent(mbevtType), cButton(crsButton), nX(nCrdOrScrollX), nY(nCrdOrScrollY) {}
	};
	/// KeyboardEvent struct
	struct NWL_API KeyboardEvent : public AEvent
	{
	public:
		union {
			KeyCodes keyCode = KC_SPACE;
			union { Char8 cNarr; Char16 wNarr; } Char;
		};
		UInt32 unRepeats = 0;
	public:
		// ReleaseEvent
		KeyboardEvent(EventTypes kevtType, KeyCodes keyCodeOrChar) :
			AEvent(kevtType), keyCode(keyCodeOrChar), unRepeats(0) {}
		// PressEvent
		KeyboardEvent(EventTypes kevtType, KeyCodes keyCodeOrChar, UInt32 unRepeatCount) :
			AEvent(kevtType), keyCode(keyCodeOrChar), unRepeats(unRepeatCount) {}
	};
	/// WindowEvent struct
	struct NWL_API WindowEvent : public AEvent
	{
	public:
		Int32 nX = 0, nY = 0;
	public:
		// WindowCloseEvent
		WindowEvent(EventTypes wevType) : AEvent(wevType) {}
		// WindowResizeEvent
		WindowEvent(EventTypes wevType, Int32 nWidthOrCrdX, Int32 nHeightOrCrdY) :
			AEvent(wevType), nX(nWidthOrCrdX), nY(nHeightOrCrdY) {}
	};
}

#endif	//NW_AEVENT_H