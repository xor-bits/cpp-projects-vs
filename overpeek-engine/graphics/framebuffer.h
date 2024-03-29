#pragma once

#include "texture.h"
#include "../internal_libs.h"

namespace oe {

	class FrameBuffer {
	private:
		unsigned int p_rbo;
		unsigned int p_id;

		Texture *p_texture;
		int p_width;
		int p_height;

	public:
		FrameBuffer(int width, int height);
		~FrameBuffer();

		void bind();
		static void unbind();

		void clear();
		void clearColor(glm::vec4 c);

		inline int getWidth() { return p_width; }
		inline int getHeight() { return p_height; }
		inline float getAspect() { return (float)p_width / (float)p_height; }
	};

}