/* CS 324.Bolden.........Visual Studio 2022...........Greyson Biggs
 * 2/15/2022 .................Windows 10 i5-8600K.............bigg3448@vandals.uidaho.edu
 *
 * Homework 1 for CS 324 (Computer Graphics), Spring 2022.
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
	double x, y;
	int i;


	//////////////////////////////////////
	//Plots
	//////////////////////////////////////

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

	//////////////////////////////////////

	//Plot the above with a dashed line.
	Canvas gc2(size, size, colors::WHITE);
	SetWindow(0, -10, (3.0 * PI), 10);
	//Drawing axes
	p = WindowToViewport(3 * PI, 0);
	p = ViewportToCanvas(p.x, p.y, size, size);
	MoveTo2D(p.x, p.y);
	p = WindowToViewport(0, 0); //Initial point is at 0, 0.
	p = ViewportToCanvas(p.x, p.y, size, size);
	DrawTo2D(p.x, p.y, gc2);

	i = 0;

	for (x = 0; x <= (3.0 * PI); x += 0.02) {
		y = 3.0 * exp((-0.33 * x)) * sin(3.0 * x);
		p = WindowToViewport(x, y);
		p = ViewportToCanvas(p.x, p.y, size, size);
		if (i == 2) {
			i = 0;
			DrawTo2D(p.x, p.y, gc2);
		}
		else {
			i++;
			MoveTo2D(p.x, p.y);
		}
	}
	std::string fileName2("sinusoidaldashed.ppm");
	SaveCanvasToFile(gc2, fileName2);

	//////////////////////////////////////

	//Plot the function y = (3x^2 - 12x - 15) / (x^2 - 3x - 10) for x = -6 to 6, with a continuous line.
	Canvas gc3(size, size, colors::WHITE);
	SetWindow(-6, -10, 6, 15);
	//Drawing axes
	p = WindowToViewport(0, -10);
	p = ViewportToCanvas(p.x, p.y, size, size);
	MoveTo2D(p.x, p.y);
	p = WindowToViewport(0, 15);
	p = ViewportToCanvas(p.x, p.y, size, size);
	DrawTo2D(p.x, p.y, gc3);

	p = WindowToViewport(6, 0);
	p = ViewportToCanvas(p.x, p.y, size, size);
	MoveTo2D(p.x, p.y);
	p = WindowToViewport(-6, 0);
	p = ViewportToCanvas(p.x, p.y, size, size);
	DrawTo2D(p.x, p.y, gc3);


	for (x = -6; x <= 6; x += 0.01) {
		y = ((3 * pow(x, 2)) - (12 * x) - 15) / ((pow(x, 2)) - (3 * x) - 10);
		p = WindowToViewport(x, y);
		p = ViewportToCanvas(p.x, p.y, size, size);
		if (y > 30000) { //fix for drawing a line from +inf to -inf
			MoveTo2D(p.x, size);
			continue;
		}
		DrawTo2D(p.x, p.y, gc3);
	}
	std::string fileName3("quadraticcontinuous.ppm");
	SaveCanvasToFile(gc3, fileName3);

	//////////////////////////////////////

	//Plot the above with a dashed line.
	Canvas gc4(size, size, colors::WHITE);
	SetWindow(-6, -10, 6, 15);
	//Drawing axes
	p = WindowToViewport(0, -10);
	p = ViewportToCanvas(p.x, p.y, size, size);
	MoveTo2D(p.x, p.y);
	p = WindowToViewport(0, 15);
	p = ViewportToCanvas(p.x, p.y, size, size);
	DrawTo2D(p.x, p.y, gc4);

	p = WindowToViewport(6, 0);
	p = ViewportToCanvas(p.x, p.y, size, size);
	MoveTo2D(p.x, p.y);
	p = WindowToViewport(-6, 0);
	p = ViewportToCanvas(p.x, p.y, size, size);
	DrawTo2D(p.x, p.y, gc4);

	i = 0;

	for (x = -6; x <= 6; x += 0.01) {
		y = ((3 * pow(x, 2)) - (12 * x) - 15) / ((pow(x, 2)) - (3 * x) - 10);
		p = WindowToViewport(x, y);
		p = ViewportToCanvas(p.x, p.y, size, size);
		if (y > 30000) { //fix for drawing a line from +inf to -inf
			MoveTo2D(p.x, size);
			continue;
		}
		if (i == 3) {
			i = 0;
			DrawTo2D(p.x, p.y, gc4);
		}
		else {
			i++;
			MoveTo2D(p.x, p.y);
		}
	}
	std::string fileName4("quadraticdashed.ppm");
	SaveCanvasToFile(gc4, fileName4);

	//////////////////////////////////////

	//Plot the function y = sqrt(bx^3 +.5x^2) for some b.
	Canvas gc5(size, size, colors::WHITE);
	SetWindow(-6, -6, 6, 6);
	//Drawing axes
	p = WindowToViewport(0, -6);
	p = ViewportToCanvas(p.x, p.y, size, size);
	MoveTo2D(p.x, p.y);
	p = WindowToViewport(0, 6);
	p = ViewportToCanvas(p.x, p.y, size, size);
	DrawTo2D(p.x, p.y, gc5);

	p = WindowToViewport(6, 0);
	p = ViewportToCanvas(p.x, p.y, size, size);
	MoveTo2D(p.x, p.y);
	p = WindowToViewport(-6, 0);
	p = ViewportToCanvas(p.x, p.y, size, size);
	DrawTo2D(p.x, p.y, gc5);


	for (x = -6; x <= 6; x += 0.02) {
		y = sqrt(((2.0 * x) + (0.5 * pow(x, 2))));
		if (isnan(y)) {
			y = 0;
		}
		p = WindowToViewport(x, y);
		p = ViewportToCanvas(p.x, p.y, size, size);
		DrawTo2D(p.x, p.y, gc5);
	}
	std::string fileName5("quadratics20continuous.ppm");
	SaveCanvasToFile(gc5, fileName5);


	//////////////////////////////////////

	//Plot the function y = 3.0*e^(-0.33x)*sin(3x) for x = 0 to x = 3*pi, with a continuous line with the non-default Viewport coordinates.
	Canvas gc6(size, size, colors::WHITE);
	SetWindow(0, -10, (3 * PI), 10);
	SetViewport(-0.5, -0.5, 1.5, 1.0);
	//Drawing axes
	p = WindowToViewport(3 * PI, 0);
	p = ViewportToCanvas(p.x, p.y, size, size);
	MoveTo2D(p.x, p.y);
	p = WindowToViewport(0, 0);
	p = ViewportToCanvas(p.x, p.y, size, size);
	DrawTo2D(p.x, p.y, gc6);


	for (x = 0; x <= (3.0 * PI); x += 0.01) {
		y = 3.0 * exp((-0.33 * x)) * sin(3.0 * x);
		p = WindowToViewport(x, y);
		p = ViewportToCanvas(p.x, p.y, size, size);
		DrawTo2D(p.x, p.y, gc6);
	}
	std::string fileName6("sinusoidalcontaltviewport.ppm");
	SaveCanvasToFile(gc6, fileName6);

	return 1;
}