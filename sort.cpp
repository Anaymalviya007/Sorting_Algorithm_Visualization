#include "raylib.h"
#include  <vector>

#define ScreenWidth 1200
#define ScreenHeight 800

#define MinWindowWidth 500
#define MinWindowHeight 800

#define FPS 120



// Piller States:
#define NORMAL 0
#define SORTED 1
#define SELECTED 2



using namespace std;

//Size of the Array
int NumberOfPillar =50;

// Sorting Speed:
int SortingSpeed = 61;

// Bools:
bool ShouldRandomizeArray = true;
bool ShouldShowMenuScreen = true;
bool BubbleSortPressed = false;
bool ShouldShowStartOption = false;
bool ShouldStartSorting = false;
bool addSpeed = false;
bool subSpeed = false;
bool addSize = false;
bool subSize = false;
bool NormalSize = false;
bool NormalSpeed = false;
bool ShouldShowEndingScreen = false;



//Screens:
void ShowMenuScreen();
void Button(float x, float y, char *Text, Color color, bool &state);
void Bubble_Sort_Button(float size, char Bubble_Sort_text[]);
void SortArray(); 
void DrawArray(vector<pair<int , int>>arr);
void RandomizeArray(vector<pair<int , int>>&arr);
void ShowStartOptions();
void ChangeSize(char operation, int &value);
void Start_Button(float size, float font, char Start[]);
void ChangeSpeed(char operation, int &value);
void Bubble_Sort(vector<pair<int, int>> &arr);
void ShowEndingScreen();
Color FindColorForPiller(int PillerState);




//The Array itself:
vector<pair<int , int >> arr(NumberOfPillar);


 
int main()
{
    //Windows Configuration:
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);  //Enable config flags for resizable window
    InitWindow(ScreenWidth,ScreenHeight," Anay's Sorting Algorithm Visualization");
    SetWindowMinSize(MinWindowWidth,MinWindowHeight);


      
    //Set FPS:   
    SetTargetFPS(FPS);


    while (!WindowShouldClose())
    {
        if (ShouldShowMenuScreen)
            ShowMenuScreen();


        ShouldShowStartOption = false;
        if (BubbleSortPressed)
            ShouldShowStartOption = true;

        if ( ShouldShowStartOption )
            ShowStartOptions();

        if(ShouldRandomizeArray)
            RandomizeArray(arr);


        if(ShouldStartSorting)
        {
            ShouldShowMenuScreen = false;
            ShouldShowStartOption = false;


            SortArray();

            ShouldStartSorting = false;
            ShouldShowEndingScreen = true;
        }

           if (ShouldShowEndingScreen)
            ShowEndingScreen();

        BeginDrawing();

        ClearBackground(BLACK);

        EndDrawing();
    }
    CloseWindow();


    return 0; 
}





//drawing the Pillers:
void DrawArray(vector<pair<int , int>>arr)
{
    float BarWidth = (float) GetScreenWidth() / NumberOfPillar;

    for (int i = 0; i < NumberOfPillar; i++)
    {
        Color color = FindColorForPiller(arr[i].second);

        DrawRectangleV(Vector2{(float) i*BarWidth, (float) GetScreenHeight()- arr[i].first},
                       Vector2{BarWidth,(float) arr[i].first},
                       color);        
    }
    
}

//for ramdome value of array
void RandomizeArray(vector<pair<int , int>> &arr)
{
    for (int i = 0 ; i < NumberOfPillar; i++)
        arr[i] = {GetRandomValue(40,MinWindowWidth - 80), NORMAL};

        ShouldRandomizeArray = false;

    return;
}


Color FindColorForPiller (int pillerState)
{
    switch (pillerState)
    {
    case SELECTED:
        return RED;
        break;
    case SORTED:
        return GREEN;
        break;
    default:
        return BLUE;
        break;
    }
}


void ShowMenuScreen()
{
    float font = (2.5 * GetScreenWidth()) / 100; //the font is 2.5% of screen and resizeable
    char Bubble_Sort_Text[] = "Bubble Sort!";
    float tmp = MeasureText(Bubble_Sort_Text,font)/2; 
    Bubble_Sort_Button(tmp, Bubble_Sort_Text);
    DrawArray(arr);

}


void Bubble_Sort_Button(float size, char Bubble_Sort_text[])
{
    Color color;
    if (BubbleSortPressed)
        color = BLUE;
    else 
        color = WHITE;

 Button(GetScreenWidth()/2-size , GetScreenHeight()/20, Bubble_Sort_text, color, BubbleSortPressed);
}




void Button(float x, float y, char *Text, Color color, bool &state)
{
    float font = (2.5 * GetScreenWidth() / 100);
    Rectangle r1 = {
        .x = x,
        .y = y,
        .width = (float) MeasureText(Text, font),
        .height = (float) font,
    };
 if (CheckCollisionPointRec(GetMousePosition(), r1))
 {
        DrawText(Text, x, y, font, RED);

        if (IsMouseButtonPressed(0)){

            if (state == true)
                state = false;
            else
                state = true;


            return;
        }
    } else {
        DrawText(Text, x, y, font, color);
    }


    return;
}






