#include "Renderer.h"
#include "Triangle.h"
#include "Color.h"
#include "Math.h"
#include "Circle.h"
#include "RegularPolygon.h"
#include "Utility.h"

#include <GLM\gtc\matrix_transform.hpp>
#include <memory>


#include "assert.h"

#include "sse_util.h"

#include "test_allocator.h"
#include "stack_allocator.h"
#include "pool_allocator.h"


//#TODO:
//1. Fix warnings -> #DONE
//TODO list COMPLETE: learnopengl.com -> add features


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

class some_huge_class
{
	long long lots_of_memory[123456789];
};

class destructor_print
{
public:
	int m_id;
	~destructor_print() { std::cout << "destructor_print::~destructor_print()\n"; }
};

int main()
{
	static const glm::mat4 Identity(1.0f);

	using namespace Core;

	using Geometry::Triangle;
	using Geometry::RegularPolygon;
	using Geometry::Shape2D;
	using Geometry::Circle;


	__m128 v = _mm_set_ps(2.8f, 4.1f, 1.6f, 22.5f);

	__m128 v2 = _mm_set_ps(3, 1, 8, 2);

	auto v3 = sse::add_m128(v, v2);

	float x = sse::element_m128(v3, 0);
	float err = sse::element_m128(v3, 50);

/*Allocator debugging*/
	try
	{
		mem::test_allocator<int> alloc(3);

		auto root = alloc.get();
		auto lastelem = alloc.get(2);
		*lastelem = 5;
		std::cout << *alloc.get(2) << std::endl;


		/*BAD ALLOCATOR*/
	}
	catch (const std::exception&)
	{

	}


/*Stack allocator*/ /*GOOD ALLOCATOR*/
	try
	{
		std::cout << "\n\n\n";
		std::cout << "----STACK ALLOCATOR----\n";

		mem::stack_allocator alloc(20 * sizeof(long long));

		auto destr_identify = alloc.allocate<destructor_print>();
		destr_identify->m_id = 42;

		auto p = alloc.allocate<double>();

		alloc.deallocate(p.get());
		alloc.deallocate(destr_identify.get());

		auto ptr = alloc.allocate<int>();


		std::cout << "-----------------------\n";
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	}

/*Pool allocator*/ /*GOOD ALLOCATOR*/
	try
	{ 
		std::cout << "\n\n\n";
		std::cout << "----POOL ALLOCATOR----\n";

		mem::pool_allocator<destructor_print> alloc;

		std::cout << "----------------------"
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	}

	std::cin.get();

/*	try
	{
		auto window = Renderer::Init(800, 600, "GL Utility");

		glEnable(GL_DEBUG_OUTPUT);
//		glDebugMessageCallback((GLDEBUGPROC)MessageCallback, nullptr);
	
		std::vector<std::unique_ptr<Shape2D> > shapes;
//		shapes.push_back(std::unique_ptr<Shape2D>(new Triangle(
//			glm::vec3(-1.0f, -1.0f, 0.0f), 
//			glm::vec3(1.0f, -1.0f, 0.0f), 
//			glm::vec3(0.0f, 1.0f, 0.0f)
//		))); 

		float vertices[] = {
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};

		// world space positions of our cubes
		glm::vec3 cubePositions[] = {
			glm::vec3(0.0f,  0.0f,  0.0f),
			glm::vec3(2.0f,  5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3(2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3(1.3f, -2.0f, -2.5f),
			glm::vec3(1.5f,  2.0f, -2.5f),
			glm::vec3(1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
		};

		unsigned int VBO, VAO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
		glEnableVertexAttribArray(0);
		

		Shader mainShader;
		std::string base = "C:/Users/michi_000/Desktop/C++/OpenGL/GL_Utility/x64/Debug/";
		std::string vtx = base + "shaders/vertex.glsl", frag = base + "shaders/fragment.glsl";

		mainShader.load(vtx, frag);

//		for (auto & shape : shapes)
//		{
	//		shape->setShader(&mainShader);
//		}

		glm::mat4 model { Identity };
		model = glm::rotate(model, Math::Angle(-55.0f).radians(), glm::vec3(1.0f, 0.0f, 0.0f));

		glm::mat4 view { Identity };
//		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -0.3f));
		
		glm::mat4 projection { Identity };
		projection = glm::perspective(Math::Angle(45.0f).radians(), 800.0f / 600.0f, 0.1f, 100.0f);

		std::cout << model << std::endl;
		std::cout << view << std::endl;
		std::cout << projection;

		static const float pi = 3.14159265f;

		mainShader.use();
		
		

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

			glBindVertexArray(VAO);
			for (unsigned int i = 0; i < 10; i++)
			{
				// calculate the model matrix for each object and pass it to shader before drawing
				glm::mat4 model { Identity };
				model = glm::translate(model, cubePositions[i]);
				float angle = 20.0f * i;
				model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
				mainShader.setUniform("model", model);
				mainShader.setUniform("view", view);
				mainShader.setUniform("projection", projection);

				glDrawArrays(GL_TRIANGLES, 0, 36);
			}


			Renderer::SwapBuffers();
			glfwPollEvents();
		} while (!Renderer::WindowShouldClose() && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS);
	}
	catch (Core::Misc::Exception e)
	{
		logpp::Console::error(e.what());
		std::cin.get();
	}
	catch (Core::Shader::Exception e)
	{
		logpp::Console::error(e.what());
		std::cin.get();
	}

	glfwTerminate();

*/ //<-- Old rendering code, disabled as we are testing allocators now
	return 0;
}