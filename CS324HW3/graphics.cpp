#include <fstream>

#include "graphics.h"
Point pg;
Viewport v;
Window w;

//This doesn't *really* need to be a function right now; in it's current form it's just a formality for the assignment. Assigns the global Viewport bounds.
void SetViewport(double vp_min_x, double vp_min_y, double vp_max_x, double vp_max_y) {
    v.vp_min_x = vp_min_x;
    v.vp_min_y = vp_min_y;
    v.vp_max_x = vp_max_x;
    v.vp_max_y = vp_max_y;
}

//This doesn't *really* need to be a function right now; in it's current form it's just a formality for the assignment. Assigns the global Window bounds.
void SetWindow(double win_min_x, double win_min_y, double win_max_x, double win_max_y) {
    w.win_min_x = win_min_x;
    w.win_min_y = win_min_y;
    w.win_max_x = win_max_x;
    w.win_max_y = win_max_y;
}

//This doesn't *really* need to be a function right now; in it's current form it's just a formality for the assignment. Assigns the global canvas-space Point.
void MoveTo2D(double x, double y) {
    pg.x = x;
    pg.y = y;
}

void DrawTo2D(double xd, double yd, Canvas& c, color col) {
    int x = round(xd);
    int y = round(yd);
    int gx = round(pg.x);
    int gy = round(pg.y);

    //printf("x: %i, y: %i, gx: %i, gy: %i\n", x, y, gx, gy); //Debug.
    Line(c, gx, gy, x, y, col);
    MoveTo2D(xd, yd);
}

//Converts Window coordinates to Viewport coordinates.
Point WindowToViewport(double x, double y) {
    //Confine passed coordinates to window bounds.
    if (x > w.win_max_x)
        x = w.win_max_x;
    if (x < w.win_min_x)
        x = w.win_min_x;
    if (y > w.win_max_y)
        y = w.win_max_y;
    if (y < w.win_min_y)
        y = w.win_min_y;

    Point p;
    /*
    * The relative position of the point in the Window and the Viewport are the same, therefore:
    * (x_w - x_wmin) / (x_wmax - x_wmin) = (x_v - x_vmin) / (x_vmax - x_vmin).
    * Solving for x_v, we get x_vmin + ((x_w - x_wmin) * (x_vmax - x_vmin)) / (x_wmax - x_wmin).
    * ex. For some window where x_wmin = -2 and x_wmax = 8, and some viewport where x_vmin = -1 and x_vmax = 1, we want to map the window coordinate x = 3 (which would be right in the middle of the Window) to Viewport space. Therefore:
    * x_v = -1 + ((3 + 2) * (1 + 1)) / (8 + 2) = -1 + 10/10 = 0 (which is right in the middle of the Viewport).
    * Same principles applies to the y coordinates.
    */
    p.x = v.vp_min_x + (x - w.win_min_x) * ((v.vp_max_x - v.vp_min_x) / (w.win_max_x - w.win_min_x));
    p.y = v.vp_min_y + (y - w.win_min_y) * ((v.vp_max_y - v.vp_min_y) / (w.win_max_y - w.win_min_y));
    return p;
}

//Converts cartesian Viewport coordinates to device-space Canvas coordinates (which still need to be round()ed to ints).
Point ViewportToCanvas(double x, double y, int dimx, int dimy) {
    //Confine passed coordinates to viewport bounds.
    if (x > v.vp_max_x)
        x = v.vp_max_x;
    if (x < v.vp_min_x)
        x = v.vp_min_x;
    if (y > v.vp_max_y)
        y = v.vp_max_y;
    if (y < v.vp_min_y)
        y = v.vp_min_y;

    Point p;
    /*
    * Given the dimensions of the canvas and a viewpoint coordinate, find the matching canvas coordinate. Very similar to the WindowToViewport equation.
    * (x_c / dimx) = (x_v - x_vmin) / (x_vmax - x_vmin)
    * Solving for x_c, we get dimx * (x_v - x_vmin) / (x_vmax - x_vmin).
    * ex. For some viewport where x_vmin = -1 and x_vmax = 1, and a canvas where dimx = 1000, we want to map the cartesian viewport coordinate x_v = 0.5 to canvas/pixel-space (which would be 3/4ths across the canvas from left to right). Therefore:
    * x_c = 1000 * (0.5 + 1) / (1 + 1) = 1000 * 0.75 = 750 (indeed, 3/4ths across the canvas from left to right).
    */
    p.x = dimx * ((x - v.vp_min_x) / (v.vp_max_x - v.vp_min_x));
    //the y dimension is flipped in canvas-space, compared to cartesian space; 0 is at the very top.
    p.y = dimy * ((-y - v.vp_min_y) / (v.vp_max_y - v.vp_min_y));
    return p;
}

