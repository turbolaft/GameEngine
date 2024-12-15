#pragma once

#include <vector>
#include <string>

#include <fstream>

#include <assimp/Importer.hpp>
#include "Shader.h"
#include "Mesh.h"

#include <assimp/scene.h>

class ModelObject
{
public:
    ModelObject(char* path)
    {
        loadModel(path);
    }
    void draw();
	void setShader(Shader* shader);
private:
    // model data
    std::vector<Mesh> meshes;
    std::string directory;

    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture_t> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
        std::string typeName);
};