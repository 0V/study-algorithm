#pragma once

#include <iostream>
#include <array>
#include "vector2d.h"

// line := (x1, y1) (x2, y2)
// triangle := (x1, y1) (x2, y2) (x3, y3)
// line is not a line segment
bool IsIntersectedLineAndTriangle2D(const std::array<Vec2, 2> &line, const std::array<Vec2, 3> &triangle)
{
  std::array<Vec2, 2> edge_first{triangle[0], triangle[1]};
  std::array<Vec2, 2> edge_second{triangle[1], triangle[2]};

  return IsIntersectedLineAndLineSegment2D(line, edge_first) || IsIntersectedLineAndLineSegment2D(line, edge_second);
}

// line := (x1, y1) (x2, y2)
// triangle := (x1, y1) (x2, y2) (x3, y3)
bool IsIntersectedLineSegmentAndTriangle2D(const std::array<Vec2, 2> &line_segment, const std::array<Vec2, 3> &triangle)
{
  std::array<std::array<Vec2, 2>, 3> edges{
      std::array<Vec2, 2>{triangle[0], triangle[1]},
      std::array<Vec2, 2>{triangle[1], triangle[2]},
      std::array<Vec2, 2>{triangle[2], triangle[0]}};

  return IsIntersectedLineSegment2D(line_segment, edges[0]) ||
         IsIntersectedLineSegment2D(line_segment, edges[1]) ||
         IsIntersectedLineSegment2D(line_segment, edges[2]);
}
