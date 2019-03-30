#include <iostream>
#include <vector>
#include <array>
#include <fstream>
#include <random>
#include "vector2d.h"
#include "node.h"
#include "graph.h"

void CreateGraph()
{
  constexpr int NodeSize = 3;
  std::array<Node, NodeSize> nodes;

  std::cout << "Definition\n"
            << "Input ID and (x, y) as follow: \nID x y > ";

  for (size_t i = 0; i < NodeSize; i++)
  {
    std::cin >> nodes[i].id;
    std::cin >> nodes[i].p.x;
    std::cin >> nodes[i].p.y;
  }

  Graph<NodeSize> graph(nodes);

  for (auto &node : graph.to_pairs())
  {
    std::cout << node[0] << " " << node[1] << std::endl;
  }
}

int main()
{
  /**/ CreateGraph(); //*/
}