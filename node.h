//
//  node.h
//  Pokéman
//
//  Created by John West on 4/3/15.
//  Copyright (c) 2015 John West. All rights reserved.
//

#ifndef Poke_man_node_h
#define Poke_man_node_h

#include <cmath>
#include <algorithm>

struct node {
public:
	double x;
	double y;
};

struct nodeEdge {
public:
	int previous;
	double distance;

	nodeEdge() {}

	nodeEdge(int prev, double dist)
	: previous(prev), distance(dist) {}
};

struct nodeEdgeComparator {
public:
	bool operator() (const nodeEdge &one, const nodeEdge &two) {
		return one.distance < two.distance;
	}
};

struct nodeBeginnerDistance {
public:
	double operator() (const node &one, const node &two);
};

double nodeBeginnerDistance::operator() (const node &one, const node &two) {

	if (((one.x < 0) && (one.y < 0)) && ((two.x > 0) || (two.y > 0))) {
		return -1;
	}
	else if (((two.x < 0) && (two.y < 0)) && ((one.x > 0) || (one.y > 0))){
		return -1;
	}
	else {
		double x_dist = one.x - two.x;
		double y_dist = one.y - two.y;
		double dist = (x_dist * x_dist) + (y_dist * y_dist);

		return sqrt(dist);
	}
}

struct nodeFlyDistance {
public:
	double operator() (const node &one, const node &two);
};

double nodeFlyDistance::operator() (const node &one, const node &two) {

	double x_dist = one.x - two.x;
	double y_dist = one.y - two.y;
	double dist = (x_dist * x_dist) + (y_dist * y_dist);

	return sqrt(dist);
}

#endif
