#pragma once
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
#include <vector>
#include <deque>
#include "graphics.h"

struct Vertex
{
    Vector3 vertex;
    Vector2 uv;
    Vector3 normal;
    Color color = WHITE;
};

struct Triangle
{
    Vertex v1;
    Vertex v2;
    Vertex v3;
};

struct GeoObject
{
public:
    ~GeoObject();
    void Render();
    void Push(Vertex vert);
    void Push(Vector3 POS, Vector2 UV, Vector3 NORMAL, Color COLOR);
    void Push(Triangle tri);
    void Flush();
    void Clear();
private:
    void UnloadFromGPU();
    Mesh mesh;
    bool dirty = true;
    std::deque<Vertex> vertQueue;
    bool loaded = false;
    std::vector<Vector3> verts;
	std::vector<Vector2> uvs;
	std::vector<Vector3> normals;
	std::vector<Color> colors;
    TextureAtlas atlas;
};

