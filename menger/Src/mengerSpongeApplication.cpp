#include "include/mengerSpongeApplication.hpp"
#define GLT_IMPLEMENTATION
#include <gltext/gltext.h>
#include <chrono>
//#include <glad/glad.h>
#include "include/defs.hpp"
#include "include/mengerScene1.hpp"
#include "include/mengerScene2.hpp"
#include "include/mengerScene3.hpp"
#include "include/mengerScene4.hpp"
#include "include/mengerScene5.hpp"
#include "include/mengerScene6.hpp"
//#include "include/shader.hpp"
#include "include/camera.hpp"


static constexpr char FILE_NAME [] {"mengerSpongeApplication.cpp"};


mengerSponge::~mengerSponge()
{
	for (auto scene : mengerScenes)
	{
		std::cout << "type of scene = " << typeid(scene).name() << '\n';
		delete scene;
	}
}


int mengerSponge::init()
{
	static constexpr char FUNC_NAME [] {"mengerSpongeApplication.cpp"};
	int ret{ error::NONE };

	if (int err = graphics::init() != 0)
	{
		ret = err;
	}
	else
	{
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);
		glFrontFace(GL_CCW);

		// Lighting...
		glEnable(GL_LIGHTING);
/*		lightingEnabled = true;
		glEnable(GL_LIGHTING);

		GLfloat global_ambient [] = { 0.1f, 0.05f, 0.3f, 1.0f };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient); // Set global ambient light model.

		glShadeModel(GL_SMOOTH); // Set shading model.
		
		// Specify light0.
		GLfloat ambient [] = {0.025f, 0.15f, 0.015f};
		GLfloat diffuse [] = {0.25f, 0.45f, 0.1f};
		GLfloat specular [] = {0.2f, 0.3f, 0.15f , 0.1f};
		GLfloat position[] = { -1.6f, 1.5f, 2.0f, 1.0f };
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
		glLightfv(GL_LIGHT0, GL_POSITION, position);
		// Enable light0.
	glEnable(GL_LIGHT0); */


		// Enable color tracking (allows us to set material using glColor3f();
		glEnable(GL_COLOR_MATERIAL);
		// Set specular exponent. The range is [1,128].
		glMateriali(GL_FRONT, GL_SHININESS, 1);

		//glMatrixMode(GL_PROJECTION);

		/* mainWindowTitle = title;
    fullScreen = fullscreen;
    windowWidth = width;
    windowHeight = height;
    screenWidth = 0;
    screenHeight = 0;
    sDLWindow = nullptr;
    sDLRenderer = nullptr;
    gLContext = nullptr;*/

//		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			// specify implementation-specific hints
//		gluPerspective(90, this->screenWidth / this->screenHeight, 0.05, 1.0);

		//		glMatrixMode(GL_PROJECTION);        // select projection matrix
		//        glViewport(0, 0, this->windowWidth, this->windowHeight);    // set the viewport
		//        glMatrixMode(GL_PROJECTION);        // set matrix mode
		//		glLoadIdentity();					// reset projection matrix
		//        GLfloat aspect = (GLfloat)this->windowWidth / this->windowHeight;
		//        gluPerspective(win.field_of_view_angle, aspect, win.z_near, win.z_far);		// set up a perspective projection matrix
		//        glMatrixMode(GL_MODELVIEW);			// specify which matrix is the current matrix
		//        glShadeModel(GL_SMOOTH);
		//        glClearDepth(1.0f);					// specify the clear value for the depth buffer
		//        glEnable(GL_DEPTH_TEST);
		//        glDepthFunc(GL_LEQUAL);
		//        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			// specify implementation-specific hints
		//        glClearColor(0.0, 0.0, 0.0, 1.0);

				// DON'T DELETE ME!!!!!!!!!!!!!
		gltInit();

		mengerScenes[0] = (new mengerScene1());
		mengerScenes[1] = (new mengerScene2());
		mengerScenes[currentMengerScene]->init();

		//cam.init(sDLWindow);
	}

	return ret;
}


void mengerSponge::done()
{
	gltTerminate();
	graphics::done();
}


bool mengerSponge::tick(unsigned int timeDelta)
{
    quitApp = false;
    updateState(timeDelta, checkInput());
    renderFrame();
    return quitApp;
}


