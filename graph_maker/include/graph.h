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
  double length;
};

struct greater_length
{
  bool operator()(IndexLength &a, IndexLength &b) const
  {
    return a.length < b.length;
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

  bool IsIntersectedHalfLineAndLineSegment2D(const Line &half_line, const Line &line_segment_second, double length)
  {
    vec2 axis = half_line[1] - half_line[0];
    vec2 semi = axis.normalized() * length;
    Line line_segment_first{half_line[0], half_line[0] + semi};
    return IsIntersectedLineAndLineSegment2D(line_segment_first, line_segment_second) &&
           IsIntersectedLineAndLineSegment2D(line_segment_second, line_segment_first);
  }

  std::array<Node, NSize> nodes_;
  Matrix matrix_; // adjacency matrix
  double sin_theta_;
  double cos_theta_;
  double angle_;
  const vec2 AxisY = vec2(0, 1);
  std::array<std::vector<Line>, NSize> angle_range_list;

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
    for (int i = 0; i < NSize; i++)
    {
      test_one(i);
    }
  };

  void test_one(int index)
  {
    std::array<IndexLength, NSize> lens;
    Node &node = nodes_[index];
    std::vector<Line> &angle_range = angle_range_list[index];
    std::vector<int> ids;

    for (int i = 0; i < NSize; i++)
    {
      lens[i] = IndexLength{i, (node.p - nodes_[i].p).length()};
    }

    std::sort(lens.begin(), lens.end(), greater_length());

    double limit = limit_length_ratio * lens[1].length;
    limit = limit > min_length ? limit : min_length;

    angle_range.emplace_back(Line{
        rotate(node.p, nodes_[lens[1].index].p),
        rotate_inv(node.p, nodes_[lens[1].index].p)});

    ids.emplace_back(lens[1].index);

    for (int i = 2; i < lens.size(); i++)
    {
      if (lens[i].length > limit)
      {
        break;
      }

      bool is_hit = false;

      int target_index = lens[i].index;
      auto &target_node = nodes_[target_index];

      for (auto &lines : angle_range)
      {
        if (IsIntersectedHalfLineAndLineSegment2D(Line{node.p, target_node.p},
                                                  lines, 100000))
        {
          is_hit = true;
          break;
        }
      }

      if (is_hit)
        continue;

      angle_range.emplace_back(Line{
          rotate(node.p, target_node.p),
          rotate_inv(node.p, target_node.p)});

      angle_range_list[target_index].emplace_back(Line{
          rotate(target_node.p, node.p),
          rotate_inv(target_node.p, node.p)});

      ids.emplace_back(target_index);
    }

    for (auto &j : ids)
    {
      matrix_[index][j] = true;
    }
  }

public:
  double limit_length_ratio = 3;
  double min_length = 100;

  Graph(std::array<Node, NSize> &nodes, double angle) : nodes_(nodes)
  {
    for (int i = 0; i < NSize; i++)
    {
      matrix_[i] = std::array<bool, NSize>();
    }
    for (int i = 0; i < NSize; i++)
    {
      angle_range_list[i] = std::vector<Line>();
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
    for (int i = 0; i < NSize; i++)
    {
      for (int j = i; j < NSize; j++)
      {
        if (matrix_[i][j] || matrix_[j][i])
        {
          pairs.emplace_back(std::array<int, 2>{nodes_[i].id, nodes_[j].id});
        }
      }
    }
    return pairs;
  }
};
