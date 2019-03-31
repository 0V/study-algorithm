#include <iostream>
#include <vector>
#include <array>
#include <fstream>
#include <random>
#include "vector2d.h"
#include "node.h"
#include "graph.h"
#include "value_sampler.h"

void CreateGraph()
{
  constexpr int NodeSize = 10;
  std::array<Node, NodeSize> nodes;

  std::cout << "Definition\n"
            << "Input ID and (x, y) as follow: \nID x y > ";

  for (int i = 0; i < NodeSize; i++)
  {
    std::cin >> nodes[i].id;
    std::cin >> nodes[i].p.x;
    std::cin >> nodes[i].p.y;
  }

  Graph<NodeSize> graph(nodes, 15);

  for (auto &idxs : graph.to_pairs())
  {
    std::cout << nodes[idxs[0]] << " " << nodes[idxs[1]] << std::endl;
  }
}

void CreateGraphFromRandom()
{
  constexpr int NodeSize = 100;
  std::array<Node, NodeSize> nodes;

  std::ofstream file("points.txt");

  int sizex = 400;
  int sizey = 400;

  ValueSampler<double> sampler_x(0, sizey);
  ValueSampler<double> sampler_y(0, sizey);

  for (int i = 0; i < NodeSize; i++)
  {
    nodes[i].id = i;
    nodes[i].p.x = sampler_x.sample();
    nodes[i].p.y = sampler_y.sample();
  }

  Graph<NodeSize> graph(nodes, 30);

  for (auto &idxs : graph.to_pairs())
  {
    std::cout << nodes[idxs[0]].p.x << " " << nodes[idxs[0]].p.y << "\n";
    std::cout << nodes[idxs[1]].p.x << " " << nodes[idxs[1]].p.y << "\n\n";
  }

  for (auto &n : nodes)
  {
    file << n.p.x << " " << n.p.y << "\n";
  }
}

int main()
{
  /*/ CreateGraph(); //*/
  /**/ CreateGraphFromRandom(); //*/
}