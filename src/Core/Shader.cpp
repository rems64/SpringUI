#include <SPUI/Shader.hpp>

SPUI::Shader::Shader(): program(0)
{
}

SPUI::Shader::Shader(const std::string& filepath)
{
    ParseShader(filepath);
    unsigned int program = glCreateProgram();
    unsigned int vs = SPUI::Shader::CompileShader(GL_VERTEX_SHADER, vertexSource);
    unsigned int fs = SPUI::Shader::CompileShader(GL_FRAGMENT_SHADER, fragmentSource);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);
}

SPUI::Shader::~Shader()
{
    glDeleteProgram(program);
}

/*
void SPUI::Shader::CreateShader(const std::string& filepath)
{
    ParseShader(filepath);
    unsigned int program = glCreateProgram();
    unsigned int vs = SPUI::Shader::CompileShader(GL_VERTEX_SHADER, source.VertexSource);
    unsigned int fs = SPUI::Shader::CompileShader(GL_FRAGMENT_SHADER, source.FragmentSource);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);
}
*/

bool SPUI::Shader::Compile()
{
    program = glCreateProgram();
    unsigned int vs = SPUI::Shader::CompileShader(GL_VERTEX_SHADER, vertexSource);
    unsigned int fs = SPUI::Shader::CompileShader(GL_FRAGMENT_SHADER, fragmentSource);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return true;
}

void SPUI::Shader::Bind()
{
    GLCall(glUseProgram(program));
}

void SPUI::Shader::Unbind()
{
    GLCall(glUseProgram(0));
}

GLint SPUI::Shader::getUniform(const GLchar* location)
{
    return GLint(glGetUniformLocation(program, location));
}

void SPUI::Shader::setUniform1f(const GLchar* location, GLfloat v1)
{
    GLint concernedUniform = glGetUniformLocation(program, location);
    GLCall(glUniform1f(concernedUniform, v1));
}

void SPUI::Shader::setUniform1f(GLint target, GLfloat v1)
{
    GLCall(glUniform1f(target, v1));
}

void SPUI::Shader::setUniform2f(const GLchar* location, GLfloat v1, GLfloat v2)
{
    GLint concernedUniform = glGetUniformLocation(program, location);
    glUniform2f(concernedUniform, v1, v2);
}

void SPUI::Shader::setUniform2f(GLint target, GLfloat v1, GLfloat v2)
{
    glUniform2f(target, v1, v2);
}

void SPUI::Shader::setUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int SPUI::Shader::GetUniformLocation(const std::string& name)
{
    GLCall(int location = glGetUniformLocation(program, name.c_str()));
    if (location == -1)
        std::cout << "Uniform doesn't exists" << std::endl;
    return location;
}

void SPUI::Shader::ParseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("//shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    };
    vertexSource = ss[0].str();
    fragmentSource = ss[1].str();
}

unsigned int SPUI::Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    return id;
}
