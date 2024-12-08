#pragma once

#include <vector>

#include "DrawableObject.h"

class Skybox
{
public:
	Skybox();
	unsigned int loadCubemap(std::vector<std::string> faces);

};