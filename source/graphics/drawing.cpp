#include "graphics.h"
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