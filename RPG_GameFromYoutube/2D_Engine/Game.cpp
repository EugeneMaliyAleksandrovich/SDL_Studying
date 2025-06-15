#include "Game.hpp"
#include "TextureManager.hpp"
#include "Map.hpp"
#include "ECS/Components.hpp"
#include "Vector2D.hpp"

Map* map;

SDL_Renderer* Game::renderer = nullptr;

Manager manager;
auto& player(manager.addEntity());

Game::Game() {

}

Game::~Game() {

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystem initialised..." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) {
			std::cout << "Window is created..." << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer is created..." << std::endl;
		}

		isRunning = true;
	}
	else {
		isRunning = false;
	}

	map = new Map();
	
	player.addComponent<TransformComponent>();
	player.addComponent<SpriteComponent>("assets/player.png");
}

void Game::handleEvent() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			break;
	}
}

void Game::update() {
	manager.refresh();
	manager.update();
	player.getComponent<TransformComponent>().position.add(Vector2D(5.0));
	if (player.getComponent<TransformComponent>().position.x > 100)
		player.getComponent<SpriteComponent>().setTexture("assets/enemy.png");
}

void Game::render() {
	SDL_RenderClear(renderer);
	map->drawMap();
	manager.draw();
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_RenderClear(renderer);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	std::cout << "Game cleaned..." << std::endl;
}