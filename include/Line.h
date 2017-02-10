#ifndef LINE_H
#define LINE_H
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>

using namespace sf;

enum Orientation { HORIZONTAL, VERTICAL };

class Switch;

class Line
{
public:
	Line(Vector2i coords, std::array<Switch*, 2> switches);
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
