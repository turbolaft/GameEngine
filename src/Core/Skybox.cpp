#include "Skybox.h"

#include "stb_image.h"

Skybox::Skybox()
{
}

void Skybox::loadCubemap(std::vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	m_textureID = textureID;
}

void Skybox::createModel(const float points[], int size)
{
	vb = new VertexBuffer(points, size);
	va = new VertexArray();
	VertexBufferLayout* layout = new VertexBufferLayout;
	layout->push<float>(3);
	va->addBuffer(vb, layout);
}

void Skybox::draw()
{
	glDepthMask(GL_FALSE);
	//glDepthFunc(GL_LEQUAL);// change depth function so depth test passes when values are equal to depth buffer's content
	shader->use();
	va->bind();
	//glDepthMask(GL_FALSE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	va->unbind();
	//glDepthMask(GL_TRUE);
	shader->unuse();
	glDepthMask(GL_TRUE);
	//glDepthMask(GL_LESS);
}