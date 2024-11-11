#pragma once

#include "Scene.h"

class SceneTwo : public Scene
{
public:
	void init(GLFWwindow*) override;
	void handleInput(GLFWwindow* window) override;
	void activate() override;
	void deactivate() override;
	void render() override;
private:

};

