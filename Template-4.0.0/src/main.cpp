// self-templated library to visualize the algorithms
#include "raylib.h"
#include <vector>

// #define - declare an identifier with token string (constant/enum val)
// substituted whenever identifier forms a token

// Set up Window
#define ScreenWidth 1200
#define ScreenHeight 800

#define MinWindowWidth 500
#define MinWindowHeight 800

// Frames per second
#define FPS 120

// Pillar States
#define UNSORTED 0
#define SORTED 1
#define SELECTED 2

// Size of the Array
int NumberOfPillars = 50;

// Sorting Speed
int SortingSpeed = 55;

// Boolean Var
bool ToRandomizeArray = true;
bool ToShowMenuScreen = true;
bool ShouldShowStartOptions = false;
bool ShouldStartSorting = false;
bool ShouldShowEndingScreen = false;

bool addSpeed = false;
bool subSpeed = false;
bool addSize = false;
bool subSize = false;

bool UnsortedSize = false;
bool UnsortedSpeed = false;

bool MuteSound = false;

// Sorting:
void Bubble_Sort(std::vector<std::pair<int, int>> &arr);

// Screens:
void ShowMenuScreen();
void ShowStartOptions();
void ShowEndingScreen();

void Start_Button(float size, float font, char Start[]);
void Button(float x, float y, char *Text, Color color, bool &state);
void Selection_Sort_Button(float size, char Selection_Sort_Text[]);
void Insertion_Sort_Button(float size, char Insertion_Sort_Text[]);
void Bubble_Sort_Button(float size, char Bubble_Sort_Text[]);
void Merge_Sort_Button(float size, char Merge_Sort_Text[]);
void Quick_Sort_Button(float size, char Quick_Sort_Text[]);

void SortArray();
void DrawArray(std::vector<std::pair<int, int>> arr);
void RandomizeArray(std::vector<std::pair<int, int>> &arr);
void Selection_Sort(std::vector<std::pair<int, int>> &arr);

void Insertion_Sort(std::vector<std::pair<int, int>> &arr);

void Bubble_Sort(std::vector<std::pair<int, int>> &arr);

void Merge_Sort(std::vector<std::pair<int, int>> &arr);
void MergeSort_Finale(std::vector<std::pair<int, int>> &arr,
                      int leftIndex, int rightIndex);
void Merge(std::vector<std::pair<int, int>> &arr,
           int leftIndex, int m, int rightIndex);

void Quick_Sort(std::vector<std::pair<int, int>> &arr);
void Quick_Sort_Final(std::vector<std::pair<int, int>> &arr, int low, int high);
int Partition(std::vector<std::pair<int, int>> &arr, int low, int high);

void ChangeSize(char operation, int &value);
void ChangeSpeed(char operation, int &value);

Color FindColorForPIller(int PillerState);
Color Beige{249, 246, 239, 225};
Color DARKRED{152, 20, 15, 225};
Color LIGHTBLUE{123, 164, 188};
Color DarkGreen{0, 105, 78};
Color DarkBlue{51, 115, 196};
Color LightOrange{248, 129, 39};
Color DarkBeige{212, 197, 180};
Color LightRED{255, 204, 1};

// The array itself:
std::vector<std::pair<int, int>> arr(NumberOfPillars);
// const audio var
const char *PLAYSOUNDICON = "./assets/Image/volume.png";
const char *MUTESOUNDICON = "./assets/Image/mute.png";
const char *BACKGROUNDSOUND = "./assets/Sound/Lofi_Fruits_Music_Gaming_Lofi.mp3";

bool SelectionSortPressed = false;
bool InsertionSortPressed = false;
bool BubbleSortPressed = false;
bool MergeSortPressed = false;
bool QuickSortPressed = false;
std::vector<bool *> SortingChoice = {
    &SelectionSortPressed,
    &InsertionSortPressed,
    &BubbleSortPressed,
    &MergeSortPressed,
    &QuickSortPressed,
};

