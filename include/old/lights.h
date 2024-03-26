#pragma once

#include <raylib.h>
#include <vector>
#include <memory>

// Custom Blend Modes
#define RLGL_SRC_ALPHA 0x0302
#define RLGL_MIN 0x8007
#define RLGL_MAX 0x8008

#define LIGHTMASKWIDTH 800
#define LIGHTMASKHEIGHT 600

class Lights
{
private:
    // Shadow geometry type
    struct ShadowGeometry
    {
        Vector2 vertices[4];
    };

    Rectangle bounds;

public:

    Lights(Rectangle BOUNDS);

    struct LightOccluder
    {
        friend class Lights;
    protected:
        Rectangle bounds;
        bool dirty = true;
        bool active = true;
    public:
        void Set(Rectangle BOUNDS);
    };

    struct LightInfo
    {
        friend class Lights;
    public:
        ~LightInfo();
    protected:
        bool active = true; // Is this light slot active?
        bool dirty = true;  // Does this light need to be updated?
        bool valid = false;  // Is this light in a valid position?

        Vector2 position;   // Light position
        float outerRadius;  // The distance the light touches
        Rectangle bounds;   // A cached rectangle of the light bounds to help with culling
        RenderTexture mask; // Alpha mask for the light

        std::vector<ShadowGeometry> shadows;
        bool Update(std::vector<std::weak_ptr<LightOccluder>>& occluders, bool dirtyOccluders, Rectangle maskBounds);
        void ComputeShadowVolumeForEdge(Vector2 sp, Vector2 ep);
        void DrawLightMask();
    public:
        void Set(Vector2 POS);
    };

    
    

private:
    std::vector<std::weak_ptr<LightOccluder>> occluders;
    std::vector<std::weak_ptr<LightInfo>> lights;

    RenderTexture2D lightMask;

public:
    
    std::shared_ptr<LightInfo> SetupLight(float radius, Color color);
    std::shared_ptr<LightOccluder> SetupOccluder(void);


    void Update(float deltaTime);
    void Render();


private:
    

};