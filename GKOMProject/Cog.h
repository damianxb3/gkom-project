#pragma once
#include "Texture.h"
#include "Shader.h"

namespace Cog
{
	float base = 1.5f;
	float length = 2.5f;
	float height = 0.6f;
	GLfloat elementTriangleVertices[] = {
		-base / 2, 0.0f,       0.0f,	0.0f, 0.0f,		0.0f, -length, height / 2,
		 base / 2, 0.0f,       0.0f,	1.0f, 0.0f,		0.0f, -length, height / 2,
		 0.0f,     height / 2, length,	0.5f, 0.5f,		0.0f, -length, height / 2,

		-base / 2, height,     0.0f,	0.0f, 0.0f,		0.0f, length, height / 2,
		 base / 2, height,	   0.0f,	1.0f, 0.0f,		0.0f, length, height / 2,
		 0.0f,	   height / 2, length,	0.5f, 0.5f,		0.0f, length, height/2,

		-base / 2, height,     0.0f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		 0.0f,     height / 2, length,	0.5f, 0.5f,		0.0f, 0.0f, 0.0f,
		-base / 2, 0.0f,       0.0f,	1.0f, 0.0f,		0.0f, 0.0f, 0.0f,

		base / 2,  0.0f,       0.0f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f,      height / 2, length,	0.5f, 0.5f,		0.0f, 0.0f, 0.0f,
		base / 2,  height,     0.0f,	1.0f, 0.0f,		0.0f, 0.0f, 0.0f
	};

	class Cog
	{
	public:
		GLuint VAO;
		GLuint VBO;

		float rotationSpeed = 0.0f;

		Cog(GLfloat* deltaTime)
		{
			this->deltaTime = deltaTime;
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(elementTriangleVertices), elementTriangleVertices, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
			glEnableVertexAttribArray(3);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}

		~Cog()
		{
			glDeleteVertexArrays(1, &VAO);
			glDeleteBuffers(1, &VBO);
		}

		void draw(Shader shader, Texture texture)
		{
			currentRotation += *deltaTime * rotationSpeed;
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture.Id);
			glUniform1i(glGetUniformLocation(shader.Program, "myTexture"), 0);
			glUniform1i(glGetUniformLocation(shader.Program, "useTexture"), 1);
			glBindVertexArray(VAO);
			GLuint COG_ELEMENTS_NUMBER = 10;
			for (GLuint i = 0; i < COG_ELEMENTS_NUMBER; i++)
			{
				glm::mat4 model;
				model = glm::translate(model, translationVec);
				model = glm::rotate(model, glm::radians(currentRotation), glm::vec3(0.0f, 1.0f, 0.0f));
				model = glm::rotate(model, glm::radians(i* 360.0f/ COG_ELEMENTS_NUMBER), glm::vec3(0.0f, 1.0f, 0.0f));
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
	private:
		glm::vec3 translationVec;
		float currentRotation = 0.0f;
		float* deltaTime;
	};
}
