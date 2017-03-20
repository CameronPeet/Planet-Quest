//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: ShaderLoader.h
// Description	: Shader Loader declaration file
// Author		: Fawad 
//

#pragma once

#include "glew.h"
#include "freeglut.h"

#include <iostream>

class ShaderLoader
{
private:

	std::string ReadShader(char *filename);
	GLuint CreateShader(GLenum shaderType,
		std::string source,
		char* shaderName);

public:

	ShaderLoader(void);
	~ShaderLoader(void);
	GLuint CreateProgram(char* VertexShaderFilename,
		char* FragmentShaderFilename);
};
