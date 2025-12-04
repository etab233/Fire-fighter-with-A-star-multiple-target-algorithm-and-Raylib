#include "raylib.h"
#include "fireState.h"
#include "visualizer.h"
#include <vector>
#include <string>

const int CELL_SIZE = 80;
const int INFO_PANEL_HEIGHT = 150;
const int GRID_MARGIN = 50;

// تابع يرسم كلمة داخل خلية
void DrawCellText(int i, int j, const char* text, Color c, int gridOffsetX, int gridOffsetY) {
    DrawText(text, 
             gridOffsetX + j * CELL_SIZE + 10, 
             gridOffsetY + i * CELL_SIZE + 10, 
             18, c);
}

// تابع يرسم رسالة في منتصف الشاشة
void DrawCenteredMessage(const char* message, int fontSize, Color color, int screenWidth, int screenHeight) {
    int textWidth = MeasureText(message, fontSize);
    int x = (screenWidth - textWidth) / 2;
    int y = (screenHeight - fontSize) / 2;
    
    DrawRectangle(x - 20, y - 20, textWidth + 40, fontSize + 40, Fade(BLACK, 0.7f));
    DrawText(message, x, y, fontSize, color);
}

// تابع يرسم لوحة المعلومات في الأعلى
void DrawInfoPanel(int resources, int buildingsCount, int firesCount, int panelWidth, int panelHeight) {
    DrawRectangle(0, 0, panelWidth, panelHeight, (Color){240, 240, 240, 255});
    DrawRectangle(0, panelHeight - 2, panelWidth, 2, DARKGRAY);
    
    DrawText("Fire Simulation Game", panelWidth/2 - MeasureText("Fire Simulation Game", 28)/2, 15, 28, DARKBLUE);
    
    int startY = 60;
    int spacing = 25;
    
    DrawText(TextFormat("Resources: %d", resources), 20, startY, 22, BLACK);
    DrawText(TextFormat("Buildings: %d", buildingsCount), 20, startY + spacing, 22, BROWN);
    DrawText(TextFormat("Fires: %d", firesCount), 20, startY + spacing * 2, 22, RED);
    
    DrawText("Use arrow keys to move", panelWidth - MeasureText("Use arrow keys to move", 18) - 20, 
             startY + spacing, 18, DARKGRAY);
}

// تابع يرسم مبنى بسيط وواقعي
void DrawSimpleBuilding(int x, int y, int width, int height, int buildingIndex) {
    // ألوان متنوعة للمباني
    Color buildingColors[] = {
        (Color){180, 120, 80, 255},   // بني فاتح
        (Color){160, 100, 60, 255},   // بني متوسط
        (Color){140, 80, 40, 255},    // بني غامق
        (Color){200, 160, 120, 255},  // بيج
        (Color){170, 130, 90, 255}    // بني رملي
    };
    
    Color borderColors[] = {
        (Color){150, 90, 50, 255},    // بني فاتح أغمق
        (Color){130, 70, 30, 255},    // بني متوسط أغمق
        (Color){110, 50, 10, 255},    // بني غامق أغمق
        (Color){170, 130, 90, 255},   // بيج أغمق
        (Color){140, 100, 60, 255}    // بني رملي أغمق
    };
    
    Color roofColors[] = {
        (Color){100, 60, 30, 255},
        (Color){80, 50, 25, 255},
        (Color){120, 70, 35, 255}
    };
    
    Color windowColors[] = {
        (Color){255, 255, 220, 255},
        (Color){255, 255, 200, 255},
        (Color){255, 255, 180, 255}
    };
    
    // اختيار ألوان بناءً على index المبنى
    int colorIndex = buildingIndex % 5;
    int roofIndex = buildingIndex % 3;
    int windowIndex = buildingIndex % 3;
    
    // جسم المبنى الرئيسي
    DrawRectangle(x, y, width, height, buildingColors[colorIndex]);
    
    // حدود المبنى - استخدام مصفوفة منفصلة للحدود لتجنب التحذيرات
    DrawRectangleLines(x, y, width, height, borderColors[colorIndex]);
    
    // سقف بسيط
    DrawRectangle(x, y - 5, width, 5, roofColors[roofIndex]);
    
    // نافذتان بسيطتان
    int windowSize = 12;
    int windowSpacing = 8;
    
    // نافذة يسار
    DrawRectangle(x + 15, y + 20, windowSize, windowSize * 1.5, windowColors[windowIndex]);
    DrawRectangleLines(x + 15, y + 20, windowSize, windowSize * 1.5, DARKGRAY);
    
    // نافذة يمين
    DrawRectangle(x + width - 15 - windowSize, y + 20, windowSize, windowSize * 1.5, windowColors[windowIndex]);
    DrawRectangleLines(x + width - 15 - windowSize, y + 20, windowSize, windowSize * 1.5, DARKGRAY);
    
    // باب
    int doorWidth = 18;
    int doorHeight = 25;
    int doorX = x + width/2 - doorWidth/2;
    int doorY = y + height - doorHeight;
    
    DrawRectangle(doorX, doorY, doorWidth, doorHeight, (Color){100, 60, 30, 255});
    DrawRectangleLines(doorX, doorY, doorWidth, doorHeight, (Color){70, 40, 20, 255});
    
    // مقبض الباب
    DrawCircle(doorX + doorWidth - 4, doorY + doorHeight/2, 2, (Color){200, 200, 200, 255});
}

