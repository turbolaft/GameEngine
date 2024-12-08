#pragma once
#include <vector>

#include "Scene.h"

#include "Shader.h"
#include "Model.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Sphere.h"
#include "Tree.h"

#include "sphere.h"
#include "Models/tree.h"

class SceneOne : public Scene
{
public:
	void init(GLFWwindow*);
	void activate() override;
	void deactivate() override;
private:

	float points[9] = {
		-0.3f, 0.75f, 0.0f,
		0.75f, -0.75f, 0.0f,
		-0.75f, -0.75f, 0.0f
	};
	float rectanglePoints[12] = {
		0.5f, 0.5f, 0.0f,
		0.75f, 0.5f, 0.0f,
		0.75f, 0.75f, 0.0f,
		0.5f, 0.75f, 0.0f
	};
};

