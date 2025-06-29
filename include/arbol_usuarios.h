#ifndef ARBOL_USUARIOS_H
#define ARBOL_USUARIOS_H

#include "perfil_usuario.h"

struct NodoUsuario {
    perfil_usuario perfil;
    NodoUsuario* izquierda = nullptr;
    NodoUsuario* derecha = nullptr;
};

class ArbolUsuarios {
public:
    ArbolUsuarios() : raiz(nullptr) {}
    ~ArbolUsuarios();

    void insertar(const perfil_usuario& perfil);
    perfil_usuario* buscar(const std::string& nombreUsuario);

private:
    NodoUsuario* raiz;

    void destruir(NodoUsuario* nodo);
    NodoUsuario* insertar(NodoUsuario* nodo, const perfil_usuario& perfil);
    perfil_usuario* buscar(NodoUsuario* nodo, const std::string& nombreUsuario);
};

#endif