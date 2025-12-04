#include "fireState.h"
#include "a_star.h"

FireState :: FireState(){
    row=10; column=10; resources=100;
    vehicle_location={0,0};

    if(row <= 0 || column <= 0) {
        throw invalid_argument("Invalid grid dimensions in constructor");
    }
    // initialize map with .
    map.resize(row);
    for(int i = 0; i < row; i++) {
        map[i].resize(column, ".");
    }
}

void FireState :: printState(){
    // التحقق من صحة الأبعاد قبل الطباعة
    if(row <= 0 || column <= 0) {
        cerr << "Error: Invalid grid dimensions in printState" << endl;
        return;
    }

    cout << "Map (" << row << "x" << column << "):" << endl;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
    cout << "\nResources: " << resources << endl;
    cout << "Buildings: ";
    for (const auto& b : buildings) {
        // التحقق من أن موقع المبنى ضمن الحدود
        if(b.location.x >= 0 && b.location.x < row && b.location.y >= 0 && b.location.y < column) {
            cout << "(" << b.location.x << "," << b.location.y << ") ";
        }
    }

    cout << "\nFires: ";
    for (const auto& fire : fires) {
        if(fire.location.x >= 0 && fire.location.x < row && fire.location.y >= 0 && fire.location.y < column) {
            cout << "(" << fire.location.x << "," << fire.location.y << ") ";
        }
    }
    cout << endl;
}

bool FireState::is_goal(){ // الهدف نطفي كل النار
    return fires.empty();
}

bool FireState :: operator ==(const FireState& other){
    if((this->vehicle_location.x == other. vehicle_location.x) 
        && (this->vehicle_location.y == other.vehicle_location.y)
        && (this->resources ==other. resources)
    ) return true;
    return false;
}

bool FireState:: is_success(){
    // يفوز الللاعب إذا :
    // 1. كل النار انطفأت أيّ حقق الهدف 
    // 2. مجموع أهمية المباني المحروقة لا تتجاوز الخمسة
    if (is_goal()){
        int imp_sum=0;
        for(int i=0; i<(int)burned_buildings.size(); i++){
            imp_sum += burned_buildings[i].importance;
        }
        return imp_sum<=5;
    }
    return false;
}

vector<pair<int, int>> FireState :: get_actions(const FireState& state, position p){
    // possible movement directions: up, right, down ,left, diagonal
    const int directionX[]={-1,0,1,0,1,-1,1,-1};
    const int directionY[]={0,1,0,-1,1,1,-1,-1};
    vector<pair<int,int>> result;

    // التحقق من أن نقطة البداية صالحة
    if(!is_valid_cell(p.x, p.y, state.row, state.column)) {
        cerr << "Warning: Invalid starting position in get_actions: (" << p.x << "," << p.y << ")" << endl;
        return result;
    }
    for(int i=0; i<8; i++){
        int newX= p.x + directionX[i];
        int newY= p.y + directionY[i];
        if(is_valid_cell(newX, newY, state.row, state.column) && state.map[newX][newY] != "H")
            result.push_back(make_pair(newX, newY));
    }
    return result;
}