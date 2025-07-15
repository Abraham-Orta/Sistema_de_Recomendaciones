#ifndef FILTRAR_DESCRIPCION_H
#define FILTRAR_DESCRIPCION_H

#include <vector>
#include <string>
#include <algorithm> //Para implementar transform
#include <cctype> // Para implementar tolower() y así poder captar tanto caracteres en mayúsculas como minúsculas
#include "producto.h"

inline std::vector<Producto> filtrarDescripcion (const std::vector<Producto>& productos, const std::string& filtroDescrip){
    std::vector<Producto> resultado;

    //En caso de que la casillas de la descripción no contega ningun texto, devolverá la lista completa de productos
    if (filtroDescrip.empty()){
        return productos;
    }

    std::string filtroLower = filtroDescrip;
    std::transform(filtroLower.begin(), filtroLower.end(), filtroLower.begin(), [](unsigned char c){return std::tolower(c);} );

    for (const auto& prod : productos){
        //nombre y descripcion a caracteres en minúsculas
        std::string nombreLower = prod.nombre;
        std::transform (nombreLower.begin(), nombreLower.end(), nombreLower.begin(),
                       [](unsigned char c){return std::tolower(c);});

        std::string descripcionLower = prod.descripcion;
        std::transform (descripcionLower.begin(), descripcionLower.end(), descripcionLower.begin(),
                       [](unsigned char c){return std::tolower(c);});

        if (nombreLower.find(filtroLower) != std::string::npos || descripcionLower.find(filtroLower) != std::string::npos){ //npos equivalente a size_t
            resultado.push_back(prod);
        }
    }
    return resultado;
}

#endif // FILTRAR_DESCRIPCION_H
