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

    virtual void Render() override;
    virtual Position* GetPos() override
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
protected:
    virtual int GetDefaultRenderQueue() override
    {
        return RQ_SPRITES;
    }
};


class ColorRectangle : public Behaviour, public GeoObject
{
public:
    virtual ~ColorRectangle() {};
    virtual void Render() override;
    virtual Position* GetPos() override
    {
        return &GetObject()->position;
    }

    void Init() override;

    Color color = WHITE;
    void SetColor(Color COLOR)
    {
        color = COLOR;
    }
    virtual int GetDefaultRenderQueue() override
    {
        return RQ_SPRITES;
    }
};

class ColorCircle : public Behaviour, public GeoObject
{
public:
    virtual ~ColorCircle() {};
    virtual void Render() override;
    virtual Position* GetPos() override
    {
        return &GetObject()->position;
    }

    void Init() override;

    Color color = WHITE;
    void SetColor(Color COLOR)
    {
        color = COLOR;
    }
    virtual int GetDefaultRenderQueue() override
    {
        return RQ_SPRITES;
    }
};