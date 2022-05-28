//Author Tim Wieland
//Purpose: Calculate the mandelbrot set
//last update: 28-05-2022
#version 400 core

in vec2 mandelbrot_xy;
out vec4 FragColor;

uniform vec3 mb_area;	//transform-x - transform-y - area_width
uniform vec2 cpixel;	//center-pixel to zoom in on

const int max_iterations = 500;

//functions
int calc_iterations(double coord_x, double coord_y);
vec4 color_from_iterations(int it);
double color_picker_helper(double temp);

//variables used in main
int iterations;
double mapped_x, mapped_y;

double zoomed_x, zoomed_y;
//delta x and y to the center-pixel
double cdx, cdy;
void main()
{
	//map the x-coordinates from -1 - 1 (normalized on the screen) to -2 - 1 (mandelbrot-set-viewport)
	//the y-coordinate stay the same; needed to show the entire set
	//		-1########0########1 becomes (- = -1)
	//	--> -2#####-#####0#####1

	//Convertning the coordinates into the mandelbrot coordinate system
	mapped_x = 1.5f * (mandelbrot_xy.x + 1.0f) - 2.0f;
	mapped_y = mandelbrot_xy.y;

	//transforming so that the passed mb_area.xy is in the center.
	mapped_x += 1.5f * (mb_area.x + 1.0f) - 2.0f;
	mapped_y += mb_area.y;

	//mapped_x *= mb_area.z;
	//mapped_y *= mb_area.z;
	
	cdx = cpixel.x - mapped_x;
	cdy = cpixel.y - mapped_y;
	mapped_x = mapped_x + cdx - cdx * mb_area.z;
	mapped_y = mapped_y + cdy - cdy * mb_area.z;

	iterations = calc_iterations(mapped_x, mapped_y);
	
	FragColor = color_from_iterations(iterations);
}

int calc_iterations(double coord_x, double coord_y)
{
	double reel = coord_x;
	double imag = coord_y;
	int it = 1;
	double reel_new, imag_new;

	//storing the old reel and imaginary part at the beginning of each iteration
	//calculate the iterations
	while(it < max_iterations )
	{
		//square the imaginary number
		reel_new = reel * reel - imag * imag;
		imag_new = 2 * reel * imag;

		//add the first complex number
		reel_new += coord_x;
		imag_new += coord_y;

		//calculate the absolute value/modulus of the nth iterated number
		if(sqrt(reel_new * reel_new + imag_new * imag_new) > 2)
			return it;

		//new values become the old
		reel = reel_new;
		imag = imag_new;

		it++;
	}
	//no end found - 0 = black.
	return 0;
}

double hue;
vec4 return_color;
double r,g,b;

//just change the hue in respect to the number of iterations and maximal number of iterations in hsl
vec4 color_from_iterations(int it)
{
	if(it == 0)
		return vec4(0.0f, 0.0f, 0.0f, 1.0f);

	
	
	hue = double(it) / double(max_iterations );
	r = hue + 0.333f;
	g = hue;
	b = hue - 0.333f;
	if (r > 1) {
		r = r - 1;
	} else if (r < 0) {
		r = r + 1;
	}

	if (b > 1) {
		b = b - 1;
	} else if (b < 0) {
		b = b + 1;
	}

	return vec4(color_picker_helper(r) ,
				color_picker_helper(g),
				color_picker_helper(b),
				1.0f);
	
}

double color_picker_helper(double temp)
{
	if (6 * temp < 1)
		return 6 * temp;
	else if (2 * temp < 1)
		return 1.0f;
	else if (3 * temp < 2)
		return (0.666f - temp)*6;
	else
		return 0.0f;
}