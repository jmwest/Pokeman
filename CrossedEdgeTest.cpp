//
//  CrossedEdgeTest.cpp
//  Pokéman
//
//  Created by John West on 4/9/15.
//  Copyright (c) 2015 John West. All rights reserved.
//

#include "CrossedEdgeTest.h"

#include "node.h"

#include <iostream>
#include <iomanip>

using namespace std;

bool check_edges_crossed(const node &e1_n1,
						 const node &e1_n2,
						 const node &e2_n1,
						 const node &e2_n2);

bool check_adjacent_edges_overlap(const node &e1_n1,
								  const node &e1_n2,
								  const node &e2_n1,
								  const node &e2_n2);

int main() {

	cout << "________________________________________\n\n";
	cout << "Begin checking edges_crossed function...\n" << endl;

	int total_correct = 0;
	int total = 0;
 
	node one, two, three, four;

	one.x = -2;
	one.y = -2;
	
	two.x = 3;
	two.y = 0;
	
	three.x = 0;
	three.y = 0;
	
	four.x = 1;
	four.y = -1;
	
	if (check_edges_crossed(one, two, three, four)) { ++total_correct; cout << '.'; } else { cout << 'x'; }

	if (check_edges_crossed(three, four, one, two)) { ++total_correct; cout << '.'; } else { cout << 'x'; }

	if (check_edges_crossed(two, one, four, three)) { ++total_correct; cout << '.'; } else { cout << 'x'; }

	if (check_edges_crossed(four, three, two, one)) { ++total_correct; cout << '.'; } else { cout << 'x'; }
	total += 4;

	one.x = 1;
	one.y = 2;

	two.x = 3;
	two.y = 2;

	three.x = -1;
	three.y = 2;

	four.x = 0;
	four.y = -2;

	if (!check_edges_crossed(one, two, three, four)) { ++total_correct; cout << '.'; } else { cout << 'x'; }

	if (!check_edges_crossed(three, four, one, two)) { ++total_correct; cout << '.'; } else { cout << 'x'; }

	if (!check_edges_crossed(two, one, four, three)) { ++total_correct; cout << '.'; } else { cout << 'x'; }

	if (!check_edges_crossed(four, three, two, one)) { ++total_correct; cout << '.'; } else { cout << 'x'; }
	total += 4;

	one.x = 1;
	one.y = 2;
	
	two.x = 3;
	two.y = 2;
	
	three.x = 2;
	three.y = 7;
	
	four.x = 0;
	four.y = -2;
	
	if (!check_edges_crossed(one, two, three, four)) { ++total_correct; cout << '.'; } else { cout << 'x'; }

	if (!check_edges_crossed(three, four, one, two)) { ++total_correct; cout << '.'; } else { cout << 'x'; }

	if (!check_edges_crossed(two, one, four, three)) { ++total_correct; cout << '.'; } else { cout << 'x'; }

	if (!check_edges_crossed(four, three, two, one)) { ++total_correct; cout << '.'; } else { cout << 'x'; }
	total += 4;

	one.x = 1;
	one.y = 2;
	
	two.x = 3;
	two.y = 2;
	
	three.x = 2;
	three.y = 3;
	
	four.x = 0;
	four.y = -2;
	
	if (check_edges_crossed(one, two, three, four)) { ++total_correct; cout << '.'; } else { cout << 'x'; }

	if (check_edges_crossed(three, four, one, two)) { ++total_correct; cout << '.'; } else { cout << 'x'; }

	if (check_edges_crossed(two, one, four, three)) { ++total_correct; cout << '.'; } else { cout << 'x'; }

	if (check_edges_crossed(four, three, two, one)) { ++total_correct; cout << '.'; } else { cout << 'x'; }
	total += 4;

	one.x = 3;
	one.y = 2;
	
	two.x = 3;
	two.y = 0;
	
	three.x = 5;
	three.y = 4;
	
	four.x = 0;
	four.y = 4;
	
	if (!check_edges_crossed(one, two, three, four)) { ++total_correct; cout << '.'; } else { cout << 'x'; }

	if (!check_edges_crossed(three, four, one, two)) { ++total_correct; cout << '.'; } else { cout << 'x'; }

	if (!check_edges_crossed(two, one, four, three)) { ++total_correct; cout << '.'; } else { cout << 'x'; }

	if (!check_edges_crossed(four, three, two, one)) { ++total_correct; cout << '.'; } else { cout << 'x'; }
	total += 4;

	one.x = 3;
	one.y = 2;
	
	two.x = 3;
	two.y = 0;
	
	three.x = 5;
	three.y = 1;
	
	four.x = 0;
	four.y = 1;
	
	if (check_edges_crossed(one, two, three, four)) { ++total_correct; cout << '.'; } else { cout << 'x'; }

	if (check_edges_crossed(three, four, one, two)) { ++total_correct; cout << '.'; } else { cout << 'x'; }

	if (check_edges_crossed(two, one, four, three)) { ++total_correct; cout << '.'; } else { cout << 'x'; }

	if (check_edges_crossed(four, three, two, one)) { ++total_correct; cout << '.'; } else { cout << 'x'; }
	total += 4;

	one.x = 3;
	one.y = 2;
	
	two.x = 3;
	two.y = 0;
	
	three.x = 3;
	three.y = 1;
	
	four.x = 0;
	four.y = 4;
	
	if (check_edges_crossed(one, two, three, four)) { ++total_correct; cout << '.'; } else { cout << 'x'; }

	if (check_edges_crossed(three, four, one, two)) { ++total_correct; cout << '.'; } else { cout << 'x'; }

	if (check_edges_crossed(two, one, four, three)) { ++total_correct; cout << '.'; } else { cout << 'x'; }

	if (check_edges_crossed(four, three, two, one)) { ++total_correct; cout << '.'; } else { cout << 'x'; }
	total += 4;

	one.x = -3;
	one.y = -2;
	
	two.x = 3;
	two.y = 2;
	
	three.x = -5;
	three.y = 4;
	
	four.x = 0;
	four.y = -4;
	
	if (check_edges_crossed(one, two, three, four)) { ++total_correct; cout << '.'; } else { cout << 'x'; }

	if (check_edges_crossed(three, four, one, two)) { ++total_correct; cout << '.'; } else { cout << 'x'; }

	if (check_edges_crossed(two, one, four, three)) { ++total_correct; cout << '.'; } else { cout << 'x'; }

	if (check_edges_crossed(four, three, two, one)) { ++total_correct; cout << '.'; } else { cout << 'x'; }
	total += 4;

	one.x = 3;
	one.y = 2;
	
	two.x = 5;
	two.y = 0;
	
	three.x = 4;
	three.y = 1;
	
	four.x = 0;
	four.y = 4;
	
	if (check_edges_crossed(one, two, three, four)) { ++total_correct; cout << '.'; } else { cout << 'x'; }
	
	if (check_edges_crossed(three, four, one, two)) { ++total_correct; cout << '.'; } else { cout << 'x'; }
	
	if (check_edges_crossed(two, one, four, three)) { ++total_correct; cout << '.'; } else { cout << 'x'; }
	
	if (check_edges_crossed(four, three, two, one)) { ++total_correct; cout << '.'; } else { cout << 'x'; }
	total += 4;

	one.x = 3;
	one.y = 2;
	
	two.x = 5;
	two.y = 0;
	
	three.x = 3;
	three.y = 2;
	
	four.x = 0;
	four.y = 4;
	
	if (!check_adjacent_edges_overlap(one, two, three, four)) { ++total_correct; cout << '.'; } else { cout << 'x'; }

	if (!check_adjacent_edges_overlap(three, four, one, two)) { ++total_correct; cout << '.'; } else { cout << 'x'; }

	if (!check_adjacent_edges_overlap(two, one, four, three)) { ++total_correct; cout << '.'; } else { cout << 'x'; }

	if (!check_adjacent_edges_overlap(four, three, two, one)) { ++total_correct; cout << '.'; } else { cout << 'x'; }
	total += 4;
	cout << endl;

	one.x = 3;
	one.y = 2;
	
	two.x = 5;
	two.y = 0;
	
	three.x = 4;
	three.y = 1;
	
	four.x = 3;
	four.y = 2;
	
	if (check_adjacent_edges_overlap(one, two, three, four)) { ++total_correct; cout << '.'; } else { cout << 'x'; }

	if (check_adjacent_edges_overlap(three, four, one, two)) { ++total_correct; cout << '.'; } else { cout << 'x'; }

	if (check_adjacent_edges_overlap(two, one, four, three)) { ++total_correct; cout << '.'; } else { cout << 'x'; }

	if (check_adjacent_edges_overlap(four, three, two, one)) { ++total_correct; cout << '.'; } else { cout << 'x'; }
	total += 4;

	one.x = 3;
	one.y = 2;
	
	two.x = 5;
	two.y = 2;
	
	three.x = 5;
	three.y = 2;
	
	four.x = -1;
	four.y = 2;
	
	if (check_adjacent_edges_overlap(one, two, three, four)) { ++total_correct; cout << '.'; } else { cout << 'x'; }
	
	if (check_adjacent_edges_overlap(three, four, one, two)) { ++total_correct; cout << '.'; } else { cout << 'x'; }
	
	if (check_adjacent_edges_overlap(two, one, four, three)) { ++total_correct; cout << '.'; } else { cout << 'x'; }
	
	if (check_adjacent_edges_overlap(four, three, two, one)) { ++total_correct; cout << '.'; } else { cout << 'x'; }
	total += 4;

	one.x = 3;
	one.y = 2;
	
	two.x = 3;
	two.y = 0;
	
	three.x = 3;
	three.y = 5;
	
	four.x = 3;
	four.y = 2;
	
	if (!check_adjacent_edges_overlap(one, two, three, four)) { ++total_correct; cout << '.'; } else { cout << 'x'; }
	
	if (!check_adjacent_edges_overlap(three, four, one, two)) { ++total_correct; cout << '.'; } else { cout << 'x'; }
	
	if (!check_adjacent_edges_overlap(two, one, four, three)) { ++total_correct; cout << '.'; } else { cout << 'x'; }
	
	if (!check_adjacent_edges_overlap(four, three, two, one)) { ++total_correct; cout << '.'; } else { cout << 'x'; }
	total += 4;

	one.x = 3;
	one.y = 2;
	
	two.x = 5;
	two.y = 0;
	
	three.x = 5;
	three.y = 0;
	
	four.x = 3;
	four.y = 2;
	
	if (!check_adjacent_edges_overlap(one, two, three, four)) { ++total_correct; cout << '.'; } else { cout << 'x'; }
	
	if (!check_adjacent_edges_overlap(three, four, one, two)) { ++total_correct; cout << '.'; } else { cout << 'x'; }
	
	if (!check_adjacent_edges_overlap(two, one, four, three)) { ++total_correct; cout << '.'; } else { cout << 'x'; }
	
	if (!check_adjacent_edges_overlap(four, three, two, one)) { ++total_correct; cout << '.'; } else { cout << 'x'; }
	total += 4;

	cout << "\n\nTesting done. Results:\n\n";
	cout << "\tNumber Correct: " << total_correct << endl;
	cout << "\tTotal Tested: " << total << endl;

	cout << setprecision(0);
	cout << fixed;

	cout << "\n\tPercent Correct: " << (double(total_correct) / total) * 100 << '%' << endl;
	cout << "________________________________________\n\n";

	cout << "Begin checking nodeBeginnerDistance...\n\n";

	nodeBeginnerDistance n_d = nodeBeginnerDistance();
	total = 0;
	total_correct = 0;

	one.x = -1;
	one.y = -3;

	two.x = -2;
	two.y = 0;

	if (n_d(one,two) != -1) { ++total_correct; cout << '.'; } else { cout << 'x'; }

	if (n_d(two,one) != -1) { ++total_correct; cout << '.'; } else { cout << 'x'; }
	total += 2;

	one.x = 0;
	one.y = -3;
	
	two.x = 2;
	two.y = 0;
	
	if (n_d(one,two) != -1) { ++total_correct; cout << '.'; } else { cout << 'x'; }
	
	if (n_d(two,one) != -1) { ++total_correct; cout << '.'; } else { cout << 'x'; }
	total += 2;

	one.x = -1;
	one.y = -3;
	
	two.x = 2;
	two.y = 1;
	
	if (n_d(one,two) == -1) { ++total_correct; cout << '.'; } else { cout << 'x'; }
	
	if (n_d(two,one) == -1) { ++total_correct; cout << '.'; } else { cout << 'x'; }
	total += 2;

	one.x = -3;
	one.y = -3;
	
	two.x = 1;
	two.y = -3;
	
	if (n_d(one,two) == -1) { ++total_correct; cout << '.'; } else { cout << 'x'; }
	
	if (n_d(two,one) == -1) { ++total_correct; cout << '.'; } else { cout << 'x'; }
	total += 2;

	one.x = -1;
	one.y = -3;
	
	two.x = 0;
	two.y = -4;
	
	if (n_d(one,two) != -1) { ++total_correct; cout << '.'; } else { cout << 'x'; }
	
	if (n_d(two,one) != -1) { ++total_correct; cout << '.'; } else { cout << 'x'; }
	total += 2;

	one.x = -1;
	one.y = -3;
	
	two.x = 0;
	two.y = 0;
	
	if (n_d(one,two) != -1) { ++total_correct; cout << '.'; } else { cout << 'x'; }
	
	if (n_d(two,one) != -1) { ++total_correct; cout << '.'; } else { cout << 'x'; }
	total += 2;

	one.x = 1;
	one.y = 3;
	
	two.x = 0;
	two.y = 0;
	
	if (n_d(one,two) != -1) { ++total_correct; cout << '.'; } else { cout << 'x'; }
	
	if (n_d(two,one) != -1) { ++total_correct; cout << '.'; } else { cout << 'x'; }
	total += 2;

	one.x = -1;
	one.y = 0;
	
	two.x = 0;
	two.y = 4;
	
	if (n_d(one,two) != -1) { ++total_correct; cout << '.'; } else { cout << 'x'; }
	
	if (n_d(two,one) != -1) { ++total_correct; cout << '.'; } else { cout << 'x'; }
	total += 2;

	one.x = 0;
	one.y = -3;
	
	two.x = 4;
	two.y = -4;
	
	if (n_d(one,two) != -1) { ++total_correct; cout << '.'; } else { cout << 'x'; }
	
	if (n_d(two,one) != -1) { ++total_correct; cout << '.'; } else { cout << 'x'; }
	total += 2;

	one.x = -5;
	one.y = -1;
	
	two.x = 4;
	two.y = 0;
	
	if (n_d(one,two) == -1) { ++total_correct; cout << '.'; } else { cout << 'x'; }
	
	if (n_d(two,one) == -1) { ++total_correct; cout << '.'; } else { cout << 'x'; }
	total += 2;

	one.x = -5;
	one.y = -1;
	
	two.x = -5;
	two.y = -1;
	
	if (n_d(one,two) == 0) { ++total_correct; cout << '.'; } else { cout << 'x'; }
	
	if (n_d(two,one) == 0) { ++total_correct; cout << '.'; } else { cout << 'x'; }
	total += 2;

	cout << "\n\nTesting done. Results:\n\n";
	cout << "\tNumber Correct: " << total_correct << endl;
	cout << "\tTotal Tested: " << total << endl;

	cout << "\n\tPercent Correct: " << (double(total_correct) / total) * 100 << '%' << endl;
	cout << "________________________________________\n\n";

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
			//			if (((!(y_intercept < e2_n1.y) && !(y_intercept > e2_n2.y))
			//				|| (!(y_intercept > e2_n1.y) && !(y_intercept < e2_n2.y)))
			//				&& ((!(e2_n1.x < e1_n1.x) && !(e2_n2.x > e1_n1.x))
			//					|| (!(e2_n1.x > e1_n1.x) && !(e2_n2.x < e1_n1.x)))){
			//				return true;
			//			}
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
			//			if (((!(y_intercept < e1_n1.y) && !(y_intercept > e1_n2.y))
			//				 || (!(y_intercept > e1_n1.y) && !(y_intercept < e1_n2.y)))
			//				&& ((!(e1_n1.x < e2_n1.x) && !(e1_n2.x > e2_n1.x))
			//					|| (!(e1_n1.x > e2_n1.x) && !(e1_n2.x < e2_n1.x)))){
			//					return true;
			//			}
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
			//			if (((!(x_intercept < e2_n1.x) && !(x_intercept > e2_n2.x))
			//				 || (!(x_intercept > e2_n1.x) && !(x_intercept < e2_n2.x)))
			//				&& ((!(e2_n1.y < e1_n1.y) && !(e2_n2.y > e1_n1.y))
			//					|| (!(e2_n1.y > e1_n1.y) && !(e2_n2.y < e1_n1.y)))){
			//					return true;
			//			}
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
			//			if (((!(x_intercept < e1_n1.x) && !(x_intercept > e1_n2.x))
			//				 || (!(x_intercept > e1_n1.x) && !(x_intercept < e1_n2.x)))
			//				&& ((!(e1_n1.y < e2_n1.y) && !(e1_n2.y > e2_n1.y))
			//					|| (!(e1_n1.y > e2_n1.y) && !(e1_n2.y < e2_n1.y)))){
			//					return true;
			//			}
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

bool check_adjacent_edges_overlap(const node &e1_n1,
								  const node &e1_n2,
								  const node &e2_n1,
								  const node &e2_n2) {

	double slope_one = 0.0;
	double slope_two = 0.0;
	
	if (e1_n1.x == e1_n2.x) {
		
		if (e2_n1.x == e2_n2.x) {
			
			if (e1_n1.x == e2_n1.x) {
				
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
	}
	//	else if (e2_n1.x == e2_n2.x) {
	//
	//		if (e1_n1.x == e1_n2.x) {
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
	//	else if (e2_n1.y == e2_n2.y) {
	//
	//		if (e1_n1.y == e1_n2.y) {
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
	else {
		
		slope_one = double(e1_n2.y - e1_n1.y)/(e1_n2.x - e1_n1.x);
		slope_two = double(e2_n2.y - e2_n1.y)/(e2_n2.x - e2_n1.x);
		
		if (slope_one == slope_two) {
			
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
	
	return false;
}

