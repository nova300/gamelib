#pragma once
#include "raylib.h"
#include "rlgl.h"
#include "engine.h"
#include "graphics.h"
#include <map>

class Skybox
{
    float convert(float radian)
    {
        return (radian * (180 / 3.14f));
    }

    struct SkyboxInfo
    {
        float yaw;
        float pitch;
        int scaledX;
        int scaledY;
        int upperLeftIndex;
    };

    SkyboxInfo skyboxinfo;

    Material skyboxMat;

    //methods
    int calculate_scaled_x();
    int calculate_scaled_y();
    int get_top_left_tile_idx();
    void render_rect(int tileIndex);

    Matrix matrix;
    Matrix modelmatrix;

    std::map<int, Rectangle> uv;

public:
    Skybox(Texture texture);
    Skybox() {};
    void Render(Camera camera);
    
};