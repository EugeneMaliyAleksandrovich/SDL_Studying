#pragma once

#include "Components.hpp"
#include "../Vector2D.hpp"

class TransformComponent : public Component {
public:
	Vector2D position; 

	TransformComponent() : position(Vector2D(0.0f, 0.0f)) {}
	TransformComponent(float x, float y) : position(Vector2D(x, y)) {}

	void update() override {
		
	}

};