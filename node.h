//
//  node.h
//  Pokéman
//
//  Created by John West on 4/3/15.
//  Copyright (c) 2015 John West. All rights reserved.
//

#ifndef Poke_man_node_h
#define Poke_man_node_h

struct node {
public:
	int x;
	int y;
};

struct nodeDistance {
public:
	double find_distance(const node &one, const node &two);
};

double nodeDistance::find_distance(const node &one, const node &two) {

	
}

#endif
