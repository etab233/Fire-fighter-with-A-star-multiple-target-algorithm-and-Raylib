#ifndef C4952150_93C7_4BA4_AD26_498613EA94DC
#define C4952150_93C7_4BA4_AD26_498613EA94DC

#include<vector>
#include<iostream>
#include "fireState.h"
using namespace std;

struct position{
    int x,y;
    position(int _x = 0, int _y = 0) : x(_x), y(_y) {};

    bool operator ==(const position& p){
        return (x== p.x && y==p.y);
    }
};

struct fire{
    position location;
    int intensity; // [1,5]
    int water_amount; // كمية الماء المطلوبة لإطفائه

    bool operator ==(const fire& f){
        return location == f.location;
    }
};

struct building{
    position location;
    int importance; // 1,2,3,4,5 حسب الأهمية
    bool is_burned;
    bool is_on_fire;

    bool operator ==(const building& f){
        return location == f.location; 
    }
};

class FireState{
public:
    // خريطة اللعبة 
    vector<vector<string>> map;
    int row, column;
    // الخلايا التي تحوي نار
    vector<fire> fires;
    // الخلايا التي تحوي مباني 
    vector<building> buildings;
    // كمية الماء المتوفرة
    int resources;
    // قائمة بالمباني المحروقة
    vector<building> burned_buildings;
    // موقع سيارة الإطفاء الحالي
    position vehicle_location;

    // باني إفتراضي
    FireState();

    bool is_goal();
    bool is_success();
    void printState();
    //تابع يرد الحركات المتاحة في حالة محددة فقط 
    vector<pair<int, int>> get_actions(const FireState& state, position p);
    // لاختبار تساوي حالتين
    bool operator ==(const FireState& other);

    // مُنشئ النسخ
    FireState(const FireState& other) {
        row = other.row;
        column = other.column;
        resources = other.resources;
        vehicle_location = other.vehicle_location;
        map = other.map;
        buildings = other.buildings;
        fires = other.fires;
        burned_buildings = other.burned_buildings;
    }
    
    // عامل التعيين
    FireState& operator=(const FireState& other) {
        if (this != &other) {
            row = other.row;
            column = other.column;
            resources = other.resources;
            vehicle_location = other.vehicle_location;
            map = other.map;
            buildings = other.buildings;
            fires = other.fires;
            burned_buildings = other.burned_buildings;
        }
        return *this;
    }
    
    // مُنشئ التحريك (move constructor)
    FireState(FireState&& other) noexcept {
        row = other.row;
        column = other.column;
        resources = other.resources;
        vehicle_location = other.vehicle_location;
        map = std::move(other.map);
        buildings = std::move(other.buildings);
        fires = std::move(other.fires);
        burned_buildings = std::move(other.burned_buildings);
    }
    
    // عامل تعيين التحريك
    FireState& operator=(FireState&& other) noexcept {
        if (this != &other) {
            row = other.row;
            column = other.column;
            resources = other.resources;
            vehicle_location = other.vehicle_location;
            map = std::move(other.map);
            buildings = std::move(other.buildings);
            fires = std::move(other.fires);
            burned_buildings = std::move(other.burned_buildings);
        }
        return *this;
    }
};

#endif /* C4952150_93C7_4BA4_AD26_498613EA94DC */
