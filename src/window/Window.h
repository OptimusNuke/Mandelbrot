#pragma once
#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

class Window
{
private:
	int _window_close_key = GLFW_KEY_SPACE;
	int window_max_width, window_max_height;
	bool fullscreen = false;
	bool _is_pressed = false;

public:
	//window
	GLFWwindow* window;

	Window(int width, int height, const char* title, bool maximize = false);
	bool shouldClose(void);
	void processInput(void);
	void MBProcessMouse(double& xpos, double& ypos, bool &new_click);

	//Default: GLFW_KEY_SPACE
	void setCloseKey(int key);

	void draw(void);
	void terminate(void);
};

#endif