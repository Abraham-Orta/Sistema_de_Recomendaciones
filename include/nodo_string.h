// nodo_string.h
#ifndef NODO_STRING_H
#define NODO_STRING_H

#include <string>

struct NodoString {
    std::string valor;
    NodoString* siguiente = nullptr;
    NodoString(const std::string& v) : valor(v), siguiente(nullptr) {}
};

struct ListaEnlazadaString {
    NodoString* cabeza = nullptr;

    ListaEnlazadaString() = default; // Constructor por defecto

    // Constructor de copia
    ListaEnlazadaString(const ListaEnlazadaString& other) {
        NodoString* actualOther = other.cabeza;
        while (actualOther) {
            agregar(actualOther->valor);
            actualOther = actualOther->siguiente;
        }
    }

    // Operador de asignación de copia
    ListaEnlazadaString& operator=(const ListaEnlazadaString& other) {
        if (this == &other) { // Manejar auto-asignación
            return *this;
        }
        limpiar(); // Limpiar recursos actuales
        NodoString* actualOther = other.cabeza;
        while (actualOther) {
            agregar(actualOther->valor);
            actualOther = actualOther->siguiente;
        }
        return *this;
    }

    void agregar(const std::string& v) {
        NodoString* nuevo = new NodoString(v);
        if (!cabeza) {
            cabeza = nuevo;
        } else {
            NodoString* actual = cabeza;
            while (actual->siguiente) actual = actual->siguiente;
            actual->siguiente = nuevo;
        }
    }

    void limpiar() {
        NodoString* actual = cabeza;
        while (actual) {
            NodoString* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
        cabeza = nullptr;
    }

    // Destructor
    ~ListaEnlazadaString() {
        limpiar();
    }
};

#endif