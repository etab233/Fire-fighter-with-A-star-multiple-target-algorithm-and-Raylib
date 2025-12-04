#ifndef A013E1DB_7896_43A2_9B08_06E3784DE788
#define A013E1DB_7896_43A2_9B08_06E3784DE788

#ifndef FIRE_SPREAD_H
#define FIRE_SPREAD_H

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include "fireState.h"
#include "fire_problem.h"

bool is_end(FireState state, position p);
bool is_valid(FireState state, position p);
fire expand(fire f);
bool is_reached(std::queue<fire> q, position p);
FireState fire_spread(FireState state);
void display_map(FireState state);
bool has_fire_at_position(const vector<fire>& fires, position pos);
bool has_building_at_position(const vector<building>& buildings, position pos);

#endif

#endif /* A013E1DB_7896_43A2_9B08_06E3784DE788 */
