#pragma once
#include <array>
#include <vector>
#include "node.h"

// template <int N>
constexpr int N = 10;
class Graph
{
private:
  using Matrix = std::array<std::array<bool, N>, N>;

  std::array<Node, N> nodes_;
  Matrix matrix_; // adjacency matrix

  void make()
  {
    for (size_t i = 0; i < N; i++)
    {
    }
  }

  void test_one(int index)
  {
    Node &node = nodes_[index];
  }

public:
  Graph(std::array<Node, N> &nodes) : nodes_(nodes)
  {
    for (size_t i = 0; i < N; i++)
    {
      matrix_[i] = std::array<bool, N>();
    }
  }

  std::vector<std::array<int, 2>> to_pairs()
  {
    std::vector<std::array<int, 2>> pairs;
    for (size_t i = 0; i < N; i++)
    {
      for (size_t j = i; j < N; j++)
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
