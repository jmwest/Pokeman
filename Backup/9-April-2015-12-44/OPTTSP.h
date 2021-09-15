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
#include <list>

#include "node.h"
#include "FASTTSP.h"

using namespace std;

class OPTTSP {
private:
	void get_pokemon_locations(vector <node> &nodes,
							   const int &num_pokemon);

//	double make_TSP_approximation(const vector <node> &nodes,
//								  vector < vector <nodeEdge> > &edges,
//								  vector <int> &route,
//								  const int &num_pokemon);

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

	FASTTSP fast;
	shortest_path = fast.make_TSP_approximation(nodes, edges, route, num_pokemon);

//	cout << "\nfirst estimate: " << shortest_path << endl;

//	shortest_path *= 0.9;

	int initial_node = 0;
	priority_depth_first_search(nodes, edges, route, vector <int> (), in_tree, n_distance, num_pokemon, 0.0, shortest_path, 0, 0, initial_node);

//	cout << "\nbest value: " << shortest_path << endl;

	/////////////////////////////////////////////////////////////////
//	cout << "Route:\n";
//	
//	for (vector <int>::iterator it = initial_route.begin(); it != initial_route.end(); ++it) {
//		cout << *it << ' ';
//	}
//	cout << "\n";
	//////////////////////////////////////////////////////////////////

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

//double OPTTSP::make_TSP_approximation(const vector <node> &nodes,
//									  vector < vector <nodeEdge> > &edges,
//									  vector <int> &route,
//									  const int &num_pokemon) {
//
//	nodeFlyDistance node_distance = nodeFlyDistance();
//
//	for (int i = 0; i < num_pokemon; ++i) {
//
//		node c_node = nodes.at(i);
//		for (int j = 0; j < num_pokemon; ++j) {
//
//			if (i != j) {
//				nodeEdge& c_edge = edges.at(i).at(j);
//				c_edge.distance = node_distance(c_node, nodes.at(j));
//				c_edge.previous = j;
//			}
//			else {
//				edges.at(i).at(j).distance = -1.0;
//			}
//		}
//
//		sort(edges.at(i).begin(), edges.at(i).end(), nodeEdgeComparator());
//	}
//
////	vector <int> num_connections (num_pokemon, 0);
////	++num_connections.at(0);
////
////	int current = 0;
////	double total_dist = 0.0;
////	for (int k = 1; k < num_pokemon; ++k) {
////		int pos = 1;
////		bool found = false;
////
////		while (!found) {
////			nodeEdge& next_edge = edges.at(current).at(pos);
////			
////			if (num_connections.at(next_edge.previous) < 2) {
////				++num_connections.at(next_edge.previous);
////				total_dist += next_edge.distance;
////
////				found = true;
////			}
////			else { ++pos; }
////		}
////
////		found = false;
////		pos = 1;
////
////		while (!found) {
////
////			if (pos < num_pokemon) {
////				if (num_connections.at(pos) == 0) {
////					current = pos;
////
////					found = true;
////				}
////				else { ++pos; }
////			}
////			else {
////				if (num_connections.at(pos % num_pokemon) == 1) {
////					current = pos;
////					
////					found = true;
////				}
////				else { ++pos; }
////			}
////		}
////	}
////
////	for (int m = 0; m < num_pokemon; ++m) {
////		if (m != current) {
////			if (num_connections.at(m) < 2) {
////				total_dist += edges.at(current).at(m).distance;
////
////				break;
////			}
////		}
////	}
//
//	vector <bool> in_tree (num_pokemon, false);
//	in_tree.at(0) = true;
//
//	int current = 0;
//	double total_dist = 0.0;
//	for (int k = 1; k < num_pokemon; ++k) {
//		int pos = 1;
//		bool found = false;
//
//		route.at(k - 1) = current;
//
//		while (!found && (pos < num_pokemon)) {
//			nodeEdge& next_edge = edges.at(current).at(pos);
//
//			if (!in_tree.at(next_edge.previous)) {
//				in_tree.at(next_edge.previous) = true;
//				total_dist += next_edge.distance;
//				current = next_edge.previous;
//
//				found = true;
//			}
//			else { ++pos; }
//		}
//	}
//
//	route.back() = current;
//
//	total_dist += node_distance(nodes.at(current), nodes.at(0));
//
//	/////////////////////////////////////////////////////////////////
////	cout << "Route:\n";
////
////	for (vector <int>::iterator it = route.begin(); it != route.end(); ++it) {
////		cout << *it << ' ';
////	}
////	cout << "\n";
//	//////////////////////////////////////////////////////////////////
//
//	return total_dist;
//}

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

	///////////////////////////////////////////////////////////
//	cerr << "\ncurrent: " << current_node << "\tlength: " << path_length << endl;
//	cerr << '\t' << "path: ";
//	for (int a = 0; a < int(current_path.size()); ++a) {
//		cerr << current_path.at(a) << ' ';
//	}
//	cerr << endl;
	///////////////////////////////////////////////////////////

