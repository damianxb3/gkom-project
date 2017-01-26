#pragma once
#include "Texture.h"

#define M_PI 3.14159265f

namespace Cylinder
{
	float height = 15.0f;
	GLfloat radius = 1.0f;
	GLuint segments = 32;

	float a = radius * cos(M_PI / segments);
	float b = radius * sin(M_PI / segments);

	GLfloat cylinderVertices[] = {
		 0.0f, 0.0f,   0.0f,	0.5f, 0.0f,		 0.0f,  -1.0f,  0.0f,
		 b,    0.0f,   a,		0.0f, 0.0f,		 0.0f,  -1.0f,  0.0f,
		-b,    0.0f,   a,	    1.0f, 1.0f,		 0.0f,  -1.0f,  0.0f,

		 0.0f, height, 0.0f,	0.5f, 0.5f,		 0.0f,  1.0f,  0.0f,
		 b,    height, a,		0.0f, 0.0f,		 0.0f,  1.0f,  0.0f,
		-b,	   height, a,		1.0f, 1.0f,		 0.0f,  1.0f,  0.0f,

		 b,    height, a,		0.0f, 0.0f,		 0.0f,  0.0f,  1.0f,
		-b,    height, a,		1.0f, 1.0f,		 0.0f,  0.0f,  1.0f,
		 b,	   0.0f,   a,		0.0f, 0.0f,		 0.0f,  0.0f,  1.0f,

		-b,    height, a,		0.0f, 0.0f,		 0.0f,  0.0f,  1.0f,
		 b,    0.0f,   a,		1.0f, 1.0f,		 0.0f,  0.0f,  1.0f,
		-b,    0.0f,   a,		0.0f, 0.0f,		 0.0f,  0.0f,  1.0f,
	};
	

	float MIN_BOUNDARY = -1.0f;
	float MAX_BOUNDARY = 16.0f;

	class Cylinder
	{
	public:
		GLuint VAO;
		GLuint VBO;
		float movementSpeed = 2.0f;

		Cylinder(float* deltaTime)
		{
			this->deltaTime = deltaTime;
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(cylinderVertices), cylinderVertices, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
			glEnableVertexAttribArray(3);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}

		~Cylinder()
		{
			glDeleteVertexArrays(1, &VAO);
			glDeleteBuffers(1, &VBO);
		}

		void draw(Shader shader, Texture texture)
		{
			if (movementSpeed < 0 && currentZPosition > MIN_BOUNDARY ||
				movementSpeed > 0 && currentZPosition < MAX_BOUNDARY)
				currentZPosition += *deltaTime * movementSpeed/10;
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture.Id);
			glUniform1i(glGetUniformLocation(shader.Program, "myTexture"), 0);
			glUniform1i(glGetUniformLocation(shader.Program, "useTexture"), 1);
			glBindVertexArray(VAO);

			for (GLuint i = 0; i < segments; i++)
			{
				glm::mat4 model;
				model = glm::translate(model, translationVec);
				model = glm::translate(model, glm::vec3(0.0f, 0.0f, currentZPosition));
				model = glm::rotate(model, glm::radians(rotationAngle), rotationAxis);
				model = glm::rotate(model, glm::radians(i * 360.0f/segments), glm::vec3(0.0f, 1.0f, 0.0f));
				glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1,
					GL_FALSE, glm::value_ptr(model));

				glDrawArrays(GL_TRIANGLES, 0, 12);
			}
			glBindVertexArray(0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		void translate(glm::vec3 translationVec)
		{
			this->translationVec = translationVec;
		}

		void rotate(float angle, glm::vec3 axis)
		{
			this->rotationAxis = axis;
			this->rotationAngle = angle;
		}
	private:
		glm::vec3 translationVec;
		glm::vec3 rotationAxis;
		float rotationAngle = 0.0f;
		float currentZPosition = 0.0f;
		float* deltaTime;
	};
}
