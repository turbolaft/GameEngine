#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>

#include "Shader.h"
#include "Model.h"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture_t {
    unsigned int id;
    std::string type;
};

class Mesh : public Model {
public:
    // mesh data
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture_t>      textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture_t> textures);

	void createModel(const float points[], int size);
    void draw();
};