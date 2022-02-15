#pragma once
#include <map>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "../Logger/Logger.h"

class ResourceManager
{

public:

	ResourceManager();
	~ResourceManager();

	void clearAssets();
	void addTexture(SDL_Renderer* renderer, const std::string& assetName, const std::string& assetPath);
	SDL_Texture* getTexture(const std::string& assetName);

private:
	std::map<std::string, SDL_Texture*>textureMap;


};