int main()
{

    // Window Configuration:
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(ScreenWidth, ScreenHeight, "C++ Sorting Algorithm Visualization - Tran Thanh Thuy");
    SetWindowMinSize(MinWindowWidth, MinWindowHeight);

    InitAudioDevice();

    // Set FPS:
    SetTargetFPS(FPS);

    // Setting up sound options:
    Image SoundIcon = LoadImage(PLAYSOUNDICON);
    ImageResize(&SoundIcon, 30, 30);

    Texture2D texture = LoadTextureFromImage(SoundIcon);

    Sound initialSound = LoadSound(BACKGROUNDSOUND);

    while (!WindowShouldClose())
    {

        {
            float x = ((2.0 * GetScreenWidth()) / 100);
            float y = ((2.0 * GetScreenHeight()) / 100);

            Rectangle r1 = {
                .x = x,
                .y = y,
                .width = (float)x + 20,
                .height = (float)y + 20,
            };

            if (CheckCollisionPointRec(GetMousePosition(), r1))
                if (IsMouseButtonPressed(0))
                    MuteSound = !MuteSound;
        }

        if (MuteSound)
        {
            DrawTexture(texture, (2 * GetScreenWidth()) / 100,
                        (2 * GetScreenHeight()) / 100, DARKRED);

            UnloadImage(SoundIcon);
            SoundIcon = LoadImage(MUTESOUNDICON);
            ImageResize(&SoundIcon, 30, 30);
            texture = LoadTextureFromImage(SoundIcon);
            PauseSound(initialSound);
        }
        else
        {
            DrawTexture(texture, (2 * GetScreenWidth()) / 100,
                        (2 * GetScreenHeight()) / 100, WHITE);

            UnloadImage(SoundIcon);
            SoundIcon = LoadImage(PLAYSOUNDICON);
            ImageResize(&SoundIcon, 30, 30);
            texture = LoadTextureFromImage(SoundIcon);
            ResumeSound(initialSound);
        }

        if (!IsSoundPlaying(initialSound) && !MuteSound)
            PlaySound(initialSound);

        BeginDrawing();

        ClearBackground(Beige);

        if (ToShowMenuScreen)
            ShowMenuScreen();

        ShouldShowStartOptions = false;
        for (bool *i : SortingChoice)
        {
            if (*i == true)
                ShouldShowStartOptions = true;
        }

        if (ShouldShowStartOptions)
            ShowStartOptions();

        if (ToRandomizeArray)
            RandomizeArray(arr);

        if (ShouldStartSorting)
        {
            ToShowMenuScreen = false;
            ShouldShowStartOptions = false;

            SortArray();

            ShouldStartSorting = false;
            ShouldShowEndingScreen = true;
        }

        if (ShouldShowEndingScreen)
            ShowEndingScreen();

        EndDrawing();
    }

    UnloadImage(SoundIcon);
    UnloadTexture(texture);
    UnloadSound(initialSound);

    CloseAudioDevice();

    CloseWindow();

    return 0;
}

// Drawing the pillers:
void DrawArray(std::vector<std::pair<int, int>> arr)
{
    float BarWidth = (float)GetScreenWidth() / NumberOfPillars;

    for (int i = 0; i < NumberOfPillars; i++)
    {
        Color color = FindColorForPIller(arr[i].second);

        DrawRectangleV(Vector2{(float)i * BarWidth, (float)GetScreenHeight() - arr[i].first},
                       Vector2{BarWidth, (float)arr[i].first},
                       color);
    }
}

// Randomizing The Array:
void RandomizeArray(std::vector<std::pair<int, int>> &arr)
{
    for (int i = 0; i < NumberOfPillars; i++)
        arr[i] = {GetRandomValue(40, MinWindowWidth - 80), UNSORTED};

    ToRandomizeArray = false;

    return;
}

