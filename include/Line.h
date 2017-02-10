#ifndef LINE_H
#define LINE_H
#pragma once
#include "Switch.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Switch.h


using namespace sf;

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
	float power;
	const float MAX_POWER = 40;
	std::array<Switch*, 2> switches;

};

#endif // !LINE_H
