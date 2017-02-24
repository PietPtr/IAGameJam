#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <map>
#include "Audio.h"
#include "Switch.h"
#include "Line.h"
#include "Machine.h"

using namespace sf;

enum GameState { START, GAME, GAMEOVER };

class Game
{
    public:
        Game(RenderWindow* window);
        static Game* gameInstance;
        void initialize();
        void update();
        void draw();
        bool isWindowOpen();

        void loadAudio(std::vector<std::string> fileNames);
        void loadTextures(std::vector<std::string> fileNames);

        void fillRoutingPanel();
        void consoleLog(std::string sender, std::string text);
        void determineSelectedConnection(Vector2i coords);

        void drawStatus();

        int randint(int low, int high, int seed);
        int randint(int low, int high);

        std::string getPrettyMissionTime();
        std::string getHoustonStatusMessage();

        bool hasActiveComputer() { return activeComputer || state == START; }

        void takeScreenshot();
    protected:
    private:
        RenderWindow* window;

        GameState state = START;

        Time dt;
        Time totalTime;
        Time missionTime = seconds(65536);
        Time missiondt;
        const float TIME_MULTIPLIER = 60.0;

        Clock clock;
        int frame = 0;
        bool focus = true;

        int windowWidth = 1280;
        int windowHeight = 720;

        std::vector<std::string> audioFileNames { };
        std::vector<std::string> textureFileNames { "font.png", "bg.png", "switch.png", "buttonInput.png",     //0-3
            "buttonOutput.png", "buttonClose.png", "scanlines.png", "info.png", "gameover.png", "broken.png",  //4-9
            "Battery.png", "co2Remover.png", "ComputerOn.png", "ComputerOff.png", "light.png", "Heater.png",   //10-15
            "dish.png", "SolarPanel.png", "SolarPanelOff.png", "WaterPurifier.png", "switchSmall.png",         //16-20
            "batteryBig.png", "effectOverlay.png", "switchSmallOff.png", "switchOff.png", "portStatus.png",    //21-25
            "win.png"}; //26

        std::vector<Audio*> sfx;
        std::vector<Texture> textures;

        std::array<Line*, 62> lines;
        std::array<Switch*, 24> switches;
        std::array<Machine*, 24> machines;

        std::string log = "";

        Line* getLine(int x, int y);
        Line* getLine(Vector2i coords);

        Switch* selectedSwitch;

        // Status variables
        // used by the status screen
        float co2 = 402; // ppm
        float temperature = 18; // C
        float lights = 10;
        bool activeComputer = false;
        bool hasLink = false;
        float waterPurifier;

        // production/consuming variables
        float co2PerSecond = 4; // ppm per second
        float heatLeakage = 0.01;  // degree per second

        bool warnedTempHigh = false;
        bool warnedCO2 = false;
        bool warnedTempLow = false;

        std::string gameOverReason;

        Vector2i selectedCoord;

        std::map<MachineType, int> machineCountMax;
        Machine* createNewMachine(Vector2i coords);

        // This timer starts running the moment the player acquires a comm link with Houston.
        // After about 4 hours Houston will inform the player that a rocket will be launched
        // to save them. The player has to keep communication online for the launch to come through.
        bool rocketBeingPrepared = false;
        Time rocketPreparationTimeline = seconds(0);
        // After the rocket is launched, this timer starts running. The player needs to have a
        // comm link for the timer to continue. After 6 hours the rendezvous is complete and the
        // player is saved.
        bool rendezVousStarted = false;
        Time rendezvousTimeline = seconds(0);

        // Map with messages and times (in seconds) when the player should get them
        std::map<int, std::string> prepStatusMsgs = {
            { 30 * 60, "PREPARATION HAS STARTED, EVERYTHING IS GOING NOMINALLY. APPROX. 3 HOURS AND 30 MINUTES UNTIL LAUNCH"},
            { 60 * 60, "SPACECRAFT AND ROCKET ARE MATED. FULL STACK IS BEING TRANSPORTED TO THE LAUNCH PAD AS WE SPEAK. 3 HOURS UNTIL LAUNCH"},
            {120 * 60, "ROCKET IS VERTICAL. LAUNCH IN 2 HOURS."},
            {180 * 60, "FUELLING OF THE VEHICLE HAS BEGUN. LAST CHECKS OF THE SPACECRAFT ARE UNDERWAY. LAUNCH IN 1 HOUR."},
            {230 * 60, "ALL SYSTEMS NOMINAL. LAUNCHING IN 10 MINUTES."},
            {239 * 60, "1 MINUTE UNTIL LAUNCH."},
            {240 * 60, "AND LIFTOFFi WE ARE COMING TO GET YOU. IN SIX HOURS THE SPACECRAFT WILL ARRIVE. MAKE SURE YOU KEEP YOUR COMMUNICATIONS ONLINE DURING THOSE SIX HOURS OR WE WILL NOT KNOW WHERE YOU ARE."}
        };

        const int PREPTIME = 4 * 60 * 60;
        const int WINTIME = 10 * 60 * 60;
};
#endif
