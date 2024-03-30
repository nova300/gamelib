#include "graphics/textureatlas.h"
#include "graphics/texturecache.h"

TextureAtlas::TextureAtlas(std::string path, int CELLWIDTH, int CELLHEIGHT)
{
    texture = CLoadTexture(path);
    cellwidth = CELLWIDTH;
    cellheight = CELLHEIGHT;
    clip.width = CELLWIDTH;
    clip.height = CELLHEIGHT;

    hsize = (int)(texture->Texture().width / CELLWIDTH);
	vsize = (int)(texture->Texture().height / CELLHEIGHT);
}


Rectangle TextureAtlas::GetDrawRect(int index)
{
    if (hsize == 0 || vsize == 0) return clip;
    int hpos = cellwidth * (int)((index % hsize));
	int vpos = cellheight * (int)(((index / hsize) % vsize));
    clip.x = hpos;
    clip.y = vpos;

    return clip;
}

Rectangle TextureAtlas::GetDrawUVS(int index)
{
    Rectangle uv = {};
    if (hsize == 0 || vsize == 0) return clip;
    float hpos = cellwidth * (int)((index % hsize));
	float vpos = cellheight * (int)(((index / hsize) % vsize));
    uv.x = hpos / texture->Texture().width;
    uv.y = vpos / texture->Texture().height;
    uv.width = uv.x + ((float)cellwidth / texture->Texture().width);
    uv.height = uv.y + ((float)cellheight / texture->Texture().height);
    return uv;
}

std::shared_ptr<CTexture> TextureAtlas::GetBaseTexture()
{
    return this->texture;
}

SpriteFrame TextureAtlas::GetSpriteFrame(int index, float time, Color color)
{
    SpriteFrame frame = {0};
    frame.width = cellwidth;
    frame.height = cellheight;

    frame.color = color;
    frame.time = time;

    frame.tex = GetBaseTexture();

    frame.src = GetDrawRect(index);

    return frame;

}