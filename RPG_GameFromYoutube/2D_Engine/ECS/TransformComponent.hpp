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

	TransformComponent() { position.zero(); }
	TransformComponent(int sc) : scale(sc) { position.zero(); }
	TransformComponent(float x, float y) : position(Vector2D(x, y)) {}
	TransformComponent(float x, float y, int h, int w, int sc) 
			: position(Vector2D(x, y)), height(h), width(w), scale(sc) {}

	void init() override {
		velocity.zero();
	}

	void update() override {
		position.x = position.x + velocity.x * speed;
		position.y = position.y + velocity.y * speed;
	}

};