#ifndef DEFS_HPP__
#define DEFS_HPP__

#include <limits.h>
#include <string>
#include <iostream>


constexpr char GRAPHICS_WIN_TITLE[] = "samWin9000 >:^{}";


namespace error
{
	enum _error
	{
		NONE,
		INIT_GENERAL = INT_MIN,
		INIT_SDL_VIDEO_SUBSYSTEM,
		INIT_SDL_RENDERER,
		INIT_OPENGL_CONTEXT,
		SHADER_FILE,
		SHADER_COMPILE,
		SHADER_LINK,
		RANGE
	};


	/* The return value of this function is generally intended for use with
	the genError() template	function that has a variable arrity of n,
	where n > 1. File should be the	name of the file where the error occured
	and func should be the function	where it occured. */
	std::string genErrorLocationStr(const std::string & file, const std::string & func);

	template <typename T>
	void genError(const T& eNum)
	{
		exit(eNum);
	}

	template <typename T, typename... Args>
	void genError(const int eNum, const T& value, const Args&... args)
	{                             // A general error has occured.
		std::cerr<<value;
		genError(eNum, args...);
	}
}


namespace  geometry
{ /* where tL stands for top left, tR stands for top right,
	bL stands for bottom left, and finally bR stands for bottom right. */
/*	enum plane
	{
		XY, YX,
		XZ, ZX,
		ZY, YZ
	};*/

	struct vertex
	{
		float x, y, z;
	};

	class cube
	{// Pos * 4 * (6 faces) + color (one per face).
	private:
		static constexpr size_t xPos {0}, yPos {1}, zPos {2},
			posFaceDataNum {4}; // Number of vertexs per face.
			

	public:
		static constexpr size_t rPos {0}, gPos {1}, bPos{2}, faces {6},
			vertexStride {3}, // Size of vertex.
			faceStride {posFaceDataNum * vertexStride}; // Size of face.
		static const size_t posDataSize {vertexStride * posFaceDataNum * faces};
		// We have one color per face.
		static const size_t colorDataSize {vertexStride * faces};

	private:
		// Faces colors + vertex data.
		float colorData [vertexStride * faces]
		{
			0.30196f, 0.9f, 0.77647f, // Color back.
			0.37196f, 0.4f, 0.57647f, // Color front.

			0.83529f, 0.50196f, 0.9f, // Color left.
			0.76529f, 0.30196f, 0.4f, // Color right.

			0.50196f, 0.50196f, 0.9f, // Color top.
			0.30196f, 0.42196f, 0.4f, // Color bottom.
		};

		float posData[vertexStride * posFaceDataNum * faces]
		{
			// Back.
			0.0f, 0.0f, 0.0f, // (bottom left) Vertex
			0.0f, 1.0f, 0.0f, // Vertex.
			1.0f, 0.0f, 0.0f, // Vertex.
			1.0f, 1.0f, 0.0f, // Vertex.
			// Front.
			0.0f, 0.0f, 1.0f, // Vertex
			1.0f, 0.0f, 1.0f, // Vertex.
			0.0f, 1.0f, 1.0f, // Vertex.
			1.0f, 1.0f, 1.0f, // Vertex.
			// Left.
			0.0f, 0.0f, 0.0f, // (bottom right) Vertex
			0.0f, 0.0f, 1.0f, // Vertex.
			0.0f, 1.0f, 0.0f, // Vertex.
			0.0f, 1.0f, 1.0f, // Vertex.
			// Right.
			1.0f, 0.0f, 0.0f, // Vertex
			1.0f, 1.0f, 0.0f, // Vertex.
			1.0f, 0.0f, 1.0f, // Vertex.
			1.0f, 1.0f, 1.0f, // Vertex.
			// Top.
			0.0f, 1.0f, 1.0f, // Vertex
			1.0f, 1.0f, 1.0f, // Vertex.
			0.0f, 1.0f, 0.0f, // Vertex.
			1.0f, 1.0f, 0.0f, // Vertex.
			// Bottom.
			0.0f, 0.0f, 1.0f, // Vertex
			0.0f, 0.0f, 0.0f, // (bottom left)
			1.0f, 0.0f, 1.0f, // Vertex.
			1.0f, 0.0f, 0.0f  // Vertex.
		};

