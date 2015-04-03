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
#include <vector>
#include <string>

#include "node.h"

using namespace std;

class MST {
private:
	void get_pokemon_locations(vector <node> & nodes, const int &num_pokemon);

public:
	MST();

	void run_MST();
};

MST::MST() {}

void MST::run_MST() {

	int num_pokemon = 0;

	cin >> num_pokemon;

	vector <node> nodes (num_pokemon);

	

	return;
}

void MST::get_pokemon_locations(vector <node> &nodes, const int & num_pokemon) {

	string input;

	getline(cin, input);

	char c = ' ';
	for (int i = 0; i < num_pokemon; ++i) {
		if (getline(cin, input)) {
			size_t pos = input.find(c);
			nodes.at(i).x = stoi(input.substr(0, pos));
			nodes.at(i).y = stoi(input.substr(pos + 1));
		}
		else {
			cerr << "\ngetline failed" << endl;
		}
	}

	return;
}

#endif
