#include "skybox.h"
#include "raymath.h"
#include "graphics.h"
#include <iostream>

#define DEGREES(x) ((x) * 0x10000 / 360)

#define CONVERT(x) ((x) * (180/3.14f))

#define GFX_DIMENSIONS_ASPECT_RATIO (4.0f / 3.0f)



#define SKYBOX_WIDTH (4 * GetScreenWidth())
#define SKYBOX_HEIGHT (4 * GetScreenHeight())

#define SKYBOX_TILE_WIDTH (GetScreenWidth() / 2)
#define SKYBOX_TILE_HEIGHT (GetScreenHeight() / 2)

#define SKYBOX_COLS (10)
#define SKYBOX_ROWS (8)

Skybox::Skybox(Texture texture)
{  
    skyboxMat = LoadMaterialDefault();
    skyboxMat.maps[0].texture = texture;

    int tilesX = 8;
    int tilesY = 8;

    float tileWidth = skyboxMat.maps[0].texture.width / tilesX;
    float tileHeight = skyboxMat.maps[0].texture.height / tilesY;

    int n = 0;
    for (unsigned int i = 0; i < tilesY; ++i)
    {   
        for (unsigned int y = 0; y < tilesX; ++y)
        {
            //unsigned char *ptr = image + (i * (tileHeight * rowLenght)) + (y * tileSizeX);
            //for (int row = 0; row < tileHeight; ++row)
            //{
            //    memcpy(tile + row * tileSizeX, ptr + row * rowLenght, sizeof(unsigned char) * tileSizeX);
            //}
            //glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, n, tileWidth, tileHeight, 1, GL_RGBA, GL_UNSIGNED_BYTE, tile);
            
            Rectangle thisUV = {};

            thisUV.x = (y * tileWidth) / skyboxMat.maps[0].texture.width;
            thisUV.y = (i * tileHeight) / skyboxMat.maps[0].texture.height;
            thisUV.width = thisUV.x;
            thisUV.height = thisUV.y;

            thisUV.width += tileWidth / skyboxMat.maps[0].texture.width;
            thisUV.height += tileHeight / skyboxMat.maps[0].texture.height;
            
            this->uv[n] = thisUV;
            n++;
        }
    }

}

int Skybox::calculate_scaled_x()
{
    float yawInDegrees = skyboxinfo.yaw + 3.14f;
    //float yawScaled = SCREEN_WIDTH * 360.0f * skyboxinfo.yaw / (fov / 3.14f);
    float yawScaled = (360 / 90.0f) * (yawInDegrees / 6.28f) * GetScreenWidth();
    int scaledX = yawScaled + 0.5f;

    if (scaledX > SKYBOX_WIDTH) 
    {
        scaledX -= scaledX / SKYBOX_WIDTH * SKYBOX_WIDTH;
    }
    return SKYBOX_WIDTH - scaledX;
}

int Skybox::calculate_scaled_y()
{
    float pitchInDegrees = skyboxinfo.pitch * 360.0f / 6.28f;

    float degreesToScale = 360.0f * pitchInDegrees / 90.0;
    int roundedY = (int)degreesToScale;

    int scaledY = roundedY + 6 * SKYBOX_TILE_HEIGHT;

    if (scaledY > SKYBOX_HEIGHT) {
        scaledY = SKYBOX_HEIGHT;
    }
    if (scaledY < GetScreenHeight()) {
        scaledY = GetScreenHeight();
    }
    return scaledY;
}

int Skybox::get_top_left_tile_idx()
{
    int tileCol = skyboxinfo.scaledX / SKYBOX_TILE_WIDTH;
    int tileRow = (SKYBOX_HEIGHT - skyboxinfo.scaledY) / SKYBOX_TILE_HEIGHT;

    return tileRow * 10 + tileCol;
}

