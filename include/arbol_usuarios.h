#ifndef ARBOL_USUARIOS_H
#define ARBOL_USUARIOS_H

#include "perfil_usuario.h"

struct NodoUsuario {
    perfil_usuario perfil;
    NodoUsuario* izquierda = nullptr;
    NodoUsuario* derecha = nullptr;
};

struct ArbolUsuarios {
    NodoUsuario* raiz = nullptr;

    void insertar(const perfil_usuario& perfil);
    NodoUsuario* buscar(const std::string& nombreUsuario);
    void destruir(NodoUsuario* nodo);
    ~ArbolUsuarios();
};

#endif