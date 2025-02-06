#include "ModelObject.h"

#include <assimp/postprocess.h>
#include <Material.h>
#include <stb_image.h>

void ModelObject::draw()
{
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i]->draw();
	}
}

void ModelObject::setShader(Shader* shader)
{
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i]->setShader(shader);
	}
}

void ModelObject::loadModel(std::string fileName, Shader* shader)
{
    Assimp::Importer importer;
    unsigned int importOptions = aiProcess_Triangulate //Converts polygons to triangles
        | aiProcess_OptimizeMeshes              // Reduces the number of submeshes
        | aiProcess_JoinIdenticalVertices       // Removes duplicate vertices
        | aiProcess_CalcTangentSpace;           // Computes tangents and bitangents

    //aiProcess_GenNormals/ai_Process_GenSmoothNormals - Generates flat/Smooth normals

    const aiScene* scene = importer.ReadFile(fileName, importOptions);
	std::vector<Material*> materials;

    if (scene) { //pokud bylo nacteni uspesne
        printf("scene->mNumMeshes = %d\n", scene->mNumMeshes);
        printf("scene->mNumMaterials = %d\n", scene->mNumMaterials);
        //Materials
        for (unsigned int i = 0; i < scene->mNumMaterials; i++)
        {
            const aiMaterial* mat = scene->mMaterials[i];

            aiString name;
            mat->Get(AI_MATKEY_NAME, name);
            printf("Material [%d] name: %s\n", i, name.C_Str());

            
            aiColor4D color;
			glm::vec3 ambient;
			glm::vec3 diffuse;
			glm::vec3 specular;

            // Ambient color
            if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_AMBIENT, &color)) {
                ambient = glm::vec3(color.r, color.g, color.b);
            }
            else {
                ambient = glm::vec3(0.1f);  // Default ambient color
            }

            // Diffuse color
            if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &color)) {
                diffuse = glm::vec3(color.r, color.g, color.b);
            }
            else {
                diffuse = glm::vec3(0.8f);  // Default diffuse color
            }

            // Specular color
            if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_SPECULAR, &color)) {
                specular = glm::vec3(color.r, color.g, color.b);
            }
            else {
                specular = glm::vec3(0.5f);  // Default specular color
            }

            // Shininess
            float shininess;
            if (AI_SUCCESS == mat->Get(AI_MATKEY_SHININESS, shininess)) {
                shininess = shininess;
            }
            else {
                shininess = 32.0f;  // Default shininess
            }

            Material* material = new Material(ambient, diffuse, specular, shininess);

            materials.push_back(material);  // Store materials for later assignment to meshes
        }
        for (unsigned int i = 0; i < scene->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[i];
            Vertex* pVertices = new Vertex[mesh->mNumVertices];
            std::memset(pVertices, 0, sizeof(Vertex) * mesh->mNumVertices);
            for (unsigned int i = 0; i < mesh->mNumVertices; i++)
            {
                if (mesh->HasPositions()) {
                    pVertices[i].Position[0] = mesh->mVertices[i].x;
                    pVertices[i].Position[1] = mesh->mVertices[i].y;
                    pVertices[i].Position[2] = mesh->mVertices[i].z;
                }

                if (mesh->HasNormals()) {
                    pVertices[i].Normal[0] = mesh->mNormals[i].x;
                    pVertices[i].Normal[1] = mesh->mNormals[i].y;
                    pVertices[i].Normal[2] = mesh->mNormals[i].z;
                }

                if (mesh->HasTextureCoords(0)) {
                    pVertices[i].Texture[0] = mesh->mTextureCoords[0][i].x;
                    pVertices[i].Texture[1] = mesh->mTextureCoords[0][i].y;
                }

                if (mesh->HasTangentsAndBitangents()) {
                    pVertices[i].Tangent[0] = mesh->mTangents[i].x;
                    pVertices[i].Tangent[1] = mesh->mTangents[i].y;
                    pVertices[i].Tangent[2] = mesh->mTangents[i].z;
                }
            }

            unsigned int* pIndices = nullptr;
            if (mesh->HasFaces()) {
                pIndices = new unsigned int[mesh->mNumFaces * 3];
                for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
                    pIndices[i * 3] = mesh->mFaces[i].mIndices[0];
                    pIndices[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
                    pIndices[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
                }
            }

            /*glGenVertexArrays(1, &VAO);

            GLuint VBO = 0;
            glGenBuffers(1, &VBO);

            GLuint IBO = 0;
            glGenBuffers(1, &IBO);

            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mesh->mNumVertices, pVertices, GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(0));
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(6 * sizeof(GLfloat)));

            glEnableVertexAttribArray(3);
            glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(8 * sizeof(GLfloat)));

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh->mNumFaces * 3, pIndices, GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(VAO);

            GLuint err = glGetError();
            if (err != GL_NO_ERROR) {
                std::cout << "GL ERROR: " << err << std::endl;
            }
            indicesCount = mesh->mNumFaces * 3;*/
			Mesh* meshObj = new Mesh(mesh->mNumFaces * 3);
            meshObj->setShader(shader);
            meshObj->createModel(pVertices, mesh->mNumVertices * sizeof(Vertex), pIndices, mesh->mNumFaces * 3);
			meshObj->setMaterial(materials[mesh->mMaterialIndex]);

			meshes.push_back(meshObj);

            delete[] pVertices;
            delete[] pIndices;
        }
    }
    else {
        printf("Error during parsing mesh from %s : %s \n", fileName.c_str(), importer.GetErrorString());
    }
    glBindVertexArray(0);
}

void ModelObject::setSkyBox()
{
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i]->setSkybox(true);
	}
}

void ModelObject::setCamera(Camera* camera)
{
	for (unsigned int i = 0; i < meshes.size(); i++)
	{

		meshes[i]->setProjection(camera->getProjectionMatrix());

		meshes[i]->setView(camera->getViewMatrix());
		meshes[i]->update();
	}
}

void ModelObject::setTexture(Texture* texture)
{
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i]->setTexture(texture);
	}
}

void ModelObject::setTransformation(Transformation* transformation)
{
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i]->setModel(transformation);
	}
}

void ModelObject::update()
{
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i]->update();
	}
}

//unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma)
//{
//	std::string filename = std::string(path);
//	filename = directory + '/' + filename;
//
//	unsigned int textureID;
//	glGenTextures(1, &textureID);
//
//	int width, height, nrComponents;
//	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
//	if (data)
//	{
//		GLenum format;
//		if (nrComponents == 1)
//			format = GL_RED;
//		else if (nrComponents == 3)
//			format = GL_RGB;
//		else if (nrComponents == 4)
//			format = GL_RGBA;
//
//		glBindTexture(GL_TEXTURE_2D, textureID);
//		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//		stbi_image_free(data);
//	}
//	else
//	{
//		std::cout << "Texture failed to load at path: " << path << std::endl;
//		stbi_image_free(data);
//	}
//
//	return textureID;
//}