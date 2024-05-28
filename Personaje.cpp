#include "Personaje.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Personaje::Personaje(int v, int amin, int amax, string n, int x, int y)
    : vida(v), ataqueMin(amin), ataqueMax(amax), nombre(n), posicionX(x), posicionY(y) {}

int Personaje::getVida() {
    return vida;
}

string Personaje::getNombre() {
    return nombre;
}

int Personaje::getPosicionX() {
    return posicionX;
}

int Personaje::getPosicionY() {
    return posicionY;
}

void Personaje::setVida(int v) {
    vida = v;
}

void Personaje::setPosicion(int x, int y) {
    posicionX = x;
    posicionY = y;
}

void Personaje::mostrarInformacion() {
    cout << "Nombre: " << nombre << "\nVida: " << vida
        << "\nPosicion: (" << posicionX << ", " << posicionY << ")\n";
}

void Personaje::atacar(Personaje& otro) {
    int dano = ataqueMin + rand() % (ataqueMax - ataqueMin + 1);
    cout << nombre << " ataca a " << otro.getNombre() << " y causa " << dano << " puntos de daño.\n";
    otro.setVida(otro.getVida() - dano);
}

bool Personaje::estaVivo() {
    return vida > 0;
}

EnemigoFinal::EnemigoFinal(int v, int amin, int amax, string n, int x, int y, int sa1, int sa2)
    : Personaje(v, amin, amax, n, x, y), superAtaque1(sa1), superAtaque2(sa2) {}

void EnemigoFinal::usarSuperAtaque(Personaje& otro) {
    int dano = (rand() % 2 == 0) ? superAtaque1 : superAtaque2;
    cout << nombre << " usa un super ataque y causa " << dano << " puntos de daño.\n";
    otro.setVida(otro.getVida() - dano);
}

void EnemigoFinal::atacar(Personaje& otro) {
    if (rand() % 3 == 0) {
        usarSuperAtaque(otro);
    }
    else {
        Personaje::atacar(otro);
    }
}
