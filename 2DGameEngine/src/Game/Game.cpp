#include "Game.h"
#include <iostream>
#include <glm/glm.hpp>

Game::Game(){}

Game::~Game()
{
	SDL_DestroyRenderer(engineRenderer);
	SDL_DestroyWindow(engineWindow);
	SDL_Quit();
}


// Set up window
void Game::Initialize()
{
	// Call SDL
	if (SDL_Init(SDL_INIT_EVERYTHING)) { std::cout << "Failed to initialize SDL library" << std::endl; return; }
	engineWindow = SDL_CreateWindow("2D Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	//if (!engineWindow) { std::cout << "Failed to create window" << std::endl; return; }
	if (!engineWindow) { Logger::Error("Failed to create window"); return; }

	// Renderer time
	engineRenderer = SDL_CreateRenderer(engineWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!engineRenderer) { Logger::Error("Failed to create render"); return; }

	engineRunning = SDL_TRUE;

	//SDL_SetWindowFullscreen(engineWindow, SDL_WINDOW_FULLSCREEN);

	// SDL Version Display
	SDL_version versionCheck{};
	SDL_GetVersion(&versionCheck);

	//std::cout << "SDL Version " << (unsigned int)versionCheck.major << " " << (unsigned int)versionCheck.minor << " " << (unsigned int)versionCheck.patch << std::endl;
	Logger::sLog("SDL Version  " + std::to_string((unsigned int)versionCheck.major) + " " + std::to_string((unsigned int)versionCheck.minor) + " " + std::to_string((unsigned int)versionCheck.patch));

	Logger::Log("Pre-Loading Done!");

	Registry mainRegistry;
	registry = &mainRegistry;

	Logger::Log("Registry Active");

}



void Game::Run()
{

	Setup();
	while (engineRunning) {
		inputPolling();
		updateWorld();
		Render();

	}

}

void Game::inputPolling() 
{	
	SDL_Event allEvents;
	while (SDL_PollEvent(&allEvents)) {
		switch (allEvents.type) {
			
		case SDL_QUIT:
			engineRunning = SDL_FALSE;
			break;

		case SDL_KEYDOWN:
			if (allEvents.key.keysym.sym == SDLK_ESCAPE) { engineRunning = SDL_FALSE; break; }
		}

		

	}



}

float xpos = 40.0f, ypos = 90.0f, xvel = 50.0f, yvel = 10.0f;
glm::vec2 playerpos(xpos, ypos);

void Game::updateWorld()
{	
	// Cap frame rate, allow control to 16ms per frame
	// SDL Delay is CPU friendly, will offload to scheduler upon function call
	int offloadTime = ms_per_frame - (SDL_GetTicks() - ms_last_frame);
	if (offloadTime > 0 && offloadTime <= ms_per_frame) { SDL_Delay(offloadTime); }

	// Now for delta time

	double dt = (SDL_GetTicks() - ms_last_frame)/ 1000.0;


	ms_last_frame = SDL_GetTicks();


	playerpos.x += xvel * dt;
	playerpos.y += yvel * dt;




}


void Game::Render()
{
	SDL_SetRenderDrawColor(engineRenderer, 137, 207, 240, 255);
	// Clears the entire render screen, forming the backbuffer right now
	SDL_RenderClear(engineRenderer);

	// Here we'll implement all our render calls, drawing objects etc.
	// Temp. texture load

	SDL_Surface* s1 = IMG_Load("./assets/images/tank-tiger-right.png");
	SDL_Texture* t1 = SDL_CreateTextureFromSurface(engineRenderer, s1);
	SDL_FreeSurface(s1);

	SDL_Rect p1{ (int)playerpos.x, (int)playerpos.y, 32, 32 };
	SDL_RenderCopy(engineRenderer, t1, NULL, &p1);
	SDL_DestroyTexture(t1);

	// Final call, where we've completed the backbuffer
	// This'll swap
	SDL_RenderPresent(engineRenderer);


}

void Game::Setup()
{
	registry->addSystem<MovementSystem>();

	Entity tigerTank = registry->createEntity();
	Entity pantherTank = registry->createEntity();
	// We're going to add components to the entity
	// Call registry, addComponent, will modify bitset
	// Then add to systems, and bam, we're done

	registry->addComponent<ObjTransformComponent>(tigerTank, glm::vec3(40.0f, 90.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), 0.0f);
	registry->addComponent<RigidBodyComponent>(tigerTank, glm::vec2(50.0f, 10.0f));
	
	registry->addComponent<ObjTransformComponent>(pantherTank);
	registry->addComponent<RigidBodyComponent>(pantherTank);

	//tigerTank.addComponent<ObjTransformComponent>(glm::vec3(40.0f, 90.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), 0.0f);
	//tigerTank.addComponent<RigidBodyComponent>(glm::vec2(50.0f, 10.0f));
	/*pantherTank.addComponent<ObjTransformComponent>();
	pantherTank.addComponent<RigidBodyComponent>();*/


	//registry->getSystem<MovementSystem>().updateMS();

}