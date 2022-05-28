//Author Tim Wieland
//Purpose: Calculate the mandelbrot set
//last update: 28-05-2022

#version 400 core
layout (location = 0) in vec3 pos;
out vec2 mandelbrot_xy;

void main()
{
	gl_Position = vec4(pos.x, pos.y, pos.z, 1.0f);
	mandelbrot_xy = vec2(pos.x, pos.y);
}