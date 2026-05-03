#include "snake.h"
#include <iostream>
#include <ctime>
#include <fstream>
#include <cstdlib>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

int SnakeGame::highScore = 0;

// simple tool to check if keyboard was hit
int kbhit(void) {
    struct termios oldt, newt;
    int ch, oldf;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}

// read key without waiting for enter
int getch(void) {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

SnakeGame::SnakeGame() : width(20), height(20) {
    highScore = 0;   
    srand((unsigned)time(NULL)); 
    HideCursor();
    LoadHighScore(); 
    init_game();
}

void SnakeGame::init_game() 
{
    gameOver = false;
    dir = RIGHT; 
    x = width / 2;
    y = height / 2;
    
    // randomize food position at the start
    foodX = rand() % width;
    foodY = rand() % height;
    
    score = 0;
    sizeOfBody = 0; 
    bodyX.clear();
    bodyY.clear();
}

void SnakeGame::HideCursor() {
    cout << "\033[?25l";
}

void SnakeGame::Draw() {
    cout << "\033[H"; 

    // draw the top wall
    for (int w = 0; w < width + 2; w++) cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) cout << "#"; // left border

            if (i == y && j == x) 
            {
                cout << "@"; // snake head icon
            } 
            else if (i == foodY && j == foodX) 
            {
                cout << "$"; // $is the reward
            } 
            else 
            {
                bool isBody = false;
                for (int k = 0; k < sizeOfBody; k++) {
                    if (bodyX[k] == j && bodyY[k] == i) {
                        cout << "s"; 
                        isBody = true;
                        break;
                    }
                }
                if (!isBody) cout << " ";
            }

            if (j == width - 1) cout << "#"; // right border
        }
        cout << endl;
    }

    for (int w = 0; w < width + 2; w++) cout << "#";
    
    cout << "\n [Current Score]: " << score 
         << " | [Record]: " << highScore 
         << string(30, ' ') << endl;   
}

void SnakeGame::Input() {
    if (kbhit()) 
    {
        int key = getch();
        switch (key) {
            case 'a': case 'A': if(dir != RIGHT) dir = LEFT; break;
            case 'd': case 'D': if(dir != LEFT) dir = RIGHT; break;
            case 'w': case 'W': if(dir != DOWN) dir = UP; break;
            case 's': case 'S': if(dir != UP) dir = DOWN; break;
            case 'q': case 'Q': gameOver = true; break; 
        }
    }
}

void SnakeGame::Logic() {
    // save the head position before moving
    int oldX = x;
    int oldY = y;

    // actual movement part
    if (dir == LEFT) x--;
    else if (dir == RIGHT) x++;
    else if (dir == UP) y--;
    else if (dir == DOWN) y++;

    // check wall collision
    if (x >= width || x < 0 || y >= height || y < 0) {
        gameOver = true;
        return; // stop logic if dead
    }

    // check if we bit ourselves
    for (int b = 0; b < sizeOfBody; b++) {
        if (bodyX[b] == x && bodyY[b] == y) {
            gameOver = true;
        }
    }

    // food logic
    if (x == foodX && y == foodY) {
        score = score + 10;
        foodX = rand() % width;
        foodY = rand() % height;
        sizeOfBody++;
        bodyX.push_back(0); 
        bodyY.push_back(0);
        
        if (score > highScore) {
            highScore = score;
        }
    }
    
    // update the body position
    if (sizeOfBody > 0) 
    {
        int tempX = bodyX[0];
        int tempY = bodyY[0];
        bodyX[0] = oldX;
        bodyY[0] = oldY;
        
        for (int i = 1; i < sizeOfBody; i++) 
        {
            int tempX2 = bodyX[i];
            int tempY2 = bodyY[i];
            bodyX[i] = tempX;
            bodyY[i] = tempY;
            tempX = tempX2;
            tempY = tempY2;
        }
    }
}

void SnakeGame::LoadHighScore() {
    ifstream read_file("highscore.txt");
    if (read_file.is_open()) {
        read_file >> highScore; 
        read_file.close();
    } else {
        highScore = 0; 
    }
}

void SnakeGame::SaveHighScore() {
    ofstream write_file("highscore.txt", ios::out | ios::trunc); 
    if (write_file.is_open()) {
        write_file << highScore; 
        write_file.close();
    }
    cout << "\033[?25h"; 
}
