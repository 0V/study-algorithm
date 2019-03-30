#include <iostream>
#include <cmath>
#include <random>
#include <fstream>

// Random number from inverse function of probability density function of exponential distribution
class ExpRandom
{
private:
  // mean: meu
  // u = U[0,1]
  inline double invProbExpFunc(const double &u)
  {
    return -meu_ * std::log(1 - u);
  }

  std::random_device seed_gen;
  std::mt19937 engine = std::mt19937(seed_gen());
  std::uniform_real_distribution<double> dist = std::uniform_real_distribution<double>(0, 1);

  double meu_;

public:
  ExpRandom(double meu) : meu_(meu) {}

  void setMeu(double meu)
  {
    meu_ = meu;
  }

  double getNext()
  {
    return invProbExpFunc(dist(engine));
  }
};

class XRandom
{
private:
  // mean: meu
  // u = U[0,1]
  inline double inv_comu_pdf(const double &u)
  {
    return 2 * std::sqrt(u);
  }

  std::random_device seed_gen;
  std::mt19937 engine = std::mt19937(seed_gen());
  std::uniform_real_distribution<double> dist = std::uniform_real_distribution<double>(0, 1);


public:


  double getNext()
  {
    return inv_comu_pdf(dist(engine));
  }
};

int main()
{
//  std::ofstream optFileDouble("result_double.txt");
  std::ofstream fout("result_x.txt");

//  ExpRandom rand(100);
  XRandom rand;

  for (size_t i = 0; i < 10000; i++)
  {
    double tmp = rand.getNext();
    fout << tmp << "\n";
  }

  fout.close();
}