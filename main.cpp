#include <vector>
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
#define EVENT_RADIUS 10.0
#define EVENT_BUTTON_HEIGHT 60
#define EVENT_BUTTON_WIDTH 30


// Class
class Event
{
    float x;
    float t;
    Color color;

    public:
        
        /**
         * Create an event (a spacetime point).
         * @constructor 
         * @param x The space coordinate (1.0 -> 3.10^8 m).
         * @param t The time coordinate (in seconds).
         * @return A spacetime point.
        */
        Event(float x, float t, Color color)
        {
            this->x = x;
            this->t = t;
            this->color = color;
        }

        void setX(float x) { this->x = x; }
        void setT(float t) { this->t = t; }
        float getX() { return this->x; }
        float getT() { return this->t; }
        Color getColor() { return this->color; }
};


// Custom Functions
Event LorentzTransform(Event point, float velocity);
float WorldToScreenX(float worldX, int offsetX);
float WorldToScreenY(float worldY, int offsetY);
float ScreenToWorldX(float screenX, int offsetX);
float ScreenToWorldY(float screenY, int offsetY);

int main()
{
    // Game definitions
    InitWindow(1000, 500, "SPACETIME GLOBE SIMULATION");
    SetTargetFPS(60);

    int globeWidth;
    int globeHeight;
    float panelWidth;
    float panelHeight;
    float velocity;
    float currentX;
    float currentY;
    std::vector<Event> eventsList;
    bool draggingMode;
    Vector2 mousePosition;
    int eventDraggedIndex;

    // Define and initialize generic limit points
    Event e0 = Event(0.0, 0.0, BLACK);
    Event e1 = Event(0.0, 0.0, BLACK);
    Event p1 = Event(0.0, 0.0, BLACK);
    Event p2 = Event(0.0, 0.0, BLACK);
    Event p3 = Event(0.0, 0.0, BLACK);
    Event p4 = Event(0.0, 0.0, BLACK);
    Event e0Prime = Event(0.0, 0.0, BLACK);
    Event e1Prime = Event(0.0, 0.0, BLACK);
    Event p1Prime = Event(0.0, 0.0, BLACK);
    Event p2Prime = Event(0.0, 0.0, BLACK);
    Event p3Prime = Event(0.0, 0.0, BLACK);
    Event p4Prime = Event(0.0, 0.0, BLACK);


    // Game loop
    while (!WindowShouldClose())
    {   
        globeWidth = (2 * GetScreenWidth())/3 - 2 * MARGIN;
        globeHeight = GetScreenHeight() - 3 * MARGIN;
        panelWidth = GetScreenWidth()/3 - MARGIN;
        panelHeight = globeHeight;

        // Drag and drop logic
        draggingMode = false;
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            mousePosition = GetMousePosition();
            for (int i = 0; i < eventsList.size(); i++)
            {
                Vector2 eventScreenCoordinates = (Vector2)
                {
                    WorldToScreenX(eventsList[i].getX(), globeWidth/2),
                    WorldToScreenY(eventsList[i].getT(), globeHeight/2)
                };

                if (CheckCollisionPointCircle(mousePosition, eventScreenCoordinates, EVENT_RADIUS + 10))
                {
                    draggingMode = true;
                    eventDraggedIndex = i;
                    break;
                }
            }
        }
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            draggingMode = false;
        }

        if (draggingMode)
        {
            mousePosition = GetMousePosition();
            eventsList[eventDraggedIndex].setX(ScreenToWorldX(mousePosition.x, globeWidth/2));
            eventsList[eventDraggedIndex].setT(ScreenToWorldY(mousePosition.y, globeHeight/2));
        }

        
        BeginDrawing();
            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

            // Draw windows
            DrawRectangleLinesEx((Rectangle){MARGIN, MARGIN, globeWidth, globeHeight}, BORDER_THICKNESS, GRID_COLOR);
            GuiPanel((Rectangle){globeWidth + 2*MARGIN, MARGIN, panelWidth, panelHeight}, "Control panel");

            
            // --- Spacetime Globe ---

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
            e0 = Event(0.0, ScreenToWorldY(MARGIN, globeHeight/2), BLACK);
            e1 = Event(0.0, ScreenToWorldY(MARGIN + globeHeight, globeHeight/2), BLACK);
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
                
                p1 = Event(-i, ScreenToWorldY(MARGIN, globeHeight/2), BLACK);
                p2 = Event(-i, ScreenToWorldY(MARGIN + globeHeight, globeHeight/2), BLACK);
                p3 = Event(i, ScreenToWorldY(MARGIN, globeHeight/2), BLACK);
                p4 = Event(i, ScreenToWorldY(MARGIN + globeHeight, globeHeight/2), BLACK);
                
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

            e0 = Event(ScreenToWorldX(MARGIN, globeWidth/2), 0.0, BLACK);
            e1 = Event(ScreenToWorldX(MARGIN + globeWidth, globeWidth/2), 0.0, BLACK);
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
                p1 = Event(ScreenToWorldX(MARGIN, globeWidth/2), -i, BLACK);
                p2 = Event(ScreenToWorldX(MARGIN + globeWidth, globeWidth/2), -i, BLACK);
                p3 = Event(ScreenToWorldX(MARGIN, globeWidth/2), i, BLACK);
                p4 = Event(ScreenToWorldX(MARGIN + globeWidth, globeWidth/2), i, BLACK);

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


            // --- Control panel ---

            // Velocity slider
            currentX = globeWidth + 2*MARGIN + 30;
            currentY = MARGIN + 60;
            // GuiLabel((Rectangle){globeWidth + 2*MARGIN + 30, MARGIN + 40, panelWidth - 30, 20}, "Velocity slider");
            GuiSlider((Rectangle){currentX, currentY, panelWidth - 200, 20}, "-C", "C", &velocity, -1.0*C, 1.0*C);
            currentX += panelWidth - 150;
            DrawText(TextFormat("v = %.2f c", velocity), currentX, currentY, 20, TEXT_COLOR);

            // Add event
            currentX = globeWidth + 2*MARGIN + 30;
            currentY += 50;
            if (GuiButton((Rectangle){currentX, currentY, 60, 30}, ""))
            {
                eventsList.push_back(Event(0.0, 0.0, RED));
            }
            DrawRectangleV((Vector2){currentX, currentY}, (Vector2){60, 30}, RED);
            DrawRectangleLinesEx((Rectangle){currentX, currentY, 60, 30}, 2.0, BLACK);

            currentX += 60 + 20;
            if (GuiButton((Rectangle){currentX, currentY, 60, 30}, ""))
            {
                eventsList.push_back(Event(1.0, 1.0, BLUE));
            }
            DrawRectangleV((Vector2){currentX, currentY}, (Vector2){60, 30}, BLUE);
            DrawRectangleLinesEx((Rectangle){currentX, currentY, 60, 30}, 2.0, BLACK);

            currentX += 60 + 20;
            if (GuiButton((Rectangle){currentX, currentY, 60, 30}, ""))
            {
                eventsList.push_back(Event(-1.0, -1.0, GREEN));
            }
            DrawRectangleV((Vector2){currentX, currentY}, (Vector2){60, 30}, GREEN);
            DrawRectangleLinesEx((Rectangle){currentX, currentY, 60, 30}, 2.0, BLACK);

            // Clear button
            currentX = globeWidth + 2*MARGIN + 30 + panelWidth - 120;
            currentY += 50;
            if (GuiButton((Rectangle){currentX, currentY, 60, 30}, "Clear all"))
            {
                eventsList.clear();
            }
            
            // Draw events
            for (Event e: eventsList)
            {
                Event ePrime = LorentzTransform(e, velocity);
                DrawCircleV(
                    (Vector2) {WorldToScreenX(ePrime.getX(), globeWidth/2), WorldToScreenY(ePrime.getT(), globeHeight/2)},
                    EVENT_RADIUS,
                    ePrime.getColor()
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
    
    return Event(x_prime, t_prime, point.getColor());
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