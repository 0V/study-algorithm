#pragma once
#include <iostream>
#include <cmath>

template<typename T>
struct Vector2d
{
  using Type = T;
  
  Type x;
  Type y;

  Vector2d() = default;

  constexpr Vector2d(Type _x, Type _y)
      : x(_x), y(_y) {}

  Type length() const
  {
    return std::sqrt(lengthSquare());
  }

  constexpr Type lengthSquare() const
  {
    return dot(*this);
  }

  constexpr Type dot(const Vector2d &other) const
  {
    return x * other.x + y * other.y;
  }

  constexpr Type cross(const Vector2d &other) const
  {
    return x * other.y - y * other.x;
  }

  Type distanceFrom(const Vector2d &other) const
  {
    return (other - *this).length();
  }

  Vector2d normalized() const
  {
    return *this / length();
  }

  constexpr bool isZero() const
  {
    return x == 0.0 && y == 0.0;
  }

  constexpr Vector2d operator+() const
  {
    return *this;
  }

  constexpr Vector2d operator-() const
  {
    return {-x, -y};
  }

  constexpr Vector2d operator+(const Vector2d &other) const
  {
    return {x + other.x, y + other.y};
  }

  constexpr Vector2d operator-(const Vector2d &other) const
  {
    return {x - other.x, y - other.y};
  }

  constexpr Vector2d operator*(Type s) const
  {
    return {x * s, y * s};
  }

  constexpr Vector2d operator/(Type s) const
  {
    return {x / s, y / s};
  }

  Vector2d &operator+=(const Vector2d &other)
  {
    x += other.x;
    y += other.y;
    return *this;
  }

  Vector2d &operator-=(const Vector2d &other)
  {
    x -= other.x;
    y -= other.y;
    return *this;
  }

  Vector2d &operator*=(Type s)
  {
    x *= s;
    y *= s;
    return *this;
  }

  Vector2d &operator/=(Type s)
  {
    x /= s;
    y /= s;
    return *this;
  }
};

template<typename T>
inline constexpr Vector2d<T> operator*(Vector2d<T> s, const Vector2d<T> &v)
{
  return {s * v.x, s * v.y};
}

template <typename Char, typename T>
inline std::basic_ostream<Char> &operator<<(std::basic_ostream<Char> &os, const Vector2d<T> &v)
{
  return os << Char('(') << v.x << Char(',') << v.y << Char(')');
}

template <typename Char, typename T>
inline std::basic_istream<Char> &operator>>(std::basic_istream<Char> &is, Vector2d<T> &v)
{
  Char unused;
  return is >> unused >> v.x >> unused >> v.y >> unused;
}

using vec2 = Vector2d<double>;