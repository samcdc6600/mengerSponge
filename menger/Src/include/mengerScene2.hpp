#ifndef MENGER_SCENE2_HPP__
#define MENGER_SCENE2_HPP__
#include <iostream>
#include "mengerScene.hpp"
#include "./shader.hpp"


class mengerScene2 : public mengerScene
{
	bool initialized {false};
	shader * sceneProgram {};
	GLuint vAOid {};
	GLuint faceElementBuffer {};
	GLuint vBOid {}; // Vertex Array Buffer object id.

public:
	mengerScene2()
	{
	}


	~mengerScene2()
	{
	if (initialized)
		{
			glDeleteVertexArrays(1, &vAOid);
			glDeleteBuffers(1, &vBOid);
			glDeleteBuffers(1, &faceElementBuffer);
			delete sceneProgram; // Deletes shader program (amung other things.)
			vAOid = 0;
			vBOid = 0;
			faceElementBuffer = 0;
		}
	}


	virtual void init()
	{
		initialized = true;


		/* A vertex array object (also known as VAO) can be bound just like a
		vertex buffer object and any subsequent vertex attribute calls from that
		point on will be stored inside the VAO. This has the advantage that when
		configuring vertex attribute pointers you only have to make those calls
		once and whenever we want to draw the object, we can just bind the
		corresponding VAO.
		A vertex array object stores the following:
		• Calls to glEnableVertexAttribArray or glDisableVertexAttribArray.
		• Vertex attribute configurations via glVertexAttribPointer.
		• Vertex buffer objects associated with vertex attributes by calls to
		glVertexAttribPointer. */

		glBindVertexArray(vBOid);

		sceneProgram = new shader("superSquareShader.vert", "superSquareShader.frag");

		// Step 2 - Create Vertex Buffer Objects (VBOs).

		glGenBuffers(1, &vBOid); // Generate ID for buffer (store in vBOid).
		/* Bind id to the GL_ARRAY_BUFFER target(only 1 id can be bound to a
		specific target at one time.) */
		glBindBuffer(GL_ARRAY_BUFFER, vBOid); /* From this point onwards any
											  buffer calls we make
											  (on the GL_ARRAY_BUFFER target)
											  will be used to configure the
											  currently bound buffer, which is
											  associated with vBOid. */
		/* GlBufferData copies data into the buffer object currently bount to
		GL_ARRAY_BUFFER. */
		glBufferData(GL_ARRAY_BUFFER, mengerSpongePosDataSize, &mengerSpongePosData[0], GL_STATIC_DRAW);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


		/* GlVertexAttribPointer tells OpenGL how it should interpret the vertex
		data. The first parameter specifies which vertex attribute we want to
		configure. We specified the location of the position vertex attribute
		in the vertex shader with "layout (location = 0)...".
		The 2nd argument specified the size of the vertex attribute (which is a
		vec3 and thus is composed of 3 values.) The third argument specifies the
		type of data. The 4th argument specifies if we want the data to be
		normalized. The fifth argument is the stride. Since the position data is
		in the format (x,y,z), where x, y and z are floats. The stride should be
		3 * sizeof(float). The last arg is the offcet in the buffer where our
		data begins (it begins at the start in this case.)
		Each vertex attribute takes its data from memory managed by a VBO and
		which VBO it takes its data from (you can have multiple VBOs) is
		determined by the VBO currently bound to GL_ARRAY_BUFFER. */
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		/* Now that we specified how OpenGL should interpret the vertex data we
		should also enable the vertex attribute with glEnableVertexAttribArray
		giving the vertex attribute location as its argument; */
		glEnableVertexAttribArray(0);


		/*// Step 3 - Create Vertex Array Objects (VAOs).
		glGenVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, vBOid);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // For vertices.
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0 * sizeof(float))); // For color.
		glEnableVertexAttribArray(1);

		// Step 4 ? Create Element Buffer Object(EBO).
		glGenBuffers(1, &faceElementBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, faceElementBuffer);
//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(faces), faces, GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mengerSpongeFaceIndiciesSize, &mengerSpongeFaceIndicies[0], GL_STATIC_DRAW);

		// Step 5 - define, create and compile the vertex shader.
		// Step 6 - define, create and compile the fragment shader.
		// Step 7 - link the shader programs.
		sceneProgram = new shader("superSquareShader.vert", "superSquareShader.frag");

		// Step 8 - see mengerScene::render().
		// Step 9 - see destructor and maybe also mengerScene::unInit().*/
	}


	virtual void render(SDL_Window* sDLWin)
	{
		// ======== Step 8 - Use The Shader Program To Render Geometry =======
		glUseProgram(sceneProgram->getId());
		glBindVertexArray(vAOid);    // Automatically binds the EBO as well.
		glDrawArrays(GL_TRIANGLES, 0, 1440);
//		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		SDL_GL_SwapWindow(sDLWin);
	}
};


#endif