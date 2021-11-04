#include <fstream>
#include <iostream>
#include <vector>
#include <sdl/SDL.h>
#include <glad/glad.h>
#include "include/utils.hpp"


static constexpr char FILE_NAME [] { "utils.cpp" };


int getFileAsStr(const std::string & fName, std::string & contents)
{
	std::ifstream file {fName};
	const int ret {file.is_open()};

	if (ret)
	{
		contents.clear();
		char fByte {};
		while(file.get(fByte))
		{
			contents.append(1, fByte); // Append one copy of fByte.
		}
		file.close();
	}

	return ret;
}


float milliToS(const unsigned int x)
{
	return (float)x / 1000.0f;
}


bool notCalledFor(const int waitTime, size_t & lastTime)
{
	bool ret {false};
	const size_t currentTime = SDL_GetTicks();

/*	if (pathNeverExecuted)
	{
		pathNeverExecuted = false;
		lastTime = currentTime;
	}*/
	if ((currentTime - waitTime) > lastTime)
	{
		ret = true;
	}
	return ret;
}


void drawSphere(const float xStart, const float yStart, const float zStart,
				const float zScale, const float r, const size_t slices,
				const size_t stacks, const bool drawNormals,
				const float normalScale)
{
	//using normals::normalLen;
	const int normalLen {1};
	const int minTesselation = 4;
	if (slices >= minTesselation && stacks >= minTesselation)
	{
		float theta{}, phi{};
		float x0{}, y0{}, z0{}, x1{}, y1{}, z1{}; // Used for visible sphere.
		float xN0{}, yN0{}, zN0{}, xN1{}, yN1{}, zN1{}; // Used for normals :)
		const float step_phi{ float(M_PI / stacks) };

		for (size_t j = 0; j <= stacks; j++)
		{
			phi = j / (float)stacks * M_PI;
			glBegin(GL_QUAD_STRIP);
			for (size_t i = 0; i <= slices; i++)
			{
				theta = i / (float)slices * 2.0 * M_PI;
				x0 = r * sinf(phi) * cosf(theta); // Calculate inner (visible) circle verticies.
				y0 = r * sinf(phi) * sinf(theta);
				z0 = r * zScale * cosf(phi);
				x1 = r * sinf(phi + step_phi) * cosf(theta);
				y1 = r * sinf(phi + step_phi) * sinf(theta);
				z1 = r * zScale * cosf(phi + step_phi);
				// Calculate outer circle vertices (used for normal lines.)
				xN0 = (r + normalLen * normalScale) * sinf(phi) * cosf(theta);
				yN0 = (r + normalLen * normalScale) * sinf(phi) * sinf(theta);
				zN0 = (r + normalLen * normalScale) * zScale * cosf(phi);
				xN1 = (r + normalLen * normalScale) * sinf(phi + step_phi) * cosf(theta);
				yN1 = (r + normalLen * normalScale) * sinf(phi + step_phi) * sinf(theta);
				zN1 = (r + normalLen * normalScale) * zScale * cosf(phi + step_phi);

				glNormal3f(xStart + xN0, yStart + yN0, zStart + zN0);
				glVertex3f(xStart + x0, yStart + y0, zStart + z0);
				glNormal3f(xStart + xN1, yStart + yN1, zStart + zN1);
				glVertex3f(xStart + x1, yStart + y1, zStart + z1);
			}
			glEnd();
		}
	//	drawSphereNormals(xStart, yStart, zStart, zScale, r, slices, stacks, drawNormals, normalScale);
	}
	else
	{
		std::cerr << "Error: (in drawSphere()) slices or stacks less then minTesselation\n";
		exit(-1);
	}
}


/*void drawSphereNormals(const float xStart, const float yStart, const float zStart, const float zScale, const float r,
					   const size_t slices, const size_t stacks, const bool drawNormals, const float normalScale)
{
	using namespace::normals;
	const float offset{ (normals::normalLen * normalScale * normals::normDrawScale) };

	if (drawNormals)
	{
		if (slices >= minTesselation && stacks >= minTesselation)
		{
			disableLighting();
			glColor3f(color[rIndex], color[gIndex], color[bIndex]);

			float theta{}, phi{};
			float x0{}, y0{}, z0{}, x1{}, y1{}, z1{}; // Used for visible sphere.
			float xN0{}, yN0{}, zN0{}, xN1{}, yN1{}, zN1{}; // Used for normals :)
			const float step_phi{ float(M_PI / stacks) };

			for (size_t j = 0; j <= stacks; j++)
			{
				phi = j / (float)stacks * M_PI;
				glBegin(GL_LINES);
				for (size_t i = 0; i <= slices; i++)
				{		// normalize2(float & a, float & b, const float normScale)
					theta = i / (float)slices * 2.0 * M_PI;
					x0 = r * sinf(phi) * cosf(theta); // Calculate inner (visible) circle verticies.
					y0 = r * sinf(phi) * sinf(theta);
					z0 = r * zScale * cosf(phi);
					x1 = r * sinf(phi + step_phi) * cosf(theta);
					y1 = r * sinf(phi + step_phi) * sinf(theta);
					z1 = r * zScale * cosf(phi + step_phi);*/
					/* Calculate outer circle vertices (used for normal lines.) "+ offset" isn't quite right because it
					   only give's the right result for true sphere's. */
