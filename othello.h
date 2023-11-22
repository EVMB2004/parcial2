#ifndef OTHELLO_H
#define OTHELLO_H

class Othello {
public:
    Othello();
    void mostrarTablero();
    void hacerMovimiento(int fila, int columna);
    bool esFinJuego();
    char obtenerJugadorActual();
    const char* obtenerTablero();
    void guardarPartida(const char jugador1[], const char jugador2[], const char* tableroCopia);
    void mostrarHistorialPartidas();

private:
    char tablero[8][8];
    char jugadorActual;
    char ganador;
    bool finJuego;

    bool esMovimientoValido(int fila, int columna);
    void voltearFichas(int fila, int columna);
    void terminarJuego();
};

#endif // OTHELLO_H