	in_tree.at(current_node) = true;
	current_path.push_back(current_node);
	++num_in;

//	priority_queue <nodeEdge, vector <nodeEdge>, nodeEdgeMaxComparator> current_edges;
	vector <nodeEdge> current_edges;

	const node& c_node = nodes.at(current_node);

	double min_remaining = calculate_partial_MST(nodes, edges, in_tree, current_node, num_in);

	if (path_length + min_remaining >= best_path) {
//		cerr << "branch trimmed." << endl;
		return;
	}
//	cerr << "pq current: " << current_node << endl;
	for (int i = 0; i < num_pokemon; ++i) {
		if (!in_tree.at(i)) {
			double d = node_distance(c_node, nodes.at(i));
//			cerr << i << ':' << d << ' ';
			nodeEdge e = nodeEdge(i, d);
//			current_edges.push(e);
			current_edges.push_back(e);
		}
	}

	if (current_edges.empty()) {
		path_length += node_distance(c_node, nodes.at(first_node));
		if (path_length < best_path) {
			best_path = path_length;
			current_best = current_path;
		}

		///////////////////////////////////////////////////////////
//		cerr << "end reached. best length = " << best_path;
		///////////////////////////////////////////////////////////
	}
	else {
//		while (!current_edges.empty()) {
//			double next_edge = current_edges.top().distance;
//			int next_node = current_edges.top().previous;
//
//			priority_depth_first_search(nodes, current_best, current_path, in_tree, node_distance, num_pokemon, path_length + next_edge, best_path, num_in, next_node, first_node);
//
//			current_edges.pop();
//		}
		for (int j = 0; j < int(current_edges.size()); ++j) {
			double next_edge = current_edges.at(j).distance;
			int next_node = current_edges.at(j).previous;

			priority_depth_first_search(nodes, edges, current_best, current_path, in_tree, node_distance, num_pokemon, path_length + next_edge, best_path, num_in, next_node, first_node);
		}	}

	return;
}

double OPTTSP::calculate_partial_MST(const vector <node> &nodes,
									 const vector < vector <nodeEdge> > &edges,
									 vector <bool> in_tree,
									 const int &start,
									 const int &num_in) {

	double total_dist = 0.0;
	double min_edge = -1.0;

	//////////////////////////////////////////////////////////
	int current = start;
	in_tree.at(current) = true;

	int num_pokemon = int(nodes.size());

	for (int a = 0; a < num_pokemon; ++a) {

		if (in_tree.at(a)) {

			for (int b = 1; b < num_pokemon; ++b) {
				nodeEdge c_edge = edges.at(a).at(b);
				int end = c_edge.previous;
				
				if (!in_tree.at(end)) {

					if (min_edge < -0.5) {
						min_edge = c_edge.distance;
					}
					else if (c_edge.distance < min_edge) {
						min_edge = c_edge.distance;
					}

					break;
				}
			}
		}
	}


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

	total_dist += 2 * min_edge;

	//////////////////////////////////////////////////////////

//	vector <nodeEdge> min_dist (num_pokemon, nodeEdge(-1, 0));
//	nodeFlyDistance node_distance = nodeFlyDistance();
//
//	int current = start;
//	node c_node = nodes.at(current);
//	nodeEdge next_edge = nodeEdge(-1, 0);
//
//	in_tree.at(current) = true;
//	min_dist.at(current).previous = 0;
//	min_dist.at(current).distance = 0;
//
//	for (int i = 1; i < num_pokemon - num_in; ++i) {
//
//		for (int j = 1; j < num_pokemon; ++j) {
//			if (!in_tree.at(j)) {
//				double dist = node_distance(c_node, nodes.at(j));
//
//				if (min_edge < -0.5) {
//					min_edge = dist;
//				}
//				else if (dist < min_edge) {
//					min_edge = dist;
//				}
//
//				nodeEdge& c_edge = min_dist.at(j);
//
//				if (c_edge.previous == -1) {
//					c_edge.previous = current;
//					c_edge.distance = dist;
//				}
//				else if (dist < c_edge.distance) {
//					c_edge.previous = current;
//					c_edge.distance = dist;
//				}
//
//				if (next_edge.previous == -1) {
//					next_edge.previous = j;
//					next_edge.distance = c_edge.distance;
//				}
//				else if (c_edge.distance < next_edge.distance) {
//					next_edge.previous = j;
//					next_edge.distance = c_edge.distance;
//				}
//			}
//		}
//
//		if (next_edge.previous != -1) {
//			current = next_edge.previous;
//			c_node = nodes.at(current);
//			total_dist += next_edge.distance;
//
//			in_tree.at(current) = true;
//
//			next_edge = nodeEdge(-1, 0);
//		}
//	}
//
//	total_dist += 2 * min_edge;

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
