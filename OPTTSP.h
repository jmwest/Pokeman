//
//  OPTTSP.h
//  Pokéman
//
//  Created by John West on 4/3/15.
//  Copyright (c) 2015 John West. All rights reserved.
//

#ifndef Poke_man_FASTTSP_h
#define Poke_man_FASTTSP_h

#include <iostream>
#include <iomanip>
#include <vector>

#include "node.h"

using namespace std;

class OPTTSP {
private:
	void get_pokemon_locations(vector <node> &nodes,
							   const int &num_pokemon);

	double make_TSP_approximation(const vector <node> &nodes,
								  vector < vector <nodeEdge> > &edges,
								  vector <int> &route,
								  const int &num_pokemon);

	void two_opt(const vector <node> &nodes,
				 vector <int> &route,
				 const int &num_pokemon);
	
	void switch_crossed_run(vector <int> &route,
							int first,
							int last);

	void priority_depth_first_search(const vector <node> &nodes,
									 const vector < vector <nodeEdge> > &edges,
									 vector <int> &current_best,
									 vector <int> current_path,
									 vector <bool> in_tree,
									 nodeFlyDistance &node_distance,
									 const int &num_pokemon,
									 double path_length,
									 double &best_path,
									 int num_in,
									 int current_node,
									 const int &first_node);

	double calculate_partial_MST(const vector <node> &nodes,
								 const vector < vector <nodeEdge> > &edges,
								 vector <bool> in_tree,
								 const int &start,
								 const int &num_in);

	void print_TSP(const double &weight,
				   const vector <int> &path);

public:
	OPTTSP();

	void run_OPTTSP();
};

OPTTSP::OPTTSP() {}

void OPTTSP::run_OPTTSP() {

	double shortest_path = 0.0;
	int num_pokemon = 0;
	
	cin >> num_pokemon;
	
	vector <node> nodes (num_pokemon);
	vector < vector <nodeEdge> > edges (num_pokemon, vector <nodeEdge> (num_pokemon, nodeEdge(-1, 0.0)));
	vector <int> route (num_pokemon, 0);
	vector <bool> in_tree (num_pokemon, false);
	nodeFlyDistance n_distance;

	get_pokemon_locations(nodes, num_pokemon);

	shortest_path = make_TSP_approximation(nodes, edges, route, num_pokemon);

	int initial_node = 0;
	in_tree.at(0) = true;
	priority_depth_first_search(nodes, edges, route, vector <int> (), in_tree, n_distance, num_pokemon, 0.0, shortest_path, 1, 0, initial_node);

	print_TSP(shortest_path, route);

	return;
}

void OPTTSP::get_pokemon_locations(vector <node> &nodes, const int & num_pokemon) {
	
	string input;
	
	getline(cin, input);
	
	static const char c = ' ';
	for (int i = 0; i < num_pokemon; ++i) {
		if (getline(cin, input)) {
			size_t pos = input.find(c);
			
			node& current = nodes.at(i);
			current.x = stoi(input.substr(0, pos));
			current.y = stoi(input.substr(pos + 1));
		}
		else {
			cerr << "\ngetline failed" << endl;
		}
	}

	return;
}

double OPTTSP::make_TSP_approximation(const vector <node> &nodes,
									  vector < vector <nodeEdge> > &edges,
									  vector <int> &route,
									  const int &num_pokemon) {

	nodeFlyDistance node_distance = nodeFlyDistance();

	for (int i = 0; i < num_pokemon; ++i) {

		node c_node = nodes.at(i);
		for (int j = 0; j < num_pokemon; ++j) {

			if (i != j) {
				nodeEdge& c_edge = edges.at(i).at(j);
				c_edge.distance = node_distance(c_node, nodes.at(j));
				c_edge.previous = j;
			}
			else {
				edges.at(i).at(j).distance = -1.0;
			}
		}

		sort(edges.at(i).begin(), edges.at(i).end(), nodeEdgeComparator());
	}

	vector <bool> in_tree (num_pokemon, false);
	in_tree.at(0) = true;

	int current = 0;

	for (int k = 1; k < num_pokemon; ++k) {
		int pos = 1;
		bool found = false;

		route.at(k - 1) = current;

		while (!found) {
			nodeEdge& next_edge = edges.at(current).at(pos);

			if (!in_tree.at(next_edge.previous)) {
				in_tree.at(next_edge.previous) = true;
				current = next_edge.previous;

				found = true;
			}
			else { ++pos; }
		}
	}

	route.back() = current;

	two_opt(nodes, route, num_pokemon);

	double total_dist = 0.0;
	for (int i = 0; i < num_pokemon - 1; i++) {
		total_dist += node_distance(nodes.at(route.at(i)), nodes.at(route.at(i + 1)));
	}

	total_dist += node_distance(nodes.at(route.front()), nodes.at(route.back()));

	return total_dist;
}

