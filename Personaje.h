#define PERSONAJE_H

#include <string>
using namespace std;

class Personaje {
protected:
    int vida;
    int ataqueMin;
    int ataqueMax;
    string nombre;
    int posicionX;
    int posicionY;

public:
    Personaje(int v, int amin, int amax, string n, int x, int y);
    int getVida();
    string getNombre();
    int getPosicionX();
    int getPosicionY();
    void setVida(int v);
    void setPosicion(int x, int y);
    void mostrarInformacion();
    void atacar(Personaje& otro);
    bool estaVivo();
};

class EnemigoFinal : public Personaje {
private:
    int superAtaque1;
    int superAtaque2;

public:
    EnemigoFinal(int v, int amin, int amax, string n, int x, int y, int sa1, int sa2);
    void usarSuperAtaque(Personaje& otro);
    void atacar(Personaje& otro);
};