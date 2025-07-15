#include "nodo_string.h"

NodoString::NodoString(const std::string& v) : valor(v), siguiente(nullptr) {}

ListaEnlazadaString::ListaEnlazadaString() = default;

ListaEnlazadaString::ListaEnlazadaString(const ListaEnlazadaString& other) {
    NodoString* actualOther = other.cabeza;
    while (actualOther) {
        agregar(actualOther->valor);
        actualOther = actualOther->siguiente;
    }
}

ListaEnlazadaString& ListaEnlazadaString::operator=(const ListaEnlazadaString& other) {
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

void ListaEnlazadaString::agregar(const std::string& v) {
    NodoString* nuevo = new NodoString(v);
    if (!cabeza) {
        cabeza = nuevo;
    } else {
        NodoString* actual = cabeza;
        while (actual->siguiente) actual = actual->siguiente;
        actual->siguiente = nuevo;
    }
}

void ListaEnlazadaString::limpiar() {
    NodoString* actual = cabeza;
    while (actual) {
        NodoString* temp = actual;
        actual = actual->siguiente;
        delete temp;
    }
    cabeza = nullptr;
}

ListaEnlazadaString::~ListaEnlazadaString() {
    limpiar();
}