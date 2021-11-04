#ifndef MENGER_SCENE_HPP__
#define MENGER_SCENE_HPP__
#include <glad/glad.h>
#include <sdl/SDL.h>
#include <vector>
#include <cmath>
#include "shader.hpp"
#include "defs.hpp"
#include "camera.hpp"


class mengerScene
{
	// ============================ MEMBER VARIABLES ===========================
	// =========================================================================
	/* Should be set to false upon first instanciation of an object of a base
	class type. */
	bool firstObjectInstanciated {true};
	enum
	{ // Should start at 0 by defalut.
		face1, face2, face3, face4, face5, face6
	};


	// ============================ MEMBER FUNCTIONS ===========================
	// =========================================================================
	// Generates new menger sponge data and populates mengerSpongeData with it.
	void genMengerSponge(size_t iterations)
	{
		/* This is to be the origin of our menger cube. Note that
		GenMengerSpongeProper() generates a cube that is 3x the unit cube... */
		geometry::vertex origin{ -1.5, -1.5, -1.5 };

		std::cout << "Freeing sponge data...\n";
		mengerSpongePosData.clear(); // May have already been populated.
		mengerSpongeFaceIndicies.clear(); // May have already been populated.
		mengerSpongePosDataSize = 0;
		mengerSpongeFaceIndiciesSize = 0;
		if (iterations > 0)
		{
			std::cout << "Done.\nGenerating new sponge data...\n";
			// genMengerSpongeProper will increment mengerSpongePosDataSize.
			
			genMengerSpongeProper(origin, iterations, iterations);
			std::cout << "Done.\n";
		}
		else
		{/* Iteration 0 is a special caseand isn't handeled by
		 genMengerSpongeProper. */
			std::cout << "Done.\nGenerating new sponge data...\n";
			/*	GenMengerSpongeProper() generates a cube that is 3x the unit cube,
			so we scale by 3. */
			geometry::cube* newCube{ new geometry::cube(origin, 3.0f) };
			copyCubePosDataTo(mengerSpongePosData, newCube);
			mengerSpongePosDataSize = newCube->posDataSize;
			delete newCube;
			std::cout << "Done.\n";
		}

		{ /* We are only interested in the color data of one cube.So we create
			one here just to get the color. We will use this color for all cubes
			when rendering. We changed the way the cube data is stored a number
			of times and it was easiest to do it this way so we didnt' have to
			write a bunch of new code (we are very time constrained.) */
			mengerSpongeColorData.clear(); // May have already been populated.
			geometry::cube* newCube {new geometry::cube(origin, 3.0f)};
			copyCubeColorDataTo(mengerSpongeColorData, newCube);
			mengerSpongeColorDataSize = newCube->colorDataSize;
			/* Populate mengerSpongeFaceIndicies with indicies pointing to the
			start of each successive set of verticies that constitute a face.
			These indicies are of course to be used with mengerSpongePosData. */
			mengerSpongeFaceIndicies.push_back(geometry::cube::faceStride * face1);
			mengerSpongeFaceIndicies.push_back(geometry::cube::faceStride * face2);
			mengerSpongeFaceIndicies.push_back(geometry::cube::faceStride * face3);
			mengerSpongeFaceIndicies.push_back(geometry::cube::faceStride * face4);
			mengerSpongeFaceIndicies.push_back(geometry::cube::faceStride * face5);
			mengerSpongeFaceIndicies.push_back(geometry::cube::faceStride * face6);
			mengerSpongeFaceIndiciesSize = geometry::cube::faces;
			delete newCube;
		}
	}


