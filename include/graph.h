#ifndef LAB_6_INCLUDE_GRAPH_H
#define LAB_6_INCLUDE_GRAPH_H

#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <unordered_map>

// Обход в ширину
// Поиск кратчайшего Беллмана-Форда

template<typename Vertex, typename Distance = double>
class Graph {
public:
	struct Edge {
		Vertex from, to;
		Distance distane;
	};

	bool has_vertex(const Vertex& v) const;
	void add_vertex(const Vertex& v);
	bool remove_vertex(const Vertex& v);

	bool has_edge(const Edge& e) const; // с учётом расстояния 
	bool has_edge(const Vertex& from, const Vertex& to) const;
	void add_edge(const Vertex& from, const Vertex& to, const Distance& dist);
	bool remove_edge(const Edge& e); // с учётом расстояния 
	bool remove_edge(const Vertex& from, const Vertex& to);

	std::vector<Vertex> vertices() const; // получение списка всех вершин
	std::vector<Edge> edges() const; // получение списка всех рёбер

	size_t order() const; //порядок
	size_t degree(const Vertex& v) const; //степень вершины

	std::vector<Edge> shortest_path(const Vertex& from,	const Vertex& to) const; // поиск кратчайшего пути


private:
	std::vector<Vertex> _vertices;
	std::unordered_map < Vertex, std::vector<Edge> > _edges;
};


#endif // !LAB_6_INCLUDE_GRAPH_H
