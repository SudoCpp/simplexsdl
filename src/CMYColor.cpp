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

#include "CMYColor.hpp"
#include "RGBColor.hpp"
#include "SDL2/SDL.h"
#include "simplextk.hpp"

namespace simplex::sdl
{
    CMYColor::CMYColor()
    {}

    CMYColor::CMYColor(uint8_t cyan, uint8_t magenta, uint8_t yellow)
    : cyan{cyan}, magenta{magenta}, yellow{yellow}
    {}

    CMYColor::CMYColor(const RGBColor& rgbColor)
    {
        CMYColor cmyColor = FromRGBColor(rgbColor);
        cyan = cmyColor.cyan;
        magenta = cmyColor.magenta;
        yellow = cmyColor.yellow;
    }

    void CMYColor::setColor(uint8_t cyan, uint8_t magenta, uint8_t yellow)
    {
        this->cyan = cyan;
        this->magenta = magenta;
        this->yellow = yellow;
    }

    CMYColor CMYColor::FromRGBColor(const RGBColor& rgbColor)
    {
        float RPrime = rgbColor.red/255;
        float GPrime = rgbColor.green/255;
        float BPrime = rgbColor.blue/255;
        float K = 1-simplex::Math::Max(RPrime, simplex::Math::Max(GPrime, BPrime));
        float CPrime = (1-RPrime-K)/(1-K);
        float MPrime = (1-GPrime-K)/(1-K);
        float YPrime = (1-BPrime-K)/(1-K);
        uint8_t cyan = CPrime * 255;
        uint8_t magenta = MPrime * 255;
        uint8_t yellow = YPrime * 255;
        return CMYColor{cyan, magenta, yellow};
    }
}