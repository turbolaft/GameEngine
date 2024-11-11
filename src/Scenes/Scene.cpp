#include "Scene.h"

void Scene::render() {
	for (auto model : models) {
		model->draw();
	}
}

void Scene::release() {
	for (auto shader : shaders) {
		delete shader;
	}
	for (auto model : models) {
		delete model;
	}
	delete camera;
}

void Scene::handleInput(GLFWwindow* window) {
	
}