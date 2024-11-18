#pragma once

#include "Scene.h"

class SceneTwo : public Scene
{
public:
	void init(GLFWwindow*) override;
	void activate() override;
	void deactivate() override;
private:

};

