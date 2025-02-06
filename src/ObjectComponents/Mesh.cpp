#include "Mesh.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"

void Mesh::createModel(const float points[], int size)
{
    /*glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    vb = new VertexBuffer(&vertices[0], vertices.size() * sizeof(Vertex));

    VertexBufferLayout layout;
    layout.push<float>(3);
    layout.push<float>(3);
    layout.push<float>(2);
    layout.push<float>(3);

    va = new VertexArray();
    va->addBuffer(vb, &layout);

    ib = new IndexBuffer(&indices[0], indices.size());

    GLuint err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cout << "GL ERROR: " << err << std::endl;
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    indicesCount = indices.size();*/
}

Mesh::Mesh(int indicesCount) : indicesCount(indicesCount) {

}

void Mesh::createModel(Vertex* vertices, unsigned int verticesSize, unsigned int* indices, unsigned int indicesSize)
{
	va = new VertexArray();
	vb = new VertexBuffer(vertices, verticesSize);
	ib = new IndexBuffer(indices, indicesSize);

	VertexBufferLayout layout;
	layout.push<float>(3);
	layout.push<float>(3);
	layout.push<float>(2);
	layout.push<float>(3);

	va->addBuffer(vb, &layout, ib);
}

void Mesh::setSkybox(bool isSkybox)
{
	this->isSkybox = isSkybox;
}

void Mesh::draw() {

    // draw mesh
    shader->use();
	va->bind();
    if (transformation && transformation->IsDynamic()) {
        this->shader->setUniform("model", transformation == nullptr ? glm::mat4(1.0f) : transformation->execute(glm::mat4(1.0f)));
    }
    if (texture != nullptr)
        texture->bindTexture();
	
    glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, NULL);
	va->unbind();
	if (texture != nullptr)
		texture->unbindTexture();
	shader->unuse();

    glActiveTexture(GL_TEXTURE0);
}