//----------------------------------------------------------------------------
// RTRApp.cpp
//----------------------------------------------------------------------------
// Assignment 1 Starter Code
//----------------------------------------------------------------------------
// RMIT University, COSC1226: Real-Time Rendering and 3D Game Programming
//----------------------------------------------------------------------------
/* Must be defined before graphicsApplication.hpp is included as stb_image.h is
   included in graphicsApplication.hpp */
#define STB_IMAGE_IMPLEMENTATION
#include "include/graphicsApplicationABS.hpp"
#include "include/defs.hpp"


static constexpr char FILE_NAME [] {"graphicsApplicationABS.cpp"};


graphics::graphics(const char* title, bool fullscreen, int width, int height)
{
    mainWindowTitle = title;
    fullScreen = fullscreen;
    windowWidth = width;
    windowHeight = height;
    screenWidth = 0;
    screenHeight = 0;
    sDLWindow = nullptr;
    sDLRenderer = nullptr;
    gLContext = nullptr;
}


int graphics::init()
{
    constexpr char FUNC_NAME [] {"graphics::init()"};
    int ret {error::NONE};

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr<<"ERROR "<<error::genErrorLocationStr(FILE_NAME, FUNC_NAME)
            <<", ("<<SDL_GetError()<<"): SDL2 video subsystem couldn't be "
            "initialized.\n";

        ret = error::INIT_SDL_VIDEO_SUBSYSTEM;
    }
    else
    {
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

        if (fullScreen == true)
        {
            sDLWindow = SDL_CreateWindow(
                mainWindowTitle.c_str(),
                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                0, 0,
                SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
        }
        else
        {
            sDLWindow = SDL_CreateWindow(
                mainWindowTitle.c_str(),
                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                windowWidth, windowHeight,
                SDL_WINDOW_OPENGL);
        }

        sDLRenderer = SDL_CreateRenderer(sDLWindow, -1, SDL_RENDERER_ACCELERATED);
        if (sDLRenderer == nullptr)
        {
            std::cerr << "ERROR " << error::genErrorLocationStr(FILE_NAME, FUNC_NAME)
                << ", (" << SDL_GetError() << "): SDL2 Renderer couldn't be created.\n";
            ret = error::INIT_SDL_RENDERER;
        }
        else
        {
            gLContext = SDL_GL_CreateContext(sDLWindow);

            if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
            {
                std::cerr << "ERROR " << error::genErrorLocationStr(FILE_NAME, FUNC_NAME)
                    << ": Failed to initialize the OpenGL context.\n";
                ret = error::INIT_OPENGL_CONTEXT;
            }
            else
            {
                SDL_DisplayMode dm;
                if (SDL_GetCurrentDisplayMode(0, &dm) == 0)
                {
                    screenWidth = dm.w;
                    screenHeight = dm.h;
                    if (fullScreen == true)
                    {
                        windowWidth = screenWidth;
                        windowHeight = screenHeight;
                    }
                    /*if (SDL_CaptureMouse(SDL_TRUE))
                    {
                        error::genError(error::INIT_GENERAL, "Error ",
                                        error::genErrorLocationStr(FILE_NAME, FUNC_NAME),
                                        ", (", SDL_GetError(),
                                        "): SDL_CaptureMouse() failed to capture mouse \n");
                    }*/
                    /* ATTENTION! ATTENTION! ATTENTION! ATTENTION! ATTENTION!
                    Update the comment in the camera constructor in camera.hpp
                    if we change this function call */
                    if (SDL_SetRelativeMouseMode(SDL_TRUE))
                    {
                        std::cerr<<"Error "
                            <<error::genErrorLocationStr(FILE_NAME, FUNC_NAME)
                            <<", ("<<SDL_GetError()
                            <<"): SDL_SetRelativeMouseMode() failed to capture "
                            "mouse \n";
                        ret = error::INIT_GENERAL;
                    }
                }
                else
                {
                    std::cerr << "WARNING " << error::genErrorLocationStr(FILE_NAME, FUNC_NAME)
                        << ": SDL coudn't retrieve current display mode details.\n";
                }

                std::cout<<"MESSAGE: OpenGL version "<<GLVersion.major
                    <<"."<<GLVersion.minor<<" initialised.\n";
            }
        }
    }

    return ret;
}


void graphics::run()
{
    bool terminateProgram = false;
    while (terminateProgram == false)
    {
        static unsigned int lastTime = 0;
        unsigned int currentTime = SDL_GetTicks();
        unsigned int timeDelta = currentTime - lastTime; // Time since last frame.
        lastTime = currentTime;
        terminateProgram = tick(timeDelta);
    }
}


void graphics::done()
{
    SDL_GL_DeleteContext(gLContext);
    SDL_DestroyRenderer(sDLRenderer);
    SDL_DestroyWindow(sDLWindow);
    SDL_Quit();
    sDLWindow = nullptr;
    sDLRenderer = nullptr;
    gLContext = nullptr;
}
