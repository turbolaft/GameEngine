#pragma once

#include <vector>
#include <string>

#include <fstream>

#include <assimp/Importer.hpp>
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Camera.h"

#include <assimp/scene.h>

class ModelObject
{
public:
    ModelObject(const char* path, Shader* shader, bool isSkybox = false)
    {
        loadModel(path, shader);
        if (isSkybox)
		    setSkyBox();
    }
    void draw();
	void setShader(Shader* shader);
	void setCamera(Camera* camera);
	void setTransformation(Transformation* transformation);
	std::vector<Mesh*>& getMeshes() { return meshes; }
	void setTexture(Texture* texture);
	void update();
private:
    // model data
    std::vector<Mesh*> meshes;
    std::string directory;

    void loadModel(std::string path, Shader* shader);
	void setSkyBox();
};