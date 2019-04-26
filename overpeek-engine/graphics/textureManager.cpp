#include "textureManager.h"

#include "../utility/logger.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <GL/glew.h>

#define USING_OPENCV 0
#if USING_OPENCV
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#endif

namespace oe {

	unsigned int TextureManager::mTextures[MAX_TEXTURES];

	unsigned int TextureManager::loadTexture(std::string path, int id) {
		int width, height, nrChannels;
		GLubyte *tmpdata = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
		if (!tmpdata) {
			oe::Logger::out("Image couldn't be loaded at path (", path.c_str(), ")", oe::error);
			system("pause");
			exit(-1);
		}

		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tmpdata);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(tmpdata);

		mTextures[id] = texture;
		return texture;
	}

	unsigned int TextureManager::loadTextureAtlas(std::string path, int id, unsigned int r) {

		int dataSize = 4 * r * r * 256;

		int width, height, nrChannels;
		GLubyte *tmpdata = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
		if (!tmpdata) {
			oe::Logger::out("Image couldn't be loaded at path (", path.c_str(), ")", oe::error);
			system("pause");
			exit(-1);
		}
		//1 048 576
		//1 048 575
		GLubyte *data = new GLubyte[dataSize];
		for (int i = 0; i < 256; i++) {
			for (int y = 0; y < r; y++) {
				for (int x = 0; x < r; x++) {
					int tmpdataX = x + (i % 16) * r;
					int tmpdataY = y * r * 16;
					int tmpdataI = floor(i / 16) * r * r * 16;

					data[4 * (x + y * r + i * r * r) + 0] = *(tmpdata + 4 * (tmpdataX + tmpdataY + tmpdataI) + 0);
					data[4 * (x + y * r + i * r * r) + 1] = *(tmpdata + 4 * (tmpdataX + tmpdataY + tmpdataI) + 1);
					data[4 * (x + y * r + i * r * r) + 2] = *(tmpdata + 4 * (tmpdataX + tmpdataY + tmpdataI) + 2);
					data[4 * (x + y * r + i * r * r) + 3] = *(tmpdata + 4 * (tmpdataX + tmpdataY + tmpdataI) + 3);
				}
			}
		}
		stbi_image_free(tmpdata);

		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D_ARRAY, texture);

		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA8, r, r, 256);
		glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0, r, r, 256, GL_RGBA, GL_UNSIGNED_BYTE, data);
		//glGenerateMipmap(GL_TEXTURE_2D_ARRAY);

		//GLint max_layers;
		//glGetIntegerv(GL_MAX_ARRAY_TEXTURE_LAYERS, &max_layers);
		//oe::Logger::out(oe::info, "Max OpenGL layers", max_layers);
		
		mTextures[id] = texture;
		return texture;
	}

	unsigned int TextureManager::getTexture(int id) {
		return mTextures[id];
	}

	void TextureManager::saveTexture(std::string path, unsigned char *data, int width, int height, bool preview) {
#if USING_OPENCV
		cv::Mat image(height, width, CV_8UC3, data);
		cv::cvtColor(image, image, CV_RGB2BGR);
		cv::imwrite((std::string)"./mandelbrot" + std::to_string(time(0)) + (std::string)".png", image);

		if (!preview) return;
		cv::namedWindow("Preview", cv::WINDOW_AUTOSIZE);
		cv::imshow("Preview", image);
#endif
	}

}