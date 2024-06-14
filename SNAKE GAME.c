#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define widht 40
#define height 20


// Game Variables
int gameOver;
int x, y, fruitX, fruitY, score;
int tailX[100];
int tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
enum eDirection dir;
char playerName[100];
int gameSpeed = 100;


// Timer variables
int hour=0,minute=0,second=0,ms=0;

// Prototipe func counter
void counter();

// Prototipe func setup
void setup();

// Prototipe func drawing
void drawing();

// Prototipe func input
void input();

// Prototipe func logic
void logic();


// Func utama
int main() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    setup();
    while (!gameOver) {
        Sleep(gameSpeed);
        system("cls");
        drawing();
        input();
        logic();
        counter();
        ms += gameSpeed;
    }

    system("cls");
	printf("\t\t+==============================+\n");
	printf("\t\t|      GAME BERAKHIR !!!       |\n");
	printf("\t\t+==============================+\n");
	printf("NAMA : %s\n", playerName);
	printf("SCORE AKHIR : %d\n", score);
	printf("WAKTU = %d:%d:%d\n",hour,minute,second);
	getch();

    return 0;
}

// Func untuk menghitung waktu
void counter(){
    if(minute > 59){
        minute = 0;
        ++hour;
    }

    if(second > 59){
        second = 0;
        ++minute;
    }

    if(ms >= 360){
        second += 1;
        ms = 0;
    }
}

// Func untuk menampilkan game menu
void setup() {
    printf("===============================Selamat Datang Di Permainan===============================\n");
    printf("=\t 1. Gunakan 'WASD' untuk menggerakkan ular\t\t\t\t\t=\n");
	printf("=\t 2. Makan buah 'F' untuk menambah score & menambah panjang tubuh ular\t\t=\n");
	printf("=\t 3. Hindari tembok & jangan makan tubuh ular atau permainan akan berakhir\t=\n");
	printf("=\t 4. Untuk mengakhiri permainan tekan tombol 'x'\t\t\t\t\t=\n");
	printf("=\t 5. Dapatkan score sebanyak mungkin & enjoy the game!!\t\t\t\t=\n");
	printf("=========================================================================================\n");
	printf("Masukkan nama anda: ");
	gets(playerName);
	
	// variabel untuk setup game
    gameOver = 0;
    dir = STOP;
    x = widht / 2;
    y = height / 2;
    fruitX = rand() % widht - 2 + 4;
    fruitY = rand() % height - 2 + 4;
    score = 0;
}

// Func untuk meggambar game variabel
void drawing() {
    int i, j, k;
    for (i = 0; i < widht + 2; i++) {
        printf("#");
    }
    printf("\n");

    for (i = 0; i < height; i++) {
        for (j = 0; j < widht; j++) {
            if (j == 0) {
                printf("#");
            }
            if (i == y && j == x) {
                printf("O");
            }
            else if (i == fruitY && j == fruitX) {
                printf("F");
            }
            else {
                int print = 0;
                for (k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        printf("o");
                        print = 1;
                    }
                }
                if (!print)
                    printf(" ");
            }

            if (j == widht - 1) {
                printf("#");
            }
        }
        printf("\n");
    }

    for (i = 0; i < widht + 2; i++) {
        printf("#");
    }
    printf("\n");
    printf("NAMA = %s\n", playerName);
    printf("SCORE = %d\n", score);
    printf("WAKTU = %d:%d:%d\n",hour,minute,second);
}

// Func untuk mengecek inputan
void input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a':
                dir = LEFT;
                break;

            case 'd':
                dir = RIGHT;
                break;

            case 'w':
                dir = UP;
                break;

            case 's':
                dir = DOWN;
                break;

            case 'x':
                gameOver = 1;
                break;
        }
    }
}

// Func untuk mengatur logika game
void logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prevX2 = x;
    int prevY2 = y;
    tailX[0] = x;
    tailY[0] = y;
    int i;

    for (i = 1; i < nTail; i++) {
        prevX2 = tailX[i];
        prevY2 = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prevX2;
        prevY = prevY2;
    }

    switch (dir) {
        case LEFT:
            x--;
            break;

        case RIGHT:
            x++;
            break;

        case UP:
            y--;
            break;

        case DOWN:
            y++;
            break;

        default:
            break;
    }

    if (x >= widht) {
//        x = 1;
        gameOver = 1;
    }
    else if (x < 0) {
//        x = widht - 1;
        gameOver = 1;
    }

    if (y >= height) {
//        y = 1;
        gameOver = 1;
    }
    else if (y < 0) {
//        y = height - 1;
        gameOver = 1;
    }

    for (i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            gameOver = 1;
        }
    }

    if (x == fruitX && y == fruitY) {
        score += 10;

        fruitX = rand() % widht;
        fruitY = rand() % height;
        nTail++;
    }
}

