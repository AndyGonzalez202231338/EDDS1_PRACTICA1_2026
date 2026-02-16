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
            actual = nuevo;
            nuevo->siguiente = nuevo;
        } else {
            nuevo->siguiente = actual->siguiente;
            actual->siguiente = nuevo;
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
        NodoJugador* prev = nullptr;

        do {
            if (temp->jugador->getNombre() == nombre) {
                if (prev != nullptr) {
                    prev->siguiente = temp->siguiente;
                } else {
                    // Si el jugador a eliminar es el actual
                    if (temp->siguiente == actual) {
                        actual = nullptr; // Solo hay un jugador
                    } else {
                        actual = temp->siguiente; // Mover el actual
                    }
                }
                delete temp;
                cantidad--;
                return;
            }
            prev = temp;
            temp = temp->siguiente;
        } while (temp != actual);
    }

    void ListaJugadores::eliminarTodos() {
        if (actual == nullptr) return;

        NodoJugador* temp = actual;
        do {
            NodoJugador* siguiente = temp->siguiente;
            delete temp;
            temp = siguiente;
        } while (temp != actual);

        actual = nullptr;
        cantidad = 0;
    }

    bool ListaJugadores::estaVacia() const {
        return actual == nullptr;
    }

    Jugador ListaJugadores::obtenerJugadorEnPosicion(int posicion){
        if (posicion < 0 || posicion >= cantidad) {
            throw out_of_range("Posición fuera de rango");
        }

        NodoJugador* temp = actual;
        for (int i = 0; i < posicion; i++) {
            temp = temp->siguiente;
        }
        return *(temp->jugador);
    }

    Jugador& ListaJugadores::obtenerJugadorEnPosicionModificable(int posicion) {
        if (posicion < 0 || posicion >= cantidad) {
            throw out_of_range("Posición fuera de rango");
        }

        NodoJugador* temp = actual;
        for (int i = 0; i < posicion; i++) {
            temp = temp->siguiente;
        }
        return *(temp->jugador); // Retorna referencia NO constante
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
        if (actual == nullptr) return;

        srand(time(0));
        int n = cantidad;

        Jugador** jugadoresArray = new Jugador*[n];
        NodoJugador* temp = actual;
        for (int i = 0; i < n; i++) {
            jugadoresArray[i] = temp->jugador;
            temp = temp->siguiente;
        }

        // Mezclar Fisher-Yates
        for (int i = n - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            swap(jugadoresArray[i], jugadoresArray[j]);  // Intercambiar punteros
        }

        // Reasignar punteros
        temp = actual;
        for (int i = 0; i < n; i++) {
            temp->jugador = jugadoresArray[i];
            temp = temp->siguiente;
        }

        delete[] jugadoresArray;
    }

    Jugador& ListaJugadores::obtenerActual(){
        return *(actual->jugador);
    }

    void ListaJugadores::siguienteTurno() {
        if (actual == nullptr) return;

        if (sentidoHorario) {
            actual = actual->siguiente;
        } else {
            NodoJugador* temp = actual;
            while (temp->siguiente != actual) {
                temp = temp->siguiente;
            }
            actual = temp;
        }
    }

    void ListaJugadores::invertirSentido() {
        sentidoHorario = !sentidoHorario;
    }

    int ListaJugadores::size() const {
        return cantidad;
    }

    bool ListaJugadores::getSentido() {
        return sentidoHorario;
    }

