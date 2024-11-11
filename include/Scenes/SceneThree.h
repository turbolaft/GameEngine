#pragma once
#include "Scene.h"
class SceneThree :
    public Scene
{
public:
	void init(GLFWwindow*) override;
	void activate() override;
	void deactivate() override;
	void handleInput(GLFWwindow* window) override;
};

