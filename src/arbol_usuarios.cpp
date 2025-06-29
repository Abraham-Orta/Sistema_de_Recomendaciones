#include "arbol_usuarios.h"

ArbolUsuarios::~ArbolUsuarios() {
    destruir(raiz);
}

void ArbolUsuarios::destruir(NodoUsuario* nodo) {
    if (nodo) {
        destruir(nodo->izquierda);
        destruir(nodo->derecha);
        delete nodo;
    }
}

void ArbolUsuarios::insertar(const perfil_usuario& perfil) {
    raiz = insertar(raiz, perfil);
}

NodoUsuario* ArbolUsuarios::insertar(NodoUsuario* nodo, const perfil_usuario& perfil) {
    if (!nodo) {
        NodoUsuario* nuevoNodo = new NodoUsuario;
        nuevoNodo->perfil = perfil;
        return nuevoNodo;
    }

    if (perfil.usuario < nodo->perfil.usuario) {
        nodo->izquierda = insertar(nodo->izquierda, perfil);
    } else if (perfil.usuario > nodo->perfil.usuario) {
        nodo->derecha = insertar(nodo->derecha, perfil);
    }

    return nodo;
}

perfil_usuario* ArbolUsuarios::buscar(const std::string& nombreUsuario) {
    return buscar(raiz, nombreUsuario);
}

perfil_usuario* ArbolUsuarios::buscar(NodoUsuario* nodo, const std::string& nombreUsuario) {
    if (!nodo) {
        return nullptr;
    }

    if (nombreUsuario == nodo->perfil.usuario) {
        return &nodo->perfil;
    } else if (nombreUsuario < nodo->perfil.usuario) {
        return buscar(nodo->izquierda, nombreUsuario);
    } else {
        return buscar(nodo->derecha, nombreUsuario);
    }
}