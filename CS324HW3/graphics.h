#pragma once

#include <vector>
#include <string>

class Point {
public:
    double x;
    double y;
};

struct Window {
    double win_min_x;
    double win_min_y;
    double win_max_x;
    double win_max_y;
};

struct Viewport {
    double vp_min_x;
    double vp_min_y;
    double vp_max_x;
    double vp_max_y;
};


//////////////////////////////////////
//Bolden's provided code.
//////////////////////////////////////

struct color {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

namespace colors {
    constexpr color BLACK{ 0,   0,   0 };
    constexpr color WHITE{ 255, 255, 255 };
    constexpr color GREEN{ 255,   0,   0 };
    constexpr color BLUE{ 0, 255,   0 };
    constexpr color RED{ 0,   0, 255 };
}

struct pixel {
    color c;
};

class Canvas
{
public:
    Canvas(std::size_t w, std::size_t h, color background = colors::WHITE);

    void SetColor(std::size_t x, std::size_t y, color c);

    pixel GetPixel(std::size_t x, std::size_t y) const;
    void SetPixel(std::size_t x, std::size_t y, pixel c);

    void Clear();

    std::size_t Width()  const { return width; }
    std::size_t Height() const { return height; }

private:
    std::size_t width, height;
    std::vector<pixel> pixels;
    color background;
};


//////////////////////////////////////
//Prototypes
//////////////////////////////////////

void Line(Canvas& c, int x1, int y1, int x2, int y2, color color);
void SaveCanvasToFile(Canvas const& canvas, std::string const& fileName);
void SetViewport(double vp_min_x, double vp_min_y, double vp_max_x, double vp_max_y);
void SetWindow(double win_min_x, double win_min_y, double win_max_x, double win_max_y);
void MoveTo2D(double x, double y);
void DrawTo2D(double xd, double yd, Canvas& c, color col = colors::BLACK);
Point WindowToViewport(double x, double y);
Point ViewportToCanvas(double x, double y, int dimx, int dimy);
void InitGraphics();