//
//  FASTTSP.h
//  Pokéman
//
//  Created by John West on 4/3/15.
//  Copyright (c) 2015 John West. All rights reserved.
//

#ifndef Poke_man_FASTTSP_h
#define Poke_man_FASTTSP_h

#include <iostream>
#include <vector>
#include <list>

#include "node.h"

using namespace std;

class FASTTSP {
private:
	void get_pokemon_locations(vector <node> &nodes, const int &num_pokemon);
	double make_fly_MST(vector <node> &nodes, const int &num_pokemon);

public:
	FASTTSP();

	void run_FASTTSP();
};

FASTTSP::FASTTSP() {}

void FASTTSP::run_FASTTSP() {

	double shortest_path = 0.0;
	int num_pokemon = 0;
	
	cin >> num_pokemon;
	
	vector <node> nodes (num_pokemon);

	get_pokemon_locations(nodes, num_pokemon);

	shortest_path = make_fly_MST(nodes, num_pokemon);

	cout << "\nfirst estimate: " << shortest_path << endl;

	return;
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

double FASTTSP::make_fly_MST(vector <node> &nodes, const int &num_pokemon) {

	vector < vector <nodeEdge> > distances (num_pokemon, vector <nodeEdge> (num_pokemon, nodeEdge(-1, 0.0)));
	nodeFlyDistance node_distance = nodeFlyDistance();

	for (int i = 0; i < num_pokemon; ++i) {

		node& c_node = nodes.at(i);
		for (int j = 0; j < num_pokemon; ++j) {

			if (i != j) {
				nodeEdge& c_edge = distances.at(i).at(j);
				c_edge.distance = node_distance(c_node, nodes.at(j));
				c_edge.previous = j;
			}
			else {
				distances.at(i).at(j).distance = -1.0;
			}
		}

		sort(distances.at(i).begin(), distances.at(i).end(), nodeEdgeComparator());
	}

	vector <bool> in_tree (num_pokemon, false);
	in_tree.front() = true;
	vector <int> route (num_pokemon, 0);
//cerr << "oh" << endl;
	int current = 0;
	double total_dist = 0.0;
	for (int k = 1; k < num_pokemon; ++k) {
		int pos = 1;
		bool found = false;
//		cerr << "\nk: " << k << " current: " << current << endl;
		route.at(k - 1) = current;

		while (!found && (pos < num_pokemon)) {
			nodeEdge& next_edge = distances.at(current).at(pos);
//cerr << "pos: " << pos << " next_edge: " << next_edge.previous << ' ';
			if (!in_tree.at(next_edge.previous)) {
				in_tree.at(next_edge.previous) = true;
				total_dist += next_edge.distance;
				current = next_edge.previous;

				found = true;
			}
			else { ++pos; }
		}
	}
//	cerr << "no" << endl;
	route.back() = current;

	total_dist += node_distance(nodes.at(current), nodes.at(0));

	cout << "Route:\n";

	for (vector <int>::iterator it = route.begin(); it != route.end(); ++it) {
		cout << *it << ' ';
	}
	cout << "\n";

	return total_dist;
}

#endif
