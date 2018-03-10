#include "common\glinit.h"

#include "Triangle.h"
#include "Renderer.h"
#include "Color.h"
#include "Math.h"
#include "Circle.h"
#include "RegularPolygon.h"

#include <memory>

//#TODO:
//1. Add a value_type to Vertex class -> DONE
//2. Change float to Vertex::value_type where appropriate -> DONE
//3. Delete copy constructors for Triangle class, use move semantics instead -> 
//4. Add formulas from circle to Math.h DONE
//5. Add Polygon and RegularPolygon classes -> IN PROGRESS -> DONE
//	5a) Polygon -> IN PROGRESS -> SEE ALSO 16 -> CANCELED
//	5b) RegularPolygon -> DONE
//6. Use RegularPolygon class to draw Circle -> DONE
//7. Create base class where Circle, Triangle, Polygon, etc can derive from (ex Shape2D) -> IN PROGRESS -> DONE
//8. Use this base class -> IN PROGRESS -> DONE
//9. logpp templates -> IN PROGRESS -> DONE
//10. gl error callback -> IN PROGRESS -> DONE
//11. Add namespaces -> IN PROGRESS -> DONE
//12. Add Angle class -> IN PROGRESS -> DONE
//13. Use Angle class -> PUSH! -> DONE
//14. Rename Geometry namespace? -> NAH
//15. Triangle::operator- ->Shape2D::operator- -> CANCELED -> OPERATOR- DELETED
//16. Polygon.cpp: Check valid vertices in constructor -> NEEDS THINKING -> THINKING DONE -> CHECKS ARE NOT NEEDED SO -> CANCELED
//17. Polygon.cpp: Polygon::generateVertices(): Implement -> CANCELED
// 
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
		auto window = Renderer::Init(600, 600, "GL Utility");

		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback((GLDEBUGPROC)MessageCallback, 0);
	
		std::vector<std::unique_ptr<Shape2D> > shapes;

		Shader mainShader;
		std::string base = "C:/Users/michi_000/Desktop/C++/OpenGL/GL_Utility/x64/Debug/";
		std::string vtx = base + "shaders/vertex.glsl", frag = base + "shaders/fragment.glsl";

		mainShader.load(vtx, frag);

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