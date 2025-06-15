#pragma once

#include "Components.hpp"
#include "../Vector2D.hpp"

class TransformComponent : public Component {
public:
	Vector2D position; 
	Vector2D velocity;

	int height = 32;
	int width = 32;
	int scale = 1;

	int speed = 3;

	TransformComponent() : position(Vector2D(0.0f, 0.0f)) {}
	TransformComponent(int sc) : position(Vector2D(0.0f, 0.0f)), scale(sc) {}
	TransformComponent(float x, float y) : position(Vector2D(x, y)) {}
	TransformComponent(float x, float y, int h, int w, int sc) 
			: position(Vector2D(x, y)), height(h), width(w), scale(sc) {}

	void init() override {
		velocity.x = 0;
		velocity.y = 0;
	}

	void update() override {
		position.x = position.x + velocity.x * speed;
		position.y = position.y + velocity.y * speed;
	}

};