#include <iostream>
#include <vector>
#include <array>
#include <fstream>
#include <random>
#include "intersections.h"
#include "vec2.h"

void TestLineAndTriangle()
{

  std::array<Vec2, 2> line_vec2;
  std::array<Vec2, 3> triangle_vec2;

  std::cout << "Line definition\n"
            << "Input (x1, y1) (x2, y2) as follow: \nx1 y1 x2 y2 > ";

  for (size_t i = 0; i < 2; i++)
  {
    std::cin >> line_vec2[i].x;
    std::cin >> line_vec2[i].y;
  }

  std::cout << "\nTriangle definition\n"
            << "Input (x1, y1) (x2, y2) (x3, y3) as follow: \nx1 y1 x2 y2 x3 y3 > ";

  for (size_t i = 0; i < 3; i++)
  {
    std::cin >> triangle_vec2[i].x;
    std::cin >> triangle_vec2[i].y;
  }

  if (IsIntersectedLineAndTriangle2D(line_vec2, triangle_vec2))
  {
    std::cout << "Intersected" << std::endl;
  }
  else
  {
    std::cout << "Not intersected" << std::endl;
  }
}

std::random_device seed_gen_;
std::mt19937 engine_ = std::mt19937(seed_gen_());
std::uniform_real_distribution<double> dist_m10_10_ = std::uniform_real_distribution<double>(-10, 10); // [-10,10)

// output line and triangle file,
std::array<bool, 2> TestLineAndTriangleRandom(const std::string &file_name = "shape.txt")
{
  std::ofstream shape_stream(file_name);

  std::array<Vec2, 2> line = {Vec2{dist_m10_10_(engine_), dist_m10_10_(engine_)},
                              Vec2{dist_m10_10_(engine_), dist_m10_10_(engine_)}};

  std::array<Vec2, 3> triangle = {Vec2{dist_m10_10_(engine_), dist_m10_10_(engine_)},
                                  Vec2{dist_m10_10_(engine_), dist_m10_10_(engine_)},
                                  Vec2{dist_m10_10_(engine_), dist_m10_10_(engine_)}};

  for (size_t i = 0; i < 2; i++)
  {
    shape_stream << line[i].x << " " << line[i].y << "\n";
  }

  shape_stream << "\n";

  for (size_t i = 0; i < 3; i++)
  {
    shape_stream << triangle[i].x << " " << triangle[i].y << "\n";
  }
  shape_stream << triangle[0].x << " " << triangle[0].y << "\n";

  return std::array<bool, 2>{IsIntersectedLineAndTriangle2D(line, triangle),
                             IsIntersectedLineSegmentAndTriangle2D(line, triangle)};
}

// output line and triangle ,
void TestLineAndTriangleRandomRepeat(const size_t &count = 1)
{
  std::ofstream res_bool_stream("result_bool.txt");

  for (size_t i = 0; i < count; i++)
  {
    auto code = TestLineAndTriangleRandom("shape" + std::to_string(i) + ".dat");

    res_bool_stream << code[0] << " " << code[1] << "\n";
  }
}

void TestLineAndLineSegment2D()
{

  std::array<Vec2, 2> line = {Vec2{1, 1},
                              Vec2{2, 2}};

  std::vector<std::array<Vec2, 2>> line_segment_true = {{Vec2{-1, 0}, Vec2{4, 3}},
                                                        {Vec2{0, 0}, Vec2{4, 3}},
                                                        {Vec2{0.0003, 0.0002}, Vec2{0.0002, 0.0003}},
                                                        {Vec2{10002, 9999}, Vec2{-1, 1}},
                                                        {Vec2{0, 0}, Vec2{-1, 0}}};

  std::vector<std::array<Vec2, 2>> line_segment_false = {{Vec2{-1, 0}, Vec2{2, 3}},
                                                         {Vec2{0.0001, 0}, Vec2{0.0002, 0}},
                                                         {Vec2{0, -1}, Vec2{10000, 9999}}};

  std::cout << "True Test :\n";
  for (auto &seg : line_segment_true)
  {
    std::cout << "\t" << (IsIntersectedLineAndLineSegment2D(line, seg) ? "True" : "False");
    std::cout << "\t" << seg[0] << " " << seg[1] << std::endl;
  }

  std::cout << "False Test :\n";
  for (auto &seg : line_segment_false)
  {
    std::cout << "\t" << (IsIntersectedLineAndLineSegment2D(line, seg) ? "True" : "False");
    std::cout << "\t" << seg[0] << " " << seg[1] << std::endl;
  }
}

int main()
{
  /*/ TestLineAndLineSegment2D(); //*/
  /*/ TestLineAndTriangleRandomRepeat(10); //*/
  /**/ TestLineAndTriangle();               //*/
}