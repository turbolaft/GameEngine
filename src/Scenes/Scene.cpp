#include "Scene.h"

#include "PointLight.h"

void Scene::render() {
	for (auto model : models) {
		model->draw();
	}

	for (auto light : lights) {
		if (PointLight* pointLight = dynamic_cast<PointLight*>(light)) {
			pointLight->dynamicMove();
		}

		light->draw();
	}
}

void Scene::release() {
	for (auto model : models) {
		delete model;
	}
	delete camera;
}

void Scene::addModel(Model* model) {
	models.push_back(model);

	camera->addObserver((CameraObserver*) model);

	if (camera->isLightOn()) {
		camera->addObserver((LightObserver*)model);
	}
}

void Scene::addLight(Light* light) {
	lights.push_back(light);

	for (auto model : models) {
		light->addObserver(model);
	}
}