#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>

#include "Shader.h"
#include "Model.h"
#include "Texture.h"

struct Vertex
{
    float Position[3];
    float Normal[3];
    float Texture[2];
    float Tangent[3];
};

class Mesh : public Model {
private:
	int indicesCount;
	bool isSkybox = false;

public:
	Mesh(int indicesCount);

	void createModel(const float points[], int size);
	void createModel(Vertex* vertices, unsigned int verticesSize, unsigned int* indices, unsigned int indicesSize);
    void draw();
	void setSkybox(bool isSkybox);
	bool getSkybox() { return isSkybox; }
	
};