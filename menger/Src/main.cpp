//-----------------------------------------------------------------------------
// main.cpp
//-----------------------------------------------------------------------------
// Assignment 1 Starter Code
//-----------------------------------------------------------------------------
// RMIT University, COSC1226: Real-Time Rendering and 3D Game Programming
//-----------------------------------------------------------------------------
#include <iostream>
//#include "include/graphicsApplicationABS.hpp"
//#include "include/shader.hpp"
#include "include/mengerSpongeApplication.hpp"
#include "include/defs.hpp"
//#define GLT_IMPLEMENTATION
//#include <gltext/gltext.h>


static constexpr char FILE_NAME[]{ "main.cpp" };


//void openGLTutorialStuff();


int main(int argc, char** argv)
{
    constexpr char FUNC_NAME [] {"main()"};
    mengerSponge * menger = new mengerSponge(GRAPHICS_WIN_TITLE, true);

	{
        int err {};
        if((err = menger->init()) != error::NONE)
        {
        error:genError(error::INIT_GENERAL, "ERROR ",
            error::genErrorLocationStr(FILE_NAME, FUNC_NAME),
            ", (", err, "): Failed to initialise application.\n");
        }
    }

    menger->run();
    menger->done();
    return 0;
}