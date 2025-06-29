// preferencias_producto.h
#ifndef PREFERENCIAS_PRODUCTO_H
#define PREFERENCIAS_PRODUCTO_H

#include <string>
#include "nodo_string.h"

// Preferencias de productos: engloba categorías y marcas
struct PreferenciasProducto {
    ListaEnlazadaString categorias;
    ListaEnlazadaString marcas;

    void agregarCategoria(const std::string& categoria) {
        categorias.agregar(categoria);
    }
    void agregarMarca(const std::string& marca) {
        marcas.agregar(marca);
    }
};

#endif