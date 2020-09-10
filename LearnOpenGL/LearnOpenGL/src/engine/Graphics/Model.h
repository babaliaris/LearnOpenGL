#ifndef ENGINE_MODEL_H
#define ENGINE_MODEL_H
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../Graphics.h"

namespace Engine
{
	class Application;

	class Model : public Graphics
	{

	public:
		Model(const std::string& name, const std::string& path);

	private:

		Application& m_app;

		std::string m_model_root;

		void processNode(aiNode* node, const aiScene* scene);

		std::vector<Texture*> GetTextures(aiMaterial* material);

	};
}

#endif

