// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: Model.cpp
// Description	: Encapsulate required functionality and components to define and render a predefined shape.
// Author		: Cameron Peet
// Mail			: Cameron.Peet@mediadesign.school.nz

#include "Model.h"
#include "Camera.h"

Model::Model()
{

}

Model::~Model()
{

}

/*@Author : Cameron Peet
@Purpose : Choose a static function to define the vertices for the models shape, according to the enum provided
@param ModelType : Determine the shape of the model
@param Filename : Store the filepath to the desired texture (Only 1 for now ).
*/

Model::Model(ModelType Shape, char* Filename)
{
	switch (Shape)
	{
	case QUAD:
		Utils::SetQuad(*this);
		break;

	case CUBE:
		Utils::SetCube(*this);
		break;

	case TRIANGLE:
		Utils::SetTriangle(*this);
		break;

	case PYRAMID:
		Utils::SetPyramid(*this);
		break;

	case CIRCLE:
		Utils::SetCircle(*this);
		break;
	case SPHERE:
		Utils::SetSphere(*this);
		break;
	}

	m_Scale = glm::vec3(1, 1, 1);
	texturePath = Filename;
}

/*Author : Cameron Peet
Purpose :  Initialise the vao, vbo and ebo, and load any textures
*/
bool Model::Initialise()
{
	//Buffer Creation
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), &indices[0], GL_STATIC_DRAW);

	//Attribute Setting
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Texture Position
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//Vertex Normals
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Set texutre wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	Texture texture;

	if (CResources::GetTexture(texturePath, texture))
	{
		this->texture = texture.texture;
		return true;
	}
	else
	{
		int width, height;
		unsigned char* image = SOIL_load_image("Pyramid.jpg", &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0);
		return true;
	}

	return false;
}


/* 
@Author : Cameron Peet
@Purpose : Render the model in a 3D manner using the Camera, consistent across all models 
@param program : The coupled vertex and fragment shader desired for the rendering of the calling instance 
@param camera :  Address to the main camera, providing the view and projection matrices for rendering the view of the model.
*/
void Model::Render(GLuint program, Camera& camera, Light* lightSource)
{

	//enable blending
	//glEnable(GL_CULL_FACE);
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);

	glUseProgram(program);


	//GLfloat currentTime = (GLfloat)glutGet(GLUT_ELAPSED_TIME);
	//currentTime = currentTime / 1000;//convert millisecond to seconds

	////get uniform location from program and set currentTime value
	//GLint currentTimeLocation = glGetUniformLocation(program, "currentTime"); 
	//glUniform1f(currentTimeLocation, currentTime); 
	GLint objectColorLoc = glGetUniformLocation(program, "objectColor");
	GLint modelLoc = glGetUniformLocation(program, "model");
	GLint viewLoc = glGetUniformLocation(program, "view");
	GLint projLoc = glGetUniformLocation(program, "projection");

	glm::mat4 model;
	//Translate the model according to its position and apply the rotation
	model = glm::translate(model, m_Position) * glm::mat4(m_Rotation);
	//Scale the model according to private member m_Scale
	model = glm::scale(model, m_Scale);

	//Send the values to the uniform variables in the program supplied in the function call
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.GetViewMatrix()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera.GetProjectionMatrix()));
	glUniform3fv(objectColorLoc, 1, glm::value_ptr(ObjectColor));

	//Bind the texture to the uniform variable 
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(program, "Texture"), 0);

	//Bind, draw and unbind the vertex array 
	glBindVertexArray(vao);
	if(isTriangleBased)
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	else if (isLineBased)
	{
		glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, 0);

	}
	glBindVertexArray(0);


	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);
}

/**
*
* Sets the texture
* (Task ID: Model)
*
* @author  Cameron Peet
* @param _texturePath file name
* @return void
*
*/
void Model::setTexture(char* _texturePath)
{
	Texture t;

	bool result = CResources::GetTexture(_texturePath, t);

	texture = t.texture;
}

void Model::SetPosition(glm::vec3 _position)
{
	m_Position = _position;
}

glm::vec3 Model::getPosition()
{
	return m_Position;
}

glm::vec3 Model::getScale()
{
	return m_Scale;
}