	void genMengerSpongeProper(const geometry::vertex cubeOrigin,
		const size_t maxIterations, const size_t countDownIterations)
	{/* Cube positions x, y and z in the range [0, 2] No cube may have a
	 position with two 1's */
		std::vector<geometry::cube *> ret {};
		for (int x {}; x < 3; x++)
		{
			for (int y {}; y < 3; y++)
			{  // Make sure there are less than two 1's.
				y = y == 1 && x == 1 ? ++y : y; 
				for (int z {}; z < 3; z++)
				{   // Make sure there are less than two 1's.
					z = z == 1 && (x == 1 || y == 1) ? ++z: z;

					const float cubeSize {powf(1.0f / 3.0f,
						maxIterations - countDownIterations)};
					// If we are only doing one iteration we don't need to call again.
					if (countDownIterations > 1) 
					{/* Calculate newOrigin and cubeSize and then
					 call genMengerSpongeProper() again. */
						const geometry::vertex newOrigin {
							cubeOrigin.x + x * cubeSize,
							cubeOrigin.y + y * cubeSize,
							cubeOrigin.z + z * cubeSize};
						genMengerSpongeProper(newOrigin, maxIterations,
							countDownIterations -1);
					}
					else
					{// We are at the lowest level! GENERATE CUBES!
					 /* Populate mengerSpongeFaceIndicies with indicies pointing
					 to the start of each successive set of verticies that
					 constitute a face. These indicies are of course to be used
					 with mengerSpongePosData. */
						mengerSpongeFaceIndicies.push_back(
							mengerSpongePosData.size() + 
							geometry::cube::faceStride * face1);
						mengerSpongeFaceIndicies.push_back(
							mengerSpongePosData.size() +
							geometry::cube::faceStride * face2);
						mengerSpongeFaceIndicies.push_back(
							mengerSpongePosData.size() +
							geometry::cube::faceStride * face3);
						mengerSpongeFaceIndicies.push_back(
							mengerSpongePosData.size() +
							geometry::cube::faceStride * face4);
						mengerSpongeFaceIndicies.push_back(
							mengerSpongePosData.size() +
							geometry::cube::faceStride * face5);
						mengerSpongeFaceIndicies.push_back(
							mengerSpongePosData.size() +
							geometry::cube::faceStride * face6);
						mengerSpongeFaceIndiciesSize += geometry::cube::faces;

						const float cubeSize {powf(1.0f / 3.0f,
							maxIterations - (countDownIterations))};
						/* We have to calculate newOrigin here as well since
						for the case of 1 iteration the if block associated with
						the if statment that this block is associated with isn't
						executed. */
						const geometry::vertex newOrigin{
							cubeOrigin.x + x * cubeSize,
							cubeOrigin.y + y * cubeSize,
							cubeOrigin.z + z * cubeSize };

						geometry::cube* newCube{new geometry::cube(newOrigin,
																	cubeSize)};
						copyCubePosDataTo(mengerSpongePosData, newCube);
						mengerSpongePosDataSize += newCube->posDataSize;

						delete newCube;
					}
				}
			}
		}
	}


	void copyCubePosDataTo(std::vector<float> & dest, const geometry::cube * cube)
	{
		for (size_t iter{}; iter < cube->posDataSize; ++iter)
		{
			dest.push_back(cube->getPosData(iter));
		}
	}


	void copyCubeColorDataTo(std::vector<float>& dest, const geometry::cube* cube)
	{
		for (size_t iter{}; iter < cube->colorDataSize; ++iter)
		{
			dest.push_back(cube->getColorData(iter));
		}
	}


/*	void freeMengerSpongeData()
	{
		for (auto cubeIter {mengerSpongeData.begin()};
			 cubeIter > mengerSpongeData.end(); ++cubeIter)
		{// Space for cubes was allocated with new.
			delete * cubeIter;
		}
	}*/


protected:
	// ============================ MEMBER VARIABLES ===========================
	// =========================================================================
/*	const size_t vertElementXPos{0}, vertElementYPos{1},
		vertElementZPos {2}, vertElementColorRPos {3},
		vertElementColorGPos {4}, vertElementColorBPos{5}; */
	/* This should be shared by all child classesand thus has been made
	static! It must be initialised by createMengerSpongeData outside of class!
	See : https://stackoverflow.com/questions/12855649/how-can-i-initialize-a-static-const-vector-that-is-a-class-member-in-c11
	Note that we define mengerspongeData in mengerScene.cpp. */
	static std::vector<float> mengerSpongePosData;
	static std::vector<float> mengerSpongeColorData;
	// Stores indexes into that start position for faces in mengerSpongePosData.
	static std::vector<float> mengerSpongeFaceIndicies;
	static size_t mengerSpongePosDataSize;
	static size_t mengerSpongeColorDataSize;
	static size_t mengerSpongeFaceIndiciesSize;
	static size_t iterations;
	static constexpr size_t maxIterations {6};

public:
	// ============================ MEMBER FUNCTIONS ===========================
	// =========================================================================
	mengerScene()
	{
		if (firstObjectInstanciated)
		{ // Code path should only ever be executed once!
			firstObjectInstanciated = false;
			/* mengerSpongeData is staticand shared by all sub classesand thus
			should only be populated once(unless explicitly re-populated.) */
			genMengerSponge(iterations); 
		}
	}


	~mengerScene()
	{
//		freeMengerSpongeData();
	}


	void increaseIterations()
	{
		if (iterations < maxIterations)
		{
			iterations++;
			std::cout<<"Increasing iterations to "<<iterations<<".\n";
			genMengerSponge(iterations);
		}
		else
		{
			std::cout<<"Reached maximum number of iterations ("
				<<maxIterations<<").\n";
		}
	}


	void decreaseIterations()
	{
		if(iterations > 0)
		{
			iterations--;
			std::cout<<"Increasing iterations to "<<iterations<<"\n.";
			genMengerSponge(iterations);
		}
		else
		{
			std::cout<<"Reached minimum number of iterations ("
				<<0<<").\n";
		}
	}


	virtual void init() = 0;
	virtual void render(SDL_Window * sDLWin) = 0;
};


#endif