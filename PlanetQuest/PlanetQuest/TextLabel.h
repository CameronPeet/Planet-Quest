//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: TextLabel.cpp
// Description	: Define, Update and Draw Text on the screen
// Author		: Cameron Peet 
// Mail			: Cameron.Peet@mediadesign.school.nz
//


#pragma once

#include "glew.h"
#include "freeglut.h"
#include "SOIL.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "ShaderLoader.h"
#include "Camera.h"
#include "GL_Utils.h"

#include "ft2build.h"
#include FT_FREETYPE_H  

#include "ResourceManager.h"

#include <map>
#include <string>
#include <iostream>

enum TextType
{
	MENU,
	TIMER,
	GAMEOVER,
	SPLASH
};

class TextLabel
{
public:
	TextLabel(TextType _type, std::string text, std::string font = 0);
	~TextLabel();

	void Render(Camera& camera);
	void setPosition(glm::vec3 _position);
	void setColor(glm::vec3 _color);
	void setHighlight(glm::vec3 _color) { highlight = _color; };
	void setScale(GLfloat _scale);
	
	void setText(std::string _text);
	void AddText(unsigned char c);
	void LoadFont(std::string path);
	
	void setActive(bool b){ m_bIsActive = b; };
	void setButton(bool b){	m_bIsButton = b; };
	void setHighlighted(bool b){ m_bIsHighlighted = b; };

	bool isActive() { return m_bIsActive; };
	bool isButton() { return m_bIsButton; };
	bool isHighlighted() { return m_bIsHighlighted; };

	std::string getText(){ return text; };
	glm::vec3 position;
	
	int width, height;
	
	bool m_bIsButton = true;
	bool m_bIsActive = true;
	bool m_bIsHighlighted = false;

	TextType GetTextType();


private:
	std::string text;
	GLfloat scale;
	glm::vec3 color;
	glm::vec3 highlight;

	GLuint VAO, VBO, program;
	std::map<GLchar, Character> Characters;
	TextType m_TextType;


	

	//For the sake of this smaller game, an unchanging shader can be static.
	//static GLuing program;
};

