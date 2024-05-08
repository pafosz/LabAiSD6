#include "../include/graph.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "rus");

	Graph<int> G;
	G.add_vertex(1);
	G.add_vertex(2);
	G.add_vertex(3);
	G.add_vertex(4);
	G.add_vertex(5);
	G.add_edge(1, 2, 3);
	G.add_edge(2, 3, 1);
	G.add_edge(2, 5, 5);
	G.add_edge(3, 1, 3);
	G.add_edge(3, 4, 3);
	cout << G.has_vertex(12);
		

	return 0;
}