void mengerSponge::updateScene(const inputData & input)
{
	if (input.keys[SDL_SCANCODE_1])
	{
		static size_t lastTimeCalled{};
		updateToScene(scene1, lastTimeCalled);
	}
	else
	{
		if (input.keys[SDL_SCANCODE_2])
		{
			static size_t lastTimeCalled{};
			updateToScene(scene2, lastTimeCalled);
		}
		else
		{
			if (input.keys[SDL_SCANCODE_3])
			{
				static size_t lastTimeCalled{};
				updateToScene(scene3, lastTimeCalled);
			}
			else
			{
				if (input.keys[SDL_SCANCODE_4])
				{
					static size_t lastTimeCalled{};
					updateToScene(scene4, lastTimeCalled);
				}
				else
				{
					if (input.keys[SDL_SCANCODE_5])
					{
						static size_t lastTimeCalled{};
						updateToScene(scene5, lastTimeCalled);
					}
					else
					{
						if (input.keys[SDL_SCANCODE_6])
						{
							static size_t lastTimeCalled{};
							updateToScene(scene6, lastTimeCalled);
						}
					}
				}
			}
		}
	}
}


void mengerSponge::updateToScene(const size_t scene, size_t & lastTimeCalled)
{
	if (notCalledFor(minPressRegisterInterval, lastTimeCalled))
	{
		if (currentMengerScene != scene)
		{
			std::cout<<"Switching to scene "<<scene +1<<".\n";
			//mengerScenes[currentMengerScene]->unInit();
			currentMengerScene = scene;
			mengerScenes[currentMengerScene]->init();
			std::cout<<"Switched to scene "<<scene +1<<".\n";
		}
		else
		{
			std::cout<<"Already displaying scene "<<scene +1<<".\n";
		}
	}
	lastTimeCalled = SDL_GetTicks();
}


void mengerSponge::updateCamera(const unsigned int timeDelta,
								const inputData & input)
{
	/* Move the cammera in space if a movement key(WASD) is pressed(multiply
	timeDelta if by multiplier if shift is pressed(yes this is a little hacky.) */
	// Move at super penta speed if shift is pressed.
	const int multiplier{ input.keys[SDL_SCANCODE_LSHIFT] ? 5 : 1};
	if (input.keys[SDL_SCANCODE_W])
	{
		cam.forward(milliToS(timeDelta * multiplier));
	}
	if (input.keys[SDL_SCANCODE_S])
	{
		cam.backward(milliToS(timeDelta * multiplier));
	}
	if (input.keys[SDL_SCANCODE_A])
	{
		cam.left(milliToS(timeDelta * multiplier));
	}
	if (input.keys[SDL_SCANCODE_D])
	{
		cam.right(milliToS(timeDelta * multiplier));
	}
	/* Change the cammeras direction if the mouse was moved. Front is the point
	we are looking towards. */
	cam.updateFront(input.x, input.y);
	// Update OpenGL state to reflect newly calculated camera movements.
	cam.updateMatrixs();
}


void mengerSponge::updateSpongeLevel(const inputData & input)
{
	using namespace std::chrono;

	if (input.keys[SDL_SCANCODE_EQUALS])
	{
		static size_t lastTimeCalled{};
		
		if(notCalledFor(minPressRegisterInterval, lastTimeCalled))
		{
			mengerScenes[currentMengerScene]->increaseIterations();
		}
		lastTimeCalled = SDL_GetTicks();
	}
	if (input.keys[SDLK_MINUS])
	{
		static size_t lastTimeCalled{};

		if(notCalledFor(minPressRegisterInterval, lastTimeCalled))
		{
			mengerScenes[currentMengerScene]->decreaseIterations();
		}
		lastTimeCalled = SDL_GetTicks();
	}
}


void mengerSponge::updateLights(const inputData& input)
{
	if(input.keys[SDL_SCANCODE_L])
	{
		static size_t lastTimeCalled{};

		if(notCalledFor(minPressRegisterInterval, lastTimeCalled))
		{
			lightingEnabled = lightingEnabled ?
				(glDisable(GL_LIGHTING), false) : (glEnable(GL_LIGHTING), true);
		}
		lastTimeCalled = SDL_GetTicks();
	}
}


