#pragma once
#include "vector2d.h"

struct Node
{
  int id;
  vec2 p;
};

template <typename Char>
inline std::basic_ostream<Char> &operator<<(std::basic_ostream<Char> &os, const Node &node)
{
  return os << node.id << Char(' ') << node.p;
}

template <typename Char>
inline std::basic_istream<Char> &operator>>(std::basic_istream<Char> &is, Node &node)
{
  Char unused;
  return is >> unused >> node.id >> node.p >> unused;
}