#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "../Logger/Logger.h"
#include <glm/glm.hpp>
#include "../ECS/ECS.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/ObjTransformComponent.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/Render.h"
#include "../ResourceManager/ResourceManager.h"

class Game {
public:
	// Game defines the entry point to our engine
	Game();
	~Game();
	
	void Initialize();
	void Setup();
	void Run();
	void inputPolling();
	void updateWorld();
	void Render();
	

private:
	int width{800};
	int height{600};
	SDL_Window* engineWindow = nullptr;
	SDL_Renderer* engineRenderer = nullptr;
	SDL_bool engineRunning = SDL_FALSE;

	const int FPS = 60;
	const int ms_per_frame = 1000 / FPS;
	int ms_last_frame = 0;

	std::unique_ptr<Registry> registry;
	std::unique_ptr<ResourceManager> resourcemanager;

};
