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
Event LorentzTransform(Event point, float observerVelocity);
float WorldToScreenX(float worldX, int offsetX);
float WorldToScreenY(float worldY, int offsetY);
float ScreenToWorldX(float screenX, int offsetX);
float ScreenToWorldY(float screenY, int offsetY);
bool MouseInGrid(Vector2 mouse, float gridWidth, float gridHeight);

int main()
{
    // Game definitions
    InitWindow(1000, 500, "SPACETIME GLOBE SIMULATION");
    SetTargetFPS(60);

    int globeWidth;
    int globeHeight;
    float panelWidth;
    float panelHeight;
    float observerVelocity;
    float currentX;
    float currentY;
    std::vector<Event> eventsList;
    bool draggingMode;
    bool addingMode;
    int colorIndex;
    Vector2 mousePosition;
    int eventDraggedIndex;
    int activeToggle = -1;

    // Define and initialize generic limit points
    Event e_lab_0 = Event(0.0, 0.0, BLACK);
    Event e_lab_1 = Event(0.0, 0.0, BLACK);
    Event e_lab_2 = Event(0.0, 0.0, BLACK);
    Event e_lab_3 = Event(0.0, 0.0, BLACK);
    Event e0 = Event(0.0, 0.0, BLACK);
    Event e1 = Event(0.0, 0.0, BLACK);
    Event e2 = Event(0.0, 0.0, BLACK);
    Event e3 = Event(0.0, 0.0, BLACK);

    Event p_lab_1 = Event(0.0, 0.0, BLACK);
    Event p_lab_2 = Event(0.0, 0.0, BLACK);
    Event p_lab_3 = Event(0.0, 0.0, BLACK);
    Event p_lab_4 = Event(0.0, 0.0, BLACK);
    Event p_obs_1 = Event(0.0, 0.0, BLACK);
    Event p_obs_2 = Event(0.0, 0.0, BLACK);
    Event p_obs_3 = Event(0.0, 0.0, BLACK);
    Event p_obs_4 = Event(0.0, 0.0, BLACK);

    // Colors
    const Color MAIN_RED = RED;
    const Color SECONDARY_RED = (Color){0xe6, 0x29, 0x37, 0xb8};
    const Color MAIN_BLUE = BLUE;
    const Color SECONDARY_BLUE = (Color){0x00, 0x79, 0xf1, 0x80};
    const Color MAIN_GREEN = GREEN;
    const Color SECONDARY_GREEN = (Color){0x00, 0xe4, 0x30, 0x80};

    // Define event color list. Each element is a couple (color in adding mode, main color)
    std::vector<std::vector<Color>> eventColorList = {
        {MAIN_RED, SECONDARY_RED},
        {MAIN_BLUE, SECONDARY_BLUE},
        {MAIN_GREEN, SECONDARY_GREEN}
    };

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
            /*
                The main grid (the one always fixed) represents the frame of reference of the observer moving at v m/s relative to the lab frame.
                The secondary grid (the one which deforms) represents the lab frame viewed in the frame of the moving observer.
            */

            // Draw labels
            DrawText("space", MARGIN + globeWidth - 70, MARGIN + globeHeight/2 + 10, 20, TEXT_COLOR);
            DrawText("time", MARGIN + globeWidth/2 + 10, MARGIN + 10, 20, TEXT_COLOR);
            
            
            // Draw OBSERVER FRAME's axes
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

            // Draw LAB FRAME's axes on the OBSERVER's FRAME

            // Axe's points coordinates in the lab's frame
            e0 = Event(0.0, ScreenToWorldY(MARGIN, globeHeight/2), BLACK);
            e1 = Event(0.0, ScreenToWorldY(MARGIN + globeHeight, globeHeight/2), BLACK);
            e2 = Event(ScreenToWorldX(MARGIN, globeWidth/2), 0.0, BLACK);
            e3 = Event(ScreenToWorldX(MARGIN + globeWidth, globeWidth/2), 0.0, BLACK);

            // Those axe's points coordinates in the observer's frame (the lab moves at -observerVelocity)
            e_lab_0 = LorentzTransform(e0, observerVelocity);
            e_lab_1 = LorentzTransform(e1, observerVelocity);
            e_lab_2 = LorentzTransform(e2, observerVelocity);
            e_lab_3 = LorentzTransform(e3, observerVelocity);

            // Drawing axes
            DrawLineEx(
                (Vector2){WorldToScreenX(e_lab_0.getX(), globeWidth/2), WorldToScreenY(e_lab_0.getT(), globeHeight/2)},
                (Vector2){WorldToScreenX(e_lab_1.getX(), globeWidth/2), WorldToScreenY(e_lab_1.getT(), globeHeight/2)},
                SECONDARY_GRID_THICKNESS,
                SECONDARY_GRID_COLOR
            );
            DrawLineEx(
                (Vector2){WorldToScreenX(e_lab_2.getX(), globeWidth/2), WorldToScreenY(e_lab_2.getT(), globeHeight/2)},
                (Vector2){WorldToScreenX(e_lab_3.getX(), globeWidth/2), WorldToScreenY(e_lab_3.getT(), globeHeight/2)},
                SECONDARY_GRID_THICKNESS,
                SECONDARY_GRID_COLOR
            );


            // Drawing frames' vertical lines
            int s = globeWidth / GRID_SPACING;
            for (int i = 1; i <= s/2; i++)
            {   
                // Vertical lines of the OBSERVER's frame (they coincide with LAB's frame at v = 0)
                p_obs_1 = Event(-i, ScreenToWorldY(MARGIN, globeHeight/2), BLACK);
                p_obs_2 = Event(-i, ScreenToWorldY(MARGIN + globeHeight, globeHeight/2), BLACK);
                p_obs_3 = Event(i, ScreenToWorldY(MARGIN, globeHeight/2), BLACK);
                p_obs_4 = Event(i, ScreenToWorldY(MARGIN + globeHeight, globeHeight/2), BLACK);
                
                // Vertical lines of the LAB's frame viewed in the OBSERVER's frame
                p_lab_1 = LorentzTransform(p_obs_1, observerVelocity);
                p_lab_2 = LorentzTransform(p_obs_2, observerVelocity);
                p_lab_3 = LorentzTransform(p_obs_3, observerVelocity);
                p_lab_4 = LorentzTransform(p_obs_4, observerVelocity);

                // Drawing LAB's frame vertical lines
                DrawLineEx(
                    (Vector2){WorldToScreenX(p_lab_1.getX(), globeWidth/2), WorldToScreenY(p_lab_1.getT(), globeHeight/2)},
                    (Vector2){WorldToScreenX(p_lab_2.getX(), globeWidth/2), WorldToScreenY(p_lab_2.getT(), globeHeight/2)},
                    SECONDARY_GRID_THICKNESS,
                    SECONDARY_GRID_COLOR
                );
                DrawLineEx(
                    (Vector2){WorldToScreenX(p_lab_3.getX(), globeWidth/2), WorldToScreenY(p_lab_3.getT(), globeHeight/2)},
                    (Vector2){WorldToScreenX(p_lab_4.getX(), globeWidth/2), WorldToScreenY(p_lab_4.getT(), globeHeight/2)},
                    SECONDARY_GRID_THICKNESS,
                    SECONDARY_GRID_COLOR
                );


                // Drawing OBSERVER's frame vertical lines
                DrawLineEx(
                    (Vector2){WorldToScreenX(p_obs_1.getX(), globeWidth/2), WorldToScreenY(p_obs_1.getT(), globeHeight/2)},
                    (Vector2){WorldToScreenX(p_obs_2.getX(), globeWidth/2), WorldToScreenY(p_obs_2.getT(), globeHeight/2)},
                    GRID_THICKNESS,
                    GRID_COLOR
                );
                DrawLineEx(
                    (Vector2){WorldToScreenX(p_obs_3.getX(), globeWidth/2), WorldToScreenY(p_obs_3.getT(), globeHeight/2)},
                    (Vector2){WorldToScreenX(p_obs_4.getX(), globeWidth/2), WorldToScreenY(p_obs_4.getT(), globeHeight/2)},
                    GRID_THICKNESS,
                    GRID_COLOR
                );

            }

            
            // Drawing frames' horizontal lines
            int t = globeHeight / GRID_SPACING;
            for (int i = 1; i <= t/2; i++)
            {
                // Horizontal lines of the OBSERVER's frame (they coincide with LAB's frame at v = 0)
                p_obs_1 = Event(ScreenToWorldX(MARGIN, globeWidth/2), -i, BLACK);
                p_obs_2 = Event(ScreenToWorldX(MARGIN + globeWidth, globeWidth/2), -i, BLACK);
                p_obs_3 = Event(ScreenToWorldX(MARGIN, globeWidth/2), i, BLACK);
                p_obs_4 = Event(ScreenToWorldX(MARGIN + globeWidth, globeWidth/2), i, BLACK);

                // Horizontal lines of the LAB's frame viewed on the OBSERVER's frame
                p_lab_1 = LorentzTransform(p_obs_1, observerVelocity);
                p_lab_2 = LorentzTransform(p_obs_2, observerVelocity);
                p_lab_3 = LorentzTransform(p_obs_3, observerVelocity);
                p_lab_4 = LorentzTransform(p_obs_4, observerVelocity);

                // Drawing LAB's frame horizontal lines
                DrawLineEx(
                    (Vector2){WorldToScreenX(p_lab_1.getX(), globeWidth/2), WorldToScreenY(p_lab_1.getT(), globeHeight/2)},
                    (Vector2){WorldToScreenX(p_lab_2.getX(), globeWidth/2), WorldToScreenY(p_lab_2.getT(), globeHeight/2)},
                    SECONDARY_GRID_THICKNESS,
                    SECONDARY_GRID_COLOR
                );
                DrawLineEx(
                    (Vector2){WorldToScreenX(p_lab_3.getX(), globeWidth/2), WorldToScreenY(p_lab_3.getT(), globeHeight/2)},
                    (Vector2){WorldToScreenX(p_lab_4.getX(), globeWidth/2), WorldToScreenY(p_lab_4.getT(), globeHeight/2)},
                    SECONDARY_GRID_THICKNESS,
                    SECONDARY_GRID_COLOR
                );


                // Drawing OBSERVER's frame horizontal lines
                DrawLineEx(
                    (Vector2){WorldToScreenX(p_obs_1.getX(), globeWidth/2), WorldToScreenY(p_obs_1.getT(), globeHeight/2)},
                    (Vector2){WorldToScreenX(p_obs_2.getX(), globeWidth/2), WorldToScreenY(p_obs_2.getT(), globeHeight/2)},
                    GRID_THICKNESS,
                    GRID_COLOR
                );
                DrawLineEx(
                    (Vector2){WorldToScreenX(p_obs_3.getX(), globeWidth/2), WorldToScreenY(p_obs_3.getT(), globeHeight/2)},
                    (Vector2){WorldToScreenX(p_obs_4.getX(), globeWidth/2), WorldToScreenY(p_obs_4.getT(), globeHeight/2)},
                    GRID_THICKNESS,
                    GRID_COLOR
                );
            }


            // --- Control panel ---

            // Velocity slider
            currentX = globeWidth + 2*MARGIN + 30;
            currentY = MARGIN + 60;
            // GuiLabel((Rectangle){globeWidth + 2*MARGIN + 30, MARGIN + 40, panelWidth - 30, 20}, "Velocity slider");
            GuiSlider((Rectangle){currentX, currentY, panelWidth - 200, 20}, "-C", "C", &observerVelocity, -1.0*C, 1.0*C);
            currentX += panelWidth - 150;
            DrawText(TextFormat("v = %.2f c", observerVelocity), currentX, currentY, 20, TEXT_COLOR);

            // Event adding buttons
            addingMode = false;

            currentX = globeWidth + 2*MARGIN + 30;
            currentY += 50;

            GuiToggleGroup((Rectangle){currentX, currentY, 60, 30}, "RED;BLUE;GREEN", &activeToggle);
            if (activeToggle > -1)
            {
                addingMode = true;
                colorIndex = activeToggle;
            }


            // Clear button
            currentX = globeWidth + 2*MARGIN + 30 + panelWidth - 120;
            currentY += 50;
            if (GuiButton((Rectangle){currentX, currentY, 60, 30}, "Clear all"))
            {
                eventsList.clear();
            }
            

            if (addingMode)
            {
                mousePosition = GetMousePosition();
                if (MouseInGrid(mousePosition, globeWidth, globeHeight))
                {
                    DrawCircleV(GetMousePosition(), EVENT_RADIUS, eventColorList[colorIndex][1]);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        Event e = LorentzTransform(Event(ScreenToWorldX(mousePosition.x, globeWidth/2), ScreenToWorldY(mousePosition.y, globeHeight/2), BLACK), -observerVelocity);
                        
                        eventsList.push_back(
                            Event(
                                e.getX(),
                                e.getT(),
                                eventColorList[colorIndex][0]
                            )
                        );
                        activeToggle = -1;
                    }
                }
            }
            
            // Draw events
            for (Event e: eventsList)
            {
                Event ePrime = LorentzTransform(e, observerVelocity);
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


Event LorentzTransform(Event point, float observerVelocity)
{
    float gamma = 1 / (sqrt(1.0f - pow(observerVelocity/C, 2)));
    float x_prime = gamma * (point.getX() - observerVelocity * point.getT());
    float t_prime = gamma * (point.getT() - (observerVelocity * point.getX() / pow(C, 2)));
    
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

bool MouseInGrid(Vector2 mouse, float gridWidth, float gridHeight)
{
    if ((MARGIN <= mouse.x && mouse.x <= MARGIN + gridWidth) && (MARGIN <= mouse.y && mouse.y <= MARGIN + gridHeight))
    {
        return true;
    }
    return false;
}