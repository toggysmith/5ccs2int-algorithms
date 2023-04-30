#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

struct Node;

struct
Edge {
  Node* node;
  int weight;
};

struct
Node {
  std::string name;
  std::vector<Edge> edges;

  void
  add_edge(Node* node, int weight) {
    edges.push_back({node, weight});

    node->edges.push_back({this, weight});
  }
};

void
print_node(Node* node) {
  std::cout << "Node: " << node->name << '\n';

  for (const auto& edge : node->edges) {
    std::cout << "   " << edge.node->name << " (" << edge.weight << ")" << '\n';
  }
}

std::pair<Node*, int> get_lowest_node_cost_pair(std::unordered_map<Node*, int> node_cost_pair_list, std::vector<Node*> closed_list) {
  std::pair<Node*, int> lowest_node_cost_pair;

  bool is_empty = true;
  
  for (const auto& node_cost_pair : node_cost_pair_list) {
    if (node_cost_pair.second < lowest_node_cost_pair.second || is_empty) {
      if (std::find(closed_list.begin(), closed_list.end(), node_cost_pair.first) == closed_list.end()) {
        is_empty = false;
        lowest_node_cost_pair = node_cost_pair;
      }
    }
  }

  return lowest_node_cost_pair;
}

int
uniform_cost_search(Node* start_node, Node* goal_node) {
  std::unordered_map<Node*, int> open_list; // {node, cost} pairs
  std::vector<Node*> closed_list;

  // Add the start node to the open list
  open_list[start_node] = 0;

  // Get the node with the lowest cumulative cost so far
  std::pair<Node*, int> lowest_node_cost_pair;

  do {
    lowest_node_cost_pair = get_lowest_node_cost_pair(open_list, closed_list);
    
    // Add all of the neighbours of node with the lowest cumulative cost to the open list and it the closest list
    closed_list.push_back(lowest_node_cost_pair.first);

    for (const auto& edge : lowest_node_cost_pair.first->edges) {
      open_list[edge.node] = lowest_node_cost_pair.second + edge.weight;
    }
  } while (lowest_node_cost_pair.first != goal_node);

  return lowest_node_cost_pair.second;
}

int
main() {
  // Build a graph
  Node* arad = new Node{"ARAD"};
  Node* a = new Node{"a"};
  Node* b = new Node{"b"};
  Node* d = new Node{"d"};
  Node* i = new Node{"i"};
  Node* l = new Node{"l"};
  Node* m = new Node{"m"};
  Node* h = new Node{"h"};
  Node* e = new Node{"e"};
  Node* c = new Node{"c"};
  Node* f = new Node{"f"};
  Node* g = new Node{"g"};
  Node* bucharest = new Node{"bucharest"};

  arad->add_edge(a, 118);
  arad->add_edge(d, 140);
  arad->add_edge(b, 75);
  
  a->add_edge(i, 111);

  i->add_edge(l, 70);
  b->add_edge(c, 71); 
  l->add_edge(m, 75);
  m->add_edge(h, 120);
  h->add_edge(e, 146);
  h->add_edge(g, 138);
  e->add_edge(g, 97);
  e->add_edge(d, 80);
  d->add_edge(f, 99);
  f->add_edge(bucharest, 211);
  g->add_edge(bucharest, 101);
  d->add_edge(c, 151);

  // Employ uniform-cost-search to find the shortest path from ARAD to Bucharest
  int shortest_path = uniform_cost_search(arad, bucharest);

  std::cout << "The shortest path from ARAD to Bucharest is " << shortest_path << '\n';

  // Clean up everything
  delete arad;
  delete a;
  delete b;
  delete d;
  delete i;
  delete l;
  delete m;
  delete h;
  delete e;
  delete c;
  delete f;
  delete g;
  delete bucharest;

  return 0;
}
