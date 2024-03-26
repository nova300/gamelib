#include "graphics/texturecache.h"
#include <map>

struct TextureCacheEntry
{
    TextureCacheEntry(Texture2D TEXTURE,int COUNT = 1) : texture(TEXTURE), count(COUNT) 
    {
    };
    Texture2D texture;
    int count;
};

std::map<std::string, TextureCacheEntry> textureCache;

Texture2D CLoadTexture(std::string path)
{
    if (textureCache.count(path) == 0)
    {
        textureCache.emplace(path, LoadTexture(path.c_str())); // = TextureCacheEntry(LoadTexture(path.c_str()));
        TextureCacheEntry &tc = textureCache.at(path);
        return tc.texture;
    }
    else 
    {
        TextureCacheEntry &tc = textureCache.at(path);
        if (tc.count < 1) textureCache.emplace(path, LoadTexture(path.c_str()));
        else tc.count++;
        return tc.texture;
    }
}

void CUnloadTexture(Texture2D texture)
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
}