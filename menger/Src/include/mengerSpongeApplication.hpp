#ifndef SCENE_1__
#define SCENE_1__


#include <vector>
#include "graphicsApplicationABS.hpp"
#include "mengerScene.hpp"


class mengerSponge : public graphics
{
public:
    mengerSponge(const char* title, bool fullscreen = false, int width = 640, int height = 480)
        : graphics(title, fullscreen, width, height) {}
    ~mengerSponge();
    int init();
    void done();
    bool tick(const unsigned int timeDelta);
    void updateScene(const inputData& input);
    /* LastTimeCalled should be declared as a non globally scoped static
    variable. Scene should have already been range checked and be between
    [0, numberOfMengerScenes] */
    void updateToScene(const size_t scene, size_t& lastTimeCalled);
    void updateCamera(const unsigned int timeDelta, const inputData & input);
    void updateSpongeLevel(const inputData & input);
    void updateLights(const inputData& input);

private:
    bool quitApp = false;
    const int numberOfMengerScenes {6};
    int currentMengerScene {0};
    mengerScene * mengerScenes [6] {};
    enum scenes
    { // Enumerations start at 0 by default.
        scene1, scene2, scene3, scene4, scene5, scene6
    };
    camera cam;
    bool lightingEnabled {true};
    const int minPressRegisterInterval {125}; // For use with notCalledFor (in ms).


    inputData checkInput();
    void updateState(unsigned int timeDelta, const inputData & input);
    void renderFrame();
    void renderOSD();
};


#endif