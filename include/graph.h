#ifndef LAB_6_INCLUDE_GRAPH_H
#define LAB_6_INCLUDE_GRAPH_H


#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <iterator>
#include <cfloat>


// Обход в ширину
// Поиск кратчайшего Беллмана-Форда

template<typename Vertex, typename Distance = double>
class Graph {
public:
	struct Edge {
		Vertex from, to;
		Distance distance;
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
	std::vector<Edge> edges(const Vertex& v) const; // получение списка всех рёбер выходящих из вершины

	size_t order() const; //порядок
	size_t degree(const Vertex& v) const; //степень вершины

	std::vector<Edge> shortest_path(const Vertex& from, const Vertex& to) const; // поиск кратчайшего пути
	std::vector<Vertex> walk(const Vertex& start_vertex) const; // обход

	void print_vertices() const;
	void print_edges() const;


private:
	std::vector<Vertex> _vertices;
	std::unordered_map < Vertex, std::vector<Edge> > _edges;
};

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::has_vertex(const Vertex& v) const {
	return std::find(_vertices.begin(), _vertices.end(), v) != _vertices.end();
}

template<typename Vertex, typename Distance>
void Graph<Vertex, Distance>::add_vertex(const Vertex& v) {
	if (has_vertex(v)) throw std::invalid_argument("[add_vertex] the vertex already exists");
	_vertices.push_back(v);
	_edges[v] = { };
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::remove_vertex(const Vertex& v) {
	auto& it = std::find(_vertices.begin(), _vertices.end(), v);
	if (it == _vertices.end()) return false;
	_vertices.erase(v);
	_edges.erase(v);
	for (auto& vertex : _vertices) {
		auto& edges = _edges.at(vertex);
		edges.erase(std::remove_if(edges.begin(), edges.end(), [v](const Edge& e) {return e.to == v; }), edges.end());
	}
	return true;
}

template<typename Vertex, typename Distance>
void Graph<Vertex, Distance>::add_edge(const Vertex& from, const Vertex& to, const Distance& dist) {
	if (has_edge({ from, to, dist })) throw std::invalid_argument("[add_edge] the edge already exists");

	auto& edges = _edges[from];
	edges.push_back({ from, to, dist });
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::remove_edge(const Edge& e) {
	if (!has_edge(e)) return false;
	auto& edges = _edges.at(e.from);
	for (const Edge& edge : edges) {
		if (e.to == edge.to && (abs(e.distance - edge.distance) < DBL_EPSILON)) {
			edges.erase(edge);
			return true;
		}
	}
	return false;
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::has_edge(const Edge& e) const {
	auto& edges = _edges.at(e.from);
	for (const auto& edge : edges) {
		if (edge.to == e.to && (abs(e.distance - edge.distance) < DBL_EPSILON)) return true;
	}

	return false;
}

template<typename Vertex, typename Distance>
std::vector<Vertex> Graph<Vertex, Distance>::vertices() const { return _vertices; }

template<typename Vertex, typename Distance>
std::vector<typename Graph<Vertex, Distance>::Edge> Graph<Vertex, Distance>::edges(const Vertex& v) const {
	if (!has_vertex(v)) throw std::invalid_argument("[edges] there is no such vertex in the graph");

	auto& edges = _edges.at(v);
	
	return edges;
}

template<typename Vertex, typename Distance>
void Graph<Vertex, Distance>::print_vertices() const {
	std::cout << "Vertices: [ ";
	for (const Vertex& vertex : _vertices) {
		if (vertex != _vertices.back()) std::cout << vertex << ", ";
		else std::cout << vertex << " ]";
	}
}

template<typename Vertex, typename Distance>
void Graph<Vertex, Distance>::print_edges() const {
	std::cout << "Edges: " << std::endl;
	for (const Vertex& vertex : _vertices) {
		for (const Edge& edge : _edges.at(vertex)) {
			std::cout << edge.from << " -> " << edge.to << "(" << edge.distance << ")" << std::endl;
		}
	}
}



#endif // !LAB_6_INCLUDE_GRAPH_H
