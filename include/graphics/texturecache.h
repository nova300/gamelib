#pragma once
#include <raylib.h>
#include <string>

Texture2D CLoadTexture(std::string path);
void CUnloadTexture(Texture2D texture);
void ClearTextureCache(void);