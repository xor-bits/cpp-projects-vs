#include "../engine.h"
#include "logic/game.h"

#include <omp.h>
#include <Windows.h>

#define M_WINDOW_WIDTH		900
#define M_WINDOW_HEIGHT		600
#define M_ASPECT			(float)M_WINDOW_WIDTH / (float)M_WINDOW_HEIGHT

graphics::Window *window;
graphics::Shader *shader;
logic::GameLoop *gameloop;
graphics::Camera *camera;
Game game;

long long tmp = 0;

void keyPress(int key, int action) {
	if (action == GLFW_PRESS) game.keyPress(key);
}

void buttonPress(int button, int action) {
	if (action == GLFW_PRESS) game.buttonPress(button);
}

void scroll(double y) {
	game.scroll(y);
}

void render() {
	window->clear();

	long long startTime = tools::Clock::getMicroseconds();
	game.render();
	tmp += (tools::Clock::getMicroseconds() - startTime) / 1000.0;

	window->update();
	window->input();
}

int x = 0;
void update() {
	if (window->close() || window->getKey(GLFW_KEY_ESCAPE)) gameloop->stop();
	game.update();
	x++;
	//if (x > 100) {
	//	x = 0;
	//	std::cout << "FPS: " << gameloop->getFPS() << " (" << tmp / (float)gameloop->getFPS() << "ms)" << std::endl;
	//	std::cout << "UPS: " << gameloop->getUPS() << std::endl;
	//	tmp = 0;
	//}

}

void rapid() {
	game.rapidUpdate();
}

//int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow) {
int main() {
	//Window
	window = new graphics::Window(M_WINDOW_WIDTH, M_WINDOW_HEIGHT, "Test game", false);
	window->setButtonCallback(buttonPress);
	window->setKeyboardCallback(keyPress);
	window->setScrollCallback(scroll);

	//Create shader
	shader = new graphics::Shader("shaders/texture.vert.glsl", "shaders/texture.frag.glsl");
	
	//Shader stuff
	float debugZoom = 3.0;
	glm::mat4 orthographic = glm::ortho(-M_ASPECT * debugZoom, M_ASPECT* debugZoom, debugZoom, -debugZoom);
	shader->enable(); shader->SetUniformMat4("pr_matrix", orthographic);

	//Main game loop
	gameloop = new logic::GameLoop(render, update, rapid, 100, 10000);
	game.init(shader, window, gameloop);
	gameloop->start();
	game.close();
}