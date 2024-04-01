#include "graphics/texturecache.h"
#include <map>
#include <memory>

struct TextureCacheEntry
{
    TextureCacheEntry(Texture2D TEXTURE,int COUNT = 1) : texture(TEXTURE), count(COUNT) 
    {
    };
    Texture2D texture;
    int count;
};

std::map<std::string, std::weak_ptr<CTexture>> textureCache;

std::shared_ptr<CTexture> CLoadTexture(std::string path)
{
    if (textureCache.count(path) == 0)
    {
        auto tex = std::make_shared<CTexture>(path);
        textureCache.emplace(path, tex);
        return tex;
    }
    else 
    {
        auto weaktex = textureCache.at(path);
        if(weaktex.expired())
        {
            textureCache.erase(path);
            auto tex = std::make_shared<CTexture>(path);
            textureCache.emplace(path, tex);
            return tex;
        }
        else
        {
            return weaktex.lock();
        }
    }
}

std::shared_ptr<CTexture> CLoadTexture(Image img)
{
    auto tex = std::make_shared<CTexture>(img);
    return tex;
}

CTexture::CTexture(std::string path)
{
    texture = LoadTexture(path.c_str());
}

CTexture::CTexture(Image img)
{
    texture = LoadTextureFromImage(img);
}

CTexture::~CTexture()
{
    if(IsTextureReady(texture)) UnloadTexture(texture);
}

Texture2D CTexture::Texture()
{
    return texture;
}

/*void CUnloadTexture(Texture2D texture)
{
    for ( auto &[cpath, ctex] : textureCache)
    {
        if (ctex.texture.id == texture.id &&
            ctex.texture.height == texture.height &&
            ctex.texture.width == texture.width &&
            ctex.texture.format == texture.format &&
            ctex.texture.mipmaps == texture.mipmaps)
            {
                ctex.count--;
                if(ctex.count == 0)
                {
                    UnloadTexture(ctex.texture);
                }
                return;
            }
    }
}*/