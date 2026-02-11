    #include "ListaJugadores.h"
    #include <iostream>
    #include <cstdlib>
    #include <ctime>

    using namespace std;

    ListaJugadores::ListaJugadores() {
        actual = nullptr;
        cantidad = 0;
        sentidoHorario = true;
    }

    void ListaJugadores::agregarJugador(Jugador* jugador) {
        NodoJugador* nuevo = new NodoJugador(jugador);

        if (actual == nullptr) {
            // Primer jugador
            actual = nuevo;
            nuevo->siguiente = nuevo;
            nuevo->anterior = nuevo;
        } else {
            NodoJugador* ultimo = actual->anterior;

            // Conectar nuevo nodo
            nuevo->siguiente = actual;
            nuevo->anterior = ultimo;

            // Ajustar extremos
            ultimo->siguiente = nuevo;
            actual->anterior = nuevo;
        }

        cantidad++;
    }

    void ListaJugadores::mostrarJugadores() const {
        if (actual == nullptr) {
            cout << "No hay jugadores en la lista.\n";
            return;
        }

        NodoJugador* temp = actual;
        do {
            cout << temp->jugador->getNombre() << endl;
            temp = temp->siguiente;
        } while (temp != actual);
    }

    void ListaJugadores::mostrarManos() const {
        if (actual == nullptr) return;

        NodoJugador* inicio = actual;
        NodoJugador* temp = actual;

        do {
            temp->jugador->mostrarMano();
            temp = temp->siguiente;
        } while (temp != inicio);
    }

    void ListaJugadores::eliminarJugador(const string& nombre) {
        if (actual == nullptr) return;

        NodoJugador* temp = actual;

        do {
            if (temp->jugador->getNombre() == nombre) {

                // Caso: único jugador
                if (cantidad == 1) {
                    delete temp->jugador;
                    delete temp;
                    actual = nullptr;
                } 
                else {
                    temp->anterior->siguiente = temp->siguiente;
                    temp->siguiente->anterior = temp->anterior;

                    if (temp == actual) {
                        actual = temp->siguiente;
                    }

                    delete temp->jugador;
                    delete temp;
                }

                cantidad--;
                return;
            }

            temp = temp->siguiente;

        } while (temp != actual);
    }

    void ListaJugadores::eliminarTodos() {
        if (actual == nullptr) return;

        NodoJugador* temp = actual->siguiente;

        while (temp != actual) {
            NodoJugador* siguiente = temp->siguiente;
            delete temp->jugador;
            delete temp;
            temp = siguiente;
        }

        delete actual->jugador;
        delete actual;

        actual = nullptr;
        cantidad = 0;
    }

    bool ListaJugadores::estaVacia() const {
        return actual == nullptr;
    }

    Jugador ListaJugadores::obtenerJugadorEnPosicion(int posicion) {
        if (posicion < 0 || posicion >= cantidad) {
            throw out_of_range("Posición fuera de rango");
        }

        NodoJugador* temp = actual;
        for (int i = 0; i < posicion; i++) {
            temp = temp->siguiente;
        }
        return *(temp->jugador);
    }

    void ListaJugadores::setJugadorEnPosicion(int posicion, Jugador* jugador) {
        if (posicion < 0 || posicion >= cantidad) {
            throw out_of_range("Posición fuera de rango");
        }

        NodoJugador* temp = actual;
        for (int i = 0; i < posicion; i++) {
            temp = temp->siguiente;
        }
        temp->jugador = jugador;
    }

    void ListaJugadores::mostrarOrdenTurnos() const {
        if (actual == nullptr) {
            cout << "No hay jugadores.\n";
            return;
        }

        cout << "\nORDEN DE TURNOS:\n";

        NodoJugador* temp = actual;
        int i = 1;
        do {
            cout << i++ << ". " << temp->jugador->getNombre() << endl;
            temp = temp->siguiente;
        } while (temp != actual);
    }

    void ListaJugadores::mezclarTurnos() {
        if (cantidad < 2) return;

        srand(time(0));

        for (int i = cantidad - 1; i > 0; i--) {
            int j = rand() % (i + 1);

            NodoJugador* nodoI = obtenerNodoEnPosicion(i);
            NodoJugador* nodoJ = obtenerNodoEnPosicion(j);

            // Intercambiar jugadores (no nodos)
            Jugador* temp = nodoI->jugador;
            nodoI->jugador = nodoJ->jugador;
            nodoJ->jugador = temp;
        }
    }

    Jugador& ListaJugadores::obtenerActual() {
        return *(actual->jugador);
    }

    void ListaJugadores::siguienteTurno() {
        if (actual == nullptr) return;

        if (sentidoHorario) {
            actual = actual->siguiente;
        } else {
            actual = actual->anterior;
        }
    }

    void ListaJugadores::invertirSentido() {
        sentidoHorario = !sentidoHorario;
    }

    int ListaJugadores::size() const {
        return cantidad;
    }

    NodoJugador* ListaJugadores::obtenerNodoEnPosicion(int pos) {
        NodoJugador* temp = actual;
        for (int i = 0; i < pos; i++) {
            temp = temp->siguiente;
        }
        return temp;
    }