void ShowMenuScreen()
{
    float font = (2.5 * GetScreenWidth()) / 100;
    char Selection_Sort_text[] = "Selection Sort!";
    float tmp = (GetScreenWidth() * 5) / 100;
    // Selection_Sort_Button(tmp, Selection_Sort_text);

    char Insertion_Sort_Text[] = "Insertion Sort!";
    tmp += MeasureText(Selection_Sort_text, font) + font;
    Insertion_Sort_Button(tmp, Insertion_Sort_Text);

    char Bubble_Sort_Text[] = "Bubble Sort!";
    tmp += MeasureText(Insertion_Sort_Text, font) + font;
    Bubble_Sort_Button(tmp, Bubble_Sort_Text);

    char Merge_Sort_Text[] = "Merge Sort!";
    tmp += MeasureText(Bubble_Sort_Text, font) + font;
    Merge_Sort_Button(tmp, Merge_Sort_Text);

    char Quick_Sort_text[] = "Quick Sort!";
    tmp += MeasureText(Merge_Sort_Text, font) + font;
    Quick_Sort_Button(tmp, Quick_Sort_text);

    DrawArray(arr);
}

void ShowStartOptions()
{
    float font = (2.5 * GetScreenWidth() / 100);

    char StartText[] = "Start Sorting!";
    float tmp = (27 * GetScreenWidth()) / 100;
    Start_Button(tmp, font, StartText);

    tmp += MeasureText(StartText, font) + 75;
    char RandomizeArrayText[] = "Randomize Array!";
    Button(tmp, GetScreenHeight() / 20 + font * 2,
           RandomizeArrayText, DARKGRAY, ToRandomizeArray);

    addSpeed = false;
    subSpeed = false;
    addSize = false;
    subSize = false;

    UnsortedSize = false;
    UnsortedSpeed = false;

    tmp = (84.2 * GetScreenWidth()) / 100;
    char TimeButtonText[] = "Speed";

    Button(tmp, GetScreenHeight() / 20 + font * 2,
           TimeButtonText, DARKRED, UnsortedSpeed);

    if (UnsortedSpeed)
    {
        ChangeSpeed('/', SortingSpeed);
        return;
    }

    tmp += MeasureText(TimeButtonText, font) + 20;
    char SpeedPlusButtonText[] = "+";
    Button(tmp, GetScreenHeight() / 20 + font * 2,
           SpeedPlusButtonText, DARKRED, addSpeed);

    if (addSpeed)
    {
        ChangeSpeed('+', SortingSpeed);
        return;
    }

    tmp += MeasureText(SpeedPlusButtonText, font) + 20;
    char SpeedMinusButtonText[] = "-";
    Button(tmp, GetScreenHeight() / 20 + font * 2,
           SpeedMinusButtonText, DARKRED, subSpeed);

    if (subSpeed)
    {
        ChangeSpeed('-', SortingSpeed);
        return;
    }

    tmp = (5 * GetScreenWidth()) / 100;
    char SizeButtonText[] = "Size";
    Button(tmp, GetScreenHeight() / 20 + font * 2,
           SizeButtonText, DARKRED, UnsortedSize);

    if (UnsortedSize)
    {
        ChangeSize('/', NumberOfPillars);
        return;
    }

    tmp += MeasureText(SizeButtonText, font) + 20;
    char SizePlusButton[] = "+";
    Button(tmp, GetScreenHeight() / 20 + font * 2,
           SizePlusButton, DARKRED, addSize);

    if (addSize)
    {
        ChangeSize('+', NumberOfPillars);
        return;
    }

    tmp += MeasureText(SizePlusButton, font) + 20;
    char SizeMinusButton[] = "-";
    Button(tmp, GetScreenHeight() / 20 + font * 2,
           SizeMinusButton, DARKRED, subSize);

    if (subSize)
    {
        ChangeSize('-', NumberOfPillars);
        return;
    }
}

void ShowEndingScreen()
{
    DrawArray(arr);

    ToShowMenuScreen = true;
    ShouldShowStartOptions = false;
}

void ChangeSpeed(char operation, int &value)
{

    switch (operation)
    {
    case '-':
        value = value - 10 > 0 ? value - 10 : value;
        break;

    case '+':
        value += 10;

    default:
        value = 61;
        break;
    }

    SetTargetFPS(SortingSpeed);
}

