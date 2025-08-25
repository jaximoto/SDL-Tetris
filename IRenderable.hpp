#pragma once
#include <SDL3/SDL_render.h>

class IRenderable
{
public:

    virtual bool Render(SDL_Renderer* renderer) const = 0;
    virtual ~IRenderable() = default;
};
