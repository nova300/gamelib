#include "graphics/sprite.h"
#include "graphics/texturecache.h"
#include "core/object.h"

void Sprite::Render()
{
    if(!IsTextureReady(texture)) return;
    auto pos = GetObject()->position;

    Rectangle dst = Rectangle{pos.translation.x, pos.translation.y, (float)height * pos.scale.x, (float)width * pos.scale.y};
    DrawTexturePro(texture, src, dst, Vector2{0.0f, 0.0f}, pos.rotation.z, color);

}

void Sprite::Load(std::string path)
{
    texture = CLoadTexture(path);

    src = Rectangle{0.0f, 0.0f, (float)texture.width, (float)texture.height};
}

void Sprite::Load(Texture2D tex)
{
    texture = tex;
    src = Rectangle{0.0f, 0.0f, (float)texture.width, (float)texture.height};
}