#include "othello.h"  // Incluimos el archivo de encabezado de la clase Othello
#include <iostream>

int main() {
    Othello juego;  // Creamos una instancia de la clase Othello

    // Lógica del juego
    const char jugador1[] = "Jugador1";
    const char jugador2[] = "Jugador2";

    char tableroCopia[8][8];
    while (!juego.esFinJuego()) {
        juego.mostrarTablero();
        char columna;
        int fila;
        std::cout << "Turno del jugador " << juego.obtenerJugadorActual() << ". Ingresa tu movimiento (por ejemplo, A3): ";
        std::cin >> columna >> fila;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                tableroCopia[i][j] = juego.obtenerTablero()[i * 8 + j];
            }
        }
        juego.hacerMovimiento(fila - 1, columna - 'A');
    }

    juego.guardarPartida(jugador1, jugador2, reinterpret_cast<const char*>(tableroCopia));
    juego.mostrarHistorialPartidas();

    return 0;
}
