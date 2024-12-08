#pragma once
#include "Model.h"

class Tetrahedron : public Model
{
public:
	void createModel(const float points[], int size) override;
	void draw() override;
};