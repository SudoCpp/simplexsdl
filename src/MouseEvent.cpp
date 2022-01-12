/*
    BSD 3-Clause License
    
    Copyright (c) 2022, SudoCpp
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer.

    2. Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

    3. Neither the name of the copyright holder nor the names of its
    contributors may be used to endorse or promote products derived from
    this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
    FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
    DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
    OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "MouseEvent.hpp"
#include "SDL2/SDL.h"

namespace simplex::sdl
{
    MouseEvent::MouseEvent(SDL_Event* event)
    : Event((SDL_Event*)event)
    {
        if(event->type == SDL_MOUSEMOTION)
        {
            mouseEventType = MouseEventType::Move;
            timestamp = event->motion.timestamp;
            windowID = event->motion.windowID;
            x = event->motion.x;
            y = event->motion.y;
            mouseButton = MouseButton::None;
        }
        else if(event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP)
        {
            if(event->type == SDL_MOUSEBUTTONDOWN)
                mouseEventType = MouseEventType::ButtonDown;
            else
                mouseEventType = MouseEventType::ButtonUp;
            timestamp = event->button.timestamp;
            windowID = event->button.windowID;
            x = event->button.x;
            y = event->button.y;
            if(event->button.button == SDL_BUTTON_LEFT)
                mouseButton = MouseButton::Left;
            else if(event->button.button == SDL_BUTTON_MIDDLE)
                mouseButton = MouseButton::Middle;
            else if(event->button.button == SDL_BUTTON_RIGHT)
                mouseButton = MouseButton::Right;
        }
        else if(event->type == SDL_MOUSEWHEEL)
        {
            timestamp = event->wheel.timestamp;
            windowID = event->wheel.windowID;
            if(event->wheel.direction == SDL_MOUSEWHEEL_NORMAL)
            {
                x = event->wheel.x;
                y = event->wheel.y;
            }
            else
            {
                x = -event->wheel.x;
                y = -event->wheel.y;
            }
            mouseEventType = MouseEventType::None;
            if(x != 0)
                mouseEventType = (MouseEventType)(MouseEventType::ScrollHorizontal | mouseEventType);
            else if(y != 0)
                mouseEventType = (MouseEventType)(MouseEventType::ScrollVertical | mouseEventType);
        }
    }
}