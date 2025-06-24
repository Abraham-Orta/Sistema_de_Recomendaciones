// filtros.h
#ifndef FILTROS_H
#define FILTROS_H

#include <vector>
#include <string>
#include "producto.h"

inline std::vector<Producto> filtrarPorCategoria(const std::vector<Producto>& productos, const std::string& categoria) {
    std::vector<Producto> resultado;
    for (const auto& prod : productos) {
        if (categoria == "Todas" || prod.categoria == categoria) {
            resultado.push_back(prod);
        }
    }
    return resultado;
}

#endif // FILTROS_H