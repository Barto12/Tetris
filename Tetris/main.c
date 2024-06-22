#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

// Dimensiones del tablero de juego
#define WIDTH 10
#define HEIGHT 20

// Diferentes piezas del Tetris
int pieces[7][4][4][4] = {
        {
                { {0,1,0,0}, {0,1,0,0}, {0,1,0,0}, {0,1,0,0} },
                { {0,0,0,0}, {1,1,1,1}, {0,0,0,0}, {0,0,0,0} },
                { {0,1,0,0}, {0,1,0,0}, {0,1,0,0}, {0,1,0,0} },
                { {0,0,0,0}, {1,1,1,1}, {0,0,0,0}, {0,0,0,0} }
        },
        {
                { {0,0,0,0}, {1,1,0,0}, {0,1,1,0}, {0,0,0,0} },
                { {0,1,0,0}, {1,1,0,0}, {1,0,0,0}, {0,0,0,0} },
                { {0,0,0,0}, {1,1,0,0}, {0,1,1,0}, {0,0,0,0} },
                { {0,1,0,0}, {1,1,0,0}, {1,0,0,0}, {0,0,0,0} }
        },
        {
                { {0,0,0,0}, {0,1,1,0}, {1,1,0,0}, {0,0,0,0} },
                { {1,0,0,0}, {1,1,0,0}, {0,1,0,0}, {0,0,0,0} },
                { {0,0,0,0}, {0,1,1,0}, {1,1,0,0}, {0,0,0,0} },
                { {1,0,0,0}, {1,1,0,0}, {0,1,0,0}, {0,0,0,0} }
        },
        {
                { {0,0,0,0}, {0,1,0,0}, {1,1,1,0}, {0,0,0,0} },
                { {0,1,0,0}, {0,1,1,0}, {0,1,0,0}, {0,0,0,0} },
                { {0,0,0,0}, {1,1,1,0}, {0,1,0,0}, {0,0,0,0} },
                { {0,1,0,0}, {1,1,0,0}, {0,1,0,0}, {0,0,0,0} }
        },
        {
                { {0,0,0,0}, {1,1,0,0}, {1,1,0,0}, {0,0,0,0} },
                { {0,0,0,0}, {1,1,0,0}, {1,1,0,0}, {0,0,0,0} },
                { {0,0,0,0}, {1,1,0,0}, {1,1,0,0}, {0,0,0,0} },
                { {0,0,0,0}, {1,1,0,0}, {1,1,0,0}, {0,0,0,0} }
        },
        {
                { {0,0,0,0}, {0,0,1,0}, {1,1,1,0}, {0,0,0,0} },
                { {0,1,0,0}, {0,1,0,0}, {0,1,1,0}, {0,0,0,0} },
                { {0,0,0,0}, {1,1,1,0}, {1,0,0,0}, {0,0,0,0} },
                { {1,1,0,0}, {0,1,0,0}, {0,1,0,0}, {0,0,0,0} }
        },
        {
                { {0,0,0,0}, {1,0,0,0}, {1,1,1,0}, {0,0,0,0} },
                { {0,1,1,0}, {0,1,0,0}, {0,1,0,0}, {0,0,0,0} },
                { {0,0,0,0}, {1,1,1,0}, {0,0,1,0}, {0,0,0,0} },
                { {0,1,0,0}, {0,1,0,0}, {1,1,0,0}, {0,0,0,0} }
        }
};

// Tablero de juego
int board[HEIGHT][WIDTH];

// Posición y rotación de la pieza actual
int currentPiece, rotation, posX, posY;

// Función para inicializar el tablero de juego
void initBoard() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            board[y][x] = 0;
        }
    }
}

// Función para dibujar el tablero de juego en la consola
void drawBoard() {
    system("cls");
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (board[y][x] == 1) {
                printf("#");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
}

// Función para comprobar si la pieza puede moverse a la nueva posición
int canMove(int newPiece, int newRotation, int newX, int newY) {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (pieces[newPiece][newRotation][y][x] != 0) {
                int boardX = newX + x;
                int boardY = newY + y;
                if (boardX < 0 || boardX >= WIDTH || boardY < 0 || boardY >= HEIGHT || board[boardY][boardX] != 0) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

// Función para colocar la pieza actual en el tablero
void placePiece() {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (pieces[currentPiece][rotation][y][x] != 0) {
                board[posY + y][posX + x] = 1;
            }
        }
    }
}

// Función para generar una nueva pieza
void newPiece() {
    currentPiece = rand() % 7;
    rotation = 0;
    posX = WIDTH / 2 - 2;
    posY = 0;
    if (!canMove(currentPiece, rotation, posX, posY)) {
        printf("Game Over\n");
        exit(0);
    }
}

// Función para mover la pieza actual hacia abajo
void moveDown() {
    if (canMove(currentPiece, rotation, posX, posY + 1)) {
        posY++;
    } else {
        placePiece();
        newPiece();
    }
}

// Función para mover la pieza actual hacia la izquierda
void moveLeft() {
    if (canMove(currentPiece, rotation, posX - 1, posY)) {
        posX--;
    }
}

// Función para mover la pieza actual hacia la derecha
void moveRight() {
    if (canMove(currentPiece, rotation, posX + 1, posY)) {
        posX++;
    }
}

// Función para rotar la pieza actual
void rotate() {
    int newRotation = (rotation + 1) % 4;
    if (canMove(currentPiece, newRotation, posX, posY)) {
        rotation = newRotation;
    }
}

// Función principal del juego
int main() {
    srand(time(NULL));
    initBoard();
    newPiece();
    while (1) {
        drawBoard();
        if (_kbhit()) {
            switch (_getch()) {
                case 'a':
                    moveLeft();
                    break;
                case 'd':
                    moveRight();
                    break;
                case 'w':
                    rotate();
                    break;
                case 's':
                    moveDown();
                    break;
            }
        }
        Sleep(500);
        moveDown();
    }
    return 0;
}
