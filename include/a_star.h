#ifndef CF1D012D_DACA_4A75_A9DA_0511EAD9C696
#define CF1D012D_DACA_4A75_A9DA_0511EAD9C696

#include"fireState.h"
#include<iostream>
#include<vector>
using namespace std;

struct Cell{
    position location;
    int h,g,f;

    // Constructors
    Cell();
    Cell(position p);

    // comparison operator for priority queue
    bool operator <(const Cell& other)const ;
    bool operator ==(const Cell& other)const;
};

struct CompareGoals {
    bool operator()(const Cell& c1, const Cell& c2) const {
        return c1.f > c2.f; 
    }
};

bool is_valid_cell(int x, int y, int row, int column);
int heuristic(const Cell& p, const Cell& goal);
int multiple_heuristic(const vector<fire>& goal, const Cell& current);
int g1(const Cell& parent);
void a_star(FireState& state);

#endif /* CF1D012D_DACA_4A75_A9DA_0511EAD9C696 */