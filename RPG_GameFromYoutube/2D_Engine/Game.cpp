#include "Game.hpp"
#include "TextureManager.hpp"
#include "Map.hpp"
#include "ECS/Components.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"

Map* map;

SDL_Renderer* Game::renderer = nullptr;

Manager manager;
SDL_Event Game::event;
std::vector<ColliderComponent*> Game::colliders;

auto& tile0(manager.addEntity());
auto& tile1(manager.addEntity());
auto& tile2(manager.addEntity());

auto& player(manager.addEntity());
auto& wall(manager.addEntity());

enum groupLabels : std::size_t {
	GROUP_MAP,
	GROUP_PLAYERS,
	GROUP_ENEMIES,
	GROUP_COLLIDERS
};
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
	map->loadMap("assets/16x16.map", 16, 16);
	
	player.addComponent<TransformComponent>();
	player.addComponent<SpriteComponent>("assets/player_anims.png", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(GROUP_PLAYERS);

	wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
	wall.addComponent<SpriteComponent>("assets/dirt.png");
	wall.addComponent<ColliderComponent>("wall");
	wall.addGroup(GROUP_MAP);

}

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
	manager.refresh();
	manager.update();

	for (auto c : colliders) {
		if (c->tag == "player")
			continue;
		Collision::AABB(player.getComponent<ColliderComponent>(), *c);
	}
}

auto& tiles(manager.getGroup(GROUP_MAP));
auto& players(manager.getGroup(GROUP_PLAYERS));
auto& enemies(manager.getGroup(GROUP_ENEMIES));

void Game::render() {
	SDL_RenderClear(renderer);
	for (auto& t : tiles) {
		t->draw();
	}
	for (auto& p : players) {
		p->draw();
	}
	for (auto& e : enemies) {
		e->draw();
	}
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_RenderClear(renderer);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	std::cout << "Game cleaned..." << std::endl;
}

void Game::addTile(int id, int x, int y) {
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(x, y, 32, 32, id);
	tile.addGroup(GROUP_MAP);
}