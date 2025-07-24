#include <vector>
#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "style_rltech.h"

// Global constants
#define MARGIN 30.0f
#define BORDER_THICKNESS 2.0f
#define AXE_THICKNESS 2.0f
#define GRID_THICKNESS 1.0f
#define SECONDARY_GRID_THICKNESS 1.0f
#define GRID_SPACING 50.0f
#define C 1.0f
#define EVENT_RADIUS 10.0f
#define EVENT_BUTTON_HEIGHT 30.0f
#define EVENT_BUTTON_WIDTH 70.0f
#define TEXT_FONT_SIZE 16.0f

// Colors
#define BACKGROUND_COLOR RAYWHITE
#define GRID_COLOR BLACK
#define TEXT_COLOR BLACK
#define SECONDARY_GRID_COLOR GRAY
#define MAIN_RED RED
#define SECONDARY_RED (Color){0xe6, 0x29, 0x37, 0xb8}
#define MAIN_BLUE BLUE
#define SECONDARY_BLUE (Color){0x00, 0x79, 0xf1, 0x80}
#define MAIN_GREEN GREEN
#define SECONDARY_GREEN (Color){0x00, 0xe4, 0x30, 0x80}

// GUI constants
#define ELEMENT_SPACING 40.0f
#define TITLE_BOTTOM_MARGIN 30.0f
#define PANEL_BLOCKS_SPACING 60.0f
#define LETTER_SPACING 2.0f


// Event class
class Event
{
    float x;
    float t;
    Color color;

    public:
        
        // Default constructor
        Event()
        {
            this->x = 0.0f;
            this->t = 0.0f;
            this->color = BLACK;
        }
    
        /**
         * Create an event (a spacetime point).
         * @constructor 
         * @param x The space coordinate (1.0 -> 3.10^8 m).
         * @param t The time coordinate (in seconds).
         * @param color The color of the point
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

// Rod class
class Rod
{
    Event tipEvent;
    Event tailEvent;
    Color color;

    public:
        Rod(Event tipEvent, Event tailEvent, Color color)
        {
            this->tipEvent = tipEvent;
            this->tailEvent = tailEvent;
            this->color = color;
        }

        Event getTipEvent() {return this->tipEvent;}
        Event getTailEvent() {return this->tailEvent;}
        Color getColor() {return this->color;}
};

// Custom Functions
float GetGamma(float observerVelocity);
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
    Font font = LoadFont("rltech.ttf");
    GuiLoadStyleRLTech();
    GuiSetFont(font);
    GuiSetStyle(DEFAULT, TEXT_SIZE, TEXT_FONT_SIZE);

    float globeWidth;
    float globeHeight;
    float panelWidth;
    float panelHeight;
    float observerVelocity = 0.0f;
    float currentX;
    float currentY;
    std::vector<Event> eventsList; // Stores the events coordinates in the LAB's frame
    std::vector<Rod> rodsList;
    bool draggingMode;
    bool addingEventMode;
    bool addingRodModeStep1 = false;
    bool addingRodModeStep2 = false;
    int colorIndex;
    Vector2 mousePosition;
    int eventDraggedIndex;
    int activeEventToggle = -1;
    int activeRodToggle = -1;
    bool activeCheckBox = false;
    Vector2 tipPosition;
    Vector2 tailPosition;
    Event tipEvent;
    Event tailEvent;

    // Define and initialize generic limit points
    Event e0_obs;
    Event e1_obs;
    Event e2_obs;
    Event e3_obs;
    Event e0;
    Event e1;
    Event e2;
    Event e3;

    Event p_lab_1;
    Event p_lab_2;
    Event p_lab_3;
    Event p_lab_4;
    Event p_obs_1;
    Event p_obs_2;
    Event p_obs_3;
    Event p_obs_4;

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

        
        BeginDrawing();
            ClearBackground(BACKGROUND_COLOR);

            // Draw windows
            DrawRectangleLinesEx((Rectangle){MARGIN, MARGIN, globeWidth, globeHeight}, BORDER_THICKNESS, GRID_COLOR);
            GuiPanel((Rectangle){globeWidth + 2.0f*MARGIN, MARGIN, panelWidth, panelHeight}, "#142#Control panel");

            
            // --- Spacetime Globe ---
            /*
                The main grid (the one always fixed) represents the frame of reference of the observer moving at v m/s relative to the lab frame.
                The secondary grid (the one which deforms) represents the lab frame viewed in the frame of the moving observer.
            */

            // Draw labels
            DrawTextEx(font, "space", (Vector2){MARGIN + globeWidth - 70, MARGIN + globeHeight/2 + 10}, TEXT_FONT_SIZE, 2, TEXT_COLOR);
            DrawTextEx(font, "time", (Vector2){MARGIN + globeHeight/2 + 10, MARGIN + 10}, TEXT_FONT_SIZE, 2, TEXT_COLOR);
            

            // Draw LAB FRAME's axes on the OBSERVER's FRAME

            // Axes points of LAB's frame in the LAB's frame
            e0 = Event(0.0, ScreenToWorldY(MARGIN, globeHeight/2), BLACK);
            e1 = Event(0.0, ScreenToWorldY(MARGIN + globeHeight, globeHeight/2), BLACK);
            e2 = Event(ScreenToWorldX(MARGIN, globeWidth/2), 0.0, BLACK);
            e3 = Event(ScreenToWorldX(MARGIN + globeWidth, globeWidth/2), 0.0, BLACK);

            // Those axes' points converted in the OBSERVER's frame
            e0_obs = LorentzTransform(e0, observerVelocity);
            e1_obs = LorentzTransform(e1, observerVelocity);
            e2_obs = LorentzTransform(e2, observerVelocity);
            e3_obs = LorentzTransform(e3, observerVelocity);

            // Drawing axes
            DrawLineEx(
                (Vector2){WorldToScreenX(e0_obs.getX(), globeWidth/2), WorldToScreenY(e0_obs.getT(), globeHeight/2)},
                (Vector2){WorldToScreenX(e1_obs.getX(), globeWidth/2), WorldToScreenY(e1_obs.getT(), globeHeight/2)},
                SECONDARY_GRID_THICKNESS,
                SECONDARY_GRID_COLOR
            );
            DrawLineEx(
                (Vector2){WorldToScreenX(e2_obs.getX(), globeWidth/2), WorldToScreenY(e2_obs.getT(), globeHeight/2)},
                (Vector2){WorldToScreenX(e3_obs.getX(), globeWidth/2), WorldToScreenY(e3_obs.getT(), globeHeight/2)},
                SECONDARY_GRID_THICKNESS,
                SECONDARY_GRID_COLOR
            );

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
            float left_margin = globeWidth + 2*MARGIN + 15;
            currentY = MARGIN + 40;

            // Observer frame info
            currentX = left_margin;
            GuiLine((Rectangle){currentX, currentY, panelWidth - 50, 10}, "Observer frame info");

            currentY += TITLE_BOTTOM_MARGIN;
            currentX += 26;
            GuiSlider((Rectangle){currentX, currentY, panelWidth - 100, 15}, "-c", "c", &observerVelocity, -1.0f*C, 1.0f*C);

            currentX -= 20;
            currentY += ELEMENT_SPACING;
            DrawTextEx(font, TextFormat("Observer velocity = %.2f c", observerVelocity), (Vector2){currentX, currentY - 2}, TEXT_FONT_SIZE, LETTER_SPACING, TEXT_COLOR);

            currentY += 20;
            DrawTextEx(font, TextFormat("Gamma = %.2f", GetGamma(observerVelocity)), (Vector2){currentX, currentY - 2}, TEXT_FONT_SIZE, LETTER_SPACING, TEXT_COLOR);
            
            // Seeing coordinates checkbox
            currentY += 20;
            GuiCheckBox((Rectangle){currentX, currentY, TEXT_FONT_SIZE, TEXT_FONT_SIZE}, "See coordinates", &activeCheckBox);
            if (activeCheckBox)
            {
                mousePosition = GetMousePosition();
                if (MouseInGrid(mousePosition, globeWidth, globeHeight))
                {
                    DrawTextEx(
                        font,
                        TextFormat("(%.2f, %.2f)", ScreenToWorldX(mousePosition.x, globeWidth/2), ScreenToWorldY(mousePosition.y, globeHeight/2)),
                        (Vector2){mousePosition.x + 5, mousePosition.y - 20},
                        TEXT_FONT_SIZE,
                        LETTER_SPACING,
                        TEXT_COLOR
                    );
                }
            }
            
            // Event adding
            currentX = left_margin;
            currentY += PANEL_BLOCKS_SPACING;

            GuiLine((Rectangle){currentX, currentY, panelWidth - 50, 10}, "Add an event");
            currentY += TITLE_BOTTOM_MARGIN;

            addingEventMode = false;
            GuiToggleGroup((Rectangle){currentX, currentY, EVENT_BUTTON_WIDTH, EVENT_BUTTON_HEIGHT}, "Red;Blue;Green", &activeEventToggle);
            if (activeEventToggle > -1)
            {
                addingEventMode = true;
                colorIndex = activeEventToggle;
            }


            // Rod adding
            currentX = left_margin;
            currentY += PANEL_BLOCKS_SPACING;

            GuiLine((Rectangle){currentX, currentY, panelWidth - 50, 10}, "Add a rod");
            currentY += TITLE_BOTTOM_MARGIN;

            GuiToggleGroup((Rectangle){currentX, currentY, EVENT_BUTTON_WIDTH, EVENT_BUTTON_HEIGHT}, "Red;Blue;Green", &activeRodToggle);
            if (activeRodToggle > -1)
            {
                addingRodModeStep1 = true;
                addingRodModeStep2 = false;
                colorIndex = activeRodToggle;
            }

            
            // Clear all button
            currentX = left_margin;
            currentY += EVENT_BUTTON_HEIGHT + 20;
            if (GuiButton((Rectangle){currentX, currentY, 200, 30}, "Clear all"))
            {
                eventsList.clear();
                rodsList.clear();
            }
            

            // Modes

            // TO DO: Make the modes exclusives (one mode at a time)

            // Drag and drop
            draggingMode = false;
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                mousePosition = GetMousePosition();
                for (int i = 0; i < eventsList.size(); i++)
                {
                    // Get event coordinates in the current OBSERVER's frame
                    Event eventObs = LorentzTransform(eventsList[i], observerVelocity);

                    // Get the screen coordinates of that event
                    Vector2 eventScreenCoordinates = (Vector2)
                    {
                        WorldToScreenX(eventObs.getX(), globeWidth/2),
                        WorldToScreenY(eventObs.getT(), globeHeight/2)
                    };

                    if (CheckCollisionPointCircle(mousePosition, eventScreenCoordinates, EVENT_RADIUS + 20))
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
                GuiStatusBar((Rectangle){ 24, 24, 160, 40 }, "#191#Dragging mode");
                
                // Get event new coordinates (in the observer's frame)
                mousePosition = GetMousePosition();
                float xObs = ScreenToWorldX(mousePosition.x, globeWidth/2);
                float tObs = ScreenToWorldY(mousePosition.y, globeHeight/2);

                // Transform coordinates back to LAB's frame
                Event updatedEvent = LorentzTransform(Event(xObs, tObs, BLACK), -observerVelocity);

                // Update event
                eventsList[eventDraggedIndex].setX(updatedEvent.getX());
                eventsList[eventDraggedIndex].setT(updatedEvent.getT());
            }


            // Add an event
            if (addingEventMode)
            {
                GuiStatusBar((Rectangle){ 24, 24, 260, 40 }, "#191#Adding an event [SPACE to cancel]");
                if (IsKeyPressed(KEY_SPACE))
                {
                    activeEventToggle = -1;
                }
                else
                {
                    mousePosition = GetMousePosition();
                    if (MouseInGrid(mousePosition, globeWidth, globeHeight))
                    {
                        // Draw shadow event
                        DrawCircleV(GetMousePosition(), EVENT_RADIUS, eventColorList[colorIndex][1]);

                        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                        {
                            // Get the coordiantes of the event in the LAB's frame. The LAB moves at -observerVelocity relative to the OBSERVER.
                            Event e = LorentzTransform(Event(ScreenToWorldX(mousePosition.x, globeWidth/2), ScreenToWorldY(mousePosition.y, globeHeight/2), BLACK), -observerVelocity);
                            
                            // Add the event to event list
                            eventsList.push_back(
                                Event(
                                    e.getX(),
                                    e.getT(),
                                    eventColorList[colorIndex][0]
                                )
                            );
                            activeEventToggle = -1;
                        }
                    }
                }
            }

            // Add a rod
            if (addingRodModeStep1)
            {
                GuiStatusBar((Rectangle){ 24, 24, 260, 40 }, "#191# Adding a rod (1) [SPACE to cancel]");
                if (IsKeyPressed(KEY_SPACE))
                {
                    addingRodModeStep1 = false;
                    activeRodToggle = -1;
                }
                else
                {
                    mousePosition = GetMousePosition();
                    if (MouseInGrid(mousePosition, globeWidth, globeHeight))
                    {
                        // Draw the tip shadow
                        DrawLineEx(
                            mousePosition,
                            (Vector2){mousePosition.x + 2.0f, mousePosition.y},
                            EVENT_RADIUS,
                            eventColorList[colorIndex][1]
                        );

                        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                        {
                            // Get the tip screen coordinates
                            tipPosition = GetMousePosition();

                            // Create an event for the tip (in the LAB's frame)
                            tipEvent = LorentzTransform(
                                Event(ScreenToWorldX(tipPosition.x, globeWidth/2), ScreenToWorldY(tipPosition.y, globeHeight/2), eventColorList[colorIndex][0]),
                                -observerVelocity
                            );

                            addingRodModeStep1 = false;
                            addingRodModeStep2 = true;
                            activeRodToggle = -1;  // This makes sure we don't come back to addingRodModeStep1 again
                        }
                    }
                }
            }

            if (addingRodModeStep2)
            {
                GuiStatusBar((Rectangle){ 24, 24, 260, 40 }, "#191# Adding a rod (2) [SPACE to cancel]");
                if (IsKeyPressed(KEY_SPACE))
                {
                    addingRodModeStep2 = false;
                    activeRodToggle = -1;
                }
                else
                {
                    mousePosition = GetMousePosition();
                    if (MouseInGrid(mousePosition, globeWidth, globeHeight))
                    {
                        // Draw shadow rod
                        DrawLineEx(
                            tipPosition,
                            (Vector2){mousePosition.x, tipPosition.y},
                            EVENT_RADIUS,
                            eventColorList[colorIndex][1]
                        );

                        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
                        {
                            // Get tail position
                            tailPosition = GetMousePosition();

                            // Create an event for the tail (in the LAB's frame)
                            tailEvent = LorentzTransform(
                                Event(ScreenToWorldX(tailPosition.x, globeWidth/2), ScreenToWorldY(tailPosition.y, globeHeight/2), eventColorList[colorIndex][0]),
                                -observerVelocity
                            );

                            // Add the rod to the list
                            rodsList.push_back(Rod(tipEvent, tailEvent, eventColorList[colorIndex][0]));

                            addingRodModeStep2 = false;
                        }
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

            // Draw rods
            for (Rod r: rodsList)
            {
                Event tipPrime = LorentzTransform(r.getTipEvent(), observerVelocity);  // tip coordinates in the OBSERVER' frame
                Event tail = r.getTailEvent(); // 
                float gamma = GetGamma(observerVelocity);

                DrawLineEx(
                    (Vector2){WorldToScreenX(tipPrime.getX(), globeWidth/2), WorldToScreenY(tipPrime.getT(), globeHeight/2)},
                    (Vector2){WorldToScreenX(-observerVelocity * tipPrime.getT() + tail.getX()/gamma, globeWidth/2), WorldToScreenY(tipPrime.getT(), globeHeight/2)},
                    EVENT_RADIUS,
                    r.getColor()
                );
            }

            GuiStatusBar((Rectangle){ 24, 24 + globeHeight, 250, 40 }, TextFormat("%i", eventsList.size() + rodsList.size()));

        EndDrawing();
    }

    CloseWindow();
    return 0;
}


float GetGamma(float observerVelocity)
{
    return 1 / (sqrt(1.0f - pow(observerVelocity/C, 2)));
}

Event LorentzTransform(Event point, float observerVelocity)
{
    float gamma = GetGamma(observerVelocity);
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