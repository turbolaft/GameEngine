#pragma once
#include "Scene.h"

class SceneFour : public Scene
{
public:
	void init(GLFWwindow*) override;
	void activate() override;
	void deactivate() override;
};