// تابع لرسم أرضية الشبكة 
void DrawGridBackground(int gridStartX, int gridStartY, int rows, int cols, int cellSize) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int cellX = gridStartX + j * cellSize;
            int cellY = gridStartY + i * cellSize;
            
            // خلفية مربعات متبادلة الألوان
            Color cellColor = ((i + j) % 2 == 0) ? 
                (Color){245, 245, 245, 255} : 
                (Color){235, 235, 235, 255};
            
            DrawRectangle(cellX, cellY, cellSize, cellSize, cellColor);
            DrawRectangleLines(cellX, cellY, cellSize, cellSize, (Color){220, 220, 220, 255});
        }
    }
}

// تابع يرسم الشبكة كاملة 
void drawState(const FireState& state) {
    int gridWidth = state.column * CELL_SIZE + GRID_MARGIN * 2;
    int gridHeight = state.row * CELL_SIZE + GRID_MARGIN * 2;
    int windowWidth = gridWidth;
    int windowHeight = INFO_PANEL_HEIGHT + gridHeight;
    
    InitWindow(windowWidth, windowHeight, "Fire Simulation Visualizer");
    SetTargetFPS(60);

    bool showMessage = false;
    bool isWin = false;
    const char* messageText = "";
    Color messageColor = WHITE;
    int messageTimer = 0;
    const int MESSAGE_DURATION = 180;
    
    int gridStartX = GRID_MARGIN;
    int gridStartY = INFO_PANEL_HEIGHT + GRID_MARGIN;

    while(!WindowShouldClose()) {
        if (!showMessage) {
            if (state.resources <= 0) {
                showMessage = true;
                isWin = false;
                messageText = "Resources were exhausted";
                messageColor = RED;
                messageTimer = MESSAGE_DURATION;
            }
            else if (state.buildings.empty()) {
                showMessage = true;
                isWin = false;
                messageText = "Try again";
                messageColor = RED;
                messageTimer = MESSAGE_DURATION;
            }
            else if (state.fires.empty() && state.resources > 0) {
                showMessage = true;
                isWin = true;
                messageText = "Good Job";
                messageColor = GREEN;
                messageTimer = MESSAGE_DURATION;
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        DrawInfoPanel(state.resources, state.buildings.size(), state.fires.size(), 
                     windowWidth, INFO_PANEL_HEIGHT);
        
        // رسم خلفية الشبكة
        DrawGridBackground(gridStartX, gridStartY, state.row, state.column, CELL_SIZE);
        
        // رسم المباني
        int buildingIndex = 0;
        for(auto& b : state.buildings) {
            int buildingX = gridStartX + b.location.y * CELL_SIZE + 8;
            int buildingY = gridStartY + b.location.x * CELL_SIZE + 8;
            int buildingWidth = CELL_SIZE - 16;
            int buildingHeight = CELL_SIZE - 16;
            
            DrawSimpleBuilding(buildingX, buildingY, buildingWidth, buildingHeight, buildingIndex);
            buildingIndex++;
        }

        // رسم السيارة
        int carCenterX = gridStartX + state.vehicle_location.y * CELL_SIZE + CELL_SIZE / 2;
        int carCenterY = gridStartY + state.vehicle_location.x * CELL_SIZE + CELL_SIZE / 2;
    
        // جسم السيارة
        DrawRectangle(carCenterX - 22, carCenterY - 16, 44, 32, BLUE);
        DrawRectangle(carCenterX - 26, carCenterY - 26, 18, 14, DARKBLUE);
    
        // العجلات
        DrawCircle(carCenterX - 14, carCenterY + 14, 7, BLACK);
        DrawCircle(carCenterX + 14, carCenterY + 14, 7, BLACK);
        
        // تفاصيل العجلات
        DrawCircle(carCenterX - 14, carCenterY + 14, 3, GRAY);
        DrawCircle(carCenterX + 14, carCenterY + 14, 3, GRAY);
    
        // ضوء أمامي
        DrawCircle(carCenterX + 28, carCenterY, 7, YELLOW);
        DrawCircleLines(carCenterX + 28, carCenterY, 9, ORANGE);
        
        // رسم الحرائق
        for(auto& fire : state.fires) {
            int fireX = gridStartX + fire.location.y * CELL_SIZE + CELL_SIZE / 2;
            int fireY = gridStartY + fire.location.x * CELL_SIZE + CELL_SIZE / 2;
            
            DrawCircle(fireX, fireY, 16, RED);
            DrawCircle(fireX, fireY, 12, ORANGE);
            DrawCircle(fireX, fireY, 8, YELLOW);
            DrawCircleLines(fireX, fireY, 20, (Color){255, 100, 0, 200});
            
            // إضافة بعض الشرر الصغير
            DrawCircle(fireX - 10, fireY - 8, 3, YELLOW);
            DrawCircle(fireX + 8, fireY - 10, 3, YELLOW);
            DrawCircle(fireX + 5, fireY + 12, 3, YELLOW);
        }

        // عرض رسالة الفوز/الخسارة
        if (showMessage) {
            DrawCenteredMessage(messageText, 40, messageColor, windowWidth, windowHeight);
            
            const char* subMessage = isWin ? 
                "WIN! All fires are extinguished" : 
                "GAME OVER - Press ESC to exit";
            
            int subFontSize = 25;
            int subTextWidth = MeasureText(subMessage, subFontSize);
            int subX = (windowWidth - subTextWidth) / 2;
            int subY = (windowHeight - subFontSize) / 2 + 50;
            
            DrawText(subMessage, subX, subY, subFontSize, LIGHTGRAY);
            
            if (messageTimer > 0) {
                messageTimer--;
            }
        }
        
        // تعليمات التحكم
        DrawText("Press arrow keys to move the fire truck", 
                 windowWidth/2 - MeasureText("Press arrow keys to move the fire truck", 18)/2, 
                 windowHeight - 25, 18, DARKGRAY);

        EndDrawing();
        
        if (showMessage && messageTimer <= 0 && !isWin) {
            break;
        }
    }
    
    CloseWindow();
}
/*
g++ -std=c++17 -IC:/raylib/include -I./include src/main.cpp src/visualizer.cpp src/fireState.cpp src/actions.cpp src/a_star.cpp src/fire_problem.cpp src/fire_spread.cpp -LC:/raylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm -o fire_simulation.exe
fire_simulation.exe
*/