//
//  OPTTSP.h
//  Pokéman
//
//  Created by John West on 4/3/15.
//  Copyright (c) 2015 John West. All rights reserved.
//

#ifndef Poke_man_OPTTSP_h
#define Poke_man_OPTTSP_h

#include <iostream>
#include <iomanip>
#include <vector>

#include "node.h"

using namespace std;

class FASTTSP {
private:
	void get_pokemon_locations(vector <node> &nodes,
							   const int &num_pokemon);

	void print_TSP(const double &weight,
				   const vector <int> &path);

public:
	FASTTSP();

	void run_FASTTSP();

	double make_TSP_approximation(const vector <node> &nodes,
								  vector < vector <nodeEdge> > &edges,
								  vector <int> &route,
								  const int &num_pokemon);
};

FASTTSP::FASTTSP() {}

void FASTTSP::run_FASTTSP() {

	double shortest_path = 0.0;
	int num_pokemon = 0;

	cin >> num_pokemon;

	vector <node> nodes (num_pokemon);
	vector < vector <nodeEdge> > edges (num_pokemon, vector <nodeEdge> (num_pokemon, nodeEdge(-1, 0.0)));
	vector <int> route (num_pokemon, 0);

	get_pokemon_locations(nodes, num_pokemon);

	shortest_path = make_TSP_approximation(nodes, edges, route, num_pokemon);

	print_TSP(shortest_path, route);

	return;
}

double FASTTSP::make_TSP_approximation(const vector <node> &nodes,
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
	double total_dist = 0.0;
	for (int k = 1; k < num_pokemon; ++k) {
		int pos = 1;
		bool found = false;
		
		route.at(k - 1) = current;
		
		while (!found && (pos < num_pokemon)) {
			nodeEdge& next_edge = edges.at(current).at(pos);
			
			if (!in_tree.at(next_edge.previous)) {
				in_tree.at(next_edge.previous) = true;
				total_dist += next_edge.distance;
				current = next_edge.previous;
				
				found = true;
			}
			else { ++pos; }
		}
	}
	
	route.back() = current;
	
	total_dist += node_distance(nodes.at(current), nodes.at(0));

	return total_dist;
}

void FASTTSP::get_pokemon_locations(vector <node> &nodes, const int & num_pokemon) {

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

void FASTTSP::print_TSP(const double &weight, const vector <int> &path) {
	
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
