/* CS 324.Bolden.........Visual Studio 2022...........Greyson Biggs
 * 4/7/2022 .................Windows 10 i5-8600K.............bigg3448@vandals.uidaho.edu
 *
 * Homework 3 for CS 324 (Computer Graphics), Spring 2022.
 * This program builds on Homework 1 & 2 to create a basic 3D graphics library, complete with a Camera system, matrix and vector functions, and (very) basic modeling. This functionality is shown by drawing a 3D mathematical function, as well as Rubik’s Cubes.
 *---------------------------------------------------------------------
 */

#include <iostream>
#include "graphics.h"
#include <math.h>


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

	/*
	//Plot the function (sin(r) / r) / (9*cos(x / (y + .02))), for r = x^2 + y^2, x = -2PI thru 2PI, and y = -2PI thru 2PI.
	Canvas gc(size, size, colors::WHITE);
	//DrawCube(0.5, gc, colors::BLACK);
	SetWindow((-15), (-15), (15), (15));
	for (x = (-2 * PI); x <= (2 * PI); x += .2) {
		for (y = (-2 * PI); y <= (2 * PI); y += .2) {
			r = (pow(x, 2) + pow(y, 2));
			z = ( (sin(r) / r) / (9 * cos( (x / (y + 0.02) ) ) ) );
			if (y == (-2 * PI) || y == (2 * PI) || x == (-2 * PI) || x == (2 * PI)) {
				Move3D(x, y, z);
			}
			else {
				Draw3D(x, y, z, CAMERA, gc, colors::RED);
			}
			printf("%lf %lf %lf ", x, y, z);
		}
	}

	//draw axes
	Move3D(0, 10, 0);
	Draw3D(0, -10, 0, CAMERA, gc, colors::BLACK);
	Move3D(10, 0, 0);
	Draw3D(-10, 0, 0, CAMERA, gc, colors::BLACK);
	Move3D(0, 0, 10);
	Draw3D(0, 0, -10, CAMERA, gc, colors::BLACK);

	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			printf("%lf ", CAMERA[y][x]);
		}
		printf("\n");
	}
	printf("\n");

	std::string fileName("function.ppm");
	SaveCanvasToFile(gc, fileName);
	*/

	/*
	//Draw a "Rubik's Cube" with small gaps between each cube.
	Canvas gc(size, size, colors::WHITE);
	SetWindow(-6.0, -6.0, 6.0, 6.0);
	for (x = 0; x < 3; x++)
		for (y = 0; y < 3; y++)
			for (z = 0; z < 3; z++) {
				if (x == 0)
					DrawCube(x * 1.1, y * 1.1, z * 1.1, 0, 0, 0, .5, gc, colors::RED);
				if (x == 1)
					DrawCube(x * 1.1, y * 1.1, z * 1.1, 0, 0, 0, .5, gc, colors::GREEN);
				if (x == 2)
					DrawCube(x * 1.1, y * 1.1, z * 1.1, 0, 0, 0, .5, gc, colors::BLUE);
			}
				

	
	std::string fileName("cubegaps.ppm");
	SaveCanvasToFile(gc, fileName);
	*/

	/*
	//Draw a "Rubik's Cube" with no gaps between cubes.
	Canvas gc(size, size, colors::WHITE);
	SetWindow(-6.0, -6.0, 6.0, 6.0);
	for (x = 0; x < 3; x++)
		for (y = 0; y < 3; y++)
			for (z = 0; z < 3; z++) {
				if (x == 0)
					DrawCube(x, y, z, 0, 0, 0, .5, gc, colors::RED);
				if (x == 1)
					DrawCube(x, y, z, 0, 0, 0, .5, gc, colors::GREEN);
				if (x == 2)
					DrawCube(x, y, z, 0, 0, 0, .5, gc, colors::BLUE);
			}
				
	std::string fileName("cube.ppm");
	SaveCanvasToFile(gc, fileName);
	*/
	
	//Draw a 10x10x10 grid of Rubik's Cubes, with gaps between the cubes.
	Canvas gc(size, size, colors::WHITE);
	SetWindow(-50.0, -50.0,  25.0, 25.0);
	for (x = 0; x < 30; x++)
		for (y = 0; y < 30; y++)
			for (z = 0; z < 30; z++) {
					DrawCube(x * 1.1, y * 1.1, z * 1.1, 0, 0, 0, .5, gc, colors::BLACK);
			}



	std::string fileName("cubegrid.ppm");
	SaveCanvasToFile(gc, fileName);
	
	return 1;
}