void OPTTSP::two_opt(const vector <node> &nodes,
					 vector <int> &route,
					 const int &num_pokemon) {
	
	nodeFlyDistance n_d;
	
	for (int i = 0; i < num_pokemon; ++i) {
		
		double best_improvement = -1.0;
		double save = 0.0;
		int switch1 = -1;
		
		int c1_node1 = route.at(i % num_pokemon);
		int c1_node2 = route.at((i + 1) % num_pokemon);
		double c1_dist = n_d(nodes.at(c1_node1), nodes.at(c1_node2));
		
		for (int j = i + 2; j < num_pokemon + i - 1; ++j) {
			int c2_node1 = route.at(j % num_pokemon);
			int c2_node2 = route.at((j + 1) % num_pokemon);
			double c2_dist = n_d(nodes.at(c2_node1), nodes.at(c2_node2));
			
			double next1_dist = n_d(nodes.at(c1_node1), nodes.at(c2_node1));
			double next2_dist = n_d(nodes.at(c1_node2), nodes.at(c2_node2));
			
			save = c1_dist + c2_dist - next1_dist - next2_dist;
			if (save > 0.0) {
				if (switch1 == -1) {
					switch1 = j % num_pokemon;
					best_improvement = save;
				}
				else if (save > best_improvement) {
					switch1 = j % num_pokemon;
					best_improvement = save;
				}
			}
		}
		
		if (switch1 != -1) {
			int first, last;
			
			if ((i + 1) % num_pokemon < switch1) {
				first = (i + 1) % num_pokemon;
				last = switch1;
			}
			else {
				first = switch1 + 1;
				last = i % num_pokemon;
			}
			
			switch_crossed_run(route, first, last);
		}
	}
	
	return;
}

void OPTTSP::switch_crossed_run(vector <int> &route,
								int first,
								int last) {
	
	int temp;
	for (int i = 0; i < (last - first + 1) / 2; ++i) {
		temp = route.at(first + i);
		route.at(first + i) = route.at(last - i);
		route.at(last - i) = temp;
	}
	
	return;
}

void OPTTSP::priority_depth_first_search(const vector <node> &nodes,
										 const vector < vector <nodeEdge> > &edges,
										 vector <int> &current_best,
										 vector <int> current_path,
										 vector <bool> in_tree,
										 nodeFlyDistance &node_distance,
										 const int &num_pokemon,
										 double path_length,
										 double &best_path,
										 int num_in,
										 int current_node,
										 const int &first_node) {

	current_path.push_back(current_node);

	const node& c_node = nodes.at(current_node);

	if (num_in + 1 == num_pokemon) {
		int next_node = 0;

		for (int i = 0; i < num_pokemon; ++i) {
			if (!in_tree.at(i)) {
				next_node = i;

				break;
			}
		}

		current_path.push_back(next_node);

		path_length += node_distance(c_node, nodes.at(next_node));
		path_length += node_distance(nodes.at(next_node), nodes.at(first_node));

		if (path_length < best_path) {
			best_path = path_length;
			current_best = current_path;
		}
	}
	else {
		vector <nodeEdge> current_edges;

		for (int i = 0; i < num_pokemon; ++i) {
			if (!in_tree.at(i)) {
				double d = node_distance(c_node, nodes.at(i));

				nodeEdge e = nodeEdge(i, d);
				current_edges.push_back(e);
			}
		}

		for (int j = 0; j < int(current_edges.size()); ++j) {

			double next_edge = current_edges.at(j).distance;
			int next_node = current_edges.at(j).previous;

			in_tree.at(next_node) = true;
			double min_remaining = calculate_partial_MST(nodes, edges, in_tree, next_node, num_in + 1);

			if (path_length + next_edge + min_remaining <= best_path) {
				priority_depth_first_search(nodes, edges, current_best, current_path, in_tree, node_distance, num_pokemon, path_length + next_edge, best_path, num_in + 1, next_node, first_node);
			}

			in_tree.at(next_node) = false;
		}
	}

	return;
}

double OPTTSP::calculate_partial_MST(const vector <node> &nodes,
									 const vector < vector <nodeEdge> > &edges,
									 vector <bool> in_tree,
									 const int &start,
									 const int &num_in) {

	double total_dist = 0.0;
	double min_connect = -1.0;

	int current = start;
	in_tree.at(current) = true;

	int num_pokemon = int(nodes.size());

	for (int a = 0; a < 2; ++a) {

		for (int b = 1; b < num_pokemon; ++b) {
			nodeEdge c_edge;

			if (a) {
				c_edge = edges.at(start).at(b);
			}
			else {
				c_edge = edges.at(a).at(b);
			}

			int end = c_edge.previous;

			if (!in_tree.at(end)) {

				if (min_connect < -0.5) {
					min_connect = c_edge.distance;
				}
				else if (c_edge.distance < min_connect) {
					min_connect = c_edge.distance;
				}

				break;
			}
		}
	}

	total_dist += min_connect;

	for (int i = 1; i < num_pokemon - num_in; ++i) {

		for (int j = 1; j < num_pokemon; ++j) {
			nodeEdge c_edge = edges.at(current).at(j);
			int next = c_edge.previous;

			if (!in_tree.at(next)) {
				total_dist += c_edge.distance;

				in_tree.at(next) = true;
				current = next;
				break;
			}
		}
	}

	return total_dist;
}

void OPTTSP::print_TSP(const double &weight, const vector <int> &path) {

	ostringstream ss;
	
	ss << setprecision(2);
	ss << fixed;

	ss << weight << '\n';

	for (int i = 0; i < int(path.size()); ++i) {
		ss << path.at(i);

		if (i < int(path.size()) - 1) {
			ss << ' ';
		}
	}

	cout << ss.str();

	return;
}

#endif
