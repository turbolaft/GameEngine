#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "DrawableObject.h"
#include "CameraObserver.h"
#include "LightObserver.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Texture.h"
#include "Camera.h"
#include "Material.h"

class Camera;

class Model : public DrawableObject, public CameraObserver, public LightObserver
{
public:
	virtual ~Model();
	virtual void createModel(const float points[], int size) = 0;
	virtual void deleteModel();
	void onLightChange(glm::vec3 position, glm::vec3 color, int8_t type);
	void onLightChange(glm::vec3 position, glm::vec3 color, int8_t type, int8_t iterator);
	virtual void onLightChange(glm::vec3 position, glm::vec3 direction, int8_t type, float cutOff, float outerCutOff);
	virtual void onLightChange(glm::vec3 position, glm::vec3 direction, int8_t type, float cutOff, float outerCutOff, int8_t iterator);
	void onCameraChange(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& cameraPosition);
	virtual void draw() = 0;
	void setTexture(Texture* texture);
	void setUpModel(Shader* shader, Camera* camera, Transformation* transformation, Texture* texture);
	void setMaterial(Material* material);
	void setLightModel(unsigned int lightModel);
protected:
	VertexBuffer* vb;
	VertexArray* va;
	IndexBuffer* ib;
	Material* material;
	Texture* texture;
	void draw(GLenum mode, int first, int count);
	void draw(GLenum mode, GLsizei count, GLenum type, const void* indices);
	unsigned int lightModel;
};

