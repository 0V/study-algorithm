#pragma once
#include <array>
#include <vector>
#include <algorithm>
#include <cmath>
#include "vector2d.h"
#include "node.h"

constexpr double RadUnit = M_PI / 180.0;

struct IndexLength
{
  int index;
  int length;
};

struct greater_length
{
  bool operator()(IndexLength &a, IndexLength &b) const
  {
    return a.length > b.length;
  }
};

template <int NSize>
// constexpr int NSize = 10;
class Graph
{
private:
  using Line = std::array<vec2, 2>;
  using Matrix = std::array<std::array<bool, NSize>, NSize>;

  bool IsIntersectedLineAndLineSegment2D(const Line &line, const Line &line_segment)
  {
    vec2 axis = line[1] - line[0];
    vec2 seg0_dir = line[1] - line_segment[0];
    vec2 seg1_dir = line[1] - line_segment[1];
    double seg0_z = axis.cross(seg0_dir);
    double seg1_z = axis.cross(seg1_dir);

    return seg0_z * seg1_z <= 0;
  }

  std::array<Node, NSize> nodes_;
  Matrix matrix_; // adjacency matrix
  double sin_theta_;
  double cos_theta_;
  double angle_;
  const vec2 AxisY = vec2(0, 1);

  vec2 rotate_origin(const vec2 &v) const
  {
    vec2 tmp;
    tmp.x = cos_theta_ * v.x + sin_theta_ * v.y;
    tmp.y = -sin_theta_ * v.x + cos_theta_ * v.y;
    return tmp;
  }

  vec2 rotate_inv_origin(const vec2 &v) const
  {
    vec2 tmp;
    tmp.x = cos_theta_ * v.x - sin_theta_ * v.y;
    tmp.y = sin_theta_ * v.x + cos_theta_ * v.y;
    return tmp;
  }

  vec2 rotate(const vec2 &origin, const vec2 &v)
  {
    vec2 v2 = v - origin;
    return rotate_origin(v2) + origin;
  }

  vec2 rotate_inv(const vec2 &origin, const vec2 &v)
  {
    vec2 v2 = v - origin;
    return rotate_inv_origin(v2) + origin;
  }

  /*
  double get_angle(const vec2 &v)
  {
    return std::acos(AxisY.dot(v.normalized()));
  }

  void add_angle(double direction)
  {

    angle_range_.emplace_back(std::array<int, 2>{direction - angle_, direction + angle_});
  }
  */

  void make()
  {
    for (size_t i = 0; i < NSize; i++)
    {
      test_one(i);
    }
  }

  void test_one(int index)
  {
    std::array<IndexLength, NSize> lens;
    Node &node = nodes_[index];
    std::vector<Line> angle_range;
    std::vector<int> ids;

    for (size_t i = 0; i < NSize; i++)
    {
      lens[i] = IndexLength{i, (node.p - nodes_[i].p).length()};
    }

    std::sort(lens.begin(), lens.end(), greater_length());

    double limit = limit_length_ratio * lens[0].length;

    angle_range.emplace_back(Line{
        rotate(node.p, nodes_[0].p),
        rotate_inv(node.p, nodes_[0].p)});

    ids.emplace_back(nodes_[lens[0].index].id);

    for (size_t i = 1; i < lens.size(); i++)
    {

      if (lens[i].length > limit)
      {
        return;
      }

      for (auto &lines : angle_range)
      {
        if (IsIntersectedLineAndLineSegment2D(Line{nodes_[lens[i].index].p, node.p}, lines))
        {
          continue;
        }
      }

      angle_range.emplace_back(Line{
          rotate(node.p, nodes_[lens[i].index].p),
          rotate_inv(node.p, nodes_[lens[i].index].p)});

      ids.emplace_back(nodes_[lens[i].index].id);
    }

    for (auto &j : ids)
    {
      matrix_[index][j] = true;
    }
  }

public:
  double limit_length_ratio = 3;

  Graph(std::array<Node, NSize> &nodes, double angle) : nodes_(nodes)
  {
    for (size_t i = 0; i < NSize; i++)
    {
      matrix_[i] = std::array<bool, NSize>();
    }
    angle_ = angle;
    double radians = RadUnit * angle;
    sin_theta_ = std::sin(radians);
    cos_theta_ = std::cos(radians);

    make();
  }

  std::vector<std::array<int, 2>> to_pairs()
  {
    std::vector<std::array<int, 2>> pairs;
    for (size_t i = 0; i < NSize; i++)
    {
      for (size_t j = i; j < NSize; j++)
      {
        if (matrix_[i][j])
        {
          std::cout << i << " " << j << "\n";
          pairs.emplace_back(std::array<int, 2>{nodes_[i].id, nodes_[j].id});
        }
      }
    }
    return pairs;
  }
};
