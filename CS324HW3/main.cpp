/* CS 324.Bolden.........Visual Studio 2022...........Greyson Biggs
 * 2/15/2022 .................Windows 10 i5-8600K.............bigg3448@vandals.uidaho.edu
 *
 * Homework 3 for CS 324 (Computer Graphics), Spring 2022.
 * Graphs several math functions and outputs them as a .ppm file, mapping the Window-space that the functions operate in to Viewport-space to Canvas/Pixel-space.
 * TODO: Create a function that does both WindowToViewport and ViewportToCanvas in one go - would save lines.
 *---------------------------------------------------------------------
 */

#include <iostream>
#include "graphics.h"
#include <math.h>

constexpr double PI = 3.14159265358979;

int main() {

	//////////////////////////////////////
	//Init
	//////////////////////////////////////

	InitGraphics();
	constexpr int size = 1000; //Our canvas is made up of 1000 by 1000 pixels (represented by a vector of RGB values from 0 to 255)
	//Temporary stuff.
	Point p;
	double x, y, z, r;
	int i;
	mat4 CAMERA = GetCameraTransform();


	//////////////////////////////////////
	//Plots
	//////////////////////////////////////
	Canvas gc(size, size, colors::WHITE);
	//DrawCube(0.5, gc, colors::BLACK);
	SetWindow((-2 * PI), (-2 * PI), (2 * PI), (2 * PI));
	Move3D(0, 1, 0);
	Draw3D(0, -1, 0, CAMERA, gc, colors::BLACK);
	Move3D(1, 0, 0);
	Draw3D(-1, 0, 0, CAMERA, gc, colors::RED);
	Move3D(0, 0, 1);
	Draw3D(0, 0, -1, CAMERA, gc, colors::BLUE);
	/*
	for (x = (-2 * PI); x <= (2 * PI); x += .5) {
		for (y = (-2 * PI); y <= (2 * PI); y += .5) {
			r = (pow(x, 2) + pow(y, 2));
			z = ((sin(r) / r) / (9 * cos((x / (y + 0.02)))));
			Draw3D(x, y, z, CAMERA, gc, colors::BLACK);
		}
	}
	*/

	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			printf("%lf ", CAMERA[y][x]);
		}
		printf("\n");
	}

	std::string fileName("test.ppm");
	SaveCanvasToFile(gc, fileName);

	/*
	//Plot the function y = 3.0*e^(-0.33x)*sin(3x) for x = 0 to x = 3*pi, with a continuous line.
	Canvas gc(size, size, colors::WHITE); //Background color is white.
	SetWindow(0, -10, (3.0 * PI), 10); //What is drawn on our canvas will be all the space wrt the function from x = 0 to 3pi, and y = -10 to 10. Shrinking y to range from -5 to 5 makes the curve more extreme!
	//Drawing axes
	p = WindowToViewport(3 * PI, 0);
	p = ViewportToCanvas(p.x, p.y, size, size);
	MoveTo2D(p.x, p.y);
	p = WindowToViewport(0, 0);
	p = ViewportToCanvas(p.x, p.y, size, size);
	DrawTo2D(p.x, p.y, gc);


	for (x = 0; x <= (3.0 * PI); x += 0.01) {
		y = 3.0 * exp((-0.33 * x)) * sin(3.0 * x);
		p = WindowToViewport(x, y);
		p = ViewportToCanvas(p.x, p.y, size, size);
		DrawTo2D(p.x, p.y, gc);
	}
	std::string fileName("sinusoidalcontinuous.ppm");
	SaveCanvasToFile(gc, fileName);
	*/

	return 1;
}