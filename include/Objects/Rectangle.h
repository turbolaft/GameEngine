#pragma once

#include "Model.h"

class Rectangle : public Model
{
public:
	~Rectangle() override;
	void createModel(const float points[], int size) override;
	void draw() override;
	void deleteModel() override;
private:
	GLuint EBO;
	int indices[6] = {
		0, 1, 2,
		2, 3, 0
	};
};

