#pragma once

#include <string>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace graphics {

	class Window {
	private:
		//Variables
		unsigned int mWidth, mHeight;
		std::string mTitle;
		GLFWwindow *mWindow;
		static double mMouseX, mMouseY;
		static bool mKeys[];
		static bool mButtons[];

		//Functions
		bool mInit();
		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	public:
		//Variables

		
		//Functions
		Window(unsigned int width, unsigned int height, std::string title);
		~Window();

		static void checkErrors();
		bool close();
		void update();
		void clear();

		inline bool getButton(int button) { return mButtons[button]; }
		inline bool getKey(int key) { return mKeys[key]; }
		inline void getMousePos(double &mouseX, double &mouseY) { mouseX = mMouseX / mWidth * 16.0; mouseY = mMouseY / mHeight * 9.0; }
	};

}