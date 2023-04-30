#include <iostream>
#include <vector>
#include <string>

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

  print_node(e);

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
