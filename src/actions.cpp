#include "actions.h"
#include "fireState.h"
using namespace std;

FireState Action::burn_cell(FireState state, position cell, fire f){
    // إذا الخلية فيها نار لا يتغير شيء و نبقى في الحالة نفسها
    if(state.map[cell.x][cell.y] == "F") return state;
    // إذا كانت شدة النار تساوي 1 لا تنتشر ونبقى في الحالة نفسها
    if(f.intensity==1) return state;

    // انتشار النار و الانتقال لحالة جديدة
    FireState new_state= state;
    //إضافة المبنى لقائمة المباني المحروقة إذا كانت مبنى
    if(new_state.map[cell.x][cell.y] == "H"){
        building b;
        /*for(int i=0; i< (int) new_state.buildings.size(); i++){
            if((new_state.buildings[i].location.x == cell.x ) && (new_state.buildings[i].location.y == cell.y )){
                b.importance= new_state.buildings[i].importance;
                break;
            }
        }*/
        b.is_burned=false; // لسا ما انطفأ 
        b.is_on_fire=true; // يحترق الان
        b.location=cell;
        new_state.burned_buildings.push_back(b);
        // تعديل الرمز في الخريطة
        new_state.map[b.location.x][b.location.y]="X";
    }
    //تعديل شدة النار بحيث تكون أقل من الشدة الأصلية ب 1
    for(int i=0; i< (int) new_state.fires.size(); i++){
        if( (new_state.fires[i].location.x == f.location.x) && (new_state.fires[i].location.y == f.location.y)){
            new_state.fires[i].intensity= f.intensity-1;
        }
    }
    return new_state;
}

void Action::extinguish_cell(FireState& state, position cell, fire f){
    
    // الحالة 1: إذا في نار في الخلية
    bool has_fire = false;
    for(size_t i = 0; i < state.fires.size(); i++) {
        if(state.fires[i].location.x == cell.x && state.fires[i].location.y == cell.y) {
            // تحقق إذا الموارد كافية لإطفاء هذه النار
            if(state.resources >= state.fires[i].water_amount) {
                state.fires.erase(state.fires.begin() + i);
                state.resources -= f.water_amount;
                has_fire = true;
            }
            break;
        }
    }
    
    // الحالة 2: إذا في مبنى في الخلية (مع أو بدون نار)
    bool has_building = false;
    for(size_t i = 0; i < state.buildings.size(); i++) {
        if(state.buildings[i].location.x == cell.x && state.buildings[i].location.y == cell.y) {
            has_building = true;   
            // إذا المبنى مشتعل، نطفئه
            if(state.buildings[i].is_on_fire) {
                state.buildings[i].is_on_fire = false;
                state.buildings[i].is_burned = true;
                
                // إزالته من قائمة المباني المحترقة إذا كان فيها
                for(size_t j = 0; j < state.burned_buildings.size(); j++) {
                    if(state.burned_buildings[j].location.x == cell.x && 
                       state.burned_buildings[j].location.y == cell.y) {
                        state.burned_buildings.erase(state.burned_buildings.begin() + j);
                        break;
                    }
                }
            }
            break;
        }
    }
    
    //  تحديث الخريطة إذا أطفينا نار أو مبنى
    if(has_fire || (has_building && state.map[cell.x][cell.y] == "F")) {
        state.map[cell.x][cell.y] = ".";  // إرجاع الخلية لحالتها الطبيعية
    }
}