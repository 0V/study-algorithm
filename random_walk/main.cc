#include <array>
#include <fstream>
#include <iostream>
#include <random>
#include <string>

// posP : positive probability
int randomWalk(int count, double posP = 0.5) {
  int step = 0;
  std::random_device seed_gen;
  std::mt19937 engine(seed_gen());
  std::uniform_real_distribution<double> dist(0, 1);

  for (int i = 0; i < count; i++) {
    if (dist(engine) < posP)
      step++;
    else
      step--;
  }

  return step;
}

int main() {
  std::ofstream ofs("randwalk_k100_100000.txt");
  for (int k = 0; k < 100000; k++) {
    ofs << randomWalk(100, 2.0/3) << "\n";
  }
}