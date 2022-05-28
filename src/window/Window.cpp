#include "Window.h"

//helper
//TODO: Create in Window.h as a private method
void __framebuffer_size_callback__(GLFWwindow* window, int width, int height);

Window::Window(int width, int height, const char* title, bool maximize)
{
	window_max_width = width;
	window_max_height = height;

	//init
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create window
	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (maximize)
		glfwMaximizeWindow(window);

	// error check
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, __framebuffer_size_callback__);
	
	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}
}

bool Window::shouldClose(void)
{
	return glfwWindowShouldClose(window);
}

void Window::setCloseKey(int key)
{
	_window_close_key = key;
}

void Window::draw(void)
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Window::terminate(void)
{
	glfwTerminate();
}

void Window::processInput(void)
{
	if (glfwGetKey(window, _window_close_key) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void Window::MBProcessMouse(double &xpos, double &ypos, bool &new_click)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS
		&& _is_pressed == false)
	{
		_is_pressed = true;
		glfwGetCursorPos(window, &xpos, &ypos); 
		new_click = true;
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE
		&& _is_pressed == true)
	{
		_is_pressed = false;
		new_click = false;
	}
}

//helper for resizing
void __framebuffer_size_callback__(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}