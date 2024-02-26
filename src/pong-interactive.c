// I WANT TO PLAY WITH YOU
//         YOUR FRIEND, AI
#include <curses.h>
#include <stdio.h>
#include <unistd.h>

int width = 80, height = 25;
int rocket_left_y = 12;
int rocket_right_y = 12;

int p1 = 0;
int p2 = 0;

int ballX = 39;
int ballY = 10;
int ballMoveLeft = 0;
int ballMoveUp = 1;

void solid_line(int width);
void empty_line(int width, int rocket_left_y, int rocket_right_y, int i);
void height_block(int width, int height);
void control();
void printPlayerScore(int p1, int p2);
void printBall(int x, int y);
void SetCursorPos(int XPos, int YPos);
// void printWin(int )

// Main ================================================================
int main() {
    int counter = 0;
    printf("\033[2J\033[H");  // Очистка консоли
    for (int i = 0;; i++) {
        height_block(width, height);
        printPlayerScore(p1, p2);
        counter++;
        if (counter == 10) {
            counter = 0;
            // ball movement
            if (ballMoveLeft == 1) {
                ballX--;
            } else {
                ballX++;
            }

            if (ballMoveUp == 1) {
                if (ballY == 2) {
                    ballMoveUp = 0;
                }
                ballY--;
            } else {
                if (ballY == 23) {
                    ballMoveUp = 1;
                }
                ballY++;
            }
        }
        printBall(ballX, ballY);
        /// gol
        if (ballX == 2) {
            p2++;
            ballX = 39;
            ballY = 10;
            ballMoveLeft = 0;
            ballMoveUp = 0;
        }
        if (ballX == 78) {
            p1++;
            ballX = 39;
            ballY = 10;
            ballMoveLeft = 1;
            ballMoveUp = 1;
        }
        if (p1 == 21) {
            printPlayerScore(p1, p2);
            SetCursorPos(30, 10);
            printf("Player 1 is winner!\n");
            SetCursorPos(0, 26);
            break;
        }
        if (p2 == 21) {
            printPlayerScore(p1, p2);
            SetCursorPos(30, 10);
            printf("Player 2 is winner!\n");
            SetCursorPos(0, 26);
            break;
        }

        /// raketka left
        if (ballX == 11 && rocket_left_y + 2 >= ballY && rocket_left_y <= ballY) ballMoveLeft = 0;
        if (ballX == 11 && rocket_left_y - 1 == ballY && ballMoveUp == 0) {
            ballMoveLeft = 0;
            ballMoveUp = 1;
        }
        if (ballX == 11 && rocket_left_y + 3 == ballY && ballMoveUp == 1) {
            ballMoveLeft = 0;
            ballMoveUp = 0;
        }
        // todo: raketka right
        if (ballX == 68 && rocket_right_y + 2 >= ballY && rocket_right_y <= ballY) ballMoveLeft = 1;
        if (ballX == 68 && rocket_right_y - 1 == ballY && ballMoveUp == 0) {
            ballMoveLeft = 1;
            ballMoveUp = 1;
        }
        if (ballX == 68 && rocket_right_y + 3 == ballY && ballMoveUp == 1) {
            ballMoveLeft = 1;
            ballMoveUp = 0;
        }

        fflush(stdout);
        SetCursorPos(0, 26);
        control();
        // system("clear");
        usleep(10 * 1000);
        SetCursorPos(0, 0);
    }
    return 0;
}
//==============================================================
void printPlayerScore(int p1, int p2) {
    SetCursorPos(35, 3);
    printf("%d", p1);

    SetCursorPos(45, 3);
    printf("%d", p2);
}

void printBall(int x, int y) {
    SetCursorPos(x, y);
    printf("O");
}

// Make solid line
void solid_line(int width) {
    for (int t = 0; t <= width; t++) printf("-");
}

// Make empty line
void empty_line(int width, int rocket_left_y, int rocket_right_y, int i) {
    for (int t = 0; t <= width; t++) {
        if (t == 0 || t == width / 2 || (t == 10 && i <= rocket_left_y + 1 && i >= rocket_left_y - 1) ||
            (t == width - 11 && i <= rocket_right_y + 1 && i >= rocket_right_y - 1))
            printf("|");
        else if (t == width)
            printf("|\n");
        else
            printf(" ");
    }
}

// Make the field
void height_block(int width, int height) {
    solid_line(width);
    printf("\n");
    for (int i = 0; i < height - 1; i++) empty_line(width, rocket_left_y, rocket_right_y, i);
    solid_line(width);
    printf("\n");
}

// Control units
void control() {
    char ch;
    initscr();
    cbreak();
    noecho();
    scrollok(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    ch = getch();
    endwin();
    // scanf("%c", &ch);
    switch (ch) {
        case 'a':
            if (rocket_left_y > -1) rocket_left_y--;
            break;
        case 'z':
            if (rocket_left_y < height - 1) rocket_left_y++;
            break;
        case 'k':
            if (rocket_right_y > -1) rocket_right_y--;
            break;
        case 'm':
            if (rocket_right_y < height - 1) rocket_right_y++;
            break;
        case ' ':
            break;
        case 'q':
            // exit(0);
            break;
    }
}

void SetCursorPos(int XPos, int YPos) { printf("\033[%d;%dH", YPos + 1, XPos + 1); }