	public:
		cube(const vertex & origin)
		{
			translate(origin);
		}


		cube(const vertex& origin, const float scaleFactor)
		{
			scale(scaleFactor);
			translate(origin);
		}


		float getPosData(const size_t index) const
		{
			constexpr char FILE_NAME [] {"defs.hpp"};
			constexpr char FUNC_NAME [] {"getData()"};

			if (!(index >= 0 && index < posDataSize))
			{
				error::genError(error::RANGE, "ERROR ",
					error::genErrorLocationStr(FILE_NAME, FUNC_NAME),
					": index (", index, ") out of range [0, ", posDataSize,
					"].\n");
			}

			return posData[index];
		}


		float getColorData(const size_t index) const
		{
			constexpr char FILE_NAME[]{ "defs.hpp" };
			constexpr char FUNC_NAME[]{ "getData()" };

			if (!(index >= 0 && index < colorDataSize))
			{
				error::genError(error::RANGE, "ERROR ",
								error::genErrorLocationStr(FILE_NAME, FUNC_NAME),
								": index (", index, ") out of range [0, ", colorDataSize,
								"].\n");
			}

			return colorData[index];
		}


		cube * translate(const float translateBy)
		{
			return translate(translateBy, translateBy, translateBy);
		}


		cube * translate(const vertex & origin)
		{
			return translate(origin.x, origin.y, origin.z);
		}


		cube * translate(const float x, const float y, const float z)
		{ // Iterate though faces
			for(size_t faceIter {}; faceIter < posDataSize; faceIter += faceStride)
			{ // Iterate though vertexes and rgb values.
				for(size_t dataElementIter {faceIter}; // Start at current face.
					dataElementIter < (faceIter + faceStride); // iter < current face + face size.
					dataElementIter += vertexStride)
				{
				posData[dataElementIter + xPos] += x;
				posData[dataElementIter + yPos] += y;
				posData[dataElementIter + zPos] += z;
				}
			}
			return this;
		}


		cube * scale(const float factor)
		{
			for (size_t faceIter{}; faceIter < posDataSize; faceIter += faceStride)
			{ // Iterate though vertexes.
				for (size_t dataElementIter {faceIter}; // Start at current face.
					dataElementIter < (faceIter + (posFaceDataNum * vertexStride));
					dataElementIter += vertexStride)
				{/* We want to times all verticies by factor (except those which
				 are at the origin, namely these are the bottom left cornor of
				 the back face, the bottom right corner of the left face and the
				 bottom left corner of the bottom face. This is when the cube is
				 drawn isometrically with the front learning down and to the
				 left) */
					if (!(faceIter == 0 && dataElementIter == 0) &&
						!(faceIter == 0 + faceStride * 2 && dataElementIter == faceStride * 2) &&
						!(dataElementIter == faceStride * 5 + vertexStride * 1))
					{
						posData[dataElementIter + xPos] *= factor;
						posData[dataElementIter + yPos] *= factor;
						posData[dataElementIter + zPos] *= factor;
					}
				}
			}
			return this;
		}


		void displayData() const
		{
			std::cout << "cube data (excluding rgb data) for cube (" << (size_t)this << "):\n";
			for (size_t iter{}; iter < posDataSize; iter++)
			{
				if (iter % faceStride == 0)
					std::cout << "face " << iter / faceStride << " data...\n";
					std::cout<<posData[iter + xPos]<<", "<<posData[iter + yPos]
					<<", "<<posData[iter + zPos]<<'\n';
			}
			std::cout<<'\n';
		}
	};
}


#endif