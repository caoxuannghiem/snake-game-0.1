#include <Windows.h>
#include <iostream>
#include <conio.h>
using namespace std;
class Info
{
public:
    bool GameOver = false;
    bool food = false;
protected:
    int x, y;
    int score = 0;
    const int rows = 20;
    const int cols = 60;
    int snakeX = 2, snakeY = 2; // snake postition
    int foodX, foodY;
    int snakeTX[10], snakeTY[10]; // snake length 
    int Tailsnake = 0;
    char bar = '0';  // The character used to represent the bar
    int barLength = 0;  // Initial length of the bar
    int maxlength = 5; // border inital of the bar

    void notification()
    {
        GameOver = true;
        system("cls");
        cout << "You Died \n" << endl;
        cout << "\nYour Final Score: " << score;
        char key = _getch();
    }

};
class Map : public Info
{
public:
    void draw()
    {
        system("cls");
        for (int x = 0; x < rows; x++) {
            for (int y = 0; y < cols; y++) {
                if (x == 0 || x == rows - 1 || y == 0 || y == cols - 1)
                    cout << "*";
                else if (x == snakeX && y == snakeY)
                {
                    cout << "S";
                }

                else if (x == foodX && y == foodY)
                    cout << "H";
                else
                {

                    bool tailprint = false;
                    for (int i = 0; i < Tailsnake; i++)
                    {
                        if (snakeTX[i] == x && snakeTY[i] == y)
                        {
                            cout << "S";
                            tailprint = true;
                        }
                    }
                    if (!tailprint)
                    {
                        cout << " ";
                    }

                }


            }
            cout << endl;
        }
        cout << "Score: " << score << "\n";
        cout << "Press P to pause the game" << endl;
    }


};
class Food : public Map
{
public:
    void generateFood() //generate food location
    {
        foodX = rand() % (rows - 3) + 1;
        foodY = rand() % (cols - 3) + 1;
    }
    void scoreupdate() // update the score when snake eat the food
    {

        if (snakeX == foodX && snakeY == foodY)
        {
            score += 1;
            food = false;
            Tailsnake++;
        }
    }
};
class Snake : public Food
{
public:
    void logic()
    {
        int lasttailX = snakeTX[0];
        int lasttailY = snakeTY[0];
        int lasttailX2, lasttailY2;
        snakeTX[0] = snakeX;
        snakeTY[0] = snakeY;
        for (int i = 1; i < Tailsnake; i++)
        {
            lasttailX2 = snakeTX[i];
            lasttailY2 = snakeTY[i];
            snakeTX[i] = lasttailX;
            snakeTY[i] = lasttailY;
            lasttailX = lasttailX2;
            lasttailY = lasttailY2;
        }

    }
    void tailcollide() {
        for (int i = 0; i < Tailsnake; i++)
            if (snakeTX[i] == snakeX && snakeTY[i] == snakeY)
            {
                notification();
            }

    }
    void bordercollide()
    {
        if (snakeX < 1 || snakeX > rows - 2 || snakeY < 1 || snakeY > cols - 2) //snake hit the border and die
        {
            notification();
        }
    }
    void movements()
    {
        char key = _getch();
        switch (key)
        {
        case 'a': case 'A':
            snakeY--;
            break;
        case 'w': case 'W':
            snakeX--;
            break;
        case 'd': case 'D':
            snakeY++;
            break;
        case 's': case 'S':
            snakeX++;
            break;

        }
    }
    void settings()
    {
        while (true) {
            system("cls");
            cout << "+ [";
            for (int i = 0; i < maxlength; i++) {

            }
            for (int i = 0; i < barLength; i++) {
                cout << bar;
            }
            cout << "] -";
            for (int i = 0; i < maxlength; i++) {

            }
            cout << endl;
            cout << "Press + to increase the bar length." << endl;
            cout << "Press - to decrease the bar length." << endl;
            cout << "Press q to back main menu" << endl;
            char key = _getch();
            if (key == '+') {
                // Increase the bar length
                if (barLength < 5) {  // Limit the maximum length
                    barLength++;
                }
            }
            else if (key == '-')
            {
                if (barLength > 0)
                {
                    barLength++;
                }
            }
            else if (key == 'q' || key == 'Q')
            {
                break;
            }
        }

    }
    void gamerun()
    {
        while (!GameOver)
        {
            if (_kbhit)
            {
                movements();
            }
            if (!food)
            {
                food = true;    // Set the food flag to true
                generateFood(); // Generate new food if food flag is false
            }
            draw();
            scoreupdate();
            bordercollide();
            tailcollide();
            logic();
            Sleep(0.001);
        }
    }
};
int main() {
    int choice;
    Snake snakerun;
    do
    {
        cout << "-----The Snake Game v0.1-----" << endl;
        cout << "       Press 1 to Play       " << endl;
        cout << "     Press 2 to Settings     " << endl;
        cout << "    Press 3 to Exit the Game " << endl;
        cout << "-----------------------------" << endl;
        cout << "    Enter Your Choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "You Choose 1: Enter the game" << endl;
            snakerun.gamerun();
            break;
        case 2:
            cout << "You Choose 2: Settings" << endl;
            snakerun.settings();
            break;
        case 3:
            cout << "You Choose 3: Exit" << endl;
            break;
        }
        system("cls");

    } while (choice != 4);
    return 0;
}
