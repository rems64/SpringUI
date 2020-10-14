#pragma once

#include <string>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <filesystem>

#include <SPUI/Debug.hpp>
#include <glm/glm.hpp>

namespace SPUI
{
	class Shader
	{
	public:
		Shader();
		Shader(const std::string&);
		~Shader();

		//void CreateShader(const std::string&);
		bool Compile();
		void Bind();
		void Unbind();

		GLint getUniform(const GLchar*);
		void setUniform1f(const GLchar*, GLfloat);
		void setUniform1f(GLint, GLfloat);

		void setUniform2f(const GLchar*, GLfloat, GLfloat);
		void setUniform2f(GLint, GLfloat, GLfloat);

		void setUniformMat4f(const std::string& name, const glm::mat4& matrix);

	private:
		std::string vertexSource;
		std::string fragmentSource;
		unsigned int program;

		//static unsigned int CreateShader(const std::string&, const std::string&);
		int GetUniformLocation(const std::string& name);
		void ParseShader(const std::string&);
		static unsigned int CompileShader(unsigned int, const std::string&);
	};
	struct ShaderProgramSource
	{
		const std::string& VertexSource;
		const std::string& FragmentSource;
	};
}
