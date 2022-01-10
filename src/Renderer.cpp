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

#include "Renderer.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

namespace simplex::sdl
{
    Renderer::Renderer(SDL_Renderer* renderer) : renderer{renderer} {}
    Renderer::~Renderer()
    {
        //SEGFAULT ERROR
        //if(renderer)
         //   SDL_DestroyRenderer(renderer);
    }

    Renderer& Renderer::setColor(RGBColor color)
    {
        SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, color.alpha);
        return *this;
    }

    Renderer& Renderer::clear()
    {
        SDL_RenderClear(renderer);
        return *this;
    }

    Renderer& Renderer::present()
    {
        SDL_RenderPresent(renderer);
        return *this;
    }

    Renderer& Renderer::drawLine(int point1x, int point1y, int point2x, int point2y)
    {
        SDL_RenderDrawLine(renderer, point1x, point1y, point2x, point2y);
        return *this;
    }

    Renderer& Renderer::fillRect(const Rectangle& rectangle)
    {
        SDL_RenderFillRect(renderer, rectangle.rectangle);
        return *this;
    }

    Renderer& Renderer::fillRect()
    {
        SDL_RenderFillRect(renderer, nullptr);
        return *this;
    }

    Renderer& Renderer::fillRect(int xPoint, int yPoint, int width, int height)
    {
        Rectangle rectangle{xPoint, yPoint, width, height};
        SDL_RenderFillRect(renderer, rectangle.rectangle);
        return *this;
    }

    Renderer& Renderer::drawRect(const Rectangle& rectangle)
    {
        SDL_RenderDrawRect(renderer, rectangle.rectangle);
        return *this;
    }

    Renderer& Renderer::drawRect(int xPoint, int yPoint, int width, int height)
    {
        Rectangle rectangle{xPoint, yPoint, width, height};
        SDL_RenderDrawRect(renderer, rectangle.rectangle);
        return *this;
    }

    Renderer& Renderer::drawPoint(int xPoint, int yPoint)
    {
        SDL_RenderDrawPoint(renderer, xPoint, yPoint);
        return *this;
    }

    Renderer& Renderer::drawText(RGBColor& color, Font& font, int x, int y, simplex::string text)
    {
        Surface surface = Surface{TTF_RenderText_Blended(font.font, text.toCString(), {color.red, color.green, color.blue})};
        Texture* texture = createTextureFromSurface(surface);
        copyTexture(*texture, x, y);
        delete texture;
        return *this;
    }

    Texture* Renderer::createTexture(int width, int height)
    {
        return new Texture(SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height));
    }

    Texture* Renderer::createTextureFromSurface(Surface& surface)
    {
        return new Texture(SDL_CreateTextureFromSurface(renderer, surface.surface));
    }

    Renderer& Renderer::setTarget(Texture& texture)
    {
        SDL_SetRenderTarget(renderer, texture.texture);
        return *this;
    }

    Renderer& Renderer::setTarget()
    {
        SDL_SetRenderTarget(renderer, nullptr);
        return *this;
    }

    Renderer& Renderer::copyTexture(Texture& texture)
    {
        SDL_RenderCopy(renderer, texture.texture, nullptr, nullptr);
        return *this;
    }

    Renderer& Renderer::copyTexture(Texture& texture, int destinationXPosition, int destinationYPosition)
    {
        Rectangle source{0, 0, texture.getWidth(), texture.getHeight()};
        Rectangle destination{destinationXPosition, destinationYPosition, texture.getWidth(), texture.getHeight()};
        SDL_RenderCopy(renderer, texture.texture, source.rectangle, destination.rectangle);
        return *this;
    }

    Renderer& Renderer::copyTexture(Texture& texture, const Rectangle& sourceRectangle, const Rectangle& destinationRectangle)
    {
        SDL_RenderCopy(renderer, texture.texture, sourceRectangle.rectangle, destinationRectangle.rectangle);
        return *this;
    }
}