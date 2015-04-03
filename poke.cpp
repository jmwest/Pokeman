//
//  poke.cpp
//  Pokéman
//
//  Created by John West on 4/2/15.
//  Copyright (c) 2015 John West. All rights reserved.
//

#include "poke.h"

#include <stdio.h>
#include <iostream>
#include <getopt.h>

#include "MST.h"
#include "OPTTSP.h"
#include "FASTTSP.h"

using namespace std;

int main(int argc, char* argv[]) {

	MODE mode = NONE;

	parse_command_line_input(argc, argv, mode);

	switch (mode) {
		case MST_MODE: {
			MST mst;
			mst.run_MST();
			break;
		}
		case OPTTSP_MODE: {
			OPTTSP opt_tsp;
			opt_tsp.run_OPTTSP();
			break;
		}
		case FASTTSP_MODE: {
			FASTTSP fast_tsp;
			fast_tsp.run_FASTTSP();
			break;
		}
		default:
			break;
	}

	return 0;
}

void parse_command_line_input(const int & argc, char* argv[], MODE &mode) {
	static struct option longopts[] = {
		{"mode",			required_argument,		NULL, 'm'},
		{"help",			no_argument,			NULL, 'h'},
		{NULL,				0,						NULL, 0},
	};
	int idx = 0;
	char c;

	bool called_mode = false;

	// Use getopt to parse through command line input
	while ((c = getopt_long(argc, argv, "h", longopts, &idx)) != -1) {
		switch (c) {
			case 'm':
				if (strcmp(optarg, "MST")) {
					mode = MST_MODE;
				}
				else if (strcmp(optarg, "OPTTSP")) {
					mode = OPTTSP_MODE;
				}
				else if (strcmp(optarg, "FASTTSP")) {
					mode = FASTTSP_MODE;
				}

			case 'h':
				cout << "Helpful help message" << endl;

				exit(0);

			default:
				break;
		} // switch
	} // while

	if (!called_mode) {
		cerr << "A mode was not selected for this Poké. exit(1)" << endl;

		exit(1);
	}

	if (mode == NONE) {
		cerr << "A mode was not input for this Poké. exit(1)" << endl;
		
		exit(1);
	}

	return;
} // parse_command_line_input
