#ifndef _SHADER_H_
#define _SHADER_H_


//OpenGL Headers
#include <GL\glew.h>
#include <GL\glfw3.h>

//GLM Headers
#include <GLM/glm.hpp>
#include <GLM/gtc/type_ptr.hpp>

//STL Headers
#include <string>
#include <sstream>
#include <fstream>
#include <type_traits>

namespace Core
{

	class Shader
	{
	public:
		Shader();
		Shader(std::string const& vertex_path, std::string const& fragment_path);

		~Shader();

		//These have to be deleted, as this object owns an OpenGL resource, see also
		//https://www.khronos.org/opengl/wiki/Common_Mistakes#The_Object_Oriented_Language_Problem

		Shader(Shader const& other) = delete;
		Shader& operator=(Shader const& other) = delete;

		//move constructor/assignment operator, see also the link above

		Shader(Shader&& other);
		Shader& operator=(Shader&& other);



		//Activates the shader
		void use();

		bool isLoaded();

		void load(std::string const& vertex_path, std::string const& fragment_path);

		using size_type = unsigned int;

		//Uniform utility functions

		void setUniform(std::string const& name, bool b) const;
		void setUniform(std::string const& name, bool b0, bool b1) const;
		void setUniform(std::string const& name, bool b0, bool b1, bool b2) const;
		void setUniform(std::string const& name, bool b0, bool b1, bool b2, bool b3) const;

		void setUniform(std::string const& name, float f) const;
		void setUniform(std::string const& name, float f0, float f1) const;
		void setUniform(std::string const& name, float f0, float f1, float f2) const;
		void setUniform(std::string const& name, float f0, float f1, float f2, float f3) const;

		void setUniform(std::string const& name, unsigned int i) const;
		void setUniform(std::string const& name, unsigned int i0, unsigned int i1) const;
		void setUniform(std::string const& name, unsigned int i0, unsigned int i1, unsigned int i2) const;
		void setUniform(std::string const& name, unsigned int i0, unsigned int i1, unsigned int i2, unsigned int i3) const;

		void setUniform(std::string const& name, glm::vec2 const& vec) const;
		void setUniform(std::string const& name, glm::vec3 const& vec) const;
		void setUniform(std::string const& name, glm::vec4 const& vec) const;

		void setUniform(std::string const& name, glm::mat2 const& mat) const;
		void setUniform(std::string const& name, glm::mat3 const& mat) const;
		void setUniform(std::string const& name, glm::mat4 const& mat) const;

		void setUniform(std::string const& name, glm::mat2x3 const& mat) const;
		void setUniform(std::string const& name, glm::mat2x4 const& mat) const;

		void setUniform(std::string const& name, glm::mat3x2 const& mat) const;
		void setUniform(std::string const& name, glm::mat3x4 const& mat) const;

		void setUniform(std::string const& name, glm::mat4x2 const& mat) const;
		void setUniform(std::string const& name, glm::mat4x3 const& mat) const;

		class Exception
		{
		private:
			std::string msg;
		public:
			explicit Exception(std::string m) : msg(m) {}
			std::string what() { return msg; }
		};

	private:
		GLuint ID = 0;
		bool loaded;

		void release();

	};

}


#endif