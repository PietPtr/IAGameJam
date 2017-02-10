#include <SFML/Graphics.hpp>
#include "Game.h"

using namespace sf;

Game::Game(RenderWindow* _window)
{
    window = _window;
}

void Game::initialize()
{
    loadAudio(audioFileNames);
    loadTextures(textureFileNames);
    fillRoutingPanel();
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

    frame++;
}

void Game::draw()
{
    window->clear();

    for (int i = 0; i < lines.size(); i++)
    {
        lines[i]->draw(window);
    }

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

    //First 4.
    for (int x = 0; x < 4; x++)
    {
        lines[i] = new Line(Vector2i(x * 2, 2));
        i++;
    }

    //Create vertical lines.
    for (int y = 0; y < 6; y++) {
        for (int x = 0; x < 4; x++)
        {
            lines[i] = new Line(Vector2i(x * 2 + 1, 4 + y * 2));
            i++;
        }
    }

    //Create horizontal lines.
    for (int y = 0; y < 6; y++) {
        for (int x = 0; x < 5; x++)
        {
            lines[i] = new Line(Vector2i(x * 2, 5 + y * 2));
            i++;
        }
    }
}

int Game::randint(int low, int high)
{
    int value = rand() % (high + 1 - low) + low;
    srand(totalTime.asMicroseconds() * value * rand());

    return value;
}
