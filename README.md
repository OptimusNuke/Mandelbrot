# Mandelbrot set generator

Tried to implement my own Mandelbrot set generator.

### What I did
I started from the basic Mandelbrot set-formula as shown in [Wikipedia](https://en.wikipedia.org/wiki/Mandelbrot_set) without looking up any done projects.
In order to draw the set, I used opengl and implemented most maths in the fragment shader.
To pick a color by the number of iterations needed for the number to "explode", I used a simple hsl-formula.
I only alterated the hue-value and set the saturation to 100% and the luminance to 50%.

### What I learned
With this project, I first came in contact with complex numbers. I began by learning about complex numbers.
As I started implementing the formulas, I looked for a "good" way to display what I wanted to display.
The solution I came up with - opengl and using the fragment shader - needed me to first learn about opengl.
While this experience definitely was worth my time, I would rather use another api to do graphics.
In the end, I learned to stick to a project I want to finnish and to do the work.
It sure payed off!

### Some impressions of my work

![Mandelbrot 1](pictures/Mandelbrot_1.jpg/?raw=true "Mandelbrot 1")

![Mandelbrot 2](pictures/Mandelbrot_2.jpg/?raw=true "Mandelbrot 2")

![Mandelbrot 3](pictures/Mandelbrot_3.jpg/?raw=true "Mandelbrot 3")

![Mandelbrot 4](pictures/Mandelbrot_4.jpg/?raw=true "Mandelbrot 4")

![Mandelbrot 5](pictures/Mandelbrot_5.jpg/?raw=true "Mandelbrot 5")
