#include "Shader.h"

#ifdef _DEBUG

#include <iostream>

#endif

namespace Core
{

	Shader::Shader() : ID(-1), loaded(false) {}
	Shader::~Shader() { release(); }

	Shader::Shader(std::string const& vertex_path, std::string const& framgent_path)
	{
		try
		{
			load(vertex_path, framgent_path);
		}
		catch (Exception e)
		{
			throw Exception(e.what());
		}
	}

	Shader::Shader(Shader&& other) : ID(other.ID)
	{
		//Make sure the old object doesn't own this shader anymore
		other.ID = 0;
	}

	Shader& Shader::operator=(Shader&& other)
	{
		//Check for self assignment
		if (this != &other)
		{
			release();
			//this->ID is now 0
			std::swap(other.ID, this->ID);
		}

		return *this;
	}

	void Shader::load(std::string const& vertex_path, std::string const& fragment_path)
	{
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		// ensure ifstream objects can throw exceptions:
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			// open files
			vShaderFile.open(vertex_path); //Crash here!
			fShaderFile.open(fragment_path);

			std::stringstream vShaderStream, fShaderStream;
			// read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			// close file handlers
			vShaderFile.close();
			fShaderFile.close();
			// convert stream into string

			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			throw Exception(std::string("Failure while reading shader source files: " + std::string(e.what())));
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();


		// 2. compile shaders
		unsigned int vertex, fragment;
		int success;
		char infoLog[512];

		// vertex Shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, nullptr);
		glCompileShader(vertex);
		// print compile errors if any
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
			std::string error = std::string("Vertex Shader Compilation Failed: ") + std::string(infoLog);
			throw Exception(error);
		};


		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, nullptr);
		glCompileShader(fragment);
		// print compile errors if any
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
			std::string error = std::string("Fragment Shader Compilation Failed: ") + std::string(infoLog);
			throw Exception(error);
		};


		// shader Program
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		// print linking errors if any
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(ID, 512, nullptr, infoLog);
			std::string error = std::string("Failed to link shader") + std::string(infoLog);
			throw Exception(error);
		}

		// delete the shaders as they're linked into our program now and no longer necessary
		glDeleteShader(vertex);
		glDeleteShader(fragment);

		loaded = true;
	}

	void Shader::use()
	{
		if (!loaded) return;

		glUseProgram(ID);
	}

	bool Shader::isLoaded() { return loaded; }

	void Shader::setUniform(std::string const & name, bool b) const
	{
		if (!loaded) return;

		auto location = glGetUniformLocation(ID, name.c_str());
		glUniform1i(location, (int)b);
	}

	void Shader::setUniform(std::string const & name, bool b0, bool b1) const
	{
		if (!loaded) return;
		auto location = glGetUniformLocation(ID, name.c_str());
		glUniform2i(location, (int)b0, (int)b1);
	}

	void Shader::setUniform(std::string const & name, bool b0, bool b1, bool b2) const
	{
		if (!loaded) return;
		auto location = glGetUniformLocation(ID, name.c_str());
		glUniform3i(location, (int)b0, (int)b1, (int)b2);
	}

	void Shader::setUniform(std::string const & name, bool b0, bool b1, bool b2, bool b3) const
	{
		if (!loaded) return;
		auto location = glGetUniformLocation(ID, name.c_str());
		glUniform4i(location, (int)b0, (int)b1, (int)b2, (int)b3);
	}

	void Shader::setUniform(std::string const & name, float f) const
	{
		if (!loaded) return;
		auto location = glGetUniformLocation(ID, name.c_str());
		glUniform1f(location, f);
	}

	void Shader::setUniform(std::string const & name, float f0, float f1) const
	{
		if (!loaded) return;
		auto location = glGetUniformLocation(ID, name.c_str());
		glUniform2f(location, f0, f1);
	}

	void Shader::setUniform(std::string const & name, float f0, float f1, float f2) const
	{
		if (!loaded) return;
		auto location = glGetUniformLocation(ID, name.c_str());
		glUniform3f(location, f0, f1, f2);
	}

	void Shader::setUniform(std::string const & name, float f0, float f1, float f2, float f3) const
	{
		if (!loaded) return;

		auto location = glGetUniformLocation(ID, name.c_str());
		glUniform4f(location, f0, f1, f2, f2);
	}

	void Shader::setUniform(std::string const & name, unsigned int i) const
	{
		if (!loaded) return;
		auto location = glGetUniformLocation(ID, name.c_str());
		glUniform1ui(location, i);
	}

	void Shader::setUniform(std::string const & name, unsigned int i0, unsigned int i1) const
	{
		if (!loaded) return;
		auto location = glGetUniformLocation(ID, name.c_str());
		glUniform2ui(location, i0, i1);
	}

	void Shader::setUniform(std::string const & name, unsigned int i0, unsigned int i1, unsigned int i2) const
	{
		if (!loaded) return;
		auto location = glGetUniformLocation(ID, name.c_str());
		glUniform3ui(location, i0, i1, i2);
	}

	void Shader::setUniform(std::string const & name, unsigned int i0, unsigned int i1, unsigned int i2, unsigned int i3) const
	{
		if (!loaded) return;
		auto location = glGetUniformLocation(ID, name.c_str());
		glUniform4ui(location, i0, i1, i2, i3);
	}

	void Shader::setUniform(std::string const & name, glm::vec2 const & vec) const
	{
		if (!loaded) return;
		auto location = glGetUniformLocation(ID, name.c_str());
		glUniform2fv(location, 1, glm::value_ptr(vec));
	}

	void Shader::setUniform(std::string const & name, glm::vec3 const & vec) const
	{
		if (!loaded) return;
		auto location = glGetUniformLocation(ID, name.c_str());
		glUniform3fv(location, 1, glm::value_ptr(vec));
	}

	void Shader::setUniform(std::string const & name, glm::vec4 const & vec) const
	{
		if (!loaded) return;
		auto location = glGetUniformLocation(ID, name.c_str());
		glUniform4fv(location, 1, glm::value_ptr(vec));
	}

	void Shader::setUniform(std::string const & name, glm::mat2 const & mat) const
	{
		if (!loaded) return;
		auto location = glGetUniformLocation(ID, name.c_str());
		glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(mat));
	}

	void Shader::setUniform(std::string const & name, glm::mat3 const & mat) const
	{
		if (!loaded) return;
		auto location = glGetUniformLocation(ID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(mat));
	}

	void Shader::setUniform(std::string const & name, glm::mat4 const & mat) const
	{
		if (!loaded) return;
		auto location = glGetUniformLocation(ID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
	}

	void Shader::setUniform(std::string const & name, glm::mat2x3 const & mat) const
	{
		if (!loaded) return;
		auto location = glGetUniformLocation(ID, name.c_str());
		glUniformMatrix2x3fv(location, 1, GL_FALSE, glm::value_ptr(mat));
	}

	void Shader::setUniform(std::string const & name, glm::mat2x4 const & mat) const
	{
		if (!loaded) return;
		auto location = glGetUniformLocation(ID, name.c_str());
		glUniformMatrix2x4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
	}

	void Shader::setUniform(std::string const & name, glm::mat3x2 const & mat) const
	{
		if (!loaded) return;
		auto location = glGetUniformLocation(ID, name.c_str());
		glUniformMatrix3x2fv(location, 1, GL_FALSE, glm::value_ptr(mat));
	}

	void Shader::setUniform(std::string const & name, glm::mat3x4 const & mat) const
	{
		if (!loaded) return;
		auto location = glGetUniformLocation(ID, name.c_str());
		glUniformMatrix3x4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
	}

	void Shader::setUniform(std::string const & name, glm::mat4x2 const & mat) const
	{
		if (!loaded) return;
		auto location = glGetUniformLocation(ID, name.c_str());
		glUniformMatrix4x2fv(location, 1, GL_FALSE, glm::value_ptr(mat));
	}

	void Shader::setUniform(std::string const & name, glm::mat4x3 const & mat) const
	{
		if (!loaded) return;
		auto location = glGetUniformLocation(ID, name.c_str());
		glUniformMatrix4x3fv(location, 1, GL_FALSE, glm::value_ptr(mat));
	}

	void Shader::release()
	{
		glDeleteShader(this->ID);
		ID = 0;
		this->loaded = false;
	}

}