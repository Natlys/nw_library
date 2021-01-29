#ifndef NWL_EVENT_H
#define NWL_EVENT_H

#include <nwl_core.hpp>

namespace NWL
{
	enum EventTypes : UInt32 {
		ET_NONE = 1 << 0,
		ET_MOUSE_MOVE = 1 << 1, ET_MOUSE_SCROLL = 1 << 2, ET_MOUSE_PRESS = 1 << 3, ET_MOUSE_RELEASE = 1 << 4,
		ET_KEY_RELEASE = 1 << 5, ET_KEY_PRESS = 1 << 6, ET_KEY_CHAR = 1 << 7,
		ET_WINDOW_CLOSE = 1 << 8, ET_WINDOW_RESIZE = 1 << 9, ET_WINDOW_MOVE = 1 << 10, ET_WINDOW_FOCUS = 1 << 11
	};
	enum EventCategories : UInt32 {
		EC_NONE = ET_NONE,
		EC_MOUSE = ET_MOUSE_MOVE | ET_MOUSE_SCROLL | ET_MOUSE_PRESS | ET_MOUSE_RELEASE,
		EC_KEYBOARD = ET_KEY_PRESS | ET_KEY_RELEASE | ET_KEY_CHAR,
		EC_WINDOW = ET_WINDOW_CLOSE | ET_WINDOW_RESIZE | ET_WINDOW_MOVE | ET_WINDOW_FOCUS,
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
		bool bIsHandled = false;
		EventTypes EvtType = ET_NONE;
	public:
		AEvent(EventTypes evtType) : EvtType(evtType), bIsHandled(false) { }
		virtual ~AEvent() = default;
		// --predicates
		inline bool IsInCategory(EventCategories EvtCat) { return (EvtType & EvtCat); }
	};
	/// MouseEvent struct
	struct NWL_API MouseEvent : public AEvent
	{
	public:
		double nX = 0.0, nY = 0.0;
		UInt32 nButton = 0;
	public:
		// MouseMove/Scroll-Event
		MouseEvent(EventTypes mmevtType, double nCoordOrScrollX, double nCoordOrScrollY) :
			AEvent(mmevtType), nX(nCoordOrScrollX), nY(nCoordOrScrollY) {}
		// MouseButtonEvent
		MouseEvent(EventTypes mbevtType, UInt32 nButtonIndex) :
			AEvent(mbevtType), nButton(nButtonIndex) {}
	};
	/// KeyboardEvent struct
	struct NWL_API KeyboardEvent : public AEvent
	{
	public:
		// ReleaseEvent
		KeyboardEvent(EventTypes kevtType, UInt32 unKeyCode) :
			AEvent(kevtType), unKeyCode(unKeyCode), cChar(' ') {}
		// PressEvent
		KeyboardEvent(EventTypes kevtType, UInt32 unKeyCode, UInt32 unRepeatCount) :
			AEvent(kevtType), unKeyCode(unKeyCode), unRepeatCount(unRepeatCount), cChar(' ') {}
		// TypeEvent
		KeyboardEvent(Char Char) :
			AEvent(ET_KEY_CHAR), unKeyCode(0), unRepeatCount(0), cChar(Char) {}
		UInt32 unKeyCode = 0;
		UInt32 unRepeatCount = 0;
		Char cChar = ' ';
	};
	/// WindowEvent struct
	struct NWL_API WindowEvent : public AEvent
	{
	public:
		Int32 nX = 0, nY = 0;
		bool bIsFocused = false;
	public:
		// WindowCloseEvent
		WindowEvent(EventTypes wevType) :
			AEvent(wevType) {}
		// WindowFocusEvent
		WindowEvent(EventTypes wevType, bool bIsFocused) :
			AEvent(wevType), bIsFocused(bIsFocused) {}
		// WindowResizeEvent
		WindowEvent(EventTypes wevType, UInt32 nWidthOrX, UInt32 nHeightOrY) :
			AEvent(wevType), nX(nWidthOrX), nY(nHeightOrY) {}
	};
}

#endif	//NW_AEVENT_H