//Sets the global Viewport, Window, and Point to reasonable starting values.
void InitGraphics() {
    MoveTo2D(0.0, 0.0);
    SetViewport(-1.0, -1.0, 1.0, 1.0);
    SetWindow(-2.0, -2.0, 9.0, 9.0);
}


//////////////////////////////////////
//Bolden's provided code
//////////////////////////////////////

Canvas::Canvas(std::size_t w, std::size_t h, color bg)
    : width(w), height(h),
    pixels(width* height, { bg }),
    background(bg) { }


void Canvas::SetColor(std::size_t x, std::size_t y, color c) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        pixels[y * width + x] = { c };
    }
}

pixel Canvas::GetPixel(std::size_t x, std::size_t y) const {
    return pixels[y * width + x];
}

void Canvas::SetPixel(std::size_t x, std::size_t y, pixel p) {

    if (x >= 0 && x < width && y >= 0 && y < height)
    {
        pixels[y * width + x] = p;
    }
}

void Canvas::Clear() {
    for (auto& pixel : pixels) {
        pixel = { background };
    }
}

void Line(Canvas& c, int x1, int y1, int x2, int y2, color color)
{
    int xTmp, yTmp;

    if (y1 == y2) {          // Horizontal
        if (x1 > x2) {  // order for loop to work
            xTmp = x1;
            x1 = x2;
            x2 = xTmp;
        }

        for (auto i = x1; i <= x2; ++i) {
            c.SetColor(i, y1, color);
        }
        return;
    }
    else if (x1 == x2) {   // Vertical
        if (y1 > y2) {  // order for loop to work
            yTmp = y1;
            y1 = y2;
            y2 = yTmp;
        }

        for (auto j = y1; j <= y2; ++j) {
            c.SetColor(x1, j, color);
        }
        return;
    }

    double a = 1.0 * (y1 - y2) / (x1 - x2);
    double b = y1 - a * x1;
    for (double i = std::min(x1, x2); i < std::max(x1, x2); i += 1.0) {
        for (double j = std::min(y1, y2); j < std::max(y1, y2); j += 1.0) {
            double x1_intercept = a * (i - 0.5) + b;
            double x2_intercept = a * (i + 0.5) + b;
            double y1_intercept = (j - b - 0.5) / a;
            double y2_intercept = (j - b + 0.5) / a;

            if (x1_intercept >= j - 0.5 && x1_intercept <= j + 0.5) {
                c.SetColor(i, j, color);
            }
            else if (x2_intercept >= j - 0.5 && x2_intercept <= j + 0.5) {
                c.SetColor(i, j, color);
            }
            else if (y1_intercept >= i - 0.5 && y1_intercept <= i + 0.5) {
                c.SetColor(i, j, color);
            }
            else if (y2_intercept >= i - 0.5 && y2_intercept <= i + 0.5) {
                c.SetColor(i, j, color);
            }
        }
    }
}

void SaveCanvasToFile(Canvas const& canvas, std::string const& fileName)
{
    std::fstream file(fileName, std::ios::out);
    // Check!

    file << "P6 " << canvas.Width() << " " << canvas.Height() << " 255\n";

    for (auto y = 0; y < canvas.Height(); ++y) {
        for (auto x = 0; x < canvas.Width(); ++x) {
            auto const pixel = canvas.GetPixel(x, y);
            file << pixel.c.red << pixel.c.green << pixel.c.blue;
        }
    }
}