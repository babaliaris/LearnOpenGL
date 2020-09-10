#include "pch.h"
#include "Model.h"
#include "../Core.h"
#include "../Application.h"


namespace Engine
{
	Model::Model(const std::string& name, const std::string& path)
		: Graphics(name.c_str(), path.c_str(), "src/engine/Shaders/Model.vert", "src/engine/Shaders/Model.frag"),
		m_app(Application::Get())
	{

		std::string full_path = std::string(RUNTIME_DIR) + path;

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(full_path, aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_FlipUVs);

		ASSERT(scene, "aiScene should not be null. Probably the path is wrong");

		m_model_root = path.substr(0, path.find_last_of('/'));

		this->processNode(scene->mRootNode, scene);
	}




	void Model::processNode(aiNode* node, const aiScene* scene)
	{
		//For each mesh of this node.
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

			std::vector<Vertex> vertices;
			std::vector<unsigned int> indices;

			//For each vertex of this mesh.
			for (unsigned int j = 0; j < mesh->mNumVertices; j++)
			{
				Vertex new_vertex;

				new_vertex.position.x = mesh->mVertices[j].x;
				new_vertex.position.y = mesh->mVertices[j].y;
				new_vertex.position.z = mesh->mVertices[j].z;

				new_vertex.normals.x = mesh->mNormals[j].x;
				new_vertex.normals.y = mesh->mNormals[j].y;
				new_vertex.normals.z = mesh->mNormals[j].z;

				if (mesh->mTextureCoords[0])
				{
					new_vertex.textCoords.x = mesh->mTextureCoords[0][j].x;
					new_vertex.textCoords.y = mesh->mTextureCoords[0][j].y;
				}

				vertices.push_back(new_vertex);
			}

			//For each face of this mesh.
			for (unsigned int j = 0; j < mesh->mNumFaces; j++)
			{
				aiFace face = mesh->mFaces[j];

				//For each index.
				for (unsigned int k = 0; k < face.mNumIndices; k++)
				{
					indices.push_back(face.mIndices[k]);
				}
			}

			//Get the textures.
			aiMaterial *mat = scene->mMaterials[mesh->mMaterialIndex];
			std::vector<Texture*> textures = this->GetTextures(mat);

	
			CREATE_MODEL_MESH(vertices, indices, textures);

		}

		//Process the rest of the children.
		for (unsigned int i = 0; i < node->mNumChildren; i++)
			this->processNode(node->mChildren[i], scene);
	}



	std::vector<Texture*> Model::GetTextures(aiMaterial* material)
	{
		std::vector<Texture*> textures;

		unsigned int diffuse_count  = material->GetTextureCount(aiTextureType_DIFFUSE);
		unsigned int specular_count = material->GetTextureCount(aiTextureType_SPECULAR);

		for (unsigned int i = 0; i < diffuse_count; i++)
		{
			aiString path;
			material->GetTexture(aiTextureType_DIFFUSE, i, &path);

			std::string full_path = m_model_root + "/" + path.C_Str();

			textures.push_back( m_app.CreateTexture(full_path) );
		}


		for (unsigned int i = 0; i < specular_count; i++)
		{
			aiString path;
			material->GetTexture(aiTextureType_SPECULAR, i, &path);

			std::string full_path = m_model_root + "/" + path.C_Str();

			textures.push_back(m_app.CreateTexture(full_path, "specular"));
		}

		return textures;
	}
}