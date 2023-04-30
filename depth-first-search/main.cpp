#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <stack>

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

void
depth_first_search(Node* start_node, Node* goal_node) {
  // Some data structures
  std::vector<Node*> closed_list; // visited nodes
  std::stack<Node*> open_list; // frontier

  // Add the starting node to the stack and mark it as visited
  open_list.push(start_node);
  closed_list.push_back(start_node);

  // Keep going until the stack is empty
  while (!open_list.empty()) {
    // Get the head of the stack
    Node* stack_head = open_list.top();
    open_list.pop();
    std::cout << stack_head->name << std::endl;
    
    // If the head is the goal node, we can finish the search
    if (stack_head == goal_node) {
      return;
    }

    // Mark every neighbour as visited and add it to the stack
    for (const auto& edge : stack_head->edges) {
      if (std::find(closed_list.begin(), closed_list.end(), edge.node) != closed_list.end()) {
        continue;
      }

      closed_list.push_back(edge.node);
      open_list.push(edge.node);
    }
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

  // Employ depth-first-search algorithm to find shortest path from ARAD to Bucharest
  depth_first_search(arad, bucharest);

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
