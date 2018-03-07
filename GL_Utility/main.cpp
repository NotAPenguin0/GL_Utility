#include "common\glinit.h"

#include "Triangle.h"
#include "Renderer.h"
#include "Color.h"
#include "Math.h"
#include "Circle.h"
#include "RegularPolygon.h"

#include <memory>

//#TODO:
//1. Add a value_type to Vertex class DONE
//2. Change float to Vertex::value_type where appropriate DONE
//3. Delete copy constructors for Triangle class, use move semantics instead DONE
//4. Add formulas from circle to Math.h DONE
//5. Add Polygon and RegularPolygon classes -> IN PROGRESS
//	5a) Polygon -> IN PROGRESS -> SEE ALSO 16
//	5b) RegularPolygon -> DONE
//6. Use Polygon class to draw Circle
//7. Create base class where Circle, Triangle, Polygon, etc can derive from (ex Shape2D) -> IN PROGRESS -> DONE
//8. Use this base class -> IN PROGRESS
//9. logpp templates -> IN PROGRESS -> DONE
//10. gl error callback
//11. Add namespaces -> IN PROGRESS -> DONE
//12. Add Angle class -> IN PROGRESS -> DONE
//13. Use Angle class -> PUSH!
//14. Rename Geometry namespace?
//15. Triangle::operator- ->Shape2D::operator- -> CANCELED -> OPERATOR- DELETED
//16. Polygon.cpp: Check valid vertices in constructor -> NEEDS THINKING -> THINKING DONE -> CHECKS ARE NOT NEEDED SO -> CANCELED
//17. Polygon.cpp: Polygon::generateVertices(): Implement



//#FIXME:
//1. Crash when calling Circle::draw() -> If Todo #6 is implemented, this is not needed anymore




int main()
{
	using Core::Renderer;
	using Core::Vertex;
	using Core::Geometry::Triangle;
	using Core::Geometry::RegularPolygon;
	using Core::Geometry::Shape2D;

	Core::Math::Line2D l(Vertex(-4, -4), Vertex(4, 4));
	Core::Math::Line2D l2(Vertex(-4, 4), Vertex(4, -4));

	std::cout << l.intersection(l2) << "\n";

	try
	{
		auto window = Renderer::Init(600, 600, "GL Utility");

	
		std::vector<std::unique_ptr<Shape2D> > triangles;

		triangles.push_back(std::make_unique<RegularPolygon>(Vertex(0, 0), 15, 1));

//		RegularPolygon p(Vertex(0, 0), 4, 1);

	//	triangles.push_back(std::make_unique<Triangle>(Vertex(-1, -1), Vertex(-0.5, 0), Vertex(0, -1)));
	//	triangles.push_back(std::make_unique<Triangle>(Vertex(1, -1), Vertex(0.5, 0), Vertex(0, -1)));
	//	triangles.push_back(std::make_unique<Triangle>(Vertex(-0.5, 0), Vertex(0.5, 0), Vertex(0, 1)));

//		Triangle t(Vertex(-1, -1), Vertex(-0.5, 0), Vertex(0, -1));
//		Triangle t2(Vertex(1, -1), Vertex(0.5, 0), Vertex(0, -1));
		Triangle t3(Vertex(-0.5, 0), Vertex(0.5, 0), Vertex(0, 1));
		Triangle t4(Vertex(-1, 1), Vertex(1, 1), Vertex(0, -1));

		Core::Geometry::Circle c(Vertex(0, 0), 0.5f, Core::Geometry::Circle::Precision(4));

		Core::Shader mainShader;
		std::string base = "C:/Users/michi_000/Desktop/C++/OpenGL/GL_Utility/x64/Debug/";
		std::string vtx = base + "shaders/vertex.glsl", frag = base + "shaders/fragment.glsl";

		mainShader.load(vtx, frag);

//		for (std::vector<std::unique_ptr<Shape2D>>::size_type i = 0; i < triangles.size(); ++i)
//		{
//			triangles[i]->setShader(&mainShader);
//		}

//		p.setShader(&mainShader);

//		t.setShader(&mainShader);
//		c.setShader(&mainShader);

//		Renderer::setClearColor(Core::Misc::Color(0.0f, 0.0f, 0.4f));

		static const float pi = 3.14159265f;

		do
		{
			float time = (float)(glfwGetTime() + 0.25);

			Renderer::setClearColor((Core::Misc::Color((float)(std::sin(time * pi / 3) / 2 + 0.5), (float)(std::sin(time + 2 * pi  / 3) / 2 + 0.5), (float)(std::sin(time + 4 * pi / 3) / 2 + 0.5))));

			mainShader.setUniform("globalTime", (float)glfwGetTime());

			Renderer::clear();

			for (auto & triangle : triangles)
			{
				Renderer::render(*triangle);
			}

//			Renderer::render(c);

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