// nodo_string.h
#ifndef NODO_STRING_H
#define NODO_STRING_H

#include <string>

struct NodoString {
    std::string valor;
    NodoString* siguiente = nullptr;
    NodoString(const std::string& v);
};

struct ListaEnlazadaString {
    NodoString* cabeza = nullptr;

    ListaEnlazadaString();
    ListaEnlazadaString(const ListaEnlazadaString& other);
    ListaEnlazadaString& operator=(const ListaEnlazadaString& other);
    ~ListaEnlazadaString();

    void agregar(const std::string& v);
    void limpiar();
};

#endif