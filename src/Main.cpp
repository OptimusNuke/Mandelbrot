#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader/Shader.h"
#include "window/Window.h"

int main()
{
	// create window
	Window window = { 2560, 1440, "Mandelbrot", true };

	Shader shaders = { "./src/shader/mandelbrot_shader.vs", "./src/shader/mandelbrot_shader.fs" };

	// create vertice	-	two triangles to fill the entire screen
	float vertices_triangles[] = {
		//x		y		z
		-1.0f,	1.0f,	0.0f,	//1
		-1.0f,	-1.0f,	0.0f,	//2
		1.0f,	1.0f,	0.0f,	//3
		1.0f,	-1.0f,	0.0f	//4
	};
		//		1-----3
		//		|	, |
		//		| ,   |
		//		2-----4
	unsigned int indices[] = {
			0, 1, 2,
			1, 2, 3
	};
	// Creating buffer objects etc...
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VAO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_triangles), vertices_triangles, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	//looking at the monitor coordinate system!
	//in GLSL: uniform vec3 mb_area = vec3(center.x, center.y, area-width);
	int mb_area_location = glGetUniformLocation(shaders.ID, "mb_area");
	//stores the center-pixel to zoom in on!
	//vec2 cpixel = vec2(x, y);
	int mb_center_pixel = glGetUniformLocation(shaders.ID, "cpixel");

	shaders.use();

	glUniform3f(mb_area_location, 0.0f, 0.0f, 1.0f);

	double xpos = 0, ypos = 0;
	double xtotal = 0, ytotal = 0;
	double zoom_level_total = 1.0;
	double cpixelx, cpixely;
	int width, height;
	bool new_click = false;
	int clicks = 0;
	// render loop
	
	//render the mandelbrot-set first
	glBindVertexArray(VAO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	// rendering
	glfwSwapBuffers(window.window);

	//and then allow zooming etc.
	while (!window.shouldClose())
	{
		// process input
		window.processInput();
		
		//get the normalized coordinates clicked on by the user
		window.MBProcessMouse(xpos, ypos, new_click);
		if (new_click)
		{
			clicks += 1;
			glfwGetWindowSize(window.window, &width, &height);
			//normalize the screen coordinates
			xpos = (xpos - width  / 2 ) / width * 2;
			ypos = -(ypos - height / 2) / height * 2;
			
			zoom_level_total *= 0.7;

			xtotal += xpos * zoom_level_total;
			ytotal += ypos * zoom_level_total;

			//pass the normalized coordinates to the shader in order to look at this position
			glUniform3f(mb_area_location, xtotal, ytotal, zoom_level_total);
			
			//calculate and pass the complex plane-coordinates of the pixel clicked on
			cpixelx = 1.5 * (xtotal + 1.0) - 2.0;
			cpixely = ytotal;
			glUniform2f(mb_center_pixel, cpixelx , cpixely);
			//std::cout << "clicks: " << clicks << " zoom: " << 3 / (3 * zoom_level_total) * 100 << "% x: " << cpixelx << " y: " << cpixely << std::endl;
			
			new_click = false;

			//draw everything
			//glBindVertexArray(VAO);
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			// rendering
			glfwSwapBuffers(window.window);
		}
		glfwPollEvents();
	}
	
	// clean and finnish
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	
	shaders.terminate();
	window.terminate();

	return 0;
}