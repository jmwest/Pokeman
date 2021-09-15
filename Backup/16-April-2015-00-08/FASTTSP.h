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

	void uncross_edges(const vector <node> &nodes,
					   vector <int> &route,
					   const int &num_pokemon);

	bool check_edges_crossed(const node &e1_n1,
							 const node &e1_n2,
							 const node &e2_n1,
							 const node &e2_n2);

//	bool check_adjacent_edges_overlap(const node &e1_n1,
//									  const node &e1_n2,
//									  const node &e2_n1,
//									  const node &e2_n2);

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

	cerr << "Initial path:\n";
	print_TSP(shortest_path, route);

	cerr << "\nUncrossing...\n";
	uncross_edges(nodes, route, num_pokemon);

	nodeFlyDistance node_dist;

	shortest_path = 0;
	for (int i = 0; i < num_pokemon - 1; i++) {
		shortest_path += node_dist(nodes.at(route.at(i)), nodes.at(route.at(i + 1)));
	}

	shortest_path += node_dist(nodes.at(route.front()), nodes.at(route.back()));

	print_TSP(shortest_path, route);

	return;
}

double FASTTSP::make_TSP_approximation(const vector <node> &nodes,
									   vector <int> &route,
									   const int &num_pokemon) {

	nodeFlyDistance node_distance = nodeFlyDistance();

//	unordered_set <node> outies;
//
//	for (int i = 1; i < num_pokemon; ++i) {
//		outies.insert(nodes.at(i));
//	}

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

void FASTTSP::uncross_edges(const vector <node> &nodes,
							vector <int> &route,
							const int &num_pokemon) {

	node c_pair1, c_pair2, n_pair1, n_pair2;
	for (int i = 0; i < num_pokemon - 1; ++i) {

		c_pair1 = nodes.at(route.at(i));
		c_pair2 = nodes.at(route.at(i + 1));
		for (int j = i + 2; j < num_pokemon; ++j) {
//cerr << i << ' ' << j << endl;

			if (j < num_pokemon - 1) {
				n_pair1 = nodes.at(route.at(j));
				n_pair2 = nodes.at(route.at(j + 1));
			}
			else {
				n_pair1 = nodes.at(route.at(j));
				n_pair2 = nodes.at(route.at(0));
			}

			if (check_edges_crossed(c_pair1, c_pair2, n_pair1, n_pair2)) {

//cerr << "\n\nBefore cross: (" << i << ',' << i + 1 << ") (" << j << ',' << j + 1 << ")\n";
//print_TSP(0.0, route);

				if (j < num_pokemon - 1) {
					switch_crossed_run(route, i + 1, j);
				}
				else {
					switch_crossed_run(route, 0, i);
				}

//cerr << "\nAfter cross:\n";
//print_TSP(0.0, route);

//				i = -1;
//				break;
			}
		}
	}

	return;
}

bool FASTTSP::check_edges_crossed(const node &e1_n1,
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
					|| (!(e1_n1.y > e2_n1.y) && !(e1_n1.y < e2_n2.y))

					|| (!(e1_n2.y < e2_n1.y) && !(e1_n2.y > e2_n2.y))
					|| (!(e1_n2.y > e2_n1.y) && !(e1_n2.y < e2_n2.y))

					|| (!(e2_n1.y < e1_n1.y) && !(e2_n1.y > e1_n2.y))
					|| (!(e2_n1.y > e1_n1.y) && !(e2_n1.y < e1_n2.y))

					|| (!(e2_n2.y < e1_n1.y) && !(e2_n2.y > e1_n2.y))
					|| (!(e2_n2.y > e1_n1.y) && !(e2_n2.y < e1_n2.y))) {

					return true;
				}
			}
		}
		else {
			slope_two = double(e2_n2.y - e2_n1.y) / (e2_n2.x - e2_n1.x);

			x_intercept = e1_n1.x;
			y_intercept = e2_n1.y + slope_two * ( x_intercept - e2_n1.x );

			if ( ((!(x_intercept < e1_n1.x) && !(x_intercept > e1_n2.x))
				  || (!(x_intercept > e1_n1.x) && !(x_intercept < e1_n2.x)))
				
				&& ((!(y_intercept < e1_n1.y) && !(y_intercept > e1_n2.y))
					|| (!(y_intercept > e1_n1.y) && !(y_intercept < e1_n2.y)))
				
				&& ((!(x_intercept < e2_n1.x) && !(x_intercept > e2_n2.x))
					|| (!(x_intercept > e2_n1.x) && !(x_intercept < e2_n2.x)))
				
				&& ((!(y_intercept < e2_n1.y) && !(y_intercept > e2_n2.y))
					|| (!(y_intercept > e2_n1.y) && !(y_intercept < e2_n2.y))) ) {
					
					return true;
			}
		}
	}
	else if (e2_n1.x == e2_n2.x) {

		if (e1_n1.x == e1_n2.x) {

			if (e1_n1.x == e2_n1.x) {

				if ((!(e1_n1.y < e2_n1.y) && !(e1_n1.y > e2_n2.y))
					|| (!(e1_n1.y > e2_n1.y) && !(e1_n1.y < e2_n2.y))
					
					|| (!(e1_n2.y < e2_n1.y) && !(e1_n2.y > e2_n2.y))
					|| (!(e1_n2.y > e2_n1.y) && !(e1_n2.y < e2_n2.y))
					
					|| (!(e2_n1.y < e1_n1.y) && !(e2_n1.y > e1_n2.y))
					|| (!(e2_n1.y > e1_n1.y) && !(e2_n1.y < e1_n2.y))
					
					|| (!(e2_n2.y < e1_n1.y) && !(e2_n2.y > e1_n2.y))
					|| (!(e2_n2.y > e1_n1.y) && !(e2_n2.y < e1_n2.y))) {
					
					return true;
				}
			}
		}
		else {
			slope_one = double(e1_n2.y - e1_n1.y)/(e1_n2.x - e1_n1.x);

			x_intercept = e2_n1.x;
			y_intercept = e1_n1.y + slope_one * ( x_intercept - e1_n1.x );

			if ( ((!(x_intercept < e1_n1.x) && !(x_intercept > e1_n2.x))
				  || (!(x_intercept > e1_n1.x) && !(x_intercept < e1_n2.x)))
				
				&& ((!(y_intercept < e1_n1.y) && !(y_intercept > e1_n2.y))
					|| (!(y_intercept > e1_n1.y) && !(y_intercept < e1_n2.y)))
				
				&& ((!(x_intercept < e2_n1.x) && !(x_intercept > e2_n2.x))
					|| (!(x_intercept > e2_n1.x) && !(x_intercept < e2_n2.x)))
				
				&& ((!(y_intercept < e2_n1.y) && !(y_intercept > e2_n2.y))
					|| (!(y_intercept > e2_n1.y) && !(y_intercept < e2_n2.y))) ) {
					
					return true;
			}
		}
	}
	else if (e1_n1.y == e1_n2.y) {

		if (e2_n1.y == e2_n2.y) {

			if (e1_n1.y == e2_n1.y) {

				if ((!(e1_n1.x < e2_n1.x) && !(e1_n1.x > e2_n2.x))
					|| (!(e1_n1.x > e2_n1.x) && !(e1_n1.x < e2_n2.x))

					|| (!(e1_n2.x < e2_n1.x) && !(e1_n2.x > e2_n2.x))
					|| (!(e1_n2.x > e2_n1.x) && !(e1_n2.x < e2_n2.x))

					|| (!(e2_n1.x < e1_n1.x) && !(e2_n1.x > e1_n2.x))
					|| (!(e2_n1.x > e1_n1.x) && !(e2_n1.x < e1_n2.x))

					|| (!(e2_n2.x < e1_n1.x) && !(e2_n2.x > e1_n2.x))
					|| (!(e2_n2.x > e1_n1.x) && !(e2_n2.x < e1_n2.x))) {

					return true;
				}
			}
		}
		else {
			slope_two = double(e2_n2.y - e2_n1.y)/(e2_n2.x - e2_n1.x);

			x_intercept = (e1_n1.y - e2_n1.y + slope_two * e2_n1.x) / (slope_two);
			y_intercept = e1_n1.y;

			if ( ((!(x_intercept < e1_n1.x) && !(x_intercept > e1_n2.x))
				  || (!(x_intercept > e1_n1.x) && !(x_intercept < e1_n2.x)))
				
				&& ((!(y_intercept < e1_n1.y) && !(y_intercept > e1_n2.y))
					|| (!(y_intercept > e1_n1.y) && !(y_intercept < e1_n2.y)))
				
				&& ((!(x_intercept < e2_n1.x) && !(x_intercept > e2_n2.x))
					|| (!(x_intercept > e2_n1.x) && !(x_intercept < e2_n2.x)))
				
				&& ((!(y_intercept < e2_n1.y) && !(y_intercept > e2_n2.y))
					|| (!(y_intercept > e2_n1.y) && !(y_intercept < e2_n2.y))) ) {
					
					return true;
			}
		}
	}
	else if (e2_n1.y == e2_n2.y) {

		if (e1_n1.y == e1_n2.y) {

			if (e1_n1.y == e2_n1.y) {

				if ((!(e1_n1.x < e2_n1.x) && !(e1_n1.x > e2_n2.x))
					|| (!(e1_n1.x > e2_n1.x) && !(e1_n1.x < e2_n2.x))

					|| (!(e1_n2.x < e2_n1.x) && !(e1_n2.x > e2_n2.x))
					|| (!(e1_n2.x > e2_n1.x) && !(e1_n2.x < e2_n2.x))

					|| (!(e2_n1.x < e1_n1.x) && !(e2_n1.x > e1_n2.x))
					|| (!(e2_n1.x > e1_n1.x) && !(e2_n1.x < e1_n2.x))

					|| (!(e2_n2.x < e1_n1.x) && !(e2_n2.x > e1_n2.x))
					|| (!(e2_n2.x > e1_n1.x) && !(e2_n2.x < e1_n2.x))) {

					return true;
				}
			}
		}
		else {
			slope_one = double(e1_n2.y - e1_n1.y)/(e1_n2.x - e1_n1.x);

			x_intercept = (e2_n1.y - e1_n1.y + slope_one * e1_n1.x) / slope_one;
			y_intercept = e2_n1.y;

			if ( ((!(x_intercept < e1_n1.x) && !(x_intercept > e1_n2.x))
				  || (!(x_intercept > e1_n1.x) && !(x_intercept < e1_n2.x)))
				
				&& ((!(y_intercept < e1_n1.y) && !(y_intercept > e1_n2.y))
					|| (!(y_intercept > e1_n1.y) && !(y_intercept < e1_n2.y)))
				
				&& ((!(x_intercept < e2_n1.x) && !(x_intercept > e2_n2.x))
					|| (!(x_intercept > e2_n1.x) && !(x_intercept < e2_n2.x)))
				
				&& ((!(y_intercept < e2_n1.y) && !(y_intercept > e2_n2.y))
					|| (!(y_intercept > e2_n1.y) && !(y_intercept < e2_n2.y))) ) {
					
					return true;
			}
		}
	}
	else {
		slope_one = double(e1_n2.y - e1_n1.y)/(e1_n2.x - e1_n1.x);
		slope_two = double(e2_n2.y - e2_n1.y)/(e2_n2.x - e2_n1.x);

		x_intercept = (e1_n1.y - e2_n1.y - slope_one * e1_n1.x + slope_two * e2_n1.x) / (slope_two - slope_one);
		y_intercept = e1_n1.y + slope_one * ( x_intercept - e1_n1.x );

		if ( ((!(x_intercept < e1_n1.x) && !(x_intercept > e1_n2.x))
					|| (!(x_intercept > e1_n1.x) && !(x_intercept < e1_n2.x)))

			&& ((!(y_intercept < e1_n1.y) && !(y_intercept > e1_n2.y))
					|| (!(y_intercept > e1_n1.y) && !(y_intercept < e1_n2.y)))

			&& ((!(x_intercept < e2_n1.x) && !(x_intercept > e2_n2.x))
					|| (!(x_intercept > e2_n1.x) && !(x_intercept < e2_n2.x)))

			&& ((!(y_intercept < e2_n1.y) && !(y_intercept > e2_n2.y))
					|| (!(y_intercept > e2_n1.y) && !(y_intercept < e2_n2.y))) ) {

				return true;
		}
	}

	return false;
}

