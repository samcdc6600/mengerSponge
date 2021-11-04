#ifndef UTILS_HPP__
#define UTILS_HPP__


#include <string>
#include "include/defs.hpp"


/* Opens the file at path fName and copys it's contents into contents.
   Returns status of file opening operation. */
int getFileAsStr(const std::string & fName, std::string & contents);
float milliToS(const unsigned int x); // Returns x / 1000.
/* The variable passed in as lastTime should be static and have an initial value
of 0 as this function can be used to keep track of any number of time deltas.
WaitTime is the time delta within which this function will not return true upon
sucessive calls.
Last time should be set to SDL_GetTicks() after the operation that may result
from calling this function (as that operation may take some time.) */
bool notCalledFor(const int waitTime, size_t & lastTime);//, bool& pathNeverExecuted);
/* The code that makes up the basic functionallity of this function was taken
from the lecture "Procedural modelling, normals and vertex arrays"
found at the url:
http://titan.csit.rmit.edu.au/~e20068/teaching/i3dg&a/2017/lecture-promod.html
I have extended it's base functinallity. */
void drawSphere(const float xStart, const float yStart, const float zStart,
				const float zScale, const float r, const size_t slices,
				const size_t stacks, const bool drawNormals,
				const float normalScale);
/*void drawSphereNormals(const float xStart, const float yStart,
					   const float zStart, const float zScale, const float r,
					   const size_t slices, const size_t stacks,
					   const bool drawNormals, const float normalScale)*/

#endif