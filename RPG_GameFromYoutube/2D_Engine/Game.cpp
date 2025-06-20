#include "Game.hpp"
#include "TextureManager.hpp"
#include "Map.hpp"
#include "ECS/Components.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"

Map* map;

bool Game::isRunning = false;

SDL_Renderer* Game::renderer = nullptr;

Manager manager;
SDL_Event Game::event;
SDL_Rect Game::camera = { 0, 0, 800, 640 };

auto& player(manager.addEntity());

Game::Game() { }

Game::~Game() { }

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

	map = new Map("assets/terrain_ss.png", 3, 32);
	map->loadMap("assets/map.map", 25, 20);
	
	player.addComponent<TransformComponent>(800, 640, 32, 32, 4);
	player.addComponent<SpriteComponent>("assets/player_anims.png", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(GROUP_PLAYERS);

}

auto& tiles(manager.getGroup(Game::GROUP_MAP));
auto& players(manager.getGroup(Game::GROUP_PLAYERS));
auto& colliders(manager.getGroup(Game::GROUP_COLLIDERS));

void Game::handleEvent() {
	
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
	SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
	Vector2D playerPos = player.getComponent<TransformComponent>().position;
	
	manager.refresh();
	manager.update();

	for (auto& c : colliders) {
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCol, playerCol)) {
			player.getComponent<TransformComponent>().position = playerPos;
		}
	}

	camera.x = player.getComponent<TransformComponent>().position.x - 400;
	camera.y = player.getComponent<TransformComponent>().position.y - 320;

	if (camera.x < 0)
		camera.x = 0;
	if (camera.y < 0)
		camera.y = 0;
	if (camera.x > camera.w)
		camera.x = camera.w;
	if (camera.y > camera.h)
		camera.y = camera.h;
}
	

void Game::render() {
	SDL_RenderClear(renderer);
	for (auto& t : tiles) {
		t->draw();
	}
	
	/* для отладки коллизий
	for (auto& c : colliders) {
		c->draw();
	}*/

	for (auto& p : players) {
		p->draw();
	}
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_RenderClear(renderer);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	std::cout << "Game cleaned..." << std::endl;
}