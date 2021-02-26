#ifndef NWL_EVENT_H
#define NWL_EVENT_H

#include <nwl_core.hpp>
#include <io/io_device.h>

namespace NWL
{
	enum EventTypes : UInt32 {
		EVT_DEFAULT = 1 << 0,
		EVT_CURSOR_MOVE = 1 << 1, EVT_CURSOR_SCROLL = 1 << 2, EVT_CURSOR_PRESS = 1 << 3, EVT_CURSOR_RELEASE = 1 << 4, EVT_CURSOR_DOUBLE_CLICK = 1 << 5,
		EVT_KEYBOARD_RELEASE = 1 << 8, EVT_KEYBOARD_PRESS = 1 << 9, EVT_KEYBOARD_CHAR = 1 << 10,
		EVT_WINDOW_CLOSE = 1 << 12, EVT_WINDOW_RESIZE = 1 << 13, EVT_WINDOW_MOVE = 1 << 14, EVT_WINDOW_FOCUS = 1 << 15, EVT_WINDOW_DEFOCUS = 1 << 16
	};
	enum EventCategories : UInt32 {
		EVC_DEFAULT = EVT_DEFAULT,
		EVC_CURSOR = EVT_CURSOR_MOVE | EVT_CURSOR_SCROLL | EVT_CURSOR_PRESS | EVT_CURSOR_RELEASE | EVT_CURSOR_DOUBLE_CLICK,
		EVC_KEYBOARD = EVT_KEYBOARD_PRESS | EVT_KEYBOARD_RELEASE | EVT_KEYBOARD_CHAR,
		EVC_WINDOW = EVT_WINDOW_CLOSE | EVT_WINDOW_RESIZE | EVT_WINDOW_MOVE | EVT_WINDOW_FOCUS | EVT_WINDOW_DEFOCUS,
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
		EventTypes evType = EVT_DEFAULT;
	public:
		AEvent(EventTypes evtType) : evType(evtType), bIsHandled(false) { }
		virtual ~AEvent() = default;
		// --predicates
		inline bool IsInCategory(EventCategories evCat) { return (evType & evCat); }
	};
	using EventCallback = std::function<void(AEvent&)>;
}
namespace NWL
{
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