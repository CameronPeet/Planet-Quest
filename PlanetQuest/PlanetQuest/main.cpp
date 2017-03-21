#include "glew.h"
#include "freeglut.h"
#include "SOIL.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <ctime>
#include <iostream>


#include "ShaderLoader.h"
#include "Model.h"
#include "Camera.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Menu.h"

//Logger
#include "CLogger.h"

//Shaders
#include "ResourceManager.h"


std::clock_t g_CurrentTicks;
std::clock_t g_PreviousTicks;
GLuint StandardShader;
Camera g_Camera;

/**
*
* Handles the mouse
* (Task ID: Main)
*
* @author  Cameron Peet
* @param button This is the mouse button.
* @param state This is the state.
* @param x This is the position.
* @param y This is the position.
* @return void
*
*/
void MouseGL(int button, int state, int x, int y)
{
	CSceneManager& _rSceneManager = CSceneManager::GetInstance();
	_rSceneManager.GetScene()->Mouse(button, state, x, y);
}

/**
*
* Keyboard press.
* (Task ID: Main)
*
* @author  Cameron Peet
* @param c This is the character.
* @param x This is the position.
* @param y This is the position.
* @return void
*
*/
void KeyboardGL(unsigned char c, int x, int y)
{
	CSceneManager& _rSceneManager = CSceneManager::GetInstance();
	_rSceneManager.GetScene()->KeyboardDown(c, x, y);
}

/**
*
* Keyboard release.
* (Task ID: Main)
*
* @author  Cameron Peet
* @param c This is the character.
* @param x This is the position.
* @param y This is the position.
* @return void
*
*/
void KeyboardUpGL(unsigned char c, int x, int y)
{
	CSceneManager& _rSceneManager = CSceneManager::GetInstance();
	_rSceneManager.GetScene()->KeyboardUp(c, x, y);
}


void SpecialGL(int c, int x, int y)
{
	switch (c)
	{
	case GLUT_KEY_UP:
		c = 'i';
		break;
	case GLUT_KEY_DOWN:
		c = 'k';
		break;
	case GLUT_KEY_LEFT:
		c = 'j';
		break;
	case GLUT_KEY_RIGHT:
		c = 'l';
		break;
	}

	CSceneManager& _rSceneManager = CSceneManager::GetInstance();
	_rSceneManager.GetScene()->KeyboardDown(c, x, y);
}

void SpecialUpGL(int c, int x, int y)
{
	switch (c)
	{
	case GLUT_KEY_UP:
		c = 'i';
		break;
	case GLUT_KEY_DOWN:
		c = 'k';
		break;
	case GLUT_KEY_LEFT:
		c = 'j';
		break;
	case GLUT_KEY_RIGHT:
		c = 'l';
		break;
	}

	CSceneManager& _rSceneManager = CSceneManager::GetInstance();
	_rSceneManager.GetScene()->KeyboardUp(c, x, y);
}

/**
*
* Initialises the program.
* (Task ID: Main)
*
* @author  Cameron Peet
* @param void
* @return true if successful, false if not
*
*/
bool init()
{
	CLogManager& _rMainLogger = CLogManager::GetInstance();
	_rMainLogger.WriteToAll("OpenGL init() Called");

	//Shaders
	ShaderLoader shaderLoader;
	StandardShader = shaderLoader.CreateProgram("Assets/Shaders/Shader.vert", "Assets/Shaders/Shader.frag");
	GLuint TextShader = shaderLoader.CreateProgram("Assets/Shaders/text.vert", "Assets/Shaders/text.frag");
	if (StandardShader != 0 && TextShader != 0)
	{
		CResources::AddShader("Shader", StandardShader);
		CResources::AddShader("Text", TextShader);
	}
	else
	{
		_rMainLogger.WriteToAll("OpenGL init() failed due to shader loading error");
		return false;
	}

	CResources::LoadAllTextures();
	CResources::LoadAllFonts();
	CResources::LoadAllSounds();


	//Camera Set up
	g_Camera.SetPosition(glm::vec3(0.0f, -15.0f, 0.0f));  //Set camera above the plane
	g_Camera.SetEulerAngles(glm::vec3(90.0f, 0, 0));		//Set a 60 degree angle around its x axis, to point towards the plane

	CSceneManager& _rSceneManager = CSceneManager::GetInstance();
	VALIDATE(_rSceneManager.Initialise());

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // GL_FILL, GL_LINE

	_rMainLogger.WriteToAll("OpenGL init() Complete");
	return true;
}

/**
*
* Renders the program.
* (Task ID: Main)
*
* @author  Cameron Peet
* @param void
* @return void
*
*/
void render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	CSceneManager& _rSceneManager = CSceneManager::GetInstance();
	_rSceneManager.GetScene()->Render(StandardShader, g_Camera);

	glUseProgram(StandardShader);
	glBindVertexArray(0);

	glutSwapBuffers();
}

/**
*
* Handles mouse over.
* (Task ID: Main)
*
* @author  Cameron Peet
* @param x This is the mouse position.
* @param y This is the mouse position.
* @return void
*/
void PassiveMotionGL(int x, int y)
{
	CSceneManager& _rSceneManger = CSceneManager::GetInstance();
	_rSceneManger.GetScene()->PassiveMotion(x, y);
}

/**
*
* Updates the program.
* (Task ID: Main)
*
* @author  Cameron Peet
* @param void
* @return void
*/
void update()
{

	g_CurrentTicks = std::clock();
	float deltaTicks = (float)(g_CurrentTicks - g_PreviousTicks);
	g_PreviousTicks = g_CurrentTicks;

	float fDeltaTime = deltaTicks / (float)CLOCKS_PER_SEC;

	CSceneManager& _rSceneManager = CSceneManager::GetInstance();
	_rSceneManager.GetScene()->Update(fDeltaTime);

	glutPostRedisplay(); //the render function is called 
}

/**
*
* Reshapes the program.
* (Task ID: Main)
*
* @author  Cameron Peet
* @param width This is the width.
* @param height This is the height.
* @return void
*/
void Reshape(int width, int height)
{
	if (height == 0)
	{
		height = 1;
	}

	g_Camera.SetViewPort(0, 0, width, height);
	g_Camera.SetProjection(60.0f, (float)(width / height), 0.1f, 100.0f);
	Utils::WIDTH = static_cast<float>(width);
	Utils::HEIGHT = static_cast<float>(height);
	CSceneManager& _rSceneManager = CSceneManager::GetInstance();
	_rSceneManager.GetScene()->Reshape(width, height);
}

/**
*
* Main setups the entire game.
* (Task ID: Main)
*
* @author  Cameron Peet
* @param argc
* @param argv Array
* @return Returns 0.
*/

int main(int argc, char **argv)
{
	// init glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(static_cast<int>(Utils::WIDTH), static_cast<int>(Utils::HEIGHT));
	glutCreateWindow("Planet Quest: The Forging of Wynne Jackson");

	//init GLEW
	glewInit();
	VALIDATE(init());

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	// register callbacks
	glutDisplayFunc(render);
	glutIdleFunc(update);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(KeyboardGL);
	glutKeyboardUpFunc(KeyboardUpGL);
	glutSpecialFunc(SpecialGL);
	glutSpecialUpFunc(SpecialUpGL);
	glutPassiveMotionFunc(PassiveMotionGL);
	glutMouseFunc(MouseGL);
	glutMainLoop();

	return 0;

}

