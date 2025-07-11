#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"


// Global constants
#define MARGIN 30.0
#define GRID_COLOR BLACK
#define TEXT_COLOR BLACK
#define SECONDARY_GRID_COLOR GRAY
#define BORDER_THICKNESS 2.0
#define AXE_THICKNESS 2.0
#define GRID_THICKNESS 1.0
#define SECONDARY_GRID_THICKNESS 1.0
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
    float velocity;

    // Define and initialize generic limit points
    Event e0 = Event(0.0, 0.0);
    Event e1 = Event(0.0, 0.0);
    Event p1 = Event(0.0, 0.0);
    Event p2 = Event(0.0, 0.0);
    Event p3 = Event(0.0, 0.0);
    Event p4 = Event(0.0, 0.0);
    Event e0Prime = Event(0.0, 0.0);
    Event e1Prime = Event(0.0, 0.0);
    Event p1Prime = Event(0.0, 0.0);
    Event p2Prime = Event(0.0, 0.0);
    Event p3Prime = Event(0.0, 0.0);
    Event p4Prime = Event(0.0, 0.0);

    while (!WindowShouldClose())
    {   
        globeWidth = (2 * GetScreenWidth())/3 - 2 * MARGIN;
        globeHeight = GetScreenHeight() - 3 * MARGIN;
        panelWidth = GetScreenWidth()/3 - MARGIN;
        panelHeight = globeHeight;

        
        BeginDrawing();
            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

            // Draw windows
            DrawRectangleLinesEx((Rectangle){MARGIN, MARGIN, globeWidth, globeHeight}, BORDER_THICKNESS, GRID_COLOR);
            GuiPanel((Rectangle){(2.0 * GetScreenWidth())/3, MARGIN, panelWidth, panelHeight }, "Control panel");

            // Add velocity slider
            GuiSlider((Rectangle){(2.0 * GetScreenWidth())/3 + 30, MARGIN + 40, panelWidth - 200, 20}, "-C", "C", &velocity, -1.0*C, 1.0*C);
            DrawText(TextFormat("v = %.2f c", velocity), 2*MARGIN + globeWidth + panelWidth - 120, MARGIN + 40, 20, TEXT_COLOR);

            // Draw labels
            DrawText("space", MARGIN + globeWidth - 70, MARGIN + globeHeight/2 + 10, 20, TEXT_COLOR);
            DrawText("time", MARGIN + globeWidth/2 + 10, MARGIN + 10, 20, TEXT_COLOR);
            
            // Draw Axes
            DrawLineEx(
                (Vector2){MARGIN + globeWidth/2, MARGIN},
                (Vector2){MARGIN + globeWidth/2, MARGIN + globeHeight},
                AXE_THICKNESS,
                GRID_COLOR
            );
            DrawLineEx(
                (Vector2){MARGIN, MARGIN + globeHeight/2},
                (Vector2){MARGIN + globeWidth, MARGIN + globeHeight/2},
                AXE_THICKNESS,
                GRID_COLOR
            );

            // Grid
            e0 = Event(0.0, ScreenToWorldY(MARGIN, globeHeight/2));
            e1 = Event(0.0, ScreenToWorldY(MARGIN + globeHeight, globeHeight/2));
            e0Prime = LorentzTransform(e0, velocity);
            e1Prime = LorentzTransform(e1, velocity);
            DrawLineEx(
                (Vector2){WorldToScreenX(e0Prime.getX(), globeWidth/2), WorldToScreenY(e0Prime.getT(), globeHeight/2)},
                (Vector2){WorldToScreenX(e1Prime.getX(), globeWidth/2), WorldToScreenY(e1Prime.getT(), globeHeight/2)},
                SECONDARY_GRID_THICKNESS,
                SECONDARY_GRID_COLOR
            );
            int s = globeWidth / GRID_SPACING;
            for (int i = 1; i <= s/2; i++)
            {
                
                p1 = Event(-i, ScreenToWorldY(MARGIN, globeHeight/2));
                p2 = Event(-i, ScreenToWorldY(MARGIN + globeHeight, globeHeight/2));
                p3 = Event(i, ScreenToWorldY(MARGIN, globeHeight/2));
                p4 = Event(i, ScreenToWorldY(MARGIN + globeHeight, globeHeight/2));

                
                p1Prime = LorentzTransform(p1, velocity);
                p2Prime = LorentzTransform(p2, velocity);
                p3Prime = LorentzTransform(p3, velocity);
                p4Prime = LorentzTransform(p4, velocity);

                // Draw background grid (vertical)
                DrawLineEx(
                    (Vector2){WorldToScreenX(p1Prime.getX(), globeWidth/2), WorldToScreenY(p1Prime.getT(), globeHeight/2)},
                    (Vector2){WorldToScreenX(p2Prime.getX(), globeWidth/2), WorldToScreenY(p2Prime.getT(), globeHeight/2)},
                    SECONDARY_GRID_THICKNESS,
                    SECONDARY_GRID_COLOR
                );
                DrawLineEx(
                    (Vector2){WorldToScreenX(p3Prime.getX(), globeWidth/2), WorldToScreenY(p3Prime.getT(), globeHeight/2)},
                    (Vector2){WorldToScreenX(p4Prime.getX(), globeWidth/2), WorldToScreenY(p4Prime.getT(), globeHeight/2)},
                    SECONDARY_GRID_THICKNESS,
                    SECONDARY_GRID_COLOR
                );


                // Draw main grid (vertical)
                DrawLineEx(
                    (Vector2){WorldToScreenX(p1.getX(), globeWidth/2), WorldToScreenY(p1.getT(), globeHeight/2)},
                    (Vector2){WorldToScreenX(p2.getX(), globeWidth/2), WorldToScreenY(p2.getT(), globeHeight/2)},
                    GRID_THICKNESS,
                    GRID_COLOR
                );
                DrawLineEx(
                    (Vector2){WorldToScreenX(p3.getX(), globeWidth/2), WorldToScreenY(p3.getT(), globeHeight/2)},
                    (Vector2){WorldToScreenX(p4.getX(), globeWidth/2), WorldToScreenY(p4.getT(), globeHeight/2)},
                    GRID_THICKNESS,
                    GRID_COLOR
                );

            }

            e0 = Event(ScreenToWorldX(MARGIN, globeWidth/2), 0.0);
            e1 = Event(ScreenToWorldX(MARGIN + globeWidth, globeWidth/2), 0.0);
            e0Prime = LorentzTransform(e0, velocity);
            e1Prime = LorentzTransform(e1, velocity);
            DrawLineEx(
                (Vector2){WorldToScreenX(e0Prime.getX(), globeWidth/2), WorldToScreenY(e0Prime.getT(), globeHeight/2)},
                (Vector2){WorldToScreenX(e1Prime.getX(), globeWidth/2), WorldToScreenY(e1Prime.getT(), globeHeight/2)},
                SECONDARY_GRID_THICKNESS,
                SECONDARY_GRID_COLOR
            );
            int t = globeHeight / GRID_SPACING;
            for (int i = 1; i <= t/2; i++)
            {
                p1 = Event(ScreenToWorldX(MARGIN, globeWidth/2), -i);
                p2 = Event(ScreenToWorldX(MARGIN + globeWidth, globeWidth/2), -i);
                p3 = Event(ScreenToWorldX(MARGIN, globeWidth/2), i);
                p4 = Event(ScreenToWorldX(MARGIN + globeWidth, globeWidth/2), i);

                p1Prime = LorentzTransform(p1, velocity);
                p2Prime = LorentzTransform(p2, velocity);
                p3Prime = LorentzTransform(p3, velocity);
                p4Prime = LorentzTransform(p4, velocity);

                // Draw background grid (horizontal)
                DrawLineEx(
                    (Vector2){WorldToScreenX(p1Prime.getX(), globeWidth/2), WorldToScreenY(p1Prime.getT(), globeHeight/2)},
                    (Vector2){WorldToScreenX(p2Prime.getX(), globeWidth/2), WorldToScreenY(p2Prime.getT(), globeHeight/2)},
                    SECONDARY_GRID_THICKNESS,
                    SECONDARY_GRID_COLOR
                );
                DrawLineEx(
                    (Vector2){WorldToScreenX(p3Prime.getX(), globeWidth/2), WorldToScreenY(p3Prime.getT(), globeHeight/2)},
                    (Vector2){WorldToScreenX(p4Prime.getX(), globeWidth/2), WorldToScreenY(p4Prime.getT(), globeHeight/2)},
                    SECONDARY_GRID_THICKNESS,
                    SECONDARY_GRID_COLOR
                );


                // Draw main grid (horizontal)
                DrawLineEx(
                    (Vector2){WorldToScreenX(p1.getX(), globeWidth/2), WorldToScreenY(p1.getT(), globeHeight/2)},
                    (Vector2){WorldToScreenX(p2.getX(), globeWidth/2), WorldToScreenY(p2.getT(), globeHeight/2)},
                    GRID_THICKNESS,
                    GRID_COLOR
                );
                DrawLineEx(
                    (Vector2){WorldToScreenX(p3.getX(), globeWidth/2), WorldToScreenY(p3.getT(), globeHeight/2)},
                    (Vector2){WorldToScreenX(p4.getX(), globeWidth/2), WorldToScreenY(p4.getT(), globeHeight/2)},
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