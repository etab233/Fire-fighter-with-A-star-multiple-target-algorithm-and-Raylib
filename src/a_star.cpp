//-------------find the shortest path to reach the goal(burning cells)--------------

#include<iostream>
#include<math.h>
#include<algorithm>
#include<climits>
#include<queue>
#include<vector>
#include<stdexcept>
#include"fire_problem.h"
#include"fireState.h"
#include"actions.h"
#include"a_star.h"
#include "visualizer.h"

using namespace std;

Cell::Cell(){}

Cell::Cell(position p){
    location.x = p.x;
    location.y = p.y;
    f = 0;
    g = 0;
    h = 0;
}

bool Cell::operator<(const Cell& other)const {
    return this->f > other.f;
}

bool Cell::operator==(const Cell& other)const {
    return location.x == other.location.x && location.y == other.location.y;
}

int heuristic(const Cell& c, const Cell& goal){
    int x1 = c.location.x, y1 = c.location.y;
    int x2 = goal.location.x, y2 = goal.location.y;
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

int multiple_heuristic(const vector<fire>& goals, const Cell& current){
    if(goals.empty()) return 0;
    int min = INT_MAX;
    for(const auto& goal : goals){
        Cell i_goal;
        i_goal.location=goal.location;
        int h=heuristic(current, i_goal);
        if(h<min) min=h;
    }
    return min;
}

int g1(const Cell& parent){
    return parent.g + 1;
}

bool is_valid_cell(int x, int y, int row, int column){
    return ((x >= 0 && x < row) && (y >= 0 && y < column));
}

// -----------------------------------
// A* to find shortest path algorithm 
// -----------------------------------

void a_star(FireState& state){ 
    if(state.fires.empty()) {
        cout << "All fires have been extinguished!" << endl;
        return;
    }

    if(state.is_success()){
        cout<<"=== MIN ==="<<endl;
        return ;
    }

    cout << " Starting A* search from (" << state.vehicle_location.x 
         << ", " << state.vehicle_location.y << ") to extinguish " 
         << state.fires.size() << " fires" << endl;

    Cell initial;
    vector<fire> goals = state.fires;
    initial.location = state.vehicle_location; 
    initial.g = 0;
    initial.h = multiple_heuristic(goals, initial);
    initial.f = initial.g + initial.h;

    vector<vector<bool>> visited(state.row, vector<bool>(state.column, false));
    vector<vector<int>> gScore(state.row, vector<int>(state.column, INT_MAX));
    vector<vector<Cell>> parent(state.row, vector<Cell>(state.column));

    gScore[initial.location.x][initial.location.y] = initial.g;

    priority_queue<Cell,vector<Cell>, CompareGoals> frontier;
    frontier.push(initial);

    while(!frontier.empty()){
        Cell current = frontier.top();
        frontier.pop();

        if(visited[current.location.x][current.location.y]) continue;
        visited[current.location.x][current.location.y] = true;

        // البحث عن حريق في الموقع الحالي
        auto fire_it = state.fires.begin();
        while(fire_it != state.fires.end() && state.resources >0){
            if(current.location.x == fire_it->location.x && current.location.y == fire_it->location.y){
                cout << " Found fire at (" << current.location.x << ", " << current.location.y << ")" << endl;
                
                // إطفاء الحريق
                Action actions;
                actions.extinguish_cell(state, current.location, *fire_it);

                cout << "______ After Extinguishing _______" << endl;
                drawState(state);

                cout << "Fire extinguished! Remaining fires: " << state.fires.size() << endl;
                cout << "Remaining resources: " << state.resources << endl;

                // إذا بقي حرائق، نستمر من الموقع الحالي
                if(!state.fires.empty() && state.resources > 0){ 
                    cout << " Continuing to next fire from current position..." << endl;
                    a_star(state); // نمرر الحالة المحدثة
                } else if (state.fires.empty()) {
                    cout << " All fires have been extinguished!" << endl;
                } else {
                    cout << " Out of resources! Cannot extinguish remaining fires." << endl;
                    return;
                }
                
                break;
            } else {
                ++fire_it;
            }
        }

        // استكشاف الجوار
        vector<pair<int, int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};
        
        for(const auto& dir : directions){
            int newX = current.location.x + dir.first;
            int newY = current.location.y + dir.second;

            if(!is_valid_cell(newX, newY, state.row, state.column) || visited[newX][newY]) {
                continue;
            }

            int tentative_g = current.g + 1;
            
            if(tentative_g < gScore[newX][newY]) {
                gScore[newX][newY] = tentative_g;

                Cell neighbor_cell;
                neighbor_cell.location = {newX, newY};
                neighbor_cell.g = tentative_g;
                neighbor_cell.h = multiple_heuristic(state.fires, neighbor_cell);
                neighbor_cell.f = neighbor_cell.g + neighbor_cell.h;

                parent[newX][newY] = current;
                frontier.push(neighbor_cell);
            }
        }
    }
}