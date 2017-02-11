#ifndef SOLARPANEL_H
#define SOLARPANEL_H
#pragma once
#include "Audio.h"
#include "Line.h"
#include "Machine.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Line;

class SolarPanel : public Machine
{
public:
	SolarPanel(Vector2i coords);
	void setLine(Line* line);
	void update(Time dt);
	void draw(RenderWindow* window);
	float getPowerForLine(Line* line);
protected:
};

#endif
