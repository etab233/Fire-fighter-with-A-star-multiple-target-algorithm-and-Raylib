#include "fire_spread.h"
#include "fireState.h"

bool is_end(FireState state, position p){
    return ( (p.x == state.row) && (p.y == state.column) );
}

bool is_valid(FireState state, position p){
    return ((p.x<state.row) && (p.y<state.column));
}

fire expand(fire f){
    fire child;
    child.intensity= f.intensity-1;
    child.location={f.location.x+1, f.location.y+1};
    child.water_amount=f.water_amount-10;
    return child;
}

bool is_reached(queue<fire> q, position p){
    int i=0;
    while(!q.empty()){
        if((q.front().location.x == p.x) && (q.front().location.y == p.y)) return true;
        i++;
        q.pop();
    }
    return false;
}

void display_map(FireState state){
    auto map= state.map;
    cout<<endl;
    for(int i=0; i<state.row; i++){
        for(int j=0; j<state.column; j++){
            cout<<map[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<"_____________________"<<endl;
}

// دالة مساعدة للتحقق من وجود حريق في موقع معين
bool has_fire_at_position(const vector<fire>& fires, position pos) {
    for (const auto& f : fires) {
        if (f.location.x == pos.x && f.location.y == pos.y) {
            return true;
        }
    }
    return false;
}

// دالة مساعدة للتحقق من وجود مبنى في موقع معين
bool has_building_at_position(const vector<building>& buildings, position pos) {
    for (const auto& b : buildings) {
        if (b.location.x == pos.x && b.location.y == pos.y) {
            return true;
        }
    }
    return false;
}

FireState fire_spread(FireState state) {
    cout << "Starting fire spread simulation..." << endl;
    
    // إذا لم يكن هناك حرائق، لا حاجة للانتشار
    if (state.fires.empty()) {
        cout << "No fires to spread from!" << endl;
        return state;
    }
    
    // إنشاء قائمة بالحرائق الجديدة
    vector<fire> new_fires = state.fires;
    
    // انتشار النار من كل حريق موجود
    for (const auto& current_fire : state.fires) {
        int x = current_fire.location.x;
        int y = current_fire.location.y;
        
        // الانتشار في الاتجاهات الأربعة
        vector<position> directions = {
            position(-1, 0), // أعلى
            position(1, 0),  // أسفل  
            position(0, -1), // يسار
            position(0, 1)   // يمين
        };
        
        for (const auto& dir : directions) {
            int newX = x + dir.x;
            int newY = y + dir.y;
            
            // التحقق من أن الخلية ضمن الحدود
            if (newX >= 0 && newX < state.row && newY >= 0 && newY < state.column) {
                position new_pos(newX, newY);
                
                // التحقق من أن الخلية ليست فيها نار بالفعل
                if (!has_fire_at_position(new_fires, new_pos) && !has_building_at_position(state.buildings, new_pos)) {
                    
                    // إنشاء حريق جديد
                    fire new_fire;
                    new_fire.location = new_pos;
                    new_fire.intensity = 1; // شدة ابتدائية
                    new_fire.water_amount = 10; // كمية مياه مطلوبة للإطفاء
                    
                    // إضافة الحريق الجديد إلى القائمة
                    new_fires.push_back(new_fire);
                    
                    // تحديث الخريطة
                    state.map[newX][newY] = "F";
                    
                    cout << "Fire spread to (" << newX << ", " << newY << ")" << endl;
                }

                // التحقق من أن الخلية مبنى
                if (has_building_at_position(state.buildings, new_pos)) {
                    // إنشاء حريق جديد
                    fire new_fire;
                    new_fire.location = new_pos;
                    new_fire.intensity = 1; // شدة ابتدائية
                    new_fire.water_amount = 10; // كمية مياه مطلوبة للإطفاء
                    
                    // إضافة الحريق الجديد إلى القائمة
                    new_fires.push_back(new_fire);
                    
                    // تحديث الخريطة
                    state.map[newX][newY] = "X";
                    
                    cout << "Fire spread to (" << newX << ", " << newY << ")" << endl;
                }
            }
        }
    }
    
    // تحديث قائمة الحرائق في الحالة
    state.fires = new_fires;
    
    // عرض الحالة بعد الانتشار
    cout << "After spreading - Total fires: " << state.fires.size() << endl;
    for (const auto& f : state.fires) {
        cout << "Fire at (" << f.location.x << ", " << f.location.y << ")" << endl;
    }
    
    return state;
}