void ChangeSize(char operation, int &value)
{
    switch (operation)
    {
    case '-':
        if (value > 5)
        {
            value -= 5;
            for (int i = 0; i < 5; i++)
                arr.pop_back();
        }
        break;

    case '+':
        value += 5;
        for (int i = 0; i < 5; i++)
            arr.push_back({GetRandomValue(40, MinWindowWidth - 80), UNSORTED});
        break;

    default:
        while (NumberOfPillars > 50)
        {
            NumberOfPillars--;
            arr.pop_back();
        }

        while (NumberOfPillars < 50)
        {
            NumberOfPillars++;
            arr.push_back({GetRandomValue(40, MinWindowWidth - 80), UNSORTED});
        }
        break;
    }

    for (int i = 0; i < NumberOfPillars; i++)
        arr[i].second = UNSORTED;

    DrawArray(arr);
}

void Bubble_Sort_Button(float size, char Bubble_Sort_text[])
{
    Color color;
    if (BubbleSortPressed)
        color = BLUE;
    else
        color = GREEN;

    Button(GetScreenWidth() / 2 - size, GetScreenHeight() / 20, Bubble_Sort_text, color, BubbleSortPressed);
}

void Selection_Sort_Button(float size, char Selection_Sort_Text[])
{
    Color color;
    if (SelectionSortPressed)
        color = BLUE;
    else
        color = GREEN;

    Button(size, GetScreenHeight() / 20, Selection_Sort_Text, color,
           SelectionSortPressed);
}

void Insertion_Sort_Button(float size, char Insertion_Sort_Text[])
{
    Color color;
    if (InsertionSortPressed)
        color = BLUE;
    else
        color = GREEN;

    Button(size, GetScreenHeight() / 20, Insertion_Sort_Text, color,
           InsertionSortPressed);
}

void Merge_Sort_Button(float size, char Merge_Sort_Text[])
{
    Color color;
    if (MergeSortPressed)
        color = BLUE;
    else
        color = GREEN;

    Button(size, GetScreenHeight() / 20, Merge_Sort_Text, color,
           MergeSortPressed);
}

void Quick_Sort_Button(float size, char Quick_Sort_Text[])
{
    Color color;
    if (QuickSortPressed)
        color = BLUE;
    else
        color = GREEN;

    Button(size, GetScreenHeight() / 20, Quick_Sort_Text, color,
           QuickSortPressed);
}
void Start_Button(float size, float font, char Start[])
{
    Button(size, GetScreenHeight() / 20 + font * 2,
           Start, DARKGRAY, ShouldStartSorting);

    return;
}

Color FindColorForPIller(int pillerState)
{
    switch (pillerState)
    {
    case SELECTED:
        return SKYBLUE;
        break;

    case SORTED:
        return DARKGREEN;
        break;

    default:
        return GRAY;
        break;
    }
}

void SortArray()
{
    Bubble_Sort(arr);

    DrawArray(arr);
}

// Bubble Sort:
void Bubble_Sort(std::vector<std::pair<int, int>> &arr)
{

    int endingPoint = NumberOfPillars;

    bool swapped;
    do
    {
        swapped = false;

        for (int i = 0; i < endingPoint - 1; i++)
        {

            arr[i].second = SELECTED;

            if (arr[i] > arr[i + 1])
            {

                std::swap(arr[i], arr[i + 1]);

                swapped = true;
            }

            BeginDrawing();

            ClearBackground(Beige);

            for (int k = NumberOfPillars - 1; k >= endingPoint; k--)
                arr[k].second = SORTED;

            DrawArray(arr);

            for (int k = i; k >= 0; k--)
                arr[k].second = UNSORTED;

            EndDrawing();
        }

        endingPoint--;
    } while (swapped);

    for (int i = NumberOfPillars - 1; i >= 0; i--)
        arr[i].second = SORTED;
}

void Button(float x, float y, char *Text, Color color, bool &state)
{
    float font = (2.5 * GetScreenWidth() / 100);
    Rectangle r1 = {
        .x = x,
        .y = y,
        .width = (float)MeasureText(Text, font),
        .height = (float)font,
    };

    if (CheckCollisionPointRec(GetMousePosition(), r1))
    {
        DrawText(Text, x, y, font, RED);

        if (IsMouseButtonPressed(0))
        {

            if (state == true)
                state = false;
            else
                state = true;

            return;
        }
    }
    else
    {
        DrawText(Text, x, y, font, color);
    }

    return;
}
