#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
	: m_renderID(0) {}
ShaderProgram::ShaderProgram(const char* vs_path, const char* fs_path)
	: m_renderID(0)			
{
	uint32_t vs, fs;
	vs = glCreateShader(GL_VERTEX_SHADER);
	fs = glCreateShader(GL_FRAGMENT_SHADER);
	std::cout << "GL Error: " << glGetError() << " " << __FILE__ << " " << __LINE__ << std::endl;
	LoadShader(vs_path, vs_src);
	LoadShader(fs_path, fs_src);
	
	CompileShader(vs_src, vs);
	CompileShader(fs_src, fs);
	
	m_renderID = glCreateProgram();
	std::cout << "GL Error: " << glGetError() << " " << __FILE__ << " " << __LINE__ << std::endl;
	glAttachShader(m_renderID, vs);
	glAttachShader(m_renderID, fs);	
	glLinkProgram(m_renderID);	
	std::cout << "GL Error: " << glGetError() << " " << __FILE__ << " " << __LINE__ << std::endl;

	glValidateProgram(m_renderID);	
	std::cout << "GL Error: " << glGetError() << " " << __FILE__ << " " << __LINE__ << std::endl;

	glUseProgram(m_renderID);
	std::cout << "GL Error: " << glGetError() << " " << __FILE__ << " " << __LINE__ << std::endl;
	glDeleteShader(vs);
	glDeleteShader(fs);
	std::cout << "GL Error: " << glGetError() << " " << __FILE__ << " " << __LINE__ << std::endl;

}
void ShaderProgram::LoadShader(const char* path, std::string& src)
{
	std::string line;
	std::ifstream stream(path);
	std::stringstream ss;
	if (stream.is_open())
	{
		while (std::getline(stream, line))
		{
			ss << line << std::endl;			
		}
		src = ss.str();
	}
	else
		std::cout << "Shader File Failed To Open" << std::endl;
}
void ShaderProgram::CompileShader(std::string& src, uint32_t shader)
{
	const char* c = src.c_str();
	glShaderSource(shader, 1, &c, nullptr);
	std::cout << "GL Error: " << glGetError() << " " << __FILE__ << " " << __LINE__ << std::endl;
	glCompileShader(shader);
	std::cout << "GL Error: " << glGetError() << " " << __FILE__ << " " << __LINE__ << std::endl;

}
void ShaderProgram::addMatrix4fv(const glm::mat4& mat, const std::string& name)
{
	int pos = glGetUniformLocation(m_renderID, name.c_str());
	glUniformMatrix4fv(pos, 1, GL_FALSE, &mat[0][0]);
}
// value is the texture slot
void ShaderProgram::setUniform1i(int value, const std::string& name)
{
	std::cout << "GL Error: " << glGetError() << " " << __FILE__ << " " << __LINE__ << std::endl;
	int pos = glGetUniformLocation(m_renderID, name.c_str());
	std::cout << "GL Error: " << glGetError() << " " << __FILE__ << " " << __LINE__ << std::endl;

	glUniform1i(pos, value);
	std::cout << "GL Error: " << glGetError() << " " << __FILE__ << " " << __LINE__ << std::endl;
}
void ShaderProgram::setUniform1iv(int* samplers, size_t size, const std::string& name)
{
	std::cout << "GL Error: " << glGetError() << " " << __FILE__ << " " << __LINE__ << std::endl;
	int pos = glGetUniformLocation(m_renderID, name.c_str());
	std::cout << "GL Error: " << glGetError() << " " << __FILE__ << " " << __LINE__ << std::endl;
	glUniform1iv(pos, size, samplers);
	std::cout << "GL Error: " << glGetError() << " " << __FILE__ << " " << __LINE__ << std::endl;
}