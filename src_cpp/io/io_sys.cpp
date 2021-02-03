#include <nwl_pch.hpp>
#include "io_sys.h"

NWL::KeyboardState<NWL::KC_COUNT> NWL::IOSys::s_Keyboard{ 0 };
NWL::MouseState<NWL::MSB_COUNT> NWL::IOSys::s_Mouse{ 0 };

namespace NWL
{
    // --setters
    void IOSys::SetCursorIMode(InputModes iMode) {
        s_Mouse.iMode = iMode;
        switch (iMode) {
        case IM_CURSOR_NORMAL:
            break;
        case IM_CURSOR_DISABLED:
            break;
        case IM_CURSOR_HIDDEN:
            break;
        default:    break;
        }
    }
    void IOSys::SetKeyboardIMode(InputModes iMode) {
        s_Keyboard.iMode = iMode;
        switch (iMode) {
        case IM_KEYBOARD_STICK:
            break;
        case IM_KEYBOARD_LOCK:
            break;
        default:    break;
        }
    }
    // --==<core_methods>==--
    void IOSys::Update()
    {
        s_Mouse.xMoveDelta = s_Mouse.yMoveDelta = 0.0f;
        s_Mouse.xScroll = s_Mouse.yScroll = 0.0f;
        UpdateKeyboard();
        UpdateMouseButtons();
    }
    // --==</core_methods>==--
    inline void IOSys::UpdateKeyboard()
    {
        for (UInt16 ki = 0; ki < KC_COUNT; ki++) {
            ButtonState& rBs = s_Keyboard.bsKeys[ki];
            rBs.bPressed = rBs.bReleased = false;
            if (rBs.bNew != rBs.bOld) {
                if (rBs.bNew == true) {
                    rBs.bPressed = rBs.bHeld = true;
                }
                else {
                    rBs.bHeld = false;
                    rBs.bReleased = true;
                }
            }
            rBs.bOld = rBs.bNew;
        }
    }
    inline void IOSys::UpdateMouseButtons()
    {
        for (UInt16 mi = 0; mi < MSB_COUNT; mi++) {
            ButtonState& rBs = s_Mouse.bsButtons[mi];
            rBs.bPressed = rBs.bReleased = false;
            if (rBs.bNew != rBs.bOld) {
                if (rBs.bNew) {
                    rBs.bPressed = rBs.bHeld = true;
                    s_Mouse.xHeld[mi] = s_Mouse.xMove;
                    s_Mouse.yHeld[mi] = s_Mouse.yMove;
                }
                else {
                    rBs.bHeld = false;
                    rBs.bReleased = true;
                }
            }
            rBs.bOld = rBs.bNew;
        }
    }
}