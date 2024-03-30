#include "graphics/sprite.h"
#include "graphics/texturecache.h"
#include "core/object.h"

void Sprite::Render()
{
    if(!IsTextureReady(texture->Texture())) return;
    auto pos = GetObject()->position;

    Rectangle dst = Rectangle{pos.x, pos.y, (float)height * pos.scale.x, (float)width * pos.scale.y};
    DrawTexturePro(texture->Texture(), src, dst, Vector2{0.0f, 0.0f}, pos.rotation.z, color);

}

void Sprite::Load(std::string path)
{
    texture = CLoadTexture(path);

    src = Rectangle{0.0f, 0.0f, (float)texture->Texture().width, (float)texture->Texture().height};
}

void Sprite::Load(std::shared_ptr<CTexture> tex)
{
    texture = tex;
    src = Rectangle{0.0f, 0.0f, (float)texture->Texture().width, (float)texture->Texture().height};
}