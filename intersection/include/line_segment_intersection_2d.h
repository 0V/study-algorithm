#pragma once
#include <iostream>
#include <array>
#include "vector2d.h"

bool IsIntersectedLineAndLineSegment2D(const std::array<Vec2, 2> &line, const std::array<Vec2, 2> &line_segment)
{
  Vec2 axis = line[1] - line[0];
  Vec2 seg0_dir = line[1] - line_segment[0];
  Vec2 seg1_dir = line[1] - line_segment[1];
  double seg0_z = axis.cross(seg0_dir); 
  double seg1_z = axis.cross(seg1_dir);  

  return seg0_z * seg1_z <= 0;
}

bool IsIntersectedLineSegment2D(const std::array<Vec2, 2> &line_segment_first, const std::array<Vec2, 2> &line_segment_second)
{
  return IsIntersectedLineAndLineSegment2D(line_segment_first, line_segment_second) &&
         IsIntersectedLineAndLineSegment2D(line_segment_second, line_segment_first);
}