#include "../include/graph.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "rus");

	Graph<int> G;
	Graph<int>::Edge edge{ 2, 3, 1 };
	G.add_vertex(1);
	G.add_vertex(2);
	G.add_vertex(3);
	G.add_vertex(4);
	G.add_vertex(5);
	G.add_vertex(6);
	G.add_edge(1, 2, 1);
	G.add_edge(1, 3, 4);
	G.add_edge(1, 6, 30);
	G.add_edge(2, 3, 2);
	G.add_edge(2, 4, 8);
	G.add_edge(3, 4, 2);
	G.add_edge(3, 6, 10);
	G.add_edge(4, 5, 1);
	G.add_edge(4, 6, 5);
	G.add_edge(5, 6, 6);
	
	cout << G.length_shortest_path(3, 6);
	

	
	/*std::for_each(vertex.first, vertex.second, [](const auto& v) {
		std::cout << v << " ";
		});*/

	return 0;
}