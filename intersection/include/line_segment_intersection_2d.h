#pragma once
#include <iostream>
#include <array>
#include "vec2.h"

bool IsIntersectedLineAndLineSegment2D(const std::array<Vec2, 2> &line, const std::array<Vec2, 2> &line_segment)
{
  double diffx = line[1].x - line[0].x;
  double diffy = line[1].y - line[0].y;
  double a = diffy / diffx;
  double b = line[0].y - a * line[0].x;

  double pointA = a * line_segment[0].x + b - line_segment[0].y;
  double pointB = a * line_segment[1].x + b - line_segment[1].y;

  return pointA * pointB <= 0;
}

bool IsIntersectedLineSegment2D(const std::array<Vec2, 2> &line_segment_first, const std::array<Vec2, 2> &line_segment_second)

{
  return IsIntersectedLineAndLineSegment2D(line_segment_first, line_segment_second) &&
         IsIntersectedLineAndLineSegment2D(line_segment_second, line_segment_first);
}