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

	void uncross_edges(vector <node> &nodes,
					   vector <int> &route,
					   const int &num_pokemon);

	bool check_edges_crossed(const node &e1_n1,
							 const node &e1_n2,
							 const node &e2_n1,
							 const node &e2_n2);

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

	print_TSP(shortest_path, route);

	return;
}

double FASTTSP::make_TSP_approximation(const vector <node> &nodes,
							  vector <int> &route,
							  const int &num_pokemon) {

	nodeFlyDistance node_distance = nodeFlyDistance();

	vector <bool> in_tree (num_pokemon, false);
	route.push_back(0);
	in_tree.at(0) = true;

	int current = 0;
	int next = 0;
	double total_dist = 0.0;
	node c_node;
	for (int i = 1; i < num_pokemon; ++i) {

		double min_dist = -1.0;
		c_node = nodes.at(current);
		for (int j = 1; j < num_pokemon; ++j) {
			if ((current != j) && (!in_tree.at(j))) {
				double dist = node_distance(c_node, nodes.at(j));

				if (min_dist < -0.5) {
					min_dist = dist;
					next = j;
				}
				else if (dist < min_dist) {
					min_dist = dist;
					next = j;
				}
			}
		}

		current = next;
		in_tree.at(current) = true;
		total_dist += min_dist;
		min_dist = 0.0;

		route.push_back(current);
	}

	total_dist += node_distance(nodes.at(0), nodes.at(route.back()));

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

void uncross_edges(vector <node> &nodes,
				   vector <int> &route,
				   const int &num_pokemon) {

	for (int i = 0; i < num_pokemon - 1; ++i) {

		for (int j = i + 2; j < num_pokemon; ++j) {
			
		}
	}

	return;
}

bool check_edges_crossed(const node &e1_n1,
						 const node &e1_n2,
						 const node &e2_n1,
						 const node &e2_n2) {

	double x_intercept = 0.0;
	double y_intercept = 0.0;

	double slope_one = 0.0;
	double slope_two = 0.0;

	if (e1_n1.x == e1_n2.x) {

		if (e2_n1.x == e2_n2.x) {

			if (e1_n1.x == e2_n1.x) {
				if ((!(e1_n1.y < e2_n1.y) && !(e1_n1.y > e2_n2.y))
					|| (!(e1_n1.y > e2_n1.y) && !(e1_n1.y < e2_n2.y))) {
					
				}
			}
			else { return false; }
		}
		else {
			slope_one = double(e1_n2.y - e1_n1.y) / (e1_n2.x - e1_n1.x);
			slope_two = double(e2_n2.y - e2_n1.y) / (e2_n2.x - e2_n1.x);

			y_intercept = e1_n1.y + slope_one * ( ((e1_n1.y - e2_n1.y - slope_one * e1_n1.x + slope_two * e2_n1.x) / (slope_two - slope_one)) - e1_n1.x );

			if (((!(y_intercept < e2_n1.y) && !(y_intercept > e2_n2.y))
				|| (!(y_intercept > e2_n1.y) && !(y_intercept < e2_n2.y)))
				&& ((!(e2_n1.x < e1_n1.x) && !(e2_n2.x > e1_n1.x))
					|| (!(e2_n1.x > e1_n1.x) && !(e2_n2.x < e1_n1.x)))){
				return true;
			}
		}
	}
	else if (e2_n1.x == e2_n2.x) {

		if (e1_n1.x == e1_n2.x) {

			if (e1_n1.x == e2_n1.x) {

			}
			else { return false; }
		}
		else {
			slope_one = double(e1_n2.y - e1_n1.y)/(e1_n2.x - e1_n1.x);
			slope_two = double(e2_n2.y - e2_n1.y)/(e2_n2.x - e2_n1.x);

			y_intercept = e1_n1.y + slope_one * ( ((e1_n1.y - e2_n1.y - slope_one * e1_n1.x + slope_two * e2_n1.x) / (slope_two - slope_one)) - e1_n1.x );

			if (((!(y_intercept < e1_n1.y) && !(y_intercept > e1_n2.y))
				 || (!(y_intercept > e1_n1.y) && !(y_intercept < e1_n2.y)))
				&& ((!(e1_n1.x < e2_n1.x) && !(e1_n2.x > e2_n1.x))
					|| (!(e1_n1.x > e2_n1.x) && !(e1_n2.x < e2_n1.x)))){
					return true;
			}
		}
	}
	else if (e1_n1.y == e1_n2.y) {

		if (e2_n1.y == e2_n2.y) {

			if (e1_n1.y == e2_n1.y) {

			}
			else { return false; }
		}
		else {
			slope_one = double(e1_n2.y - e1_n1.y)/(e1_n2.x - e1_n1.x);
			slope_two = double(e2_n2.y - e2_n1.y)/(e2_n2.x - e2_n1.x);
			
			x_intercept = (e1_n1.y - e2_n1.y - slope_one * e1_n1.x + slope_two * e2_n1.x) / (slope_two - slope_one);
			
			if ((!(x_intercept < e2_n1.x) && !(x_intercept > e2_n2.x))
				|| (!(x_intercept > e2_n1.x) && !(x_intercept < e2_n2.x))) {
				return true;
			}
			if (((!(x_intercept < e2_n1.x) && !(x_intercept > e2_n2.x))
				 || (!(x_intercept > e2_n1.x) && !(x_intercept < e2_n2.x)))
				&& ((!(e2_n1.y < e1_n1.y) && !(e2_n2.y > e1_n1.y))
					|| (!(e2_n1.y > e1_n1.y) && !(e2_n2.y < e1_n1.y)))){
					return true;
			}
		}
	}
	else if (e2_n1.y == e2_n2.y) {

		if (e1_n1.y == e1_n2.y) {

			if (e1_n1.y == e2_n1.y) {

			}
			else { return false; }
		}
		else {
			slope_one = double(e1_n2.y - e1_n1.y)/(e1_n2.x - e1_n1.x);
			slope_two = double(e2_n2.y - e2_n1.y)/(e2_n2.x - e2_n1.x);
			
			x_intercept = (e1_n1.y - e2_n1.y - slope_one * e1_n1.x + slope_two * e2_n1.x) / (slope_two - slope_one);
			
			if ((!(x_intercept < e1_n1.x) && !(x_intercept > e1_n2.x))
				|| (!(x_intercept > e1_n1.x) && !(x_intercept < e1_n2.x))) {
				return true;
			}
			if (((!(x_intercept < e1_n1.x) && !(x_intercept > e1_n2.x))
				 || (!(x_intercept > e1_n1.x) && !(x_intercept < e1_n2.x)))
				&& ((!(e1_n1.y < e2_n1.y) && !(e1_n2.y > e2_n1.y))
					|| (!(e1_n1.y > e2_n1.y) && !(e1_n2.y < e2_n1.y)))){
					return true;
			}
		}
	}
	else {
		
	}

	return false;
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