//bool FASTTSP::check_adjacent_edges_overlap(const node &e1_n1,
//										   const node &e1_n2,
//										   const node &e2_n1,
//										   const node &e2_n2) {
//
//	double slope_one = 0.0;
//	double slope_two = 0.0;
//
//	if (e1_n1.x == e1_n2.x) {
//
//		if (e2_n1.x == e2_n2.x) {
//
//			if (e1_n1.x == e2_n1.x) {
//
//				if ((!(e1_n1.x < e2_n1.x) && !(e1_n1.x > e2_n2.x))
//					|| (!(e1_n1.x > e2_n1.x) && !(e1_n1.x < e2_n2.x))
//					
//					|| (!(e1_n2.x < e2_n1.x) && !(e1_n2.x > e2_n2.x))
//					|| (!(e1_n2.x > e2_n1.x) && !(e1_n2.x < e2_n2.x))
//					
//					|| (!(e2_n1.x < e1_n1.x) && !(e2_n1.x > e1_n2.x))
//					|| (!(e2_n1.x > e1_n1.x) && !(e2_n1.x < e1_n2.x))
//					
//					|| (!(e2_n2.x < e1_n1.x) && !(e2_n2.x > e1_n2.x))
//					|| (!(e2_n2.x > e1_n1.x) && !(e2_n2.x < e1_n2.x))) {
//					
//					return true;
//				}
//			}
//		}
//	}
//	else if (e1_n1.y == e1_n2.y) {
//
//		if (e2_n1.y == e2_n2.y) {
//
//			if (e1_n1.y == e2_n1.y) {
//				
//				if ((!(e1_n1.x < e2_n1.x) && !(e1_n1.x > e2_n2.x))
//					|| (!(e1_n1.x > e2_n1.x) && !(e1_n1.x < e2_n2.x))
//					
//					|| (!(e1_n2.x < e2_n1.x) && !(e1_n2.x > e2_n2.x))
//					|| (!(e1_n2.x > e2_n1.x) && !(e1_n2.x < e2_n2.x))
//					
//					|| (!(e2_n1.x < e1_n1.x) && !(e2_n1.x > e1_n2.x))
//					|| (!(e2_n1.x > e1_n1.x) && !(e2_n1.x < e1_n2.x))
//					
//					|| (!(e2_n2.x < e1_n1.x) && !(e2_n2.x > e1_n2.x))
//					|| (!(e2_n2.x > e1_n1.x) && !(e2_n2.x < e1_n2.x))) {
//					
//					return true;
//				}
//			}
//		}
//	}
//	else {
//
//		slope_one = double(e1_n2.y - e1_n1.y)/(e1_n2.x - e1_n1.x);
//		slope_two = double(e2_n2.y - e2_n1.y)/(e2_n2.x - e2_n1.x);
//
//		if (slope_one == slope_two) {
//
//			if ((!(e1_n1.x < e2_n1.x) && !(e1_n1.x > e2_n2.x))
//				|| (!(e1_n1.x > e2_n1.x) && !(e1_n1.x < e2_n2.x))
//				
//				|| (!(e1_n2.x < e2_n1.x) && !(e1_n2.x > e2_n2.x))
//				|| (!(e1_n2.x > e2_n1.x) && !(e1_n2.x < e2_n2.x))
//				
//				|| (!(e2_n1.x < e1_n1.x) && !(e2_n1.x > e1_n2.x))
//				|| (!(e2_n1.x > e1_n1.x) && !(e2_n1.x < e1_n2.x))
//				
//				|| (!(e2_n2.x < e1_n1.x) && !(e2_n2.x > e1_n2.x))
//				|| (!(e2_n2.x > e1_n1.x) && !(e2_n2.x < e1_n2.x))) {
//				
//				return true;
//			}
//		}
//	}
//
//	return false;
//}


void FASTTSP::switch_crossed_run(vector <int> & route,
								 int first,
								 int last) {

//	if ((last - first) > (num_pokemon / 2)) {
//		for (int i = last; i > first; --i) {
//			
//		}
//	}
//	else {
//		for (int i = first; i < last; ++i) {
//			
//		}
//	}

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
