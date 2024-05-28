#include <iostream>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include "Personaje.h"

using namespace std;

const int FILAS = 10;
const int COLUMNAS = 5;

void inicializarTablero(char tablero[FILAS][COLUMNAS]) {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            tablero[i][j] = 'X';
        }
    }
}

void colocarSalida(char tablero[FILAS][COLUMNAS]) {
    tablero[FILAS - 1][COLUMNAS / 2] = 'S';
}

void colocarEnemigos(char tablero[FILAS][COLUMNAS], int numEnemigos) {
    for (int i = 0; i < numEnemigos; i++) {
        int x, y;
        do {
            x = rand() % FILAS;
            y = rand() % COLUMNAS;
        } while (tablero[x][y] != 'X');
        tablero[x][y] = 'E';
    }
}

void mostrarTablero(char tablero[FILAS][COLUMNAS], Personaje& heroe) {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (i == heroe.getPosicionX() && j == heroe.getPosicionY()) {
                cout << 'H' << " ";
            }
            else if (tablero[i][j] == 'S') {
                cout << 'S' << " ";
            }
            else if (tablero[i][j] == 'E') {
                cout << 'E' << " ";
            }
            else {
                cout << 'X' << " ";
            }
        }
        cout << endl;
    }
}

bool moverHeroe(Personaje& heroe, char direccion, char tablero[FILAS][COLUMNAS]) {
    int nuevaX = heroe.getPosicionX();
    int nuevaY = heroe.getPosicionY();

    if (direccion == 'W') nuevaX--;
    else if (direccion == 'S') nuevaX++;
    else if (direccion == 'A') nuevaY--;
    else if (direccion == 'D') nuevaY++;

    if (nuevaX < 0 || nuevaX >= FILAS || nuevaY < 0 || nuevaY >= COLUMNAS) {
        cout << "Movimiento inválido. Intenta de nuevo.\n";
        return false;
    }

    heroe.setPosicion(nuevaX, nuevaY);
    return true;
}

int main() {
    srand(time(0));

    char tablero[FILAS][COLUMNAS];
    inicializarTablero(tablero);

    colocarSalida(tablero);

    int numEnemigos = 5;
    colocarEnemigos(tablero, numEnemigos);

    Personaje heroe(100, 15, 25, "Heroe", 0, 0);
    tablero[heroe.getPosicionX()][heroe.getPosicionY()] = 'H';

    EnemigoFinal jefeFinal(150, 20, 30, "Jefe Final", FILAS - 1, COLUMNAS / 2 - 1, 50, 75);
    tablero[jefeFinal.getPosicionX()][jefeFinal.getPosicionY()] = 'J';

    char direccion;
    bool jugando = true;
    while (jugando) {
        mostrarTablero(tablero, heroe);
        cout << "¿Cuál será tu siguiente movimiento? (W/A/S/D): ";
        cin >> direccion;

        if (moverHeroe(heroe, direccion, tablero)) {
            int x = heroe.getPosicionX();
            int y = heroe.getPosicionY();

            if (tablero[x][y] == 'E') {
                cout << "¡Has encontrado a un enemigo!\n";
                Personaje enemigo(50, 5, 15, "Enemigo", x, y);

                char respuesta;
                cout << "¿Estás preparado para la batalla? (S/N): ";
                cin >> respuesta;
                if (respuesta != 'S' && respuesta != 's') {
                    cout << "¡Vuelve cuando estés preparado para luchar!\n";
                    continue;
                }

                cout << "Vida del héroe antes de la batalla: " << heroe.getVida() << endl;

                while (heroe.estaVivo() && enemigo.estaVivo()) {
                    heroe.atacar(enemigo);
                    if (enemigo.estaVivo()) {
                        enemigo.atacar(heroe);
                    }
                    Sleep(1000);
                }

                if (!heroe.estaVivo()) {
                    cout << "¡Game Over! El enemigo te ha derrotado.\n";
                    jugando = false;
                }
                else {
                    tablero[x][y] = 'X';
                    cout << "Vida del héroe después de la batalla: " << heroe.getVida() << endl;
                }
            }
            else if (tablero[x][y] == 'S') {
                cout << "¡Has encontrado la salida! ¡Felicidades, has ganado el juego!\n";
                jugando = false;
            }
        }
    }

    return 0;
}
