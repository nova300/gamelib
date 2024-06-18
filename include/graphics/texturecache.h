#pragma once
#include <raylib.h>
#include <string>
#include <memory>

class CTexture
{
public:
    CTexture(std::string path);
    CTexture(Image img);
    ~CTexture();
    Texture2D Texture();
private:
    Texture2D texture;
};

std::shared_ptr<CTexture> CLoadTexture(std::string path);

std::shared_ptr<CTexture> CLoadTexture(Image img);

void SetPackedTexturePtr(unsigned char* data, int dataSize, const char* path);