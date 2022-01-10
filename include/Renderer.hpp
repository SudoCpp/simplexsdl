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

#ifndef SIMPLEX_SDL_RENDERER_HPP
#define SIMPLEX_SDL_RENDERER_HPP

#include "CMYColor.hpp"
#include "RGBColor.hpp"
#include "Rectangle.hpp"
#include "Texture.hpp"
#include "Surface.hpp"
#include "Font.hpp"

class SDL_Renderer;
namespace simplex::sdl
{
    class Renderer
    {
        SDL_Renderer* renderer;
        public:
        Renderer(SDL_Renderer* renderer);
        ~Renderer();

        Renderer& setColor(RGBColor color);
        Renderer& clear();
        Renderer& present();
        Renderer& drawLine(int point1x, int point1y, int point2x, int point2y);
        Renderer& fillRect(const Rectangle& rectangle);
        Renderer& fillRect(int xPoint, int yPoint, int width, int height);
        Renderer& fillRect();
        Renderer& drawRect(const Rectangle& rectangle);
        Renderer& drawRect(int xPoint, int yPoint, int width, int height);
        Renderer& drawPoint(int xPoint, int yPoint);
        Renderer& setTarget(Texture& texture);
        Renderer& setTarget();
        Renderer& copyTexture(Texture& texture);
        //Will not stretch
        Renderer& copyTexture(Texture& texture, int destinationXPosition, int destinationYPosition);
        Renderer& copyTexture(Texture& texture, const Rectangle& sourceRectangle, const Rectangle& destinationRectangle);
        
        Renderer& drawText(RGBColor& color, Font& font, int x, int y, simplex::string text);

        Texture* createTexture(int width, int height);
        Texture* createTextureFromSurface(Surface& surface);
    };
}

#endif //SIMPLEX_SDL_RENDERER_HPP