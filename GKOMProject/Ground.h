#pragma once
namespace Ground
{
	const GLfloat size = 2000.0f;
	GLfloat groundVertices[] = {
		-size, 0.0f, -size,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
		-size, 0.0f, size,		0.0f, size/2,		0.0f, 1.0f, 0.0f,
		size, 0.0f, -size,		size/2, 0.0f,		0.0f, 1.0f, 0.0f,
		-size, 0.0f, size,		0.0f, size/2,		0.0f, 1.0f, 0.0f,
		size, 0.0f, -size,		size/2, 0.0f,		0.0f, 1.0f, 0.0f,
		size, 0.0f, size,		size/2, size/2,		0.0f, 1.0f, 0.0f
	};


	class Ground
	{
	public:
		GLuint VAO;
		GLuint VBO;
		Ground()
		{
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(groundVertices), groundVertices, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
			glEnableVertexAttribArray(3);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}
		~Ground()
		{
			glDeleteVertexArrays(1, &VAO);
			glDeleteBuffers(1, &VBO);
		}
		void draw(Shader shader, Texture texture)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture.Id);
			glUniform1i(glGetUniformLocation(shader.Program, "myTexture"), 0);
			glUniform1i(glGetUniformLocation(shader.Program, "useTexture"), 1);
			glBindVertexArray(VAO);

			glm::mat4 model;
			glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1,
				GL_FALSE, glm::value_ptr(model));

			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindVertexArray(0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

	};
}