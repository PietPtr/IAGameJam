#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>
#include <iomanip> // setprecision
#include <sstream> // stringstream

using namespace sf;
int main()
{
    srand(time(NULL));

    RenderWindow window(VideoMode(856, 720), "Float");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    Game game(&window);

    game.initialize();

    while (window.isOpen())
    {
        game.update();
        game.draw();
    }

    return 0;
}

// From: https://github.com/PietPtr/MiniLD59/blob/e3a48ab02b22124b886a0d8442a6ea8e8fe0d839/src/main.cpp
int drawString(RenderWindow* window, std::string text, Vector2f position, Texture* fontTexture, Color color, int newLine)
{
    bool shouldStartNewLine = false;

    int lines = 1;

    int drawY = position.y;
    int drawX = position.x;

    int letterWidth = 5;
    int letterHeight = 7;

    int charactersSinceNewline = 0;
    for (int i = 0; i < text.length(); i++)
    {
        int num = (int)(text[i]);

        Sprite charSprite;
        charSprite.setTexture(*fontTexture);

        drawX += letterWidth + 1;

        if (num >= 48 && num <= 57)
            charSprite.setTextureRect(IntRect((num - 48) * letterWidth, 0, letterWidth, letterHeight));
        else if (num >= 65 && num <= 90)
            charSprite.setTextureRect(IntRect((num - 55) * letterWidth, 0, letterWidth, letterHeight));
        else if (num >= 97 && num <= 122)
            charSprite.setTextureRect(IntRect((num - 61) * letterWidth, 0, letterWidth, letterHeight));
        else if (num == 58)
            charSprite.setTextureRect(IntRect(62 * letterWidth, 0, letterWidth, letterHeight));
        else if (num == 46)
            charSprite.setTextureRect(IntRect(63 * letterWidth, 0, letterWidth, letterHeight));
        else if (num == 44)
            charSprite.setTextureRect(IntRect(64 * letterWidth, 0, letterWidth, letterHeight));
        else if (num == 32)
            charSprite.setTextureRect(IntRect(66 * letterWidth, 0, letterWidth, letterHeight));
        else if (num == 45)
            charSprite.setTextureRect(IntRect(67 * letterWidth, 0, letterWidth, letterHeight));
        else if (num == 39)
            charSprite.setTextureRect(IntRect(68 * letterWidth, 0, letterWidth, letterHeight));
        else if (num == 38)
        {
            shouldStartNewLine = true;
            charSprite.setTextureRect(IntRect(66 * letterWidth, 0, letterWidth, letterHeight));
        }
        else
            charSprite.setTextureRect(IntRect(65 * letterWidth, 0, letterWidth, letterHeight));

        charSprite.setColor(color);
        charSprite.setPosition(Vector2f(drawX, drawY));
        window->draw(charSprite);

        charactersSinceNewline++;

        if (newLine != -1 && charactersSinceNewline % newLine == 0 && i != 0)
        {
            shouldStartNewLine = true;
        }
        if (shouldStartNewLine && num == 32)
        {
            shouldStartNewLine = false;
            drawY += letterHeight + 4;
            drawX = position.x;
            charactersSinceNewline = 0;
            lines++;
        }
    }
    return lines;
}

std::string floatToString(float value, int precision)
{
    std::stringstream stream;
    stream << std::fixed << std::setprecision(precision) << value;
    std::string valueStr = stream.str();
    return valueStr;
}
