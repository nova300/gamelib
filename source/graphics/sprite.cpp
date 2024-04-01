#include "graphics/sprite.h"
#include "graphics/texturecache.h"
#include "core/object.h"

void Sprite::Render()
{
    if(managed)
    {
        if(!IsTextureReady(texture->Texture())) return;
        auto pos = GetObject()->position;

        Rectangle dst = Rectangle{pos.x, pos.y, (float)height * pos.scale.x, (float)width * pos.scale.y};
        DrawTexturePro(texture->Texture(), src, dst, Vector2{0.0f, 0.0f}, pos.rotation.z, color);
    }
    else
    {
        if(!IsTextureReady(unmanagedTexture)) return;
        auto pos = GetObject()->position;

        Rectangle dst = Rectangle{pos.x, pos.y, (float)height * pos.scale.x, (float)width * pos.scale.y};
        DrawTexturePro(unmanagedTexture, src, dst, Vector2{0.0f, 0.0f}, pos.rotation.z, color);
    }

}

void Sprite::Load(std::string path)
{
    managed = true;
    texture = CLoadTexture(path);
    width = texture->Texture().width;
    height = texture->Texture().height;
    src = Rectangle{0.0f, 0.0f, (float)texture->Texture().width, (float)texture->Texture().height};
}

void Sprite::Load(std::shared_ptr<CTexture> tex)
{
    managed = true;
    texture = tex;
    width = texture->Texture().width;
    height = texture->Texture().height;
    src = Rectangle{0.0f, 0.0f, (float)texture->Texture().width, (float)texture->Texture().height};
}

void Sprite::Load(Texture2D tex)
{
    unmanagedTexture = tex;
    width = tex.width;
    height = tex.height;
    src = Rectangle{0.0f, 0.0f, (float)unmanagedTexture.width, (float)unmanagedTexture.height};
    managed = false;
}