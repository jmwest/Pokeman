//
//  CrossedEdgeTest.cpp
//  Pokéman
//
//  Created by John West on 4/9/15.
//  Copyright (c) 2015 John West. All rights reserved.
//

#include "CrossedEdgeTest.h"

#include <iostream>

using namespace std;

struct node {
	int x;
	int y;
};

bool check_edges_crossed(const node &e1_n1,
						 const node &e1_n2,
						 const node &e2_n1,
						 const node &e2_n2);

int main() {

	node one, two, three, four;

	one.x = 5;
	one.y = 6;

	two.x = 2;
	two.y = 6;

	three.x = 0;
	three.y = 4;

	four.x = 4;
	four.y = 5;

	if (check_edges_crossed(one, two, three, four)) {
		cout << "They cross1!" << endl;
	}
	else {
		cout << "No crossing1 here :(" << endl;
	}

	if (check_edges_crossed(three, four, one, two)) {
		cout << "They cross2!" << endl;
	}
	else {
		cout << "No crossing2 here :(" << endl;
	}

	if (check_edges_crossed(two, one, four, three)) {
		cout << "They cross3!" << endl;
	}
	else {
		cout << "No crossing3 here :(" << endl;
	}

	if (check_edges_crossed(four, three, two, one)) {
		cout << "They cross4!" << endl;
	}
	else {
		cout << "No crossing4 here :(" << endl;
	}

	return 0;
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

