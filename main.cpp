#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"


// Global constants
#define MARGIN 30.0
#define GRID_COLOR BLACK
#define TEXT_COLOR BLACK
#define SECONDARY_GRID_COLOR GRAY
#define LINE_THICKNESS 2.0
#define GRID_THICKNESS 1.0
#define GRID_SPACING 50
#define C 1.0


// Class
class Event
{
    float __x;
    float __t;

    public:
        
        /**
         * Create an event (a spacetime point).
         * @constructor 
         * @param __x The space coordinate (1.0 -> 3.10^8 m).
         * @param __t The time coordinate (in seconds).
         * @return A spacetime point.
        */
        Event(float x, float t)
        {
            this->__x = x;
            this->__t = t;
        }

        float getX() { return this->__x; }
        float getT() { return this->__t; }

};


// Custom Functions
Event LorentzTransform(Event point, float velocity);
float WorldToScreenX(float worldX, int offsetX);
float WorldToScreenY(float worldY, int offsetY);
float ScreenToWorldX(float screenX, int offsetX);
float ScreenToWorldY(float screenY, int offsetY);

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

            // Draw windows
            DrawRectangleLinesEx((Rectangle){MARGIN, MARGIN, globeWidth, globeHeight}, LINE_THICKNESS, GRID_COLOR);
            GuiPanel((Rectangle){ (2.0 * GetScreenWidth())/3, MARGIN, panelWidth, panelHeight }, "Control panel");

            // Draw labels
            DrawText("space", MARGIN + globeWidth - 70, MARGIN + globeHeight/2 + 10, 20, TEXT_COLOR);
            DrawText("time", MARGIN + globeWidth/2 + 10, MARGIN + 10, 20, TEXT_COLOR);
            
            // Draw main frame
            // // Axes
            DrawLineEx(
                (Vector2){MARGIN + globeWidth/2, MARGIN},
                (Vector2){MARGIN + globeWidth/2, MARGIN + globeHeight},
                LINE_THICKNESS,
                GRID_COLOR
            );
            DrawLineEx(
                (Vector2){MARGIN, MARGIN + globeHeight/2},
                (Vector2){MARGIN + globeWidth, MARGIN + globeHeight/2},
                LINE_THICKNESS,
                GRID_COLOR
            );

            // // Grid
            int s = globeWidth / GRID_SPACING;
            for (int i = 1; i <= s/2; i++)
            {
                DrawLineEx(
                    (Vector2){WorldToScreenX(-i, globeWidth/2), MARGIN},
                    (Vector2){WorldToScreenX(-i, globeWidth/2), MARGIN + globeHeight},
                    GRID_THICKNESS,
                    GRID_COLOR
                );
                DrawLineEx(
                    (Vector2){WorldToScreenX(i, globeWidth/2), MARGIN},
                    (Vector2){WorldToScreenX(i, globeWidth/2), MARGIN + globeHeight},
                    GRID_THICKNESS,
                    GRID_COLOR
                );

            }

            int t = globeHeight / GRID_SPACING;
            for (int i = 1; i <= t/2; i++)
            {
                DrawLineEx(
                    (Vector2){MARGIN, WorldToScreenY(-i, globeHeight/2)},
                    (Vector2){MARGIN + globeWidth, WorldToScreenY(-i, globeHeight/2)},
                    GRID_THICKNESS,
                    GRID_COLOR
                );
                DrawLineEx(
                    (Vector2){MARGIN, WorldToScreenY(i, globeHeight/2)},
                    (Vector2){MARGIN + globeWidth, WorldToScreenY(i, globeHeight/2)},
                    GRID_THICKNESS,
                    GRID_COLOR
                );
            }
            

        EndDrawing();
    }

    CloseWindow();
    return 0;
}


Event LorentzTransform(Event point, float velocity)
{
    float gamma = 1 / (sqrt(1 - pow(velocity/C, 2)));
    float x_prime = gamma * (point.getX() - velocity * point.getT());
    float t_prime = gamma * (point.getT() - (velocity * point.getX() / pow(C, 2)));
    
    return Event(x_prime, t_prime);
}

float WorldToScreenX(float worldX, int offsetX)
{
    return worldX * GRID_SPACING + MARGIN + offsetX;
}

float WorldToScreenY(float worldY, int offsetY)
{
    return - worldY * GRID_SPACING + MARGIN + offsetY;
}

float ScreenToWorldX(float screenX, int offsetX)
{
    return (screenX - MARGIN - offsetX) / GRID_SPACING;
}

float ScreenToWorldY(float screenY, int offsetY)
{
    return (-screenY + MARGIN + offsetY) / GRID_SPACING ;
}