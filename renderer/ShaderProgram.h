#pragma once
#include <GL/glew.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
class ShaderProgram
{
public:
	ShaderProgram();
	ShaderProgram(const char* vs_path, const char* fs_path);
	void addMatrix4fv(const glm::mat4& mat, const std::string& name);
	void setUniform1i(int value, const std::string& name);
	void setUniform1iv(int* samplers, size_t size, const std::string& name);
private:
	void LoadShader(const char* path, std::string& src);
	void CompileShader(std::string& src, uint32_t shader);
	uint32_t m_renderID;
	std::string vs_src, fs_src;
};