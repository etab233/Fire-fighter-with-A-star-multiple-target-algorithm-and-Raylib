#include <iostream>
#include "fire_problem.h"
#include "fireState.h"
#include "fire_spread.h"
#include "a_star.h"
#include "actions.h"
#include "visualizer.h"

using namespace std;

void validate_state(const FireState& state, const string& context) {
    cout << "=== Validating State (" << context << ") ===" << endl;
    cout << "Grid: " << state.row << "x" << state.column << endl;
    cout << "Vehicle: (" << state.vehicle_location.x << "," << state.vehicle_location.y << ")" << endl;
    cout << "Fires count: " << state.fires.size() << endl;
    cout << "Resources: " << state.resources << endl;
    
    if(state.row <= 0 || state.column <= 0) {
        throw invalid_argument("Invalid grid dimensions: " + to_string(state.row) + "x" + to_string(state.column));
    }
    
    if(state.vehicle_location.x < 0 || state.vehicle_location.x >= state.row ||
       state.vehicle_location.y < 0 || state.vehicle_location.y >= state.column) {
        throw invalid_argument("Vehicle outside grid: (" + 
                              to_string(state.vehicle_location.x) + "," + 
                              to_string(state.vehicle_location.y) + ")");
    }
    cout << "State validation passed!" << endl;
}

int main()
{
    try {
        FireState f;
        
        f.map = {
            {".", ".", ".", ".", "H"},
            {"F", ".", ".", ".", "H"},
            {".", ".", ".", ".", "H"},
            {".", ".", ".", ".", "F"}
        };
        f.row = 4;
        f.column = 5;
        f.resources = 50;
        f.vehicle_location = position(0, 0);
        
        building b1, b2, b3;
        b1.location = position(0, 4);
        b2.location = position(1, 4);
        b3.location = position(2, 4);
        b1.importance = 1;
        b2.importance = 2;
        b3.importance = 3;
        b1.is_burned = false;
        b2.is_burned = false;
        b3.is_burned = false;
        b1.is_on_fire = false;
        b2.is_on_fire = false;
        b3.is_on_fire = false;
        f.buildings = {b1, b2, b3};

        fire fire1;
        fire1.location = position(1, 0);
        fire1.intensity = 2;
        fire1.water_amount = 10;

        fire fire2;
        fire2.location = position(3,4);
        fire2.intensity = 5;
        fire2.water_amount = 10;

        f.fires = {fire1, fire2};

        validate_state(f, "Initial State");
        cout << "=== Initial State ===" << endl;
        drawState(f);

        FireProblem problem;
        
        cout << "\n=== Fire Spread Process ===" << endl;
        FireState spread_state = fire_spread(f);
        validate_state(spread_state, "After Fire Spread");
        drawState(spread_state);
        
        cout << "\n=== Path Search ===" << endl;
        validate_state(spread_state, "Before A*");
        a_star(spread_state);

    } catch (const exception& e) {
        cerr << "Error in main: " << e.what() << endl;
        return 1;
    }

    return 0;
}