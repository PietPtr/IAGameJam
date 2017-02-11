#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Audio.h"
#include "Switch.h"
#include "Line.h"
#include "Machine.h"

using namespace sf;

class Game
{
    public:
        Game(RenderWindow* window);
        void initialize();
        void update();
        void draw();
        bool isWindowOpen();

        void loadAudio(std::vector<std::string> fileNames);
        void loadTextures(std::vector<std::string> fileNames);

        void fillRoutingPanel();
        void consoleLog(std::string text);
        void determineSelectedConnection(Vector2i coords);

        void drawStatus();

        int randint(int low, int high, int seed);
        int randint(int low, int high);

        std::string getPrettyMissionTime();
    protected:
    private:
        RenderWindow* window;

        Time dt;
        Time totalTime;
        Time missionTime = seconds(65536);
        const float TIME_MULTIPLIER = 10.0;

        Clock clock;
        int frame = 0;
        bool focus = true;

        int windowWidth = 1280;
        int windowHeight = 720;

        std::vector<std::string> audioFileNames { };
        std::vector<std::string> textureFileNames { "font.png", "bg.png", "switch.png", "buttonInput.png",
            "buttonOutput.png", "buttonClose.png", "temperature.png", "scanlines.png"};

        std::vector<Audio*> sfx;
        std::vector<Texture> textures;

        std::array<Line*, 64> lines;
        std::array<Switch*, 24> switches;
        std::array<Machine*, 22> machines;

        std::string log = "";

        Line* getLine(int x, int y);
        Line* getLine(Vector2i coords);

        Switch* selectedSwitch;

        /*ppm*/
        int co2 = 402;
        /*Celcius*/
        float temperature = 18;

        float lights;
        /*If true we show the information panel*/
        bool showInfo;

        bool hasLink = true;

        float waterPurifier;
};
#endif
