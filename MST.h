//
//  MST.h
//  Pokéman
//
//  Created by John West on 4/3/15.
//  Copyright (c) 2015 John West. All rights reserved.
//

#ifndef Poke_man_MST_h
#define Poke_man_MST_h

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>

#include "node.h"

using namespace std;

class MST {
private:
	void get_pokemon_locations(vector <node> & nodes, const int &num_pokemon);

	void print_MST(const double& distance, const vector <nodeEdge>& edges);

public:
	MST();

	void run_MST();
};

MST::MST() {}

void MST::run_MST() {

	double total_dist = 0.0;

	int num_pokemon = 0;

	cin >> num_pokemon;

	vector <node> nodes (num_pokemon);
	vector <bool> in_tree (num_pokemon, false);
	vector <nodeEdge> min_dist (num_pokemon, nodeEdge(-1, 0));
	nodeBeginnerDistance node_distance = nodeBeginnerDistance();

	get_pokemon_locations(nodes, num_pokemon);

	int current = 0;
	node& c_node = nodes.at(current);
	nodeEdge next_edge = nodeEdge(-1, 0);

	in_tree.at(current) = true;
	min_dist.at(current).distance = 0;

	for (int i = 1; i < num_pokemon; ++i) {

		for (int j = 1; j < num_pokemon; ++j) {
			if (!in_tree.at(j)) {
				double dist = node_distance(c_node, nodes.at(j));

				nodeEdge& c_edge = min_dist.at(j);

				if (dist >= -0.5) {
					if (c_edge.previous == -1) {
						c_edge.previous = current;
						c_edge.distance = dist;
					}
					else if (dist < c_edge.distance) {
						c_edge.previous = current;
						c_edge.distance = dist;
					}
				}

				if (c_edge.distance >= -0.5) {
					if (next_edge.previous == -1) {
						next_edge.previous = j;
						next_edge.distance = c_edge.distance;
					}
					else if (c_edge.distance < next_edge.distance) {
						next_edge.previous = j;
						next_edge.distance = c_edge.distance;
					}
				}
			}
		}

		if (next_edge.previous != -1) {
			current = next_edge.previous;
			c_node = nodes.at(current);
			total_dist += next_edge.distance;

			in_tree.at(current) = true;

			next_edge = nodeEdge(-1, 0);
		}
	}

	print_MST(total_dist, min_dist);

	return;
}

void MST::get_pokemon_locations(vector <node> &nodes, const int & num_pokemon) {

	string input;
	bool coast_pkmn = false;

	getline(cin, input);

	static const char c = ' ';
	for (int i = 0; i < num_pokemon; ++i) {
		if (getline(cin, input)) {
			size_t pos = input.find(c);

			node& current = nodes.at(i);
			current.x = stoi(input.substr(0, pos));
			current.y = stoi(input.substr(pos + 1));

			if (!coast_pkmn) {
				if ((current.y == 0) && (current.x <= 0)) {
					coast_pkmn = true;
				}
				else if ((current.x == 0) && (current.y < 0)) {
					coast_pkmn = true;
				}
			}
		}
		else {
			cerr << "\ngetline failed" << endl;
		}
	}

	if (!coast_pkmn) {
		cerr << "Cannot construct MST" << endl;
		exit(1);
	}

	return;
}

void MST::print_MST(const double& distance, const vector <nodeEdge>& edges) {

	ostringstream ss;

	ss << setprecision(2);
	ss << fixed;

	ss << distance << '\n';

	int first, second;
	for (int i = 1; i < int(edges.size()); ++i) {

		if (edges.at(i).previous < i) {
			first = edges.at(i).previous;
			second = i;
		}
		else {
			first = i;
			second = edges.at(i).previous;
		}

		ss << first << ' ' << second << '\n';
	}

	cout << ss.str();

	return;
}


#endif
