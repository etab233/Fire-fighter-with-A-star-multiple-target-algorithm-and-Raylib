#ifndef B68F8518_3068_4244_8AFC_508650759227
#define B68F8518_3068_4244_8AFC_508650759227

#include<iostream>
#include<vector>
#include<string>
#include"fireState.h"
using namespace std;

class FireProblem{
public:
    FireState initial_state;
    FireState goal_state;

    // باني إفتراضي يصنع حالة البداية
    FireProblem();
    FireState get_initialState();
    vector<pair<int,int>> get_actions(const FireState& state, position p);
};

#endif /* B68F8518_3068_4244_8AFC_508650759227 */
