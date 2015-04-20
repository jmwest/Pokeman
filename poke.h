//
//  poke.h
//  Pokéman
//
//  Created by John West on 4/2/15.
//  Copyright (c) 2015 John West. All rights reserved.
//

#ifndef __Poke_man__poke__
#define __Poke_man__poke__

#include <stdio.h>

enum MODE {NONE, MST_MODE, OPTTSP_MODE, FASTTSP_MODE};

void parse_command_line_input(const int & argc, char* argv[], MODE &mode);

#endif /* defined(__Poke_man__poke__) */
