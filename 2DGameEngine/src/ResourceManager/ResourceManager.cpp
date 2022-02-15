#include "ResourceManager.h"


ResourceManager::ResourceManager() { Logger::Log("Resource Manager Active"); }
ResourceManager::~ResourceManager() { Logger::Log("Resource Manager Inactive"); }

void ResourceManager::addTexture(SDL_Renderer* renderer, const std::string& assetName, const std::string& assetPath)
{
	SDL_Surface* s1 = IMG_Load(assetPath.c_str());
	SDL_Texture* t1 = SDL_CreateTextureFromSurface(renderer, s1);
	SDL_FreeSurface(s1);
	textureMap.insert(std::map<std::string, SDL_Texture*>::value_type(assetName, t1));


}

void ResourceManager::clearAssets()
{
	textureMap.clear();

}

SDL_Texture* ResourceManager::getTexture(const std::string& assetName)
{
	if (textureMap.count(assetName)) { return textureMap.at(assetName); }
	else { return nullptr; }

}