void Skybox::render_rect(int tileIndex)
{
    int x = tileIndex % SKYBOX_COLS * SKYBOX_TILE_WIDTH;
    int y = SKYBOX_HEIGHT - tileIndex / SKYBOX_COLS * SKYBOX_TILE_HEIGHT;

    int texIndex = tileIndex - (2 * (int)(tileIndex / 10));

    if (tileIndex % 10 == 8 || tileIndex % 10 == 9)
    {
        texIndex = tileIndex - 8 - (2 * (int)(tileIndex / 10));
    }

    Rectangle uv = this->uv[texIndex];
    //Rectangle uv = atlas.GetDrawUVS(texIndex);

    //DrawQuadWall(skyboxMat.maps[0].texture, uvs, mvp, Vector2{(float)SKYBOX_TILE_WIDTH, (float)SKYBOX_TILE_HEIGHT}, Vector2Zero(), 0.0f, WHITE);

    Color col = WHITE;

    rlBegin(RL_QUADS);
    rlColor4ub(col.r, col.g, col.b, col.a);
    
    float z = -1;

    rlTexCoord2f(uv.x, uv.y);
    rlVertex3f(x, y, z);

    rlTexCoord2f(uv.x, uv.height);
    rlVertex3f(x, y - SKYBOX_TILE_HEIGHT, z);
    
    rlTexCoord2f(uv.width, uv.height);
    rlVertex3f(x + SKYBOX_TILE_WIDTH, y - SKYBOX_TILE_HEIGHT, z);

    rlTexCoord2f(uv.width, uv.y);
    rlVertex3f(x + SKYBOX_TILE_WIDTH, y, z);

    rlEnd();

    //DrawScreenQuad(skyboxMat.maps[0].texture, uvs);

    //verts[0] = gfx_make_vertex(x, y, -1, 0, 0);
    //verts[1] = gfx_make_vertex(x, y - SKYBOX_TILE_HEIGHT, -1, 0, 1);
    //verts[2] = gfx_make_vertex(x + SKYBOX_TILE_WIDTH, y - SKYBOX_TILE_HEIGHT, -1, 1, 1);
    //verts[3] = gfx_make_vertex(x + SKYBOX_TILE_WIDTH, y, -1, 1, 0);
    //return verts;
}

void Skybox::Render(Camera camera)
{
    
    auto cameraFront = Vector3Normalize(Vector3Subtract(camera.position, camera.target));
    auto cameraFocus = Vector3Add(camera.position, cameraFront);
    auto cameraFace = Vector3Subtract(camera.target, camera.position);
    
    skyboxinfo.yaw = ((atan2f(cameraFace.x, cameraFace.z)));
    skyboxinfo.pitch = -((atan2f(sqrtf(cameraFace.x * cameraFace.x + cameraFace.z * cameraFace.z), cameraFace.y)));
    skyboxinfo.scaledX = calculate_scaled_x();
    skyboxinfo.scaledY = calculate_scaled_y();
    skyboxinfo.upperLeftIndex = get_top_left_tile_idx();

    float left = skyboxinfo.scaledX;
    float right = skyboxinfo.scaledX + GetScreenWidth();

    float half_width = (4.0f / 3.0f) / GFX_DIMENSIONS_ASPECT_RATIO * GetScreenWidth() / 2;
    float center = (skyboxinfo.scaledX + GetScreenWidth() / 2);
    if (half_width < GetScreenWidth() / 2)
    {
        left = center - half_width;
        right = center + half_width;
    }

    matrix = MatrixOrtho(left, right, skyboxinfo.scaledY - GetScreenHeight(), skyboxinfo.scaledY, 0.0f, 3.0f);
    modelmatrix = MatrixIdentity();

    Matrix viewmatrix = GetCameraMatrix(camera);

    rlDrawRenderBatchActive();

    rlSetTexture(skyboxMat.maps[0].texture.id);

    rlMatrixMode(RL_PROJECTION);
    rlPushMatrix();
    rlLoadIdentity();
    rlOrtho(left, right, skyboxinfo.scaledY - GetScreenHeight(), skyboxinfo.scaledY, -10.0f, 50000.0f);

    rlMatrixMode(RL_MODELVIEW);
    rlLoadIdentity();
    //rlMultMatrixf(MatrixToFloat(viewmatrix));
    rlMultMatrixf(MatrixToFloat(MatrixIdentity()));

    for (int row = 0; row < 3; row++) 
    {
        for (int col = 0; col < 3; col++) 
        {
            int tileIndex = skyboxinfo.upperLeftIndex + (row * SKYBOX_COLS) + col;

            render_rect(tileIndex);
        }
    }

    rlDrawRenderBatchActive();

    rlMatrixMode(RL_PROJECTION);
    rlPopMatrix();

    rlMatrixMode(RL_MODELVIEW);
    rlLoadIdentity();

    rlSetTexture(0);

}