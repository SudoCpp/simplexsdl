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

#include "Framework.hpp"
#include "Window.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "WindowEvent.hpp"
#include "MouseEvent.hpp"

#define __class__ "simplex::sdl::Framework"

namespace simplex::sdl
{
    Framework* Framework::instance = nullptr;

    Framework::Framework() : Singleton(this), event{nullptr}
    {
        if(SDL_Init(SDL_INIT_VIDEO) < 0)
            throw Exception("SDL2 could not be initialized: "+ string{SDL_GetError()}, __ExceptionParams__);
        if(TTF_Init() < 0)
            throw Exception("SDL2_ttf could not be initialized: "+ string{SDL_GetError()}, __ExceptionParams__);
    }

    Framework::~Framework()
    {
        for(Window* window : windows)
            delete window;

        TTF_Quit();
        SDL_Quit();
    }

    Framework& Framework::GetInstance()
    {
        if(instance == nullptr)
            instance = new Framework();
        return *instance;
    }

    Window& Framework::CreateWindow(string title)
    {
        Framework& instance = Framework::GetInstance();
        Window* window = new Window(title);
        instance.windows.add(window);
        return *window;
    }

    Window& Framework::CreateWindow(string title, int width, int height, bool resizable)
    {
        Framework& instance = Framework::GetInstance();
        Window* window = new Window(title, width, height, resizable);
        instance.windows.add(window);
        return *window;
    }

    Event* Framework::GetEvent()
    {
        SDL_Event sdlEvent;
        if(SDL_PollEvent(&sdlEvent))
        {
            Framework& instance = GetInstance();
            delete instance.event;
            instance.event = nullptr;
            if(sdlEvent.type == SDL_WINDOWEVENT)
                instance.event = new WindowEvent{(SDL_WindowEvent*)&sdlEvent};
            else if(sdlEvent.type == SDL_MOUSEBUTTONDOWN || sdlEvent.type == SDL_MOUSEBUTTONUP
                || sdlEvent.type == SDL_MOUSEMOTION || sdlEvent.type == SDL_MOUSEWHEEL)
                instance.event = new MouseEvent{&sdlEvent};
            else
                instance.event = new Event{&sdlEvent};
            return instance.event;
        }
        return nullptr;
    }
}

#undef __class__