/*					xN0 = (r + offset) * sinf(phi) * cosf(theta);
					yN0 = (r + offset) * sinf(phi) * sinf(theta);
					zN0 = (r + offset) * zScale * cosf(phi);
					xN1 = (r + offset) * sinf(phi + step_phi) * cosf(theta);
					yN1 = (r + offset) * sinf(phi + step_phi) * sinf(theta);
					zN1 = (r + offset) * zScale * cosf(phi + step_phi);

					glVertex3f(xStart + xN0, yStart + yN0, zStart + zN0);
					glVertex3f(xStart + x0, yStart + y0, zStart + z0);
					glVertex3f(xStart + xN1, yStart + yN1, zStart + zN1);
					glVertex3f(xStart + x1, yStart + y1, zStart + z1);
				}
				glEnd();
			}
			enableLighting();
		}
		else
		{
			std::cerr << "Error: (in drawSphereNormals()) slices or stacks less then minTesselation\n";
			exit(RANGE_ERROR);
		}
	}
}*/

/*
void genSquare(const int plane, const geometry::vertex & bottomLeftCorner,
	const float width, const float length, geometry::square & ret)
{// bottomLeftCorner is the origin point of the cube. 
	constexpr char FUNC_NAME [] {"genCube()"};
	using namespace geometry;

	switch(plane)
	{
	case  geometry::XY:
	case  geometry::YX:
		std::cout<<"in YX\n";
		ret.setBottomLeft(bottomLeftCorner);
		ret.setTopLeft(bottomLeftCorner.data[vertex::xPos],
			bottomLeftCorner.data[vertex::yPos] + length,
			bottomLeftCorner.data[vertex::zPos],
			bottomLeftCorner.data[vertex::rPos],
			bottomLeftCorner.data[vertex::gPos],
			bottomLeftCorner.data[vertex::bPos]);
		ret.setTopRight(bottomLeftCorner.data[vertex::xPos] + width,
			bottomLeftCorner.data[vertex::yPos] + length,
			bottomLeftCorner.data[vertex::zPos],
			bottomLeftCorner.data[vertex::rPos],
			bottomLeftCorner.data[vertex::gPos],
			bottomLeftCorner.data[vertex::bPos]);
		ret.setBottomRight(bottomLeftCorner.data[vertex::xPos] + width,
			bottomLeftCorner.data[vertex::yPos],
			bottomLeftCorner.data[vertex::zPos],
			bottomLeftCorner.data[vertex::rPos],
			bottomLeftCorner.data[vertex::gPos],
			bottomLeftCorner.data[vertex::bPos]);
		break;
	case  geometry::XZ:
	case  geometry::ZX:
		ret.setBottomLeft(bottomLeftCorner);
		ret.setTopLeft(bottomLeftCorner.data[vertex::xPos],
			bottomLeftCorner.data[vertex::yPos],
			bottomLeftCorner.data[vertex::zPos] + length,
			bottomLeftCorner.data[vertex::rPos],
			bottomLeftCorner.data[vertex::gPos],
			bottomLeftCorner.data[vertex::bPos]);
		ret.setTopRight(bottomLeftCorner.data[vertex::xPos] + width,
			bottomLeftCorner.data[vertex::yPos],
			bottomLeftCorner.data[vertex::zPos] + length,
			bottomLeftCorner.data[vertex::rPos],
			bottomLeftCorner.data[vertex::gPos],
			bottomLeftCorner.data[vertex::bPos]);
		ret.setBottomRight(bottomLeftCorner.data[vertex::xPos] + width,
			bottomLeftCorner.data[vertex::yPos],
			bottomLeftCorner.data[vertex::zPos],
			bottomLeftCorner.data[vertex::rPos],
			bottomLeftCorner.data[vertex::gPos],
			bottomLeftCorner.data[vertex::bPos]);
		break;
	case  geometry::ZY:
	case  geometry::YZ:
		ret.setBottomLeft(bottomLeftCorner);
		ret.setTopLeft(bottomLeftCorner.data[vertex::xPos],
			bottomLeftCorner.data[vertex::yPos] + length,
			bottomLeftCorner.data[vertex::zPos],
			bottomLeftCorner.data[vertex::rPos],
			bottomLeftCorner.data[vertex::gPos],
			bottomLeftCorner.data[vertex::bPos]);
		ret.setTopRight(bottomLeftCorner.data[vertex::xPos],
			bottomLeftCorner.data[vertex::yPos] + length,
			bottomLeftCorner.data[vertex::zPos] + width,
			bottomLeftCorner.data[vertex::rPos],
			bottomLeftCorner.data[vertex::gPos],
			bottomLeftCorner.data[vertex::bPos]);
		ret.setBottomRight(bottomLeftCorner.data[vertex::xPos],
			bottomLeftCorner.data[vertex::yPos],
			bottomLeftCorner.data[vertex::zPos] + width,
			bottomLeftCorner.data[vertex::rPos],
			bottomLeftCorner.data[vertex::gPos],
			bottomLeftCorner.data[vertex::bPos]);
		break;
	default:
	error:genError(error::RANGE, "ERROR ",
		error::genErrorLocationStr(FILE_NAME, FUNC_NAME),
		": argument plane (", plane, ") out of range, expected "
		"coordinates::XY, ...YX, ...XZ, ...ZX, ...ZY or ...YZ which are ",
		geometry::XY, ' ', geometry::YX, ' ', geometry::XZ, ' ',
		geometry::ZX, ' ', geometry::ZY, ' ', geometry::YZ, ' ',
		"respectively.\n");

	}
}


void genCube(const geometry::vertex& backBottomLeftCorner, const float width,
	const float length, geometry::cube & ret)
{
	geometry::square square {};

}*/