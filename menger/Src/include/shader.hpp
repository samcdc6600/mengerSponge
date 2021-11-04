#ifndef SHADER_HPP__
#define SHADER_HPP__

#include <string>
#include <glad/glad.h>
#include "utils.hpp"
#include "defs.hpp"


class shader
{
private:
	//const std::string vertSrc, fragSrc;
  	const char * vertSrc;
	const char * fragSrc;
	GLuint shaderProg {};


	std::string getSrc(const std::string & fName)
	{
		constexpr char FUNC_NAME [] {"getSrc()"};
		std::string ret {};
		if (!getFileAsStr(fName, ret)) // Read file contents into ret.
			error::genError(error::SHADER_FILE, "Error ", error::genErrorLocationStr("shader.hpp", FUNC_NAME),
				": couldn't open the shader file \"", fName, "\". Exiting.");
		return ret += '\0'; // We need to add the null byte.
	}

public: /* We allocate memory for vertSrcand fragSrcand copy vertFNameand
		fragFName to vertSrcand fragSrc respectively. We also create vertex
		and fragment shader objects. */
	shader(const std::string & vertFName, const std::string & fragFName):
		vertSrc(new char [getSrc(vertFName).size() + 1]), // .size() doesn't include the null byte.
		fragSrc(new char [getSrc(fragFName).size() + 1])
	{ // glShaderSource() needs an lvalue of type "char *" (This definitly isn't as efficient as it could be...)
		constexpr char FUNC_NAME[]{ "Shader()" };

		// Read contents of shader files into xxxCPPStrSrc and copy to xxxSrc.
		std::string vertCPPStrSrc {getSrc(vertFName)};
		size_t vertSrcSize {vertCPPStrSrc.size() + 1};
		memcpy((void *)vertSrc, vertCPPStrSrc.c_str(), vertSrcSize);
		std::string fragCPPStrSrc {getSrc(fragFName)};
		size_t fragSrcSize { fragCPPStrSrc .size() + 1};
		memcpy((void *)fragSrc, fragCPPStrSrc.c_str(), fragSrcSize);

		int errOk{};
		char errInfo[512];
		// Create shaders and get their id's.
		const GLuint vertexShader{ glCreateShader(GL_VERTEX_SHADER) };
		const GLuint fragmentShader{ glCreateShader(GL_FRAGMENT_SHADER) };
		// Compile vertex shader.
		glShaderSource(vertexShader, 1, &vertSrc, nullptr);
		glCompileShader(vertexShader);
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &errOk);

		if (!errOk)
		{
			glGetShaderInfoLog(vertexShader, 512, nullptr, errInfo);
			error::genError(error::SHADER_COMPILE, "ERROR ",
				error::genErrorLocationStr("shader.hpp", FUNC_NAME),
				": Info (", errInfo, "): Failed to compile vertex shader : "
				"\n\"\n", vertSrc, "\n\"\n");
		}
		else
		{
			// Compile fragment shader.
			glShaderSource(fragmentShader, 1, &fragSrc, nullptr);
			glCompileShader(fragmentShader);
			glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &errOk);
			if (!errOk)
			{
				glGetShaderInfoLog(fragmentShader, 512, nullptr, errInfo);
				error::genError(error::SHADER_COMPILE, "ERROR ",
					error::genErrorLocationStr("shader.hpp", FUNC_NAME),
					": Info (", errInfo, "): Failed to compile fragment "
					"shader : \n\"\n", fragSrc, "\n\"\n");
			}
			else
			{
				// Link objects to form shader program.
				shaderProg = glCreateProgram();
				glAttachShader(shaderProg, vertexShader);
				glAttachShader(shaderProg, fragmentShader);
				glLinkProgram(shaderProg);
				glGetProgramiv(shaderProg, GL_LINK_STATUS, &errOk);
				if (!errOk)
				{
					glGetProgramInfoLog(shaderProg, 512, NULL, errInfo);
					error::genError(error::SHADER_LINK, "ERROR ",
						error::genErrorLocationStr("shader.hpp", FUNC_NAME),
						": Info (", errInfo, "): Failed to link shaders to "
						"create shader program. Shaders (vert and frag) : "
						"\n\"\n", vertSrc, "\n\"\n", "\n\"\n", fragSrc,
						"\n\"\n");
				}
			}
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}


	~shader()
	{
		delete [] vertSrc;
		delete [] fragSrc;
		glDeleteProgram(shaderProg);
		shaderProg = 0;
	}


	GLuint getId()
	{
		return shaderProg;
	}
};


#endif