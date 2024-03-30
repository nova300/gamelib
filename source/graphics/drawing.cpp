#include "raylib.h"
#include "rlgl.h"

// Draw a part of a texture (defined by a rectangle) with 'pro' parameters
// NOTE: origin is relative to destination rectangle size
void DrawTextureProZ(Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float depth, float rotation, Color tint)
{
    // Check if texture is valid
    if (texture.id > 0)
    {
        float width = (float)texture.width;
        float height = (float)texture.height;

        bool flipX = false;

        if (source.width < 0) { flipX = true; source.width *= -1; }
        if (source.height < 0) source.y -= source.height;

        rlEnableTexture(texture.id);

        rlPushMatrix();
        rlTranslatef(dest.x, dest.y, 0.0f);
        rlRotatef(rotation, 0.0f, 0.0f, 1.0f);
        rlTranslatef(-origin.x, -origin.y, 0.0f);

        rlBegin(RL_QUADS);
        rlColor4ub(tint.r, tint.g, tint.b, tint.a);
        rlNormal3f(0.0f, 0.0f, 1.0f);                          // Normal vector pointing towards viewer

        // Bottom-left corner for texture and quad
        if (flipX) rlTexCoord2f((source.x + source.width) / width, source.y / height);
        else rlTexCoord2f(source.x / width, source.y / height);
        rlVertex3f(0.0f, 0.0f, depth);

        // Bottom-right corner for texture and quad
        if (flipX) rlTexCoord2f((source.x + source.width) / width, (source.y + source.height) / height);
        else rlTexCoord2f(source.x / width, (source.y + source.height) / height);
        rlVertex3f(0.0f, dest.height, depth);

        // Top-right corner for texture and quad
        if (flipX) rlTexCoord2f(source.x / width, (source.y + source.height) / height);
        else rlTexCoord2f((source.x + source.width) / width, (source.y + source.height) / height);
        rlVertex3f(dest.width, dest.height, depth);

        // Top-left corner for texture and quad
        if (flipX) rlTexCoord2f(source.x / width, source.y / height);
        else rlTexCoord2f((source.x + source.width) / width, source.y / height);
        rlVertex3f(dest.width, 0.0f, depth);
        rlEnd();
        rlPopMatrix();

        rlDisableTexture();
    }
}

void DrawQuad(Texture2D texture, Rectangle source, Vector3 position, Vector3 rotation, Vector3 scale, Vector2 size, Vector2 origin, Color tint)
{
    if (texture.id == 0) return;

    rlSetTexture(texture.id);
        rlPushMatrix();
            rlTranslatef(-origin.x, -origin.y, 0.0f);

            rlScalef(scale.x, scale.y, scale.z);
            
            Quaternion q = QuaternionFromEuler(rotation.x, rotation.y, rotation.z);
            float angle;
            Vector3 axis;
            QuaternionToAxisAngle(q, &axis, &angle);
            rlRotatef(angle, axis.x, axis.y, axis.z);
            
            rlTranslatef(position.x, position.y, position.z);

            

            rlBegin(RL_QUADS);
                rlColor4ub(tint.r, tint.g, tint.b, tint.a);
                rlNormal3f(0.0f, 0.0f, 1.0f);                          // Normal vector pointing towards viewer


                // Top left
                rlTexCoord2f((float)source.x/texture.width, (float)source.y/texture.height);
                rlVertex3f(0.0f, 0.0f, 0.0f);

                // bottom left
                rlTexCoord2f((float)source.x/texture.width, (float)(source.y + source.height)/texture.height);
                rlVertex3f(0.0f, -size.y, 0.0f);

                // bottom right
                rlTexCoord2f((float)(source.x + source.width)/texture.width, (float)(source.y + source.height)/texture.height);
                rlVertex3f(size.x, -size.y, 0.0f);

                // top right
                rlTexCoord2f((float)(source.x + source.width)/texture.width, (float)source.y/texture.height);
                rlVertex3f(size.x, 0.0f, 0.0f);
                
            rlEnd();
    rlPopMatrix();
    rlSetTexture(0);
}

void DrawQuadWall(Texture2D texture, Rectangle source, Matrix transform, Vector2 size, Vector2 origin, float rotation, Color tint)
{
    if (texture.id == 0) return;

    rlSetTexture(texture.id);
        rlPushMatrix();
            
            if (rotation != 0.0f) rlRotatef(rotation, 0.0f, 0.0f, 1.0f);
            rlTranslatef(-origin.x, -origin.y, 0.0f);
            rlMultMatrixf(MatrixToFloat(transform));
            

            rlBegin(RL_QUADS);
                rlColor4ub(tint.r, tint.g, tint.b, tint.a);
                rlNormal3f(0.0f, 0.0f, 1.0f);                          // Normal vector pointing towards viewer


                // Top left
                rlTexCoord2f((float)source.x/texture.width, (float)source.y/texture.height);
                rlVertex3f(0.0f, 0.0f, 0.0f);

                // bottom left
                rlTexCoord2f((float)source.x/texture.width, (float)(source.y + source.height)/texture.height);
                rlVertex3f(0.0f, -size.y, 0.0f);

                // bottom right
                rlTexCoord2f((float)(source.x + source.width)/texture.width, (float)(source.y + source.height)/texture.height);
                rlVertex3f(size.x, -size.y, 0.0f);

                // top right
                rlTexCoord2f((float)(source.x + source.width)/texture.width, (float)source.y/texture.height);
                rlVertex3f(size.x, 0.0f, 0.0f);
                
            rlEnd();
    rlPopMatrix();
    rlSetTexture(0);
}

void DrawQuadFloor(Texture2D texture, Rectangle source, Matrix transform, Vector2 size, Vector2 origin, float rotation, Color tint)
{
    if (texture.id == 0) return;

    rlSetTexture(texture.id);
        rlPushMatrix();
            
            if (rotation != 0.0f) rlRotatef(rotation, 0.0f, 1.0f, 0.0f);
            rlTranslatef(-origin.x, 0.0f, -origin.y);
            rlMultMatrixf(MatrixToFloat(transform));
            

            rlBegin(RL_QUADS);
                rlColor4ub(tint.r, tint.g, tint.b, tint.a);
                rlNormal3f(0.0f, 1.0f, 0.0f);                          // Normal vector pointing towards viewer

                // Top left
                rlTexCoord2f((float)source.x/texture.width, (float)source.y/texture.height);
                rlVertex3f(0.0f, 0.0f, 0.0f);

                // bottom left
                rlTexCoord2f((float)source.x/texture.width, (float)(source.y + source.height)/texture.height);
                rlVertex3f(0.0f, 0.0f, size.y);

                // bottom right
                rlTexCoord2f((float)(source.x + source.width)/texture.width, (float)(source.y + source.height)/texture.height);
                rlVertex3f(size.x, 0.0f, size.y);

                // top right
                rlTexCoord2f((float)(source.x + source.width)/texture.width, (float)source.y/texture.height);
                rlVertex3f(size.x, 0.0f, 0.0f);
                
            rlEnd();
    rlPopMatrix();
    rlSetTexture(0);
}

void DrawColorQuad(Matrix transform, Vector2 size, Vector2 origin, float rotation, Color tint)
{
        rlPushMatrix();
            
            if (rotation != 0.0f) rlRotatef(rotation, 0.0f, 0.0f, 1.0f);
            rlTranslatef(-origin.x, -origin.y, 0.0f);
            rlMultMatrixf(MatrixToFloat(transform));
            

            rlBegin(RL_QUADS);
                rlColor4ub(tint.r, tint.g, tint.b, tint.a);
                rlNormal3f(0.0f, 0.0f, 1.0f);                          // Normal vector pointing towards viewer


                // Top left
                rlVertex3f(0.0f, 0.0f, 0.0f);

                // bottom left
                rlVertex3f(0.0f, -size.y, 0.0f);

                // bottom right
                rlVertex3f(size.x, -size.y, 0.0f);

                // top right
                rlVertex3f(size.x, 0.0f, 0.0f);
                
            rlEnd();
    rlPopMatrix();
}

void DrawScreenQuad(Texture2D texture, Rectangle source)
{
    DrawTexturePro(texture, source, Rectangle{0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()}, Vector2{0,0}, 0.0, WHITE);
}

Vector2 GetScreenToWorld3D(Vector2 position, Camera camera)
{
    Matrix invMatCamera = MatrixInvert(GetCameraMatrix(camera));
    Vector3 transform = Vector3Transform(Vector3{ position.x, position.y, 0 }, invMatCamera);

    return Vector2{ transform.x, transform.y };
}