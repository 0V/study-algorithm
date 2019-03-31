#include <iostream>
#include <cmath>
#include <random>
#include <fstream>

#include "value_sampler.h"

class MCTester
{
private:
  ValueSampler<double> sampler = ValueSampler<double>(-1, 1);
  ValueSampler<double> sampler01 = ValueSampler<double>(0, 1);

public:
  void strastifying_pi()
  {
    int inside_count = 0;
    int inside_count_str = 0;
    constexpr int SqrtCount = 10000;
    for (size_t i = 0; i < SqrtCount; i++)
    {
      for (size_t j = 0; j < SqrtCount; j++)
      {
        double x = sampler.sample();
        double y = sampler.sample();

        if (x * x + y * y < 1)
        {
          inside_count++;
        }

        x = (double)(i + sampler01.sample()) / SqrtCount;
        y = (double)(j + sampler01.sample()) / SqrtCount;
        if (x * x + y * y < 1)
        {
          inside_count_str++;
        }
        if (i != 0 && j != 0 && (i * j) % 1000000 == 0)
        {
          std::cout << "[" << i * j << " REG]" << (4.0 * (double)inside_count / (SqrtCount * SqrtCount)) << "\n";
          std::cout << "[" << i * j << " STR]" << (4.0 * (double)inside_count_str / (SqrtCount * SqrtCount)) << "\n";
        }
      }
    }

    std::cout << "[Regular]" << (4.0 * (double)inside_count / (SqrtCount * SqrtCount)) << "\n";

    std::cout << "[Strastifying]" << (4.0 * (double)inside_count_str / (SqrtCount * SqrtCount)) << "\n";
  }

  void regular_pi()
  {
    int inside_count = 0;
    int all_count = 0;
    while (true)
    {
      all_count++;
      double x = sampler.sample();
      double y = sampler.sample();
      if (x * x + y * y < 1)
      {
        inside_count++;
      }
      if (all_count % 1000000 == 0)
      {
        std::cout << "[" << all_count << "]" << (4.0 * (double)inside_count / all_count) << "\n";
      }
    }
  }

  void integral_x_pow_2()
  {
    double sum = 0;
    constexpr int N = 1000000;

    for (size_t i = 0; i < N; i++)
    {
      double x = 2 * sampler01.sample();
      sum += x * x;
    }

    std::cout << "I = " << 2 * sum / N << std::endl;
    std::cout << "True = 2.6666..." << std::endl;
  }

  void importance_sampling_xyz()
  {
    for (size_t i = 0; i < 200; i++)
    {
      double r1 = sampler01.sample();
      double r2 = sampler01.sample();
      double x = std::cos(2 * M_PI * r1) * 2 * std::sqrt(r2 * (1 - r2));
      double y = std::sin(2 * M_PI * r1) * 2 * std::sqrt(r2 * (1 - r2));
      double z = 1 - 2 * r2;
      std::cout << x << " " << y << " " << z << "\n";
    }
  }
};

int main()
{
  MCTester tester;
  //  tester.regular_pi();
  tester.importance_sampling_xyz();
}