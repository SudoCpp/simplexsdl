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

#include "Surface.hpp"
#include "SDL2/SDL.h"

#define __class__ "simplex::sdl::Surface"

namespace simplex::sdl
{
    Surface::Surface(SDL_Surface* surface, bool manageMemory)
    : surface{surface}, freeSurface{manageMemory}
    {}

    Surface::~Surface()
    {
        if(freeSurface)
            SDL_FreeSurface(surface);
    }

    Surface& Surface::blitFrom(Surface& source, const Rectangle& sourceRect, Rectangle& destinationRect)
    {
        SDL_BlitSurface(source.surface, sourceRect.rectangle, surface, destinationRect.rectangle);
        return *this;
    }
    Surface& Surface::blitFrom(Surface& source, const Rectangle& sourceRect)
    {
        SDL_BlitSurface(source.surface, sourceRect.rectangle, surface, nullptr);
        return *this;
    }
    Surface& Surface::blitFrom(Surface& source, Rectangle& destinationRect)
    {
        SDL_BlitSurface(source.surface, nullptr, surface, destinationRect.rectangle);
        return *this;
    }
    Surface& Surface::blitFrom(Surface& source)
    {
        SDL_BlitSurface(source.surface, nullptr, surface, nullptr);
        return *this;
    }

    Surface* Surface::CreateFromBMP(string bmpFilePath)
    {
        SDL_Surface* image = SDL_LoadBMP(bmpFilePath.toCString());
        if(image != nullptr)
            return new Surface{image};
        else
            throw Exception("Unable to load bitmap. " + string{ SDL_GetError() }, __ExceptionParams__);
    }

    int Surface::getWidth()
    {
        return surface->w;
    }

    int Surface::getHeight()
    {
        return surface->h;
    }
}

#undef __class__