#ifndef _GL_INIT_FUNCTIONS_H_
#define _GL_INIT_FUNCTIONS_H_

#include <GL\glew.h>
#include <GL\glfw3.h>

#include "logpp\log++.h"

namespace GLInit
{


	inline void SetGLFWWindowHints()
	{
		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); /*OpenGL 3.3*/
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

	inline void InitGLFW()
	{
		if (!glfwInit())
		{
			logpp::Console::error("Failed to initialize GLFW!");
			return;
		}


		SetGLFWWindowHints();
	}

	inline void InitGLEW()
	{
		glewExperimental = true; //Needed in core profile
		if (glewInit() != GLEW_OK)
		{
			logpp::Console::error("Failed to initialize GLEW!");
			return;
		}
	}

	inline GLuint CreateVAO()
	{
		GLuint VertexArrayID;
		glGenVertexArrays(1, &VertexArrayID);
		glBindVertexArray(VertexArrayID);

		return VertexArrayID;
	}

	inline GLFWwindow* CreateWin(int width, int height, char const* caption)
	{
		auto window = glfwCreateWindow(width, height, caption, nullptr, nullptr);
		if (window == nullptr)
		{
			std::string msg = "Failed to create window!";
			logpp::Console::error(msg);
			glfwTerminate();
			return nullptr;
		}

		glfwMakeContextCurrent(window);

		return window;
	}

	inline GLFWwindow* Init(int width, int height, char const* caption)
	{

		InitGLFW();

		auto window = CreateWin(width, height, caption);

		InitGLEW();

		return window;
	}

}

#endif