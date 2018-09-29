#include "simpleRenderer.h"


namespace graphics {

	VertexArray *SimpleRenderer::m_VAO;
	Buffer *SimpleRenderer::m_VBO;
	Buffer *SimpleRenderer::m_TBO;
	IndexBuffer *SimpleRenderer::m_IBO;

	FontLoader *SimpleRenderer::m_fontLoader;
	Shader *SimpleRenderer::m_shader;
	Shader *SimpleRenderer::m_textShader;

	bool renderInitialized;
	bool fontInitialized;

	void SimpleRenderer::init(Shader *shader, Shader *textShader, std::string fontpath) {
		m_shader = shader;
		m_textShader = textShader;

		m_fontLoader = new FontLoader(fontpath);

		GLfloat textureCoords[] = {
			0.0, 0.0,
			0.0, 1.0,
			1.0, 1.0,
			1.0, 0.0
		};

		GLushort indices[] = {
			0, 1, 2,
			0, 2, 3
		};

		m_VAO = new VertexArray();
		m_IBO = new IndexBuffer(indices, 6);
		m_VBO = new Buffer(0, 8, 2, GL_DYNAMIC_DRAW);
		m_TBO = new Buffer(textureCoords, 8, 2, GL_STATIC_DRAW);
		m_VAO->addBuffer(m_VBO, 0);
		m_VAO->addBuffer(m_TBO, 1);
	}

	void SimpleRenderer::renderBox(float x, float y, float w, float h) {
		m_shader->enable();
		m_shader->setUniform4f("color", glm::vec4(1.0f, 0.5f, 0.0f, 1.0f));
		m_VAO->bind();
		
		GLfloat vertices[] = {
			x + 0, y + 0,
			x + 0, y + h,
			x + w, y + h,
			x + w, y + 0
		};
		m_VBO->setBufferData(vertices, 8, 2);
		
		m_IBO->bind();
		glDrawElements(GL_TRIANGLES, m_IBO->getCount(), GL_UNSIGNED_SHORT, 0);
	}

	void SimpleRenderer::renderBox(float x, float y, float w, float h, GLuint texture) {
		m_shader->enable();
		m_shader->setUniform4f("color", glm::vec4(1.0f, 0.5f, 0.0f, 1.0f));
		
		m_VAO->bind();
		glBindTexture(GL_TEXTURE_2D, texture);
		
		GLfloat vertices[] = {
			x + 0, y + 0,
			x + 0, y + h,
			x + w, y + h,
			x + w, y + 0
		};
		m_VBO->setBufferData(vertices, 8, 2);
		
		m_IBO->bind();
		glDrawElements(GL_TRIANGLES, m_IBO->getCount(), GL_UNSIGNED_SHORT, 0);
	}

	void SimpleRenderer::renderText(float x, float y, float w, float h, std::string text, glm::vec3 color, int xAlign, int yAlign) {
		m_fontLoader->renderText(m_textShader, text, x, y, w, h, color, xAlign, yAlign);
	}

}