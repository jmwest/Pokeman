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
#include <unordered_set>

#include "node.h"

using namespace std;

class FASTTSP {
private:
	void get_pokemon_locations(vector <node> &nodes,
							   const int &num_pokemon);

	void two_opt(const vector <node> &nodes,
				 vector <int> &route,
				 const int &num_pokemon,
				 double &distance);

	void switch_crossed_run(vector <int> &route,
							int first,
							int last);

	void print_TSP(const double &weight,
				   const vector <int> &path);

public:
	FASTTSP();

	void run_FASTTSP();

	double make_TSP_approximation(const vector <node> &nodes,
								  vector <int> &route,
								  const int &num_pokemon);
};

FASTTSP::FASTTSP() {}

void FASTTSP::run_FASTTSP() {

	double shortest_path = 0.0;
	int num_pokemon = 0;

	cin >> num_pokemon;

	vector <node> nodes (num_pokemon);
	vector <int> route;

	get_pokemon_locations(nodes, num_pokemon);

	shortest_path = make_TSP_approximation(nodes, route, num_pokemon);

	two_opt(nodes, route, num_pokemon, shortest_path);

	print_TSP(shortest_path, route);

	return;
}

double FASTTSP::make_TSP_approximation(const vector <node> &nodes,
									   vector <int> &route,
									   const int &num_pokemon) {

	nodeFlyDistance node_distance = nodeFlyDistance();

	unordered_set <int> outies;

	for (int i = 1; i < num_pokemon; ++i) {
		outies.insert(i);
	}

	route.push_back(0);
	
	int current = 0;
	int next = 0;
	double total_dist = 0.0;
	node c_node;
	for (int i = 1; i < num_pokemon; ++i) {
		
		double min_dist = -1.0;
		c_node = nodes.at(current);

		for (unordered_set <int>::iterator it = outies.begin(); it != outies.end(); ++it) {
			double dist = node_distance(c_node, nodes.at(*it));

			if (min_dist < -0.5) {
				min_dist = dist;
				next = *it;
			}
			else if (dist < min_dist) {
				min_dist = dist;
				next = *it;
			}
		}

		current = next;
		outies.erase(current);
		total_dist += min_dist;
		min_dist = 0.0;

		route.push_back(current);
	}
	
	total_dist += node_distance(nodes.at(0), nodes.at(route.back()));

	return total_dist;
}

void FASTTSP::get_pokemon_locations(vector <node> &nodes,
									const int & num_pokemon) {

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

void FASTTSP::two_opt(const vector <node> &nodes,
					  vector <int> &route,
					  const int &num_pokemon,
					  double &distance) {

	nodeFlyDistance n_d;

	int num_not_fixed = 0;
	int lower_est = distance / 1.3;
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

			distance -= best_improvement;
			switch_crossed_run(route, first, last);
		}
		else {
			++num_not_fixed;
		}

		if ((num_pokemon > 1000) && ((lower_est >= distance) && (num_not_fixed > (num_pokemon / 3)))) {
			break;
		}

		if ((num_pokemon > 10000) && ((lower_est >= distance) && (num_not_fixed > num_pokemon / 5))) {
			break;
		}
	}

	return;
}

void FASTTSP::switch_crossed_run(vector <int> &route,
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

void FASTTSP::print_TSP(const double &weight,
						const vector <int> &path) {
	
	ostringstream ss;
	
	ss << setprecision(2);
	ss << fixed;
	
	ss << weight << '\n';

	int num_pkmn = int(path.size());
	int begin = 0;
	for (int a = 0; a < num_pkmn; ++a) {
		if (!path.at(a)) {
			begin = a;

			break;
		}
	}
	
	for (int i = 0; i < num_pkmn; ++i) {
		ss << path.at(begin % num_pkmn);
		
		if (i < int(path.size()) - 1) {
			ss << ' ';
		}

		++begin;
	}
	
	cout << ss.str();
	
	return;
}

#endif
