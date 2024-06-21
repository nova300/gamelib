#pragma once

#include "core/behaviour.h"
#include <raylib.h>
#include <string>
#include "graphics/texturecache.h"
#include "core/object.h"
#include "graphics/geoobject.h"

class Sprite : public Behaviour, public GeoObject
{
public:
    virtual ~Sprite() {};
    void Load(std::shared_ptr<CTexture> tex);
    void Load(std::string path);
    void Load(Texture2D texture);

    virtual void Render();
    virtual Position* GetPos()
    {
        return &GetObject()->position;
    }

    void Init() override;

    Color color = WHITE;
private:
    std::shared_ptr<CTexture> texture;
    Texture2D unmanagedTexture;
    bool managed = true;
    Rectangle src;
};