// filtrar_precios.h
#ifndef FILTRAR_PRECIOS_H
#define FILTRAR_PRECIOS_H

#include <vector>
#include <string>
#include "producto.h"

inline std::vector<Producto> FiltrarPorPrecio (const std::vector<Producto>& productos, const std::string& rangoPrecio){
	std::vector<Producto> resultado;
	
	for (const auto& prod : productos){
        if (rangoPrecio == "Todos los precios"){
			resultado.push_back(prod);
        } else if (rangoPrecio == "Menos de 900.0$" && prod.precio < 900.0){
			resultado.push_back(prod);
        } else if (rangoPrecio == "900.0$ a 1300.0$" && prod.precio >= 900.0 && prod.precio <= 1300.0){
			resultado.push_back(prod);
        } else if (rangoPrecio == "1300.0$ a 2500.0$" && prod.precio >= 1300.0 && prod.precio <= 2500.0){
			resultado.push_back(prod);
        } else if (rangoPrecio == "2500.0$ a 25000.0$" && prod.precio >= 2500.0 && prod.precio <= 25000.0){
			resultado.push_back(prod);
        } else if (rangoPrecio == "Más de 25000.0$" && prod.precio > 25000.0){
			resultado.push_back(prod);
		}
	}
	return resultado;
}

#endif // FILTRAR_PRECIOS_H
