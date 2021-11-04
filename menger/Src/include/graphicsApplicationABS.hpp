//-----------------------------------------------------------------------------
// RTRApp.h
//-----------------------------------------------------------------------------
// Assignment 1 Starter Code
//-----------------------------------------------------------------------------
// RMIT University, COSC1226: Real-Time Rendering and 3D Game Programming
//-----------------------------------------------------------------------------
#ifndef MENGER_SPONGE_HPP__
#define MENGER_SPONGE_HPP__


#include <string>
#include <iostream>
#include <glad/glad.h>
#include <sdl/SDL.h>
#include <stb/stb_image.h>

class graphics
{
public:
    graphics(const char* title, bool fullscreen = false, int width = 1024, int height = 768);
    virtual int init();
    virtual void done();
    virtual void run();
    virtual bool tick(unsigned int timeDelta) = 0;
    //SDL_Window * getSDLWindow() {return sDLWindow;}

protected:
    struct inputData
    {
        const Uint8 * keys{};
        int x {}, y {}; // For mouse.
        Uint32 mouseButtons{};
    };

public:
    virtual void updateCamera(unsigned int timeDelta, const inputData & input) = 0;

protected:
    std::string mainWindowTitle;
    bool fullScreen;
    int windowWidth;
    int windowHeight;
    int screenWidth;
    int screenHeight;
    SDL_Window * sDLWindow;
    SDL_Renderer * sDLRenderer;
    SDL_GLContext gLContext;
};


#endif