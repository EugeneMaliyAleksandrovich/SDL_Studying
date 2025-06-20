#pragma once

extern "C" {
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
}
#include <iostream>
#include <vector>

class AssetManager;

class ColliderComponent;

class Game {
public:
	Game();
	~Game();

	void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvent();
	void update();
	void render();
	void clean();

	bool running() { return isRunning; }

	static SDL_Renderer* renderer;
	static SDL_Event event;
	static bool isRunning;
	static SDL_Rect camera;
	static AssetManager* assets;

	enum groupLabels : std::size_t {
		GROUP_MAP,
		GROUP_PLAYERS,
		GROUP_COLLIDERS,
		GROUP_PROJECTILES
	};

private:
	int cnt = 0;
	SDL_Window *window;
};