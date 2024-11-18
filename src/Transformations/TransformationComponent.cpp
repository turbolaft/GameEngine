#include "TransformationComponent.h"

void TransformationComponent::addChild(Transformation* child)
{
	children.push_back(child);
}

void TransformationComponent::removeChild(Transformation* child)
{
	children.erase(std::remove(children.begin(), children.end(), child), children.end());
}

glm::mat4 TransformationComponent::execute(glm::mat4 matrixInput)
{
	glm::mat4 result = matrixInput;
	for (Transformation* child : children) {
		result = child->execute(result);

		if (child->IsDynamic()) {
			isDynamic = true;
		}
	}
	return result;
}