mengerSponge::inputData mengerSponge::checkInput()
{
	inputData ret{};

	/* SDL_PumpEvents() gathers all the pending input information from devices
	and places it in the event queue. Should only be run in the thread that
	initialized the video subsystem. */
	SDL_PumpEvents();

	if (ret.keys = SDL_GetKeyboardState(nullptr))
	{// Handle keyboard events.
        if (ret.keys[SDL_SCANCODE_ESCAPE])
		{
            quitApp = true;
        }
    }
	/* The current button state is returned as a button bitmask, which can be
	tested using the SDL_BUTTON(X) macros (where X is generally 1 for the left,
	2 for middle, 3 for the right button), and x and y are set to the mouse
	deltas since the last call to SDL_GetRelativeMouseState() or since event
	initialization. You can pass NULL for either x or y. */
	ret.mouseButtons = SDL_GetRelativeMouseState(&ret.x, &ret.y);

	return ret;
}


void mengerSponge::updateState(const unsigned int timeDelta, const inputData & input)
{
	updateScene(input);
	updateCamera(timeDelta, input);
	//std::cout << "input.keys[SDLK_PLUS] = " << input.keys[SDLK_EQUALS] << '\n';
	updateSpongeLevel(input);
	updateLights(input);
}


void mengerSponge::renderFrame()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, windowWidth, windowHeight);


	//glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glOrtho(0, this->windowWidth, this->windowHeight, 0, 1, -1);
//	glMatrixMode(GL_MODELVIEW);

//	glMatrixMode(GL_PROJECTION);        // set matrix mode
//	glLoadIdentity();					// reset projection matrix
//	GLfloat aspect = (GLfloat)this->windowWidth / this->windowHeight;
	//gluPerspective(90, aspect, 0.01, -1.0);		// set up a perspective projection matrix
//	glMatrixMode(GL_MODELVIEW);			// specify which matrix is the current matrix
	
	
    renderOSD();
	mengerScenes[currentMengerScene]->render(sDLWindow);
	
    
//	openGLTutorialStuff();

	//openGLTutorialStuff();

    // The rest of your frame rendering code goes here

/*   glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glEnd();

    glBegin(GL_TRIANGLES);

    glVertex3f(0.9, 0.9, -0.5);
    glVertex3f(0, 0.9, -0.5);
    glVertex3f(0, 0, -0.5);

    glEnd();


    SDL_GL_SwapWindow(sDLWindow); */
}


// Render On-Screen Display
void mengerSponge::renderOSD()
{
	GLTtext* hello_msg = gltCreateText();
	gltSetText(hello_msg, "Hello World!");

	gltBeginDraw();
	gltColor(0.0f, 1.0f, 0.0f, 1.0f);
	gltDrawText2D(hello_msg, 10, 10, 2.0);
	gltEndDraw();

	gltDeleteText(hello_msg);
	glUseProgram(0); // Gl text doesn't unbind the it's shader program!
}


/*
void openGLTutorialStuff()
{
	float vertices[] = {
		// points colours
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // bottom right
		0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,   // top right
		-0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f,  // top left
	};

	unsigned int faces[] =
	{
		0, 1, 2,    // First triangle.
		0, 2, 3    // Second triangle.
	};

	// Step 2 - Create Vertex Buffer Objects (VBOs)
	unsigned int vertexBuffer = 0;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Step 3 - Create Vertex Array Objects (VAOs)
	GLuint vertexArray = 0;
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // For vertices.
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); // For color.
	glEnableVertexAttribArray(1);

	// Step 4 – Create Element Buffer Object(EBO)
	GLuint m_faceElementBuffer = 0;
	glGenBuffers(1, &m_faceElementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_faceElementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(faces), faces, GL_STATIC_DRAW);
	{
		shader* squareShader{ new shader("superSquareShader.vert", "superSquareShader.frag") };
		glUseProgram(squareShader->getId());
		delete squareShader;
	}

	// Step 5 – Define, Createand Compile the Vertex Shader
	glBindVertexArray(vertexArray);    // Automatically binds the EBO as well.
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	//SDL_GL_SwapWindow(m_SDLWindow);

	// Step 9 - Clean Up
	glDeleteVertexArrays(1, &vertexArray);
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &m_faceElementBuffer);
	vertexArray = 0;
	vertexBuffer = 0;
	m_faceElementBuffer = 0;
}
*/