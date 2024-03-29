#include "gl.h"

#include "../internal_libs.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>


namespace oe {

	void GL::enableDepth() {
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glDepthMask(GL_FALSE);
	}

	void GL::disableDepth() {
		glDisable(GL_DEPTH_TEST);
	}

	void GL::setLineWidth(float w) {
		glLineWidth(w);
	}

	void GL::setPointRadius(float w) {
		glPointSize(w);
	}

	void GL::enableBlending() {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void GL::disableBlending() {
		glDisable(GL_BLEND);
	}

	void GL::setBackFaceCulling(bool on) {
		if (on) glEnable(GL_CULL_FACE);
		else glDisable(GL_CULL_FACE);

		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);
	}

	void GL::setSwapInterval(unsigned int interval) {
		glfwSwapInterval(interval);
	}

	int GL::checkGLErrors() {
		GLenum err = glGetError();
		if (err != 0) {
			std::string errorText;
			switch (err)
			{
			case GL_NO_ERROR:
				errorText = "How did you get an error while not getting an error?";
				break;
			case GL_INVALID_ENUM:
				errorText = "Invalid enum!";
				break;
			case GL_INVALID_VALUE:
				errorText = "Invalid value!";
				break;
			case GL_INVALID_OPERATION:
				errorText = "Invalid operation!";
				break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:
				errorText = "Invalid framebuffer operation!";
				break;
			case GL_OUT_OF_MEMORY:
				errorText = "Out of memory!";
				break;
			default:
				errorText = "Unknown error!";
				break;
			}
			spdlog::error("OpenGL ({}):\n{}", err, errorText);
			return err;
		}
		return 0;
	}

	std::string GL::getRenderer() {
		return std::string((char*)glGetString(GL_RENDERER));
	}

	std::string GL::getVendor() {
		return std::string((char*)glGetString(GL_VENDOR));
	}

}
