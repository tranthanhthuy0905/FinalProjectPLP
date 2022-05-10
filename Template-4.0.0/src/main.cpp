#include "raylib.h"
#include <vector>
#include <string>
using namespace std;

// #define - declare the constant values in combination of identifier and token string

// Define window's setup values
#define windowWidth 1200
#define windowHeight 800

#define minWindowWidth 800
#define minWindowHeight 500

// Define actions' states
#define UNSORTED 0
#define SORTED 1
#define SELECTED 2

// Frames per second
#define FPS 120

// Declare the variables
int sortingSize = 50; // no of pillars
int sortingSpeed = 60;

// Boolean values to navigate actions
bool ToRandomizeArr = false;
bool ToShowMenu = true;
bool ToShowStartOpt = false;
bool ToStartSorting = false;
bool ToEndSorting = false;

// Boolean states to display algorithms
bool btnPressed = false;
bool addSpeed = false;
bool subSpeed = false;
bool addSize = false;
bool subSize = false;

bool normalSize = false;
bool normalSpeed = false;

bool ToMuteSound = false;

// Sorting algorithms
void Bubble_Sort(std::vector<std::pair<int, int>> &arr);

// Screens
void ShowMenu();
void ShowStartOpt();
void EndSorting();

// Buttons
void Button(float x, float y, char *Text, Color color, bool &state);
void start_btn();

void Bubble_Sort_Button();

// Logical Functions
void SortArray();
void DrawArray(vector<pair<int, int>> arr);
void RandomizeArr(vector<pair<int, int>> arr);

// Navigating Actions
void ChangeSpeed();
void ChangeSize();

// Set up colors
Color fillColor(int actionStates);
Color Beige{249, 246, 239, 225};
Color DARKRED{152, 20, 15, 225};

vector<pair<int, int>> arr(sortingSize);

// const audio var
const char *PLAYSOUNDICON = "./assets/Image/volume.png";
const char *MUTESOUNDICON = "./assets/Image/mute.png";
const char *BACKGROUNDSOUND = "./assets/Sound/Lofi_Fruits_Music_Gaming_Lofi.mp3";

int main()
{
    // auto file = LoadFileData("./data/Module 6 - Data Practice copy.xlsx");
    // std::cout << file << std::endl;

    // Windowm Configuration:
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(windowWidth, windowHeight, "C++ Sorting Algorithm Visualization - Tran Thanh Thuy");
    SetWindowMinSize(minWindowWidth, minWindowHeight);

    InitAudioDevice();

    // Set FPS
    SetTargetFPS(FPS);

    // Set up sound options
    Image SoundIcon = LoadImage(PLAYSOUNDICON);
    ImageResize(&SoundIcon, 30, 30);

    Texture2D texture = LoadTextureFromImage(SoundIcon);

    Sound initialSound = LoadSound(BACKGROUNDSOUND);

    // Check if running program (NOT pressing Esc)
    while (!WindowShouldClose())
    {
        {
            // Create the window container
            float x = ((2.0 * GetScreenWidth()) / 100);
            float y = ((2.0 * GetScreenHeight()) / 100);

            Rectangle r1 = {
                .x = x,
                .y = y,
                .width = (float)x + 20,
                .height = (float)y + 20,
            };

            // Catch the event users mute/unmute sound
            if (CheckCollisionPointRec(GetMousePosition(), r1))
                if (IsMouseButtonPressed(0))
                    ToMuteSound = !ToMuteSound;
        }

        if (ToMuteSound)
        {
            DrawTexture(texture, (2 * GetScreenWidth()) / 100, (2 * GetScreenHeight()) / 100, DARKRED);
            UnloadImage(SoundIcon);
            SoundIcon = LoadImage(MUTESOUNDICON);
            ImageResize(&SoundIcon, 30, 30);
            texture = LoadTextureFromImage(SoundIcon);
            PauseSound(initialSound);
        }
        else
        {
            DrawTexture(texture, (2 * GetScreenWidth()) / 100, (2 * GetScreenHeight()) / 100, WHITE);
            UnloadImage(SoundIcon);
            SoundIcon = LoadImage(PLAYSOUNDICON);
            ImageResize(&SoundIcon, 30, 30);
            texture = LoadTextureFromImage(SoundIcon);
            ResumeSound(initialSound);
        }

        if (!IsSoundPlaying(initialSound) && !ToMuteSound)
        {
            PlaySound(initialSound);
        }
        BeginDrawing();
        ClearBackground(Beige);

        // Show the menu screen
        if (ToShowMenu)
        {
            ShowMenu();
            ToShowStartOpt = false;
        }

        if (btnPressed)
        {
            ToShowStartOpt = true;
        }

        if (ToShowStartOpt)
        {
            ShowStartOpt();
        }

        EndDrawing();
    }
    UnloadImage(SoundIcon);
    UnloadTexture(texture);
    UnloadSound(initialSound);

    CloseAudioDevice();
    CloseWindow();
    return 0;
}

void ShowMenu()
{
    // Just to make code run
    CloseWindow();
    // Code Algorithms to be shown here
}

void ShowStartOpt()
{
    // Just to make code run
    CloseWindow();
    // Show the Sorting choices
}