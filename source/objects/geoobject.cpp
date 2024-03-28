#include "geo.h"
#include <rlgl.h>
#include <config.h>

GeoObject::~GeoObject()
{
	if(loaded)
	{
		UnloadFromGPU();
	}
}

void GeoObject::Clear()
{
	vertQueue.clear();
	verts.clear();
	uvs.clear();
	normals.clear();
	colors.clear();
	if(loaded) UnloadFromGPU();
	mesh = {0};
	loaded = false;
	dirty = true;
}

void GeoObject::UnloadFromGPU()
{
	rlUnloadVertexArray(mesh.vaoId);

    if (mesh.vboId != NULL) for (int i = 0; i < MAX_MESH_VERTEX_BUFFERS; i++) rlUnloadVertexBuffer(mesh.vboId[i]);
    RL_FREE(mesh.vboId);
}

void GeoObject::Flush()
{
	if(!dirty) return; //dirty flag is not set, gpu and cpu data should be identical and we dont need to do anything
	if(loaded)
	{
		UnloadFromGPU();
		mesh = {};
		loaded = false;
	}
	
	mesh.vertexCount = verts.size();
	mesh.triangleCount = mesh.triangleCount / 3;
	
	mesh.vertices = (float*)verts.data();
	mesh.texcoords = (float*)uvs.data();
	mesh.normals = (float*)normals.data();
	mesh.colors = (unsigned char*)colors.data();

	UploadMesh(&mesh ,true);
	dirty = false;
	loaded = true;

}

void GeoObject::Push(Vertex vert)
{

	vertQueue.push_back(vert);

	while(vertQueue.size() >= 3)
	{
		Triangle tri;
		tri.v1 = vertQueue.front();
		vertQueue.pop_front();
		tri.v2 = vertQueue.front();
		vertQueue.pop_front();
		tri.v3 = vertQueue.front();

		Push(tri);
	}
}

void GeoObject::Push(Vector3 POS, Vector2 UV, Vector3 NORMAL, Color COLOR)
{
	Push(Vertex{POS, UV, NORMAL, COLOR});
}

void GeoObject::Push(Triangle tri)
{
	//triangles.push_back(tri);

	Vertex *vt = &(tri.v1);

		for(int i = 0; i < 2; i++)
		{
			verts.push_back(vt[i].vertex);
			uvs.push_back(vt[i].uv);
			normals.push_back(vt[i].normal);
			colors.push_back(vt[i].color);
		}

	dirty = true;
}