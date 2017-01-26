#pragma once

namespace Cuboid
{
	const float length = 35.0f;
	const float width = 15.0f;
	const float height = 2.0f;
	const glm::vec3 color(0.4f, 0.1f, 0.0f);

	GLfloat cuboidVertices[] = {
		// bottom:
		-width / 2, 0.0f,   -length / 2,	color.x, color.y, color.z,		0.0f, -1.0f, 0.0f,
		 width / 2, 0.0f,   -length / 2,	color.x, color.y, color.z,		0.0f, -1.0f, 0.0f,
		 width / 2, 0.0f,    length / 2,	color.x, color.y, color.z,		0.0f, -1.0f, 0.0f,
		-width / 2, 0.0f,   -length / 2,	color.x, color.y, color.z,		0.0f, -1.0f, 0.0f,
		-width / 2, 0.0f,    length / 2,	color.x, color.y, color.z,		0.0f, -1.0f, 0.0f,
		 width / 2, 0.0f,    length / 2,	color.x, color.y, color.z,		0.0f, -1.0f, 0.0f,
		 // top:
		 -width / 2, height, -length / 2,	color.x, color.y, color.z,		0.0f,  1.0f,  0.0f,
		 -width / 2, height,  length / 2,	color.x, color.y, color.z,		0.0f,  1.0f,  0.0f,
		  width / 2, height,  length / 2,	color.x, color.y, color.z,		0.0f,  1.0f,  0.0f,
		 -width / 2, height, -length / 2,	color.x, color.y, color.z,		0.0f,  1.0f,  0.0f,
		  width / 2, height, -length / 2,	color.x, color.y, color.z,		0.0f,  1.0f,  0.0f,
		  width / 2, height,  length / 2,	color.x, color.y, color.z,		0.0f,  1.0f,  0.0f,
		  // front:
		 -width / 2, 0.0f,   -length / 2,	color.x, color.y, color.z,		0.0f,  0.0f,  -1.0f,
		  width / 2, 0.0f,   -length / 2,	color.x, color.y, color.z,		0.0f,  0.0f,  -1.0f,
		  width / 2, height, -length / 2,	color.x, color.y, color.z,		0.0f,  0.0f,  -1.0f,
		 -width / 2, 0.0f,   -length / 2,	color.x, color.y, color.z,		0.0f,  0.0f,  -1.0f,
		 -width / 2, height, -length / 2,	color.x, color.y, color.z,		0.0f,  0.0f,  -1.0f,
		  width / 2, height, -length / 2,	color.x, color.y, color.z,		0.0f,  0.0f,  -1.0f,
		  // back:
		 -width / 2, 0.0f,    length / 2,	color.x, color.y, color.z,		0.0f,  0.0f,  -1.0f,
		  width / 2, 0.0f,    length / 2,	color.x, color.y, color.z,		0.0f,  0.0f,  -1.0f,
		  width / 2, height,  length / 2,	color.x, color.y, color.z,		0.0f,  0.0f,  -1.0f,
		 -width / 2, 0.0f,    length / 2,	color.x, color.y, color.z,		0.0f,  0.0f,  -1.0f,
		 -width / 2, height,  length / 2,	color.x, color.y, color.z,		0.0f,  0.0f,  -1.0f,
		  width / 2, height,  length / 2,	color.x, color.y, color.z,		0.0f,  0.0f,  -1.0f,
		  // left:
		 -width / 2, 0.0f,    length / 2,	color.x, color.y, color.z,		-1.0f, 0.0f,  0.0f,
		 -width / 2, height,  length / 2,	color.x, color.y, color.z,		-1.0f, 0.0f,  0.0f,
		 -width / 2, 0.0f,   -length / 2,	color.x, color.y, color.z,		-1.0f, 0.0f,  0.0f,
		 -width / 2, 0.0f,   -length / 2,	color.x, color.y, color.z,		-1.0f, 0.0f,  0.0f,
		 -width / 2, height, -length / 2,	color.x, color.y, color.z,		-1.0f, 0.0f,  0.0f,
		 -width / 2, height,  length / 2,	color.x, color.y, color.z,		-1.0f, 0.0f,  0.0f,
		  // right:
		 width / 2, 0.0f,   -length / 2,	color.x, color.y, color.z,		1.0f, 0.0f,  0.0f,
		 width / 2, 0.0f,    length / 2,	color.x, color.y, color.z,		1.0f, 0.0f,  0.0f,
		 width / 2, height,  length / 2,	color.x, color.y, color.z,		1.0f, 0.0f,  0.0f,
		 width / 2, 0.0f,   -length / 2,	color.x, color.y, color.z,		1.0f, 0.0f,  0.0f,
		 width / 2, height, -length / 2,	color.x, color.y, color.z,		1.0f, 0.0f,  0.0f,
		 width / 2, height,  length / 2,	color.x, color.y, color.z,		1.0f, 0.0f,  0.0f

	};

	class Cuboid
	{
	public:
		GLuint VAO;
		GLuint VBO;

		Cuboid()
		{
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(cuboidVertices), cuboidVertices, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
			glEnableVertexAttribArray(3);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}

		~Cuboid()
		{
			glDeleteVertexArrays(1, &VAO);
			glDeleteBuffers(1, &VBO);
		}

		void draw(Shader shader)
		{
			glUniform1i(glGetUniformLocation(shader.Program, "useTexture"), 0);
			glm::mat4 model;
			glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"),
				1, GL_FALSE, glm::value_ptr(model));
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			glBindVertexArray(0);
		}
	private:
		glm::vec3 translationVec;
	};
}
