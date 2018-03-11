#include "Renderer.h"
#include "Triangle.h"
#include "Color.h"
#include "Math.h"
#include "Circle.h"
#include "RegularPolygon.h"

#include <GLM\gtc\matrix_transform.hpp>

#include <memory>

//#TODO:
//1. Fix warnings
//TODO list COMPLETE: learnopengl.com -> add features




//#FIXME:
//1. Crash when calling Circle::draw() -> If Todo #6 is implemented, this is not needed anymore -> FIXED

void MessageCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);
}



int main()
{
	using namespace Core;

	using Geometry::Triangle;
	using Geometry::RegularPolygon;
	using Geometry::Shape2D;
	using Geometry::Circle;

	

	try
	{
		auto window = Renderer::Init(800, 600, "GL Utility");

		glEnable(GL_DEBUG_OUTPUT);
//		glDebugMessageCallback((GLDEBUGPROC)MessageCallback, nullptr);
	
		std::vector<std::unique_ptr<Shape2D> > shapes;
//		shapes.push_back(std::unique_ptr<Shape2D>(new Circle(Vertex(0, 0), 1, Circle::Precision(10))));

		Shader mainShader;
		std::string base = "C:/Users/michi_000/Desktop/C++/OpenGL/GL_Utility/x64/Debug/";
		std::string vtx = base + "shaders/vertex.glsl", frag = base + "shaders/fragment.glsl";

		mainShader.load(vtx, frag);

		glm::mat4 model;
		model = glm::rotate(model, Math::Angle(-55.0f).radians(), glm::vec3(1.0f, 0.0f, 0.0f));

		glm::mat4 view;
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -0.3f));

		glm::mat4 projection;
		projection = glm::perspective(Math::Angle(45.0f).radians(), 800.0f / 600.0f, 0.1f, 100.0f);

		static const float pi = 3.14159265f;

		do
		{
			auto time = (float)(glfwGetTime() + 0.25);

			Renderer::setClearColor((Core::Misc::Color((float)(std::sin(time * pi / 3) / 2 + 0.5), (float)(std::sin(time + 2 * pi  / 3) / 2 + 0.5), (float)(std::sin(time + 4 * pi / 3) / 2 + 0.5))));

			mainShader.setUniform("globalTime", (float)glfwGetTime());

			Renderer::clear();

			for (auto & shape : shapes)
			{
				Renderer::render(*shape);
			}


			Renderer::SwapBuffers();
			glfwPollEvents();
		} while (!Renderer::WindowShouldClose() && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS);
	}
	catch (Core::Misc::Exception e)
	{
		logpp::Console::error(e.what());
	}
	catch (Core::Shader::Exception e)
	{
		logpp::Console::error(e.what());
	}

	glfwTerminate();

	std::cin.get();

	return 0;
}