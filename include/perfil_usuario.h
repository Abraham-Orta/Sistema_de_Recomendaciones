// perfil_usuario.h
#ifndef PERFIL_USUARIO_H
#define PERFIL_USUARIO_H

#include <string>
#include "preferencias_producto.h"
#include "nodo_string.h"

struct perfil_usuario {
    std::string nombre;
    std::string apellido;
    std::string id;
    std::string usuario; // Nombre de usuario
    std::string contraseña;

    PreferenciasProducto preferencias;

    ListaEnlazadaString productos_comprados;
    ListaEnlazadaString productos_favoritos;
};

#endif