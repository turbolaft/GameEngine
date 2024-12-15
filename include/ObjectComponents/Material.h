#pragma once

#include <glm/glm.hpp>

class Material
{
private:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
public:
	Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess)
		: ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess) {}

	glm::vec3 getAmbient() { return ambient; }
	glm::vec3 getDiffuse() { return diffuse; }
	glm::vec3 getSpecular() { return specular; }
	float getShininess() { return shininess; }
};
