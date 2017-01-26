#include <iostream>
#include <vector>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "Cog.h"
#include "Cuboid.h"
#include "Cylinder.h"
#include "Shader.h"
#include "Skybox.h"
#include "Ground.h"


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void do_movement();
GLuint loadCubemap();

const GLuint SCREEN_WIDTH = 800;
const GLuint SCREEN_HEIGHT = 600;
const char WINDOW_TITLE[] = "GKOM - przenosnik";

bool keys[1024];
bool firstMouse = true;
Camera camera(glm::vec3(0.0f, 10.0f, 10.0f));
GLfloat lastX = 400, lastY = 300;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

bool movementOn = false;
float cogSpeedValue = 10.0f;

glm::vec3 lightPos(1.2f, 5.0f, 2.0f);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE, nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);

	glewExperimental = GL_TRUE;
	glewInit();

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_DEPTH_TEST);

//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	Shader mainShader("shader.vert", "shader.frag");
	Shader skyboxShader("skybox.vert", "skybox.frag");

	// init textures:
	Texture woodTexture("wood.jpg");
	Texture metalTexture("metal.jpg");
	Texture grassTexture("grass.jpg");

	// init skybox:
	GLuint cubemapTexture = loadCubemap();
	Skybox::Skybox skybox(&skyboxShader, cubemapTexture);

	// init objects:
	Ground::Ground ground;
	Cuboid::Cuboid base;
	Cylinder::Cylinder trunk(&deltaTime);
	Cog::Cog* cog[2];
	cog[0] = new Cog::Cog(&deltaTime);
	cog[1] = new Cog::Cog(&deltaTime);


	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();
		do_movement();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// skybox:
		glDepthMask(GL_FALSE);
		skyboxShader.Use();
		glm::mat4 view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
		glm::mat4 projection = glm::perspective(camera.Zoom, float(SCREEN_WIDTH)/ float(SCREEN_HEIGHT), 0.1f, 100.0f);
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		skybox.draw();
		glDepthMask(GL_TRUE);

		// scene:
		mainShader.Use();
		
		// create light:
		GLint lightPosLoc = glGetUniformLocation(mainShader.Program, "lightPos");
		glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);

		view = camera.GetViewMatrix();
		projection = glm::perspective(camera.Zoom, float(SCREEN_WIDTH) / float(SCREEN_HEIGHT), 0.1f, 1000.0f);
		glUniformMatrix4fv(glGetUniformLocation(mainShader.Program, "view"),
			1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(mainShader.Program, "projection"),
			1, GL_FALSE, glm::value_ptr(projection));		
		GLint modelLoc = glGetUniformLocation(mainShader.Program, "model");
		GLint textureLoc = glGetUniformLocation(mainShader.Program, "myTexture");
		GLboolean useTextureLoc = glGetUniformLocation(mainShader.Program, "useTexture");
		
		//draw ground:
		ground.draw(mainShader, grassTexture);

		// draw base cuboid:
		base.draw(mainShader);

		// draw trunk:
		trunk.draw(mainShader, woodTexture);
		trunk.rotate(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		trunk.translate(glm::vec3(0.0f, Cuboid::height + Cylinder::radius, -15.0f));
		if (!movementOn)
		{
			cogSpeedValue = 0.0f;
		}
		trunk.movementSpeed = cogSpeedValue;

		// draw cogs:
		cog[0]->draw(mainShader, metalTexture);
		cog[0]->translate(glm::vec3(-3.0f, Cuboid::height+Cog::height/2, 0.0f));
		cog[0]->rotationSpeed = -cogSpeedValue;
		cog[1]->draw(mainShader, metalTexture);
		cog[1]->translate(glm::vec3(3.0f, Cuboid::height + Cog::height / 2, 0.0f));
		cog[1]->rotationSpeed = cogSpeedValue;

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}

void do_movement()
{
	if (keys[GLFW_KEY_W])
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		movementOn = !movementOn;
		cogSpeedValue = 5.0f;
	}
	if (key == GLFW_KEY_EQUAL && action == GLFW_PRESS)
		cogSpeedValue += 2.0f;
	if (key == GLFW_KEY_MINUS && action == GLFW_PRESS)
		cogSpeedValue -= 2.0f;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

GLuint loadCubemap()
{
	std::vector<const GLchar*> faces;
	faces.push_back("Skybox/right.jpg");
	faces.push_back("Skybox/left.jpg");
	faces.push_back("Skybox/top.jpg");
	faces.push_back("Skybox/bottom.jpg");
	faces.push_back("Skybox/back.jpg");
	faces.push_back("Skybox/front.jpg");

	GLuint textureID;
	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0);

	int width, height;
	unsigned char* image;

	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	for (GLuint i = 0; i < faces.size(); i++)
	{
		image = SOIL_load_image(faces[i], &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
			GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image
		);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	return textureID;
}