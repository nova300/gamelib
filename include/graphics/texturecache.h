#pragma once
#include <raylib.h>
#include <string>
#include <memory>

class CTexture
{
public:
    CTexture(std::string path);
    ~CTexture();
    Texture2D Texture();
private:
    Texture2D texture;
};

std::shared_ptr<CTexture> CLoadTexture(std::string path);