#pragma once

#include "Components.hpp"

class PositionComponent : public Component {
private:
	int xpos = 0;
	int ypos = 0;

public:
	PositionComponent() : xpos(0), ypos(0) {}
	PositionComponent(int x, int y) : xpos(x), ypos(y) {}

	int x() { return xpos; }
	int y() { return ypos; }

	void update() override {
		xpos++;
		ypos++;

	}

	void setPos(int x, int y) {
		xpos = x;
		ypos = y;
	}
};