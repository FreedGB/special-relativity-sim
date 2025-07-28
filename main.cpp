#include <vector>
#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "style_rltech.h"
#include "style_genesis.h"

// Global constants
#define MARGIN 30.0f
#define BORDER_THICKNESS 2.0f
#define AXE_THICKNESS 2.0f
#define GRID_THICKNESS 1.0f
#define SECONDARY_GRID_THICKNESS 1.0f
#define GRID_SPACING 50.0f
#define C 1.0f
#define EVENT_RADIUS 10.0f
#define EVENT_BUTTON_HEIGHT 20.0f
#define EVENT_BUTTON_WIDTH 60.0f
#define TEXT_FONT_SIZE 16.0f

// Colors
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

        void set_x(float x) { this->x = x; }
        void set_t(float t) { this->t = t; }
        float get_x() { return this->x; }
        float get_t() { return this->t; }
        Color get_color() { return this->color; }
};

// Rod class
class Rod
{
    Event tip_event;
    Event tail_event;
    Color color;

    public:
        Rod(Event tip_event, Event tail_event, Color color)
        {
            this->tip_event = tip_event;
            this->tail_event = tail_event;
            this->color = color;
        }

        Event get_tip_event() {return this->tip_event;}
        Event get_tail_event() {return this->tail_event;}
        Color get_color() {return this->color;}
};

// Custom Functions
float get_gamma(float observer_velocity);
Event lorentz_transform(Event point, float observer_velocity);
float world_to_screen_x(float world_x, int offset_x);
float world_to_screen_y(float world_y, int offset_y);
float screen_to_world_x(float screen_x, int offset_x);
float screen_to_world_y(float screen_y, int offset_y);
bool mouse_in_grid(Vector2 mouse, float globe_width, float globe_height);

int main()
{
    // Game definitions
    InitWindow(1000, 500, "SPACETIME GLOBE SIMULATION");
    SetTargetFPS(60);

    float globe_width;
    float globe_height;
    float panel_width;
    float panel_height;
    float observer_velocity = 0.0f;
    float current_x;
    float current_y;
    std::vector<Event> events_list; // Stores the events coordinates in the LAB's frame
    std::vector<Rod> rods_list;
    bool dragging_mode;
    bool adding_event_mode;
    bool adding_rod_mode_step_1 = false;
    bool adding_rod_mode_step_2 = false;
    int color_index;
    Vector2 mouse_position;
    int event_dragged_index;
    int active_event_toggle = -1;
    int active_rod_toggle = -1;
    bool show_coordinates = false;
    bool show_nb_elements = true;
    Vector2 tip_position;
    Vector2 tail_position;
    Event tip_event;
    Event tail_event;
    int current_theme = 0;
    int previous_theme = 0;
    Font font;
    Color text_color;
    Color grid_color;
    Color secondary_grid_color;

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
    std::vector<std::vector<Color>> colors_list = {
        {MAIN_RED, SECONDARY_RED},
        {MAIN_BLUE, SECONDARY_BLUE},
        {MAIN_GREEN, SECONDARY_GREEN}
    };

    // Set RLTech theme as default
    font = LoadFont("rltech.ttf");
    GuiLoadStyleRLTech();
    GuiSetFont(font);
    text_color = GetColor(GuiGetStyle(DEFAULT, TEXT_COLOR_NORMAL));
    grid_color = GetColor(GuiGetStyle(DEFAULT, BORDER_COLOR_NORMAL));
    secondary_grid_color = GetColor(GuiGetStyle(DEFAULT, BORDER_COLOR_DISABLED));

    // Game loop
    while (!WindowShouldClose())
    {   
        // Update globe and panel sizes
        globe_width = (2 * GetScreenWidth())/3 - 2 * MARGIN;
        globe_height = GetScreenHeight() - 2 * MARGIN;
        panel_width = GetScreenWidth()/3 - MARGIN;
        panel_height = globe_height;

        // Update theme
        if (previous_theme != current_theme)
        {
            GuiLoadStyleDefault(); // Unloads previous style

            switch (current_theme)
            {
                case 0:
                    GuiLoadStyleRLTech();
                    font = LoadFont("rltech.ttf");
                    break;
                case 1:
                    GuiLoadStyleGenesis();
                    font = LoadFont("genesis.ttf");
                    break;
                default: break;
            }
            GuiSetFont(font);
            text_color = GetColor(GuiGetStyle(DEFAULT, TEXT_COLOR_NORMAL));
            grid_color = GetColor(GuiGetStyle(DEFAULT, BORDER_COLOR_NORMAL));
            secondary_grid_color = GetColor(GuiGetStyle(DEFAULT, BORDER_COLOR_DISABLED));
            previous_theme = current_theme;
        }

        
        BeginDrawing();
            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

            // Draw windows
            DrawRectangleLinesEx((Rectangle){MARGIN, MARGIN, globe_width, globe_height}, BORDER_THICKNESS, grid_color);
            GuiPanel((Rectangle){globe_width + 2.0f*MARGIN, MARGIN, panel_width, panel_height}, "#142#Control panel");

            
            // --- Spacetime Globe ---
            /*
                The main grid (the one always fixed) represents the frame of reference of the observer moving at v m/s relative to the lab frame.
                The secondary grid (the one which deforms) represents the lab frame viewed in the frame of the moving observer.
            */

            // Draw labels
            DrawTextEx(font, "space", (Vector2){MARGIN + globe_width - 70, MARGIN + globe_height/2 + 10}, TEXT_FONT_SIZE, 2, text_color);
            DrawTextEx(font, "time", (Vector2){MARGIN + globe_height/2 + 10, MARGIN + 10}, TEXT_FONT_SIZE, 2, text_color);
            

            // Draw LAB FRAME's axes on the OBSERVER's FRAME

            // Axes points of LAB's frame in the LAB's frame
            e0 = Event(0.0, screen_to_world_y(MARGIN, globe_height/2), BLACK);
            e1 = Event(0.0, screen_to_world_y(MARGIN + globe_height, globe_height/2), BLACK);
            e2 = Event(screen_to_world_x(MARGIN, globe_width/2), 0.0, BLACK);
            e3 = Event(screen_to_world_x(MARGIN + globe_width, globe_width/2), 0.0, BLACK);

            // Those axes' points converted in the OBSERVER's frame
            e0_obs = lorentz_transform(e0, observer_velocity);
            e1_obs = lorentz_transform(e1, observer_velocity);
            e2_obs = lorentz_transform(e2, observer_velocity);
            e3_obs = lorentz_transform(e3, observer_velocity);

            // Drawing LAB frame's axes
            DrawLineEx(
                (Vector2){world_to_screen_x(e0_obs.get_x(), globe_width/2), world_to_screen_y(e0_obs.get_t(), globe_height/2)},
                (Vector2){world_to_screen_x(e1_obs.get_x(), globe_width/2), world_to_screen_y(e1_obs.get_t(), globe_height/2)},
                SECONDARY_GRID_THICKNESS,
                secondary_grid_color
            );
            DrawLineEx(
                (Vector2){world_to_screen_x(e2_obs.get_x(), globe_width/2), world_to_screen_y(e2_obs.get_t(), globe_height/2)},
                (Vector2){world_to_screen_x(e3_obs.get_x(), globe_width/2), world_to_screen_y(e3_obs.get_t(), globe_height/2)},
                SECONDARY_GRID_THICKNESS,
                secondary_grid_color
            );

            // Draw OBSERVER frame's axes
            DrawLineEx(
                (Vector2){MARGIN + globe_width/2, MARGIN},
                (Vector2){MARGIN + globe_width/2, MARGIN + globe_height},
                AXE_THICKNESS,
                grid_color
            );
            DrawLineEx(
                (Vector2){MARGIN, MARGIN + globe_height/2},
                (Vector2){MARGIN + globe_width, MARGIN + globe_height/2},
                AXE_THICKNESS,
                grid_color
            );

            // Draw the 4 arrows
            // The order here matters, but I don't understand the logic. I just tried testing different orders
            DrawTriangle(
                (Vector2){MARGIN + globe_width/2, MARGIN},
                (Vector2){MARGIN + globe_width/2 - 10.0f, MARGIN + 15.0f},
                (Vector2){MARGIN + globe_width/2 + 10.0f, MARGIN + 15.0f},
                grid_color
            );
            DrawTriangle(
                (Vector2){MARGIN + globe_width/2 - 10.0f, MARGIN + globe_height - 15.0f},
                (Vector2){MARGIN + globe_width/2, MARGIN + globe_height},
                (Vector2){MARGIN + globe_width/2 + 10.0f, MARGIN + globe_height - 15.0f},
                grid_color
            );
            DrawTriangle(
                (Vector2){MARGIN + 15.0f, MARGIN + globe_height/2 - 10.0f},
                (Vector2){MARGIN, MARGIN + globe_height/2},
                (Vector2){MARGIN + 15.0f, MARGIN + globe_height/2 + 10.0f},
                grid_color
            );
            DrawTriangle(
                (Vector2){MARGIN + globe_width, MARGIN + globe_height/2},
                (Vector2){MARGIN + globe_width - 15.0f, MARGIN + globe_height/2 - 10.0f},
                (Vector2){MARGIN + globe_width - 15.0f, MARGIN + globe_height/2 + 10.0f},
                grid_color
            );


            // Drawing frames' vertical lines
            int s = globe_width / GRID_SPACING;
            for (int i = 1; i <= s/2; i++)
            {   
                // Vertical lines of the OBSERVER's frame (they coincide with LAB's frame at v = 0)
                p_obs_1 = Event(-i, screen_to_world_y(MARGIN, globe_height/2), BLACK);
                p_obs_2 = Event(-i, screen_to_world_y(MARGIN + globe_height, globe_height/2), BLACK);
                p_obs_3 = Event(i, screen_to_world_y(MARGIN, globe_height/2), BLACK);
                p_obs_4 = Event(i, screen_to_world_y(MARGIN + globe_height, globe_height/2), BLACK);
                
                // Vertical lines of the LAB's frame viewed in the OBSERVER's frame
                p_lab_1 = lorentz_transform(p_obs_1, observer_velocity);
                p_lab_2 = lorentz_transform(p_obs_2, observer_velocity);
                p_lab_3 = lorentz_transform(p_obs_3, observer_velocity);
                p_lab_4 = lorentz_transform(p_obs_4, observer_velocity);

                // Drawing LAB's frame vertical lines
                DrawLineEx(
                    (Vector2){world_to_screen_x(p_lab_1.get_x(), globe_width/2), world_to_screen_y(p_lab_1.get_t(), globe_height/2)},
                    (Vector2){world_to_screen_x(p_lab_2.get_x(), globe_width/2), world_to_screen_y(p_lab_2.get_t(), globe_height/2)},
                    SECONDARY_GRID_THICKNESS,
                    secondary_grid_color
                );
                DrawLineEx(
                    (Vector2){world_to_screen_x(p_lab_3.get_x(), globe_width/2), world_to_screen_y(p_lab_3.get_t(), globe_height/2)},
                    (Vector2){world_to_screen_x(p_lab_4.get_x(), globe_width/2), world_to_screen_y(p_lab_4.get_t(), globe_height/2)},
                    SECONDARY_GRID_THICKNESS,
                    secondary_grid_color
                );


                // Drawing OBSERVER's frame vertical lines
                DrawLineEx(
                    (Vector2){world_to_screen_x(p_obs_1.get_x(), globe_width/2), world_to_screen_y(p_obs_1.get_t(), globe_height/2)},
                    (Vector2){world_to_screen_x(p_obs_2.get_x(), globe_width/2), world_to_screen_y(p_obs_2.get_t(), globe_height/2)},
                    GRID_THICKNESS,
                    grid_color
                );
                DrawLineEx(
                    (Vector2){world_to_screen_x(p_obs_3.get_x(), globe_width/2), world_to_screen_y(p_obs_3.get_t(), globe_height/2)},
                    (Vector2){world_to_screen_x(p_obs_4.get_x(), globe_width/2), world_to_screen_y(p_obs_4.get_t(), globe_height/2)},
                    GRID_THICKNESS,
                    grid_color
                );

            }

            
            // Drawing frames' horizontal lines
            int t = globe_height / GRID_SPACING;
            for (int i = 1; i <= t/2; i++)
            {
                // Horizontal lines of the OBSERVER's frame (they coincide with LAB's frame at v = 0)
                p_obs_1 = Event(screen_to_world_x(MARGIN, globe_width/2), -i, BLACK);
                p_obs_2 = Event(screen_to_world_x(MARGIN + globe_width, globe_width/2), -i, BLACK);
                p_obs_3 = Event(screen_to_world_x(MARGIN, globe_width/2), i, BLACK);
                p_obs_4 = Event(screen_to_world_x(MARGIN + globe_width, globe_width/2), i, BLACK);

                // Horizontal lines of the LAB's frame viewed on the OBSERVER's frame
                p_lab_1 = lorentz_transform(p_obs_1, observer_velocity);
                p_lab_2 = lorentz_transform(p_obs_2, observer_velocity);
                p_lab_3 = lorentz_transform(p_obs_3, observer_velocity);
                p_lab_4 = lorentz_transform(p_obs_4, observer_velocity);

                // Drawing LAB's frame horizontal lines
                DrawLineEx(
                    (Vector2){world_to_screen_x(p_lab_1.get_x(), globe_width/2), world_to_screen_y(p_lab_1.get_t(), globe_height/2)},
                    (Vector2){world_to_screen_x(p_lab_2.get_x(), globe_width/2), world_to_screen_y(p_lab_2.get_t(), globe_height/2)},
                    SECONDARY_GRID_THICKNESS,
                    secondary_grid_color
                );
                DrawLineEx(
                    (Vector2){world_to_screen_x(p_lab_3.get_x(), globe_width/2), world_to_screen_y(p_lab_3.get_t(), globe_height/2)},
                    (Vector2){world_to_screen_x(p_lab_4.get_x(), globe_width/2), world_to_screen_y(p_lab_4.get_t(), globe_height/2)},
                    SECONDARY_GRID_THICKNESS,
                    secondary_grid_color
                );


                // Drawing OBSERVER's frame horizontal lines
                DrawLineEx(
                    (Vector2){world_to_screen_x(p_obs_1.get_x(), globe_width/2), world_to_screen_y(p_obs_1.get_t(), globe_height/2)},
                    (Vector2){world_to_screen_x(p_obs_2.get_x(), globe_width/2), world_to_screen_y(p_obs_2.get_t(), globe_height/2)},
                    GRID_THICKNESS,
                    grid_color
                );
                DrawLineEx(
                    (Vector2){world_to_screen_x(p_obs_3.get_x(), globe_width/2), world_to_screen_y(p_obs_3.get_t(), globe_height/2)},
                    (Vector2){world_to_screen_x(p_obs_4.get_x(), globe_width/2), world_to_screen_y(p_obs_4.get_t(), globe_height/2)},
                    GRID_THICKNESS,
                    grid_color
                );
            }


            // --- Control panel ---
            float left_margin = globe_width + 2*MARGIN + 15;
            current_y = MARGIN + 40;

            // Observer frame info
            current_x = left_margin;
            GuiLine((Rectangle){current_x, current_y, panel_width - 50, 10}, "Observer frame info");

            current_y += TITLE_BOTTOM_MARGIN;
            current_x += 26;
            GuiSlider((Rectangle){current_x, current_y, panel_width - 100, 15}, "-c", "c", &observer_velocity, -1.0f*C, 1.0f*C);

            current_x -= 20;
            current_y += ELEMENT_SPACING;
            DrawTextEx(font, TextFormat("Observer velocity = %.2f c", observer_velocity), (Vector2){current_x, current_y - 2}, TEXT_FONT_SIZE, LETTER_SPACING, text_color);

            current_y += 20;
            DrawTextEx(font, TextFormat("Gamma = %.2f", get_gamma(observer_velocity)), (Vector2){current_x, current_y - 2}, TEXT_FONT_SIZE, LETTER_SPACING, text_color);
            
            // See coordinates checkbox
            current_y += 20;
            GuiCheckBox((Rectangle){current_x, current_y, TEXT_FONT_SIZE, TEXT_FONT_SIZE}, "See coordinates", &show_coordinates);
            if (show_coordinates)
            {
                mouse_position = GetMousePosition();
                if (mouse_in_grid(mouse_position, globe_width, globe_height))
                {
                    DrawTextEx(
                        font,
                        TextFormat("(%.2f, %.2f)", screen_to_world_x(mouse_position.x, globe_width/2), screen_to_world_y(mouse_position.y, globe_height/2)),
                        (Vector2){mouse_position.x + 5, mouse_position.y - 20},
                        TEXT_FONT_SIZE,
                        LETTER_SPACING,
                        text_color
                    );
                }
            }
            
            // Elements adding
            current_x = left_margin;
            current_y += PANEL_BLOCKS_SPACING;

            GuiLine((Rectangle){current_x, current_y, panel_width - 50, 10}, "Add an element");
            current_y += TITLE_BOTTOM_MARGIN;

            // Events
            GuiGroupBox((Rectangle){current_x, current_y, panel_width - 50, EVENT_BUTTON_HEIGHT + 20}, "Events");
            current_y += 10;
            current_x += 10;
            adding_event_mode = false;
            GuiToggleGroup((Rectangle){current_x, current_y, EVENT_BUTTON_WIDTH, EVENT_BUTTON_HEIGHT}, "Red;Blue;Green", &active_event_toggle);
            if (active_event_toggle > -1)
            {
                adding_event_mode = true;
                color_index = active_event_toggle;

                // Disable other modes
                dragging_mode = false;
                adding_rod_mode_step_1 = false;
                adding_rod_mode_step_2 = false;
                active_rod_toggle = -1;
            }


            // Rods
            current_x = left_margin;
            current_y += EVENT_BUTTON_HEIGHT + 20;
            GuiGroupBox((Rectangle){current_x, current_y, panel_width - 50, EVENT_BUTTON_HEIGHT + 20}, "Rods");
            current_y += 10;
            current_x += 10;
            adding_rod_mode_step_1 = false;
            GuiToggleGroup((Rectangle){current_x, current_y, EVENT_BUTTON_WIDTH, EVENT_BUTTON_HEIGHT}, "Red;Blue;Green", &active_rod_toggle);
            if (active_rod_toggle > -1)
            {
                adding_rod_mode_step_1 = true;
                adding_rod_mode_step_2 = false;
                color_index = active_rod_toggle;

                // Disable other modes
                dragging_mode = false;
                adding_event_mode = false;
                active_event_toggle = -1;
            }

            // See info panel checkbox
            current_y += EVENT_BUTTON_HEIGHT + 20;
            GuiCheckBox((Rectangle){current_x, current_y, TEXT_FONT_SIZE, TEXT_FONT_SIZE}, "Show number of elements", &show_nb_elements);
            if (show_nb_elements)
            {
                GuiPanel((Rectangle){MARGIN, MARGIN + globe_height - 70, 150, 70 }, "Number of elements");
                DrawTextEx(font, TextFormat("Events: %i", events_list.size()), (Vector2){MARGIN + 8,  MARGIN + globe_height - 40}, TEXT_FONT_SIZE, LETTER_SPACING, text_color);
                DrawTextEx(font, TextFormat("Rods: %i", rods_list.size()), (Vector2){MARGIN + 8,  MARGIN + globe_height - 20}, TEXT_FONT_SIZE, LETTER_SPACING, text_color);
            }

            // Theme selector
            GuiComboBox((Rectangle){MARGIN + globe_width - 150, MARGIN, 150, 30}, "RLtech theme;Genesis theme", &current_theme);

            
            // Clear all button
            current_x = left_margin;
            current_y += EVENT_BUTTON_HEIGHT + 20;
            if (GuiButton((Rectangle){current_x, current_y, 200, 30}, "#143#Clear all elements"))
            {
                events_list.clear();
                rods_list.clear();
            }
            

            // Modes

            // Drag and drop
            dragging_mode = false;
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                mouse_position = GetMousePosition();
                for (int i = 0; i < events_list.size(); i++)
                {
                    // Get event coordinates in the current OBSERVER's frame
                    Event event_obs = lorentz_transform(events_list[i], observer_velocity);

                    // Get the screen coordinates of that event
                    Vector2 eventScreenCoordinates = (Vector2)
                    {
                        world_to_screen_x(event_obs.get_x(), globe_width/2),
                        world_to_screen_y(event_obs.get_t(), globe_height/2)
                    };

                    if (CheckCollisionPointCircle(mouse_position, eventScreenCoordinates, EVENT_RADIUS + 20))
                    {
                        dragging_mode = true;
                        event_dragged_index = i;

                        // Disable other modes
                        adding_event_mode = false;
                        active_event_toggle = -1;
                        adding_rod_mode_step_1 = false;
                        adding_rod_mode_step_2 = false;
                        active_rod_toggle = -1;
                        break;
                    }
                }
            }
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            {
                dragging_mode = false;
            }

            if (dragging_mode)
            {   
                GuiPanel((Rectangle){MARGIN, MARGIN, 260, 100}, "#191#Dragging ana event");
                DrawTextEx(font, "- Hold LEFT_MOUSE to move.\n- Release LEFT_MOUSE to stop.", (Vector2){MARGIN + 8, MARGIN + 40}, TEXT_FONT_SIZE, LETTER_SPACING, text_color);
                
                // Get event new coordinates (in the observer's frame)
                mouse_position = GetMousePosition();
                float x_obs = screen_to_world_x(mouse_position.x, globe_width/2);
                float t_obs = screen_to_world_y(mouse_position.y, globe_height/2);

                // Transform coordinates back to LAB's frame
                Event updated_event = lorentz_transform(Event(x_obs, t_obs, BLACK), -observer_velocity);

                // Update event
                events_list[event_dragged_index].set_x(updated_event.get_x());
                events_list[event_dragged_index].set_t(updated_event.get_t());
            }


            // Add an event
            if (adding_event_mode)
            {   
                GuiPanel((Rectangle){MARGIN, MARGIN, 260, 100}, "#191#Adding an event");
                DrawTextEx(font, "LEFT_MOUSE to place.\nSPACE to cancel.", (Vector2){MARGIN + 8, MARGIN + 40}, TEXT_FONT_SIZE, LETTER_SPACING, text_color);
                
                if (IsKeyPressed(KEY_SPACE))
                {
                    active_event_toggle = -1;
                }
                else
                {
                    mouse_position = GetMousePosition();
                    if (mouse_in_grid(mouse_position, globe_width, globe_height))
                    {
                        // Draw shadow event
                        DrawCircleV(GetMousePosition(), EVENT_RADIUS, colors_list[color_index][1]);

                        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                        {
                            // Get the coordiantes of the event in the LAB's frame. The LAB moves at -observer_velocity relative to the OBSERVER.
                            Event e = lorentz_transform(Event(screen_to_world_x(mouse_position.x, globe_width/2), screen_to_world_y(mouse_position.y, globe_height/2), BLACK), -observer_velocity);
                            
                            // Add the event to event list
                            events_list.push_back(
                                Event(
                                    e.get_x(),
                                    e.get_t(),
                                    colors_list[color_index][0]
                                )
                            );
                            active_event_toggle = -1;
                        }
                    }
                }
            }

            // Add a rod
            if (adding_rod_mode_step_1)
            {
                GuiPanel((Rectangle){MARGIN, MARGIN, 260, 100}, "#191#Adding a rod [1]");
                DrawTextEx(font, "1- LEFT_MOUSE to place the tip.\n2- RIGHT_MOUSE to place the tail.\nSPACE to cancel", (Vector2){MARGIN + 8, MARGIN + 40}, TEXT_FONT_SIZE, LETTER_SPACING, text_color);
                
                if (IsKeyPressed(KEY_SPACE))
                {
                    adding_rod_mode_step_1 = false;
                    active_rod_toggle = -1;
                }
                else
                {
                    mouse_position = GetMousePosition();
                    if (mouse_in_grid(mouse_position, globe_width, globe_height))
                    {
                        // Draw the tip shadow
                        DrawLineEx(
                            mouse_position,
                            (Vector2){mouse_position.x + 2.0f, mouse_position.y},
                            EVENT_RADIUS,
                            colors_list[color_index][1]
                        );

                        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                        {
                            // Get the tip screen coordinates
                            tip_position = GetMousePosition();

                            // Create an event for the tip (in the LAB's frame)
                            tip_event = lorentz_transform(
                                Event(screen_to_world_x(tip_position.x, globe_width/2), screen_to_world_y(tip_position.y, globe_height/2), colors_list[color_index][0]),
                                -observer_velocity
                            );

                            adding_rod_mode_step_1 = false;
                            adding_rod_mode_step_2 = true;
                            active_rod_toggle = -1;  // This makes sure we don't come back to adding_rod_mode_step_1 again
                        }
                    }
                }
            }

            if (adding_rod_mode_step_2)
            {
                GuiPanel((Rectangle){MARGIN, MARGIN, 260, 100}, "#191#Adding a rod [2]");
                DrawTextEx(font, "1- LEFT_MOUSE to place the tip.\n2- RIGHT_MOUSE to place the tail.\nSPACE to cancel", (Vector2){MARGIN + 8, MARGIN + 40}, TEXT_FONT_SIZE, LETTER_SPACING, text_color);
                if (IsKeyPressed(KEY_SPACE))
                {
                    adding_rod_mode_step_2 = false;
                    active_rod_toggle = -1;
                }
                else
                {
                    mouse_position = GetMousePosition();
                    if (mouse_in_grid(mouse_position, globe_width, globe_height))
                    {
                        // Draw shadow rod
                        DrawLineEx(
                            tip_position,
                            (Vector2){mouse_position.x, tip_position.y},
                            EVENT_RADIUS,
                            colors_list[color_index][1]
                        );

                        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
                        {
                            // Get tail position
                            tail_position = GetMousePosition();

                            // Create an event for the tail (in the LAB's frame)
                            tail_event = lorentz_transform(
                                Event(screen_to_world_x(tail_position.x, globe_width/2), screen_to_world_y(tail_position.y, globe_height/2), colors_list[color_index][0]),
                                -observer_velocity
                            );

                            // Add the rod to the list
                            rods_list.push_back(Rod(tip_event, tail_event, colors_list[color_index][0]));

                            adding_rod_mode_step_2 = false;
                        }
                    }
                }
            }
            
            // Draw events
            for (Event e: events_list)
            {
                Event ePrime = lorentz_transform(e, observer_velocity);
                DrawCircleV(
                    (Vector2) {world_to_screen_x(ePrime.get_x(), globe_width/2), world_to_screen_y(ePrime.get_t(), globe_height/2)},
                    EVENT_RADIUS,
                    ePrime.get_color()
                );
            }

            // Draw rods
            for (Rod r: rods_list)
            {
                Event tipPrime = lorentz_transform(r.get_tip_event(), observer_velocity);  // tip coordinates in the OBSERVER' frame
                Event tail = r.get_tail_event(); // tail in the LAB's frame (because of the formula used)
                float gamma = get_gamma(observer_velocity);

                // Draw contracted rod. Formula explained in README.md
                DrawLineEx(
                    (Vector2){world_to_screen_x(tipPrime.get_x(), globe_width/2), world_to_screen_y(tipPrime.get_t(), globe_height/2)},
                    (Vector2){world_to_screen_x(-observer_velocity * tipPrime.get_t() + tail.get_x()/gamma, globe_width/2), world_to_screen_y(tipPrime.get_t(), globe_height/2)},
                    EVENT_RADIUS,
                    r.get_color()
                );
            }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}


float get_gamma(float observer_velocity)
{
    return 1 / (sqrt(1.0f - pow(observer_velocity/C, 2)));
}

Event lorentz_transform(Event point, float observer_velocity)
{
    float gamma = get_gamma(observer_velocity);
    float x_prime = gamma * (point.get_x() - observer_velocity * point.get_t());
    float t_prime = gamma * (point.get_t() - (observer_velocity * point.get_x() / pow(C, 2)));
    
    return Event(x_prime, t_prime, point.get_color());
}

float world_to_screen_x(float world_x, int offset_x)
{
    return world_x * GRID_SPACING + MARGIN + offset_x;
}

float world_to_screen_y(float world_y, int offset_y)
{
    return - world_y * GRID_SPACING + MARGIN + offset_y;
}

float screen_to_world_x(float screen_x, int offset_x)
{
    return (screen_x - MARGIN - offset_x) / GRID_SPACING;
}

float screen_to_world_y(float screen_y, int offset_y)
{
    return (-screen_y + MARGIN + offset_y) / GRID_SPACING ;
}

bool mouse_in_grid(Vector2 mouse, float globe_width, float globe_height)
{
    if ((MARGIN <= mouse.x && mouse.x <= MARGIN + globe_width) && (MARGIN <= mouse.y && mouse.y <= MARGIN + globe_height))
    {
        return true;
    }
    return false;
}