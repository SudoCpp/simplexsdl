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

#include "WindowEvent.hpp"
#include "SDL2/SDL.h"

namespace simplex::sdl
{
     WindowEvent::WindowEvent(SDL_WindowEvent* event)
     : Event((SDL_Event*)event), timestamp{event->timestamp}, windowID{event->windowID},
     data1{event->data1}, data2{event->data2}
     {
          if(event->event == SDL_WINDOWEVENT_MINIMIZED)
               windowType = WindowEventType::Minimized;
          else if(event->event == SDL_WINDOWEVENT_MAXIMIZED)
               windowType = WindowEventType::Maxamized;
          else if(event->event == SDL_WINDOWEVENT_RESIZED)
               windowType = WindowEventType::Resized;
          else if(event->event == SDL_WINDOWEVENT_RESTORED)
               windowType = WindowEventType::Restored;
          else if(event->event == SDL_WINDOWEVENT_FOCUS_GAINED)
               windowType = WindowEventType::GainedFocus;
          else if(event->event == SDL_WINDOWEVENT_FOCUS_LOST)
               windowType = WindowEventType::LostFocus;
     }
}