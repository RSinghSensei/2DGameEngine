#pragma once
#include "../ECS/ECS.h"
#include "../Components/SpriteComponent.h"
#include "../Components/ObjTransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../ResourceManager/ResourceManager.h"
#include <SDL.h>
#include <SDL_image.h>

class RenderSystem: public System
{
public:
	RenderSystem()
	{
		addComponentRequirement<SpriteComponent>();
		addComponentRequirement<ObjTransformComponent>();
		addComponentRequirement<RigidBodyComponent>();
	}


	void update(SDL_Renderer* renderer, std::unique_ptr<ResourceManager>& resourcemanager)
	{
		for (auto& x : getEntityList())
		{
			const ObjTransformComponent& transformComponent = x.getComponent<ObjTransformComponent>();
			const SpriteComponent sprite_Component = x.getComponent<SpriteComponent>();

			/*SDL_Surface* s1 = IMG_Load(sprite_Component.imgPath);
			SDL_Texture* t1 = SDL_CreateTextureFromSurface(renderer, s1);
			SDL_FreeSurface(s1);*/

			SDL_Rect p1{ (int)transformComponent.pos.x, (int)transformComponent.pos.y, sprite_Component.imgDimensions.x, sprite_Component.imgDimensions.y};
			SDL_RenderCopy(renderer, resourcemanager->getTexture(sprite_Component.spriteTex), NULL, &p1);

			Logger::sLog("Entity ID: " + std::to_string(x.getID()) + " moved to " + std::to_string(transformComponent.pos.x) + " " + std::to_string(transformComponent.pos.y));


		}
	}


};