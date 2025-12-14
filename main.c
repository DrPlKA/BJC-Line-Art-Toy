#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

#define WIDTH 100
#define HEIGHT 100

char getch() {
    struct termios oldt, newt;
    char ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    read(STDIN_FILENO, &ch, 1);

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

void clearScreen() {
    system("clear");
}

int main() {
    char grid[HEIGHT][WIDTH];
    int x = WIDTH / 2;
    int y = HEIGHT / 2;
    char input;

    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
            grid[i][j] = ' ';

    while (1) {
        clearScreen();
        grid[y][x] = '4';

        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++)
                putchar(grid[i][j]);
            putchar('\n');
        }

        printf("\nWASD to draw | C clear | Q quit\n");

        input = getch();

        if (input == 'q') break;
        if (input == 'w' && y > 0) y--;
        if (input == 's' && y < HEIGHT - 1) y++;
        if (input == 'a' && x > 0) x--;
        if (input == 'd' && x < WIDTH - 1) x++;

        if (input == 'c') {
            for (int i = 0; i < HEIGHT; i++)
                for (int j = 0; j < WIDTH; j++)
                    grid[i][j] = ' ';
        }
    }

    return 0;
}