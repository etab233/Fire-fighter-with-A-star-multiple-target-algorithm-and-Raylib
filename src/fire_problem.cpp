#include "fire_problem.h"
#include "fireState.h"
#include "a_star.h"
#include <vector>

FireProblem :: FireProblem(){
    initial_state.row = 10;
    initial_state.column = 10;
    initial_state.resources = 50;
    initial_state.vehicle_location = position(0, 0);
    initial_state.map.resize(10, vector<string>(10, "."));
    
    // إضافة مباني
    building b1, b2, b3;
    b1.location = position(0, 4);
    b2.location = position(1, 4);
    b3.location = position(2, 4);
    initial_state.buildings = {b1, b2, b3};
    
    // إضافة حريق
    fire f1;
    f1.location = position(0, 0);
    initial_state.fires = {f1};
}

FireState FireProblem :: get_initialState(){
    return this->initial_state;
} 
