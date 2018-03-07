#include "Renderer.h"

namespace Core
{

	bool Renderer::is_init = false;
	GLFWwindow* Renderer::m_window = nullptr;
	GLuint Renderer::VAO = -1;

	bool Renderer::wasInit() { return is_init; }

	GLFWwindow* Renderer::Init(ScreenSize::type width, ScreenSize::type height, char const* caption)
	{
		try
		{
			InitGLFW();

			m_window = InstantiateWindow(width, height, caption);

			InitGLEW();

			is_init = true;

			VAO = CreateVAO();

			return m_window;

		}
		catch (Misc::Exception e)
		{
			throw Misc::Exception(e.what());
		}
	}

	void Renderer::SetGLFWWindowHints()
	{
		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

	void Renderer::InitGLFW()
	{
		if (!glfwInit())
		{
			throw Misc::Exception("Failed to initialize GLFW");
		}

		SetGLFWWindowHints();
	}

	void Renderer::InitGLEW()
	{
		glewExperimental = true;

		if (glewInit() != GLEW_OK)
		{
			throw Misc::Exception("Failed to initialize GLEW");
		}
	}

	GLFWwindow* Renderer::InstantiateWindow(ScreenSize::type width, ScreenSize::type height, char const* caption)
	{
		auto window = glfwCreateWindow(width, height, caption, nullptr, nullptr);

		if (window == nullptr)
		{
			glfwTerminate();
			throw Misc::Exception("Failed to create Window.");
		}

		glfwMakeContextCurrent(window);

		return window;
	}

	GLuint Renderer::CreateVAO()
	{
		GLuint VertexArrayID;
		glGenVertexArrays(1, &VertexArrayID);
		glBindVertexArray(VertexArrayID);

		return VertexArrayID;
	}

	void Renderer::SwapBuffers()
	{
		if (!wasInit()) throw Misc::Exception("void Renderer::SwapBuffers(): Call Renderer::Init() before attempting to swap buffers.");
		glfwSwapBuffers(m_window);
	}

	bool Renderer::WindowShouldClose()
	{
		if (!wasInit()) throw Misc::Exception("bool Renderer::WindowShouldClose(): Call Renderer::Init() before calling any other function.");
		return glfwWindowShouldClose(m_window);
	}
	GLFWwindow* Renderer::getWindow()
	{
		if (!wasInit()) throw Misc::Exception("GLFWwindow* Renderer::getWindow(): Call Renderer::Init() before calling any other function.");
		return m_window;
	}

	void Renderer::setClearColor(Misc::Color const& c)
	{
		glClearColor(c.r(), c.g(), c.b(), c.a());
	}

	void Renderer::clear(GLenum flags)
	{
		glClear(flags);
	}

}