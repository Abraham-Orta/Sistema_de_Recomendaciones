#include "arbol_usuarios.h"

void ArbolUsuarios::insertar(const perfil_usuario& perfil) {
    NodoUsuario** actual = &raiz;
    while (*actual) {
        if (perfil.usuario < (*actual)->perfil.usuario)
            actual = &((*actual)->izquierda);
        else
            actual = &((*actual)->derecha);
    }
    *actual = new NodoUsuario{perfil, nullptr, nullptr};
}

NodoUsuario* ArbolUsuarios::buscar(const std::string& nombreUsuario) {
    NodoUsuario* actual = raiz;
    while (actual) {
        if (nombreUsuario == actual->perfil.usuario)
            return actual;
        if (nombreUsuario < actual->perfil.usuario)
            actual = actual->izquierda;
        else
            actual = actual->derecha;
    }
    return nullptr;
}

void ArbolUsuarios::destruir(NodoUsuario* nodo) {
    if (nodo) {
        destruir(nodo->izquierda);
        destruir(nodo->derecha);
        delete nodo;
    }
}

ArbolUsuarios::~ArbolUsuarios() {
    destruir(raiz);
}