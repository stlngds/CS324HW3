#pragma once

#include <vector>
#include <string>

constexpr int X_TRANS = 1;
constexpr int Y_TRANS = 2;
constexpr int Z_TRANS = 3;
constexpr int X_ROT = 4;
constexpr int Y_ROT = 5;
constexpr int Z_ROT = 6;
constexpr int PERSPECTIVE = 7;

struct Point {
    double x;
    double y;
    double z;

    Point() {
        x = y = z = 0.0;
    }

    Point(double px, double py, double pz) {
        x = px;
        y = py;
        z = pz;
    }

    //this should absolutely be a vector but I don't wanna rewrite old code that references p.x and the like.
    double& operator[] (int index) {
        switch (index) {
            case 0:
                return x;
                break;
            case 1:
                return y;
                break;
            case 2:
                return z;
                break;
        }
    }
    const double& operator[] (int index) const {
        switch (index) {
        case 0:
            return x;
            break;
        case 1:
            return y;
            break;
        case 2:
            return z;
            break;
        default:
            return 0.0;
        }
    }
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

//Vectors of four doubles.
struct vec4 {
    double values[4];
    vec4() {
        values[0] = values[1] = values[2] = values[3] = 0;
    }
    vec4(double x, double y, double z, double w) {
        values[0] = x;
        values[1] = y;
        values[2] = z;
        values[3] = w;
    }
    const double& operator[] (int index) const {
        return values[index];
    }
    double& operator[] (int index) {
        return values[index];
    }
};


//Column-major 4x4 matrix of double vectors (access ith row and jth column with M[j][i]).
struct mat4 {
    vec4 columns[4];

    mat4() {
        columns[0] = vec4(1, 0, 0, 0);
        columns[1] = vec4(0, 1, 0, 0);
        columns[2] = vec4(0, 0, 1, 0);
        columns[3] = vec4(0, 0, 0, 1);
    }

    mat4(vec4 x, vec4 y, vec4 z, vec4 w)
    {
        columns[0] = x;
        columns[1] = y;
        columns[2] = z;
        columns[3] = w;
    }

    const vec4& operator[] (int index) const
    {
        return columns[index];
    }
    vec4& operator[] (int index)
    {
        return columns[index];
    }
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

vec4 operator*(const mat4& m, const vec4& v);
vec4 operator*(const vec4& v, const mat4& m);
mat4 operator*(const mat4& m1, const mat4& m2);
Point ApplyTransform(double x, double y, double z, mat4& m);

void SetViewport(double vp_min_x, double vp_min_y, double vp_max_x, double vp_max_y);
void SetWindow(double win_min_x, double win_min_y, double win_max_x, double win_max_y);
void MoveTo2D(double x, double y);
void Move3D(double x, double y, double z);
void DrawTo2D(double xd, double yd, Canvas& c, color col);
void Draw3D(double xd, double yd, double zd, mat4& aT, mat4& cT, Canvas& c, color col);
Point WindowToViewport(double x, double y);
Point ViewportToCanvas(double x, double y, int dimx, int dimy);
void InitGraphics();

void DefineCameraTransform(double fX, double fY, double fZ, double theta, double phi, double alpha, double r);
void DefineElementaryTransform(mat4& m, int tf, double val);
void BuildElementaryTransform(mat4& m, int tf, double val);
void SetCameraTransform(mat4& m);