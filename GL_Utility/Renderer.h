#ifndef _RENDERER_H_
#define _RENDERER_H_

#pragma warning(disable: 4005)

#include <GL\glew.h>
#include <GL\glfw3.h>

#include <type_traits>
#include <memory>

#include <typeinfo>

#include "Exception.h"
#include "Color.h"
#include "ScreenSize.h"

namespace Core
{

	class Renderer
	{
	public:
		using ScreenSize = Misc::ScreenSize;

		Renderer() = delete;

		static GLFWwindow* Init(ScreenSize::type width, ScreenSize::type height, char const* caption);
		static void SwapBuffers();
		static bool WindowShouldClose();

		static GLFWwindow* getWindow();

		//Returns true if Renderer and OpenGL are successfully initialized, false if otherwise
		static bool wasInit();

		template<typename Obj>
		static void render(Obj const& object)
		{
			//Remove reference for draw() checking, as we passed using move semantics
			using removedRef = std::remove_const<std::remove_reference_t<Obj>>::type;

			static_assert(Traits::HasDrawMethod<Obj>::value,
				"void Renderer::render(Obj object): Type Obj must have accessible draw() member returning void and taking no parameters");

			if (!wasInit())
				throw Misc::Exception("void Renderer::render(Obj object): Call Renderer::Init() first before attempting to render.");

			object.draw();
		}

		static void setClearColor(Misc::Color const& c);
		static void clear(GLenum flags = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	private:
		static bool is_init;
		static GLFWwindow* m_window;
		static GLuint VAO;

		class Traits
		{
		public:
			template<typename T>
			struct HasDrawMethod
			{
			private:
				template<typename U>
				static constexpr auto check(U*) ->
					typename std::is_same<
					decltype(std::declval<U>().draw()), //Attempt to call draw() member and see if it is correct and has the right return type
					void
					>::type;

				template<typename>
				static constexpr std::false_type check(...);

				using type = decltype(check<T>(nullptr));

			public:
				static constexpr bool value = type::value;
			};
		};

		static void SetGLFWWindowHints();
		static void InitGLFW();
		static void InitGLEW();
		static GLFWwindow* InstantiateWindow(ScreenSize::type width, ScreenSize::type height, char const* caption);
		static GLuint CreateVAO();


	};

}

#endif //_RENDERER_H_

