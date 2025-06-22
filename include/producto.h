#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <string>

struct Producto {
    std::string nombre;
    std::string descripcion;
    std::string marca;
    std::string categoria;
    std::string id; // Código único del producto    
    double precio;
};

#endif // PRODUCTO_H