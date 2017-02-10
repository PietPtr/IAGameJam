#ifndef LINE_H
#define LINE_H
#pragma once
#include "Switch.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

enum Orientation { HORIZONTAL, VERTICAL };

class Line
{
public:
	Line(Vector2i coords);
	void draw(RenderWindow* window);
	void update();
	float getPower() { return power; }
protected:
private:
	Vector2i coords;

	float power = 0;
	const float MAX_POWER = 40;

    Orientation orientation = VERTICAL;

	std::array<Switch*, 2> switches;


};

#endif // !LINE_H
