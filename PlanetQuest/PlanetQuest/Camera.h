// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: Camera.h	
// Description	: Allows for rendering 3D Content
// Author		: Cameron Peet
// Mail			: Cameron.Peet@mediadesign.school.nz



#pragma once

#include "glut.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"

enum ProjectionType
{
	Perspective, Orthographic
};


class Camera
{
public:
	Camera();
	Camera(int _iWindowWidth, int _iWindowHeight);

public:

	void SetViewPort(int x, int y, int width, int height);
	void SetProjection(float fov, float aspectRatio, float zNear, float zFar);

	//right = view width, top = view height, left and bottom are usually 0 (Bottom Left Corner of screen)
	void SetOrthographic(float left, float right, float bottom, float top);
	void SetOrthographic();

	void SetPosition(const glm::vec3& pos);
	void Translate(const glm::vec3& delta, bool local = true);
	void SetRotation(const glm::quat& rot);
	void SetEulerAngles(const glm::vec3& eulerAngles);
	void Rotate(const glm::quat& rot);

	void SetProjectionType(ProjectionType _projectionType);

	glm::mat4 GetProjectionMatrix();
	glm::mat4 GetOrthoMatrix();
	glm::mat4 GetViewMatrix();
	glm::vec4 GetViewport() const;
	glm::quat GetRotation() const;
	glm::vec3 GetEulerAngles() const;
	glm::vec3 GetPosition() const;

protected:

	void UpdateViewMatrix();
	glm::vec4 m_Viewport;
	glm::vec3 m_Position;
	glm::quat m_Rotation;
	glm::mat4 m_ViewMatrix;
	glm::mat4 m_ProjectionMatrix;
	glm::mat4 m_OrthoMatrix;
	glm::mat4 m_PerspectiveMatrix;

	ProjectionType m_ProjectionType;

private:
	bool internalUpdateRequired;

};