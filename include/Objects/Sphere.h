#pragma once
#include "Model.h"
class Sphere :
    public Model
{
public:
	~Sphere() override;
	void createModel(const float points[], int size) override;
	void draw() override;
private:
	const float a[24] = {
		-.5f, -.5f, .5f,  0, 0, 1,
		-.5f, .5f, .5f,  0, 0, 1,
	   .5f, .5f, .5f,  0, 0, 1,
	   .5f, -.5f, .5f,  0, 0, 1
	};
};