/////////////////////
void ShowStartOptions() 
{
    float font = (2.5 * GetScreenWidth() / 100);


    
    char StartText[] = "Start Sorting!";
    float tmp = (27*GetScreenWidth()) / 100;
    Start_Button(tmp, font, StartText);


    tmp += MeasureText(StartText, font) + 75;
    char RandomizeArrayText[] = "Randomize Array!";
    Button(tmp, GetScreenHeight()/20 + font*2,
        RandomizeArrayText, WHITE, ShouldRandomizeArray);

    
    addSpeed = false;
    subSpeed = false;
    addSize = false;
    subSize = false;

    NormalSize = false;
    NormalSpeed = false;

    tmp = (84.2 * GetScreenWidth()) / 100;
    char TimeButtonText[] = "Speed";

 

    Button(tmp, GetScreenHeight()/20 + font*2,
        TimeButtonText, BLUE, NormalSpeed);


    if (NormalSpeed){
        ChangeSpeed('/', SortingSpeed);
        return;
    }


    tmp += MeasureText(TimeButtonText, font) + 20;
    char SpeedPlusButtonText[] = "+";
    Button(tmp, GetScreenHeight()/20 + font*2,
        SpeedPlusButtonText, ORANGE, addSpeed); 


    if (addSpeed){
        ChangeSpeed('+', SortingSpeed);
        return;
    }

    tmp += MeasureText(SpeedPlusButtonText, font) + 20;
    char SpeedMinusButtonText[] = "-";
    Button(tmp, GetScreenHeight()/20 + font*2,
        SpeedMinusButtonText, ORANGE, subSpeed);


    if (subSpeed){
        ChangeSpeed('-', SortingSpeed);
        return;
    }


    tmp = (5 * GetScreenWidth()) / 100;
    char SizeButtonText[] = "Size";
    Button(tmp, GetScreenHeight()/20 + font*2,
        SizeButtonText, BLUE, NormalSize);
    

    if (NormalSize){
        ChangeSize('/', NumberOfPillar);
        return;
    }



    tmp += MeasureText(SizeButtonText, font) + 20;
    char SizePlusButton[] = "+";
    Button(tmp, GetScreenHeight()/20 + font*2,
        SizePlusButton, ORANGE, addSize);

    if (addSize){
        ChangeSize('+', NumberOfPillar);
        return;
    }

    tmp += MeasureText(SizePlusButton, font) + 20;
    char SizeMinusButton[] = "-";
    Button(tmp, GetScreenHeight()/20 + font*2,
        SizeMinusButton, ORANGE, subSize);


    if (subSize){
        ChangeSize('-', NumberOfPillar);
        return;
    } 
}


void Start_Button(float size, float font, char Start[]){
    Button(size, GetScreenHeight()/20 + font*2,
        Start, WHITE, ShouldStartSorting);

    return;
}


void ChangeSpeed(char operation, int &value){

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

void ChangeSize(char operation, int &value){
    switch (operation)
    {
        case '-':
            if (value > 5){
                value -= 5;
                for (int i = 0; i < 5; i++)
                    arr.pop_back();
            }
            break;

        case '+':
            value += 5;
            for (int i = 0; i < 5; i++)
                arr.push_back({GetRandomValue(40, MinWindowWidth-80), NORMAL});
            break;
            
    default:
        while (NumberOfPillar > 50){
            NumberOfPillar--;
            arr.pop_back();
        }

        while (NumberOfPillar< 50){
            NumberOfPillar++;
               arr.push_back({GetRandomValue(40, MinWindowWidth-80), NORMAL});
        }
        break;
    }


    for (int i = 0; i < NumberOfPillar; i++)
        arr[i].second = NORMAL;


    DrawArray(arr);
}


void Bubble_Sort(vector<pair<int, int>> &arr) {

    int endingPoint = NumberOfPillar;


    bool swapped;
    do {
        swapped = false;

        for (int i = 0; i < endingPoint-1; i++){

            arr[i].second = SELECTED;

            if (arr[i] > arr[i+1]){

                swap(arr[i], arr[i+1]);


                swapped = true;
            }
       


        BeginDrawing();

        ClearBackground(BLACK);


            for (int k = NumberOfPillar- 1; k >= endingPoint; k--)
                arr[k].second = SORTED;


            DrawArray(arr);


            for (int k = i; k >= 0; k--)
                arr[k].second = NORMAL;

            

        EndDrawing();


        }



        endingPoint--;
    } while(swapped);


    for (int i = NumberOfPillar-1; i >= 0; i--)
        arr[i].second = SORTED;
}

void SortArray(){
    Bubble_Sort(arr);

    DrawArray(arr);
}
void ShowEndingScreen(){
    DrawArray(arr);

    ShouldShowMenuScreen = true;
    ShouldShowStartOption = false;
}