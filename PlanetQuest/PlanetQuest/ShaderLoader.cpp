//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: ShaderLoader.h
// Description	: Shader Loader implementation file
// Author		: Unknown
//

#include "ShaderLoader.h" 
#include "CLogger.h"
#include<iostream>
#include<fstream>
#include<vector>

ShaderLoader::ShaderLoader(void) {}
ShaderLoader::~ShaderLoader(void) {}

/**
*
* This function reads the shader.
* (Task ID: ShaderLoader)
*
* @author Unknown
* @param filename This is the file name.
* @return Returns the shader code.
*
*/
std::string ShaderLoader::ReadShader(char *filename)
{
	std::string shaderCode;
	std::ifstream file(filename, std::ios::in);

	if (!file.good()) {
		std::cout << "Can't read file " << filename << std::endl;
		std::terminate();
	}

	file.seekg(0, std::ios::end);
	shaderCode.resize((unsigned int)file.tellg());
	file.seekg(0, std::ios::beg);
	file.read(&shaderCode[0], shaderCode.size());
	file.close();
	return shaderCode;
}

/**
*
* This function creates the shader.
* (Task ID: ShaderLoader)
*
* @author Unknown
* @param shaderType This is the shader type.
* @param source This is the source.
* @param shaderName This is the shader name.
* @return Returns the shader.
*
*/
GLuint ShaderLoader::CreateShader(GLenum shaderType, std::string
	source, char* shaderName)
{
	CLogManager& _rMainLogger = CLogManager::GetInstance();

	int compile_result = 0;

	GLuint shader = glCreateShader(shaderType);
	const char *shader_code_ptr = source.c_str();
	const int shader_code_size = source.size();

	glShaderSource(shader, 1, &shader_code_ptr, &shader_code_size);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result);

	//check for errors
	if (compile_result == GL_FALSE)
	{

		int info_log_length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> shader_log(info_log_length);
		glGetShaderInfoLog(shader, info_log_length, NULL, &shader_log[0]);
		std::cout << "ERROR compiling shader: " << shaderName << std::endl << &shader_log[0] << std::endl;
		std::string ErrorCode;
		ErrorCode = "ERROR compiling shader: ";
		ErrorCode += shaderName;
		_rMainLogger.WriteToAll(ErrorCode);
		return 0;
	}
	std::string Success;
	Success += shaderName;
	Success += " shader compiled successfuly";
	_rMainLogger.WriteToAll(Success);
	return shader;
}

/**
*
* This function creates the program.
* (Task ID: ShaderLoader)
*
* @author Unknown
* @param vertexShaderFilename This is the file name.
* @param fragmentShaderFilename This is the file name.
* @return Returns the program.
*
*/
GLuint ShaderLoader::CreateProgram(char* vertexShaderFilename,
	char* fragmentShaderFilename)
{
	CLogManager& _rMainLogger = CLogManager::GetInstance();

	//read the shader files and save the code
	std::string vertex_shader_code = ReadShader(vertexShaderFilename);
	std::string fragment_shader_code = ReadShader(fragmentShaderFilename);

	GLuint vertex_shader = CreateShader(GL_VERTEX_SHADER, vertex_shader_code, "vertex shader");
	GLuint fragment_shader = CreateShader(GL_FRAGMENT_SHADER, fragment_shader_code, "fragment shader");

	int link_result = 0;
	//create the program handle, attatch the shaders and link it
	GLuint program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_result);
	//check for link errors
	if (link_result == GL_FALSE)
	{

		int info_log_length = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> program_log(info_log_length);
		glGetProgramInfoLog(program, info_log_length, NULL, &program_log[0]);
		std::cout << "Shader Loader : LINK ERROR" << std::endl << &program_log[0] << std::endl;
		std::string error = "Shader Loader : LINK ERROR -> ";
		error += &program_log[0];
		_rMainLogger.WriteToAll("Shader Loader : LINK ERROR");
		return 0;
	}
	_rMainLogger.WriteToAll("Shader Linking Successful");
	return program;
}