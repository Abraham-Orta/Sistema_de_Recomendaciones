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

    // Liberar memoria
    ~ListaEnlazadaString() {
        NodoString* actual = cabeza;
        while (actual) {
            NodoString* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
    }
};

#endif