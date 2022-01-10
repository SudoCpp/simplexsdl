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

#include "RGBColor.hpp"
#include "CMYColor.hpp"
#include "SDL2/SDL.h"
#include "simplextk.hpp"

namespace simplex::sdl
{
    RGBColor::RGBColor()
    : alpha{SDL_ALPHA_OPAQUE}
    {}

    RGBColor::RGBColor(uint8_t red, uint8_t green, uint8_t blue)
    : red{red}, green{green}, blue{blue}, alpha{SDL_ALPHA_OPAQUE}
    {}

    RGBColor::RGBColor(const CMYColor& cmyColor)
    {
        RGBColor temp = FromCMYColor(cmyColor);
        red = temp.red;
        green = temp.green;
        blue = temp.blue;
    }

    RGBColor RGBColor::FromCMYColor(const CMYColor& cmyColor)
    {
        float CPrime = cmyColor.cyan/255;
        float MPrime = cmyColor.magenta/255;
        float YPrime = cmyColor.yellow/255;
        float K = 1-simplex::Math::Min(CPrime, simplex::Math::Min(MPrime, YPrime));
        uint8_t red = 255*(1-CPrime)*(1-K);
        uint8_t green = 255*(1-MPrime)*(1-K);
        uint8_t blue = 255*(1-YPrime)*(1-K);
        return RGBColor{red, blue, green};
    }

    void RGBColor::setColor(uint8_t red, uint8_t green, uint8_t blue)
    {
        this->red = red;
        this->green = green;
        this->blue = blue;
    }
}