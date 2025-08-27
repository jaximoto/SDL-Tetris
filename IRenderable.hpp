#pragma once
#include <SDL3/SDL_render.h>
#include <string>
class IRenderable
{
public:

    virtual bool Render(SDL_Renderer* renderer) const = 0;
    virtual bool ChangeSprite(const std::string& spriteName) = 0;
    virtual ~IRenderable() = default;
};
