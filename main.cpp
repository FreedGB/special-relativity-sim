#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"


// Global constants used
#define MARGIN 30.0
#define COUNTOUR_LINE_COLOR BLACK

int main()
{
    InitWindow(800, 250, "SPACETIME GLOBE SIMULATION");
    SetTargetFPS(60);

    int globeWidth;
    int globeHeight;
    float panelWidth;
    float panelHeight;

    while (!WindowShouldClose())
    {   
        globeWidth = (2 * GetScreenWidth())/3 - 2 * MARGIN;
        globeHeight = GetScreenHeight() - 3 * MARGIN;
        panelWidth = GetScreenWidth()/3 - MARGIN;
        panelHeight = globeHeight;
        
        BeginDrawing();
            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

            DrawRectangleLines(MARGIN, MARGIN, globeWidth, globeHeight, COUNTOUR_LINE_COLOR);
            GuiPanel((Rectangle){ (2.0 * GetScreenWidth())/3, MARGIN, panelWidth, panelHeight }, "Control panel");

        EndDrawing();
    }

    CloseWindow();
    return 0;
}