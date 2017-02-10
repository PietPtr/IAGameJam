#ifndef LINE_H
#define LINE_H
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>


using namespace sf;

class Switch;

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
