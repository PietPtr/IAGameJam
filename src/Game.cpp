#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace sf;

void drawString(RenderWindow* window, std::string text, Vector2f position, Texture* fontTexture, Color color, int newLine);


Game::Game(RenderWindow* _window)
{
    window = _window;
}

void Game::initialize()
{
    loadAudio(audioFileNames);
    loadTextures(textureFileNames);
    // code throws errors, can't test with it
    //fillRoutingPanel();
    consoleLog("TEST");
    consoleLog("ANOTHER TEST");
}

void Game::update()
{
    Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();
        if (event.type == Event::KeyPressed)
        {
            if (event.key.code == Keyboard::Escape)
            {
                window->close();
            }
        }
        if (event.type == Event::LostFocus) {
            focus = false;
        }
        if (event.type == Event::GainedFocus) {
            focus = true;
        }

        if (event.type == Event::Resized) {
            windowWidth = event.size.width;
            windowHeight = event.size.height;
        }
    }

    dt = clock.restart();
    totalTime += dt;
    missionTime += dt * TIME_MULTIPLIER;

    if (frame % 120 == 0)
    {
        consoleLog("PING");
    }


    frame++;
}

void Game::draw()
{
    window->clear();

    Sprite bgSprite;
    bgSprite.setTexture(textures.at(1));
    window->draw(bgSprite);

    for (int i = 0; i < lines.size(); i++)
    {
        // coords where undefined and giving segfaults, uncomment when needed again
        //lines[i]->draw(window);
    }

    drawString(window, log, Vector2f(498,341), &textures.at(0), Color(0, 200, 0), 47);

    window->display();
}

bool Game::isWindowOpen()
{
    return window->isOpen();
}

void Game::loadAudio(std::vector<std::string> audioFileNames)
{
    for (int i = 0; i < audioFileNames.size(); i++)
    {
        sfx.push_back(new Audio());
        sfx.back()->init(audioFileNames[i]);
    }
}

void Game::loadTextures(std::vector<std::string> textureFileNames)
{
    for (int i = 0; i < textureFileNames.size(); i++)
    {
        Texture texture;
        std::string path = "textures/" + textureFileNames.at(i);
        if (!texture.loadFromFile(path)) {
            window->close();
        }
        textures.push_back(texture);
        std::cout << "Loaded " << path << "\n";
    }
}

void Game::fillRoutingPanel() {
    int i = 0;
    int j = 0;

    //First 4 switches
    for (int x = 0; x < 4; x++)
    {
        switches[j] = new Switch(Vector2i(x*2, 1));
        j++;
    }

    //First 4 lines.
    for (int x = 0; x < 4; x++)
    {
        lines[i] = new Line(Vector2i(x * 2, 2), {});
        i++;
    }

    //Create vertical lines.
    for (int y = 0; y < 6; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            lines[i] = new Line(Vector2i(x * 2 + 1, 4 + y * 2), {});
            i++;
        }
    }

    //Create horizontal lines.
    for (int y = 0; y < 6; y++)
    {
        for (int x = 0; x < 5; x++)
        {
            lines[i] = new Line(Vector2i(x * 2, 5 + y * 2), {});
            i++;
        }
    }

    //Create all other switches
    for (int y = 0; y < 5; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            switches[j] = new Switch(Vector2i(x * 2, y * 2 + 5));
            j++;
        }
    }
}

void Game::consoleLog(std::string text)
{
    log += getPrettyMissionTime() + " " + text + "& ";
}

std::string Game::getPrettyMissionTime()
{

    std::string result = "";
    int missionSeconds = missionTime.asSeconds();

    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0')
       << (int)(missionTime.asSeconds() / 60 / 60) << ":"
       << std::setw(2) << std::setfill('0')
       << (int)(missionTime.asSeconds() / 60) % 60 << ":"
       << std::setw(2) << std::setfill('0')
       << ((int)(missionTime.asSeconds()) % 60);

    return ss.str();
}

int Game::randint(int low, int high)
{
    int value = rand() % (high + 1 - low) + low;
    srand(totalTime.asMicroseconds() * value * rand());

    return value;
}
