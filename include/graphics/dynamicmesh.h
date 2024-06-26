#pragma once

#include "core/object.h"
#include "core/behaviour.h"
#include "graphics/geoobject.h"
#include "graphics/texturecache.h"

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

class DynamicMesh : public Behaviour, public GeoObject
{
public:
    virtual ~DynamicMesh();

    virtual void Render() override;
    virtual Position* GetPos() override
    {
        return &GetObject()->position;
    }

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
    std::shared_ptr<CTexture> texture;
};