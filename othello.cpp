#include "othello.h"
#include <iostream>
#include <time.h>
#include <fstream>

Othello::Othello() : jugadorActual('B'), ganador(' '), finJuego(false) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            tablero[i][j] = ' ';
        }
    }
    tablero[3][3] = tablero[4][4] = 'W';
    tablero[3][4] = tablero[4][3] = 'B';
}

void Othello::mostrarTablero() {
    std::cout << "  A B C D E F G H" << std::endl;
    for (int i = 0; i < 8; i++) {
        std::cout << i + 1 << " ";
        for (int j = 0; j < 8; j++) {
            std::cout << tablero[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Othello::hacerMovimiento(int fila, int columna) {
    if (esMovimientoValido(fila, columna)) {
        tablero[fila][columna] = jugadorActual;
        voltearFichas(fila, columna);
        jugadorActual = (jugadorActual == 'B') ? 'W' : 'B';
        if (esFinJuego()) {
            terminarJuego();
        }
    } else {
        std::cout << "Movimiento inválido. Inténtalo de nuevo." << std::endl;
    }
}

bool Othello::esFinJuego() {
    for (int fila = 0; fila < 8; fila++) {
        for (int columna = 0; columna < 8; columna++) {
            if (esMovimientoValido(fila, columna)) {
                return false;
            }
        }
    }
    return true;
}

char Othello::obtenerJugadorActual() {
    return jugadorActual;
}

const char* Othello::obtenerTablero() {
    return reinterpret_cast<const char*>(tablero);
}

void Othello::guardarPartida(const char jugador1[], const char jugador2[], const char* tableroCopia) {
    time_t tiempoActual;
    struct tm *tiempoInfo;
    time(&tiempoActual);
    tiempoInfo = localtime(&tiempoActual);
    char fechaHora[80];
    strftime(fechaHora, 80, "%Y-%m-%d %H:%M:%S", tiempoInfo);

    std::ofstream archivo("ganador.txt", std::ios::app);

    if (archivo.is_open()) {
        archivo << "Fecha: " << fechaHora << std::endl;
        archivo << "Jugadores: " << jugador1 << " vs " << jugador2 << std::endl;
        archivo << "Ganador: " << ganador << std::endl;
        archivo << "Tablero final:" << std::endl;

        for (int fila = 0; fila < 8; fila++) {
            for (int columna = 0; columna < 8; columna++) {
                archivo << tableroCopia[fila * 8 + columna];
            }
            archivo << std::endl;
        }

        archivo << "---------------" << std::endl;

        archivo.close();
        std::cout << "La partida se ha guardado en ganador.txt" << std::endl;
    } else {
        std::cout << "No se pudo abrir el archivo ganador.txt" << std::endl;
    }
}

void Othello::mostrarHistorialPartidas() {
    std::ifstream archivo("ganador.txt");
    if (archivo.is_open()) {
        char linea[100];  // Tamaño suficiente para cada línea
        while (archivo.getline(linea, sizeof(linea))) {
            std::cout << linea << std::endl;
        }
        archivo.close();
    } else {
        std::cout << "No se pudo abrir el archivo ganador.txt" << std::endl;
    }
}

bool Othello::esMovimientoValido(int fila, int columna) {
    char adversario = (jugadorActual == 'B') ? 'W' : 'B';

    if (tablero[fila][columna] != ' ') {
        return false;
    }

    bool movimientoValido = false;

    for (int dirFila = -1; dirFila <= 1; dirFila++) {
        for (int dirCol = -1; dirCol <= 1; dirCol++) {
            if (dirFila == 0 && dirCol == 0) {
                continue;
            }
            int i = fila + dirFila;
            int j = columna + dirCol;

            while (i >= 0 && i < 8 && j >= 0 && j < 8 && tablero[i][j] == adversario) {
                i += dirFila;
                j += dirCol;
            }

            if (i >= 0 && i < 8 && j >= 0 && j < 8 && tablero[i][j] == jugadorActual) {
                movimientoValido = true;
            }
        }
    }

    return movimientoValido;
}

void Othello::voltearFichas(int fila, int columna) {
    char adversario = (jugadorActual == 'B') ? 'W' : 'B';

    for (int dirFila = -1; dirFila <= 1; dirFila++) {
        for (int dirCol = -1; dirCol <= 1; dirCol++) {
            if (dirFila == 0 && dirCol == 0) {
                continue;
            }
            int i = fila + dirFila;
            int j = columna + dirCol;

            while (i >= 0 && i < 8 && j >= 0 && j < 8 && tablero[i][j] == adversario) {
                i += dirFila;
                j += dirCol;
            }

            if (i >= 0 && i < 8 && j >= 0 && j < 8 && tablero[i][j] == jugadorActual) {
                i = fila + dirFila;
                j = columna + dirCol;
                while (i >= 0 && i < 8 && j >= 0 && j < 8 && tablero[i][j] == adversario) {
                    tablero[i][j] = jugadorActual;
                    i += dirFila;
                    j += dirCol;
                }
            }
        }
    }
}

void Othello::terminarJuego() {
    int fichasJugadorB = 0;
    int fichasJugadorW = 0;
    for (int fila = 0; fila < 8; fila++) {
        for (int columna = 0; columna < 8; columna++) {
            if (tablero[fila][columna] == 'B') {
                fichasJugadorB++;
            } else if (tablero[fila][columna] == 'W') {
                fichasJugadorW++;
            }
        }
    }
    if (fichasJugadorB > fichasJugadorW) {
        ganador = 'B';
    } else if (fichasJugadorW > fichasJugadorB) {
        ganador = 'W';
    }

    std::cout << "El juego ha terminado. Ganador: " << ganador << std::endl;
}
