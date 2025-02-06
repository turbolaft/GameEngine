#pragma once

#include <vector>

#include "DrawableObject.h"
#include "Model.h"

class Skybox : public Model
{
public:
	Skybox();
	void loadCubemap(std::vector<std::string> faces);
	void createModel(const float points[], int size) override;
	void draw() override;
	void setSkybox(bool isSkybox) { this->isSkybox = isSkybox; }
	bool getSkybox() { return isSkybox; }
private:
	unsigned int m_textureID;
	bool isSkybox = true;
};