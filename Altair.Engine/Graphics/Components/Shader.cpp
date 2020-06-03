#include "Shader.h"
#include "../../FileSystem/FileReaders/FileReader.h"
#include <GL/glew.h>

namespace Altair
{
	Shader::Shader()
	{
		const GLuint program = glCreateProgram();
		const GLuint vertex_id = glCreateShader(GL_VERTEX_SHADER);
		const GLuint fragment_id = glCreateShader(GL_FRAGMENT_SHADER);

		const FileReader vertex = FileReader("Vertex.vert", "GameData\\Assets\\Shaders");
		const std::string vector_string = vertex.read_from_file();
		const char* v = vector_string.c_str();

		const FileReader fragment = FileReader("Fragment.frag", "GameData\\Assets\\Shaders");
		const std::string fragment_string = fragment.read_from_file();
		const char* f = fragment_string.c_str();

		glShaderSource(vertex_id, 1, &v, nullptr);
		glCompileShader(vertex_id);

		glShaderSource(fragment_id, 1, &f, nullptr);
		glCompileShader(fragment_id);

		glAttachShader(program, vertex_id);
		glAttachShader(program, fragment_id);

		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vertex_id);
		glDeleteShader(fragment_id);

		m_shader_id = program;
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_shader_id);
	}

	void Shader::enable() const
	{
		glUseProgram(m_shader_id);
	}

	void Shader::disable()
	{
		glUseProgram(0);
	}
}
