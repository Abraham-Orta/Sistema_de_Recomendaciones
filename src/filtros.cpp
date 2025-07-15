#include "filtros.h"

std::vector<Producto> filtrarPorCategoria(const std::vector<Producto>& productos, const std::string& categoria) {
    std::vector<Producto> resultado;
    for (const auto& prod : productos) {
        if (categoria == "Todas" || prod.categoria == categoria) {
            resultado.push_back(prod);
        }
    }
    return resultado;
}

std::vector<Producto> FiltrarPorPrecio (const std::vector<Producto>& productos, const std::string& rangoPrecio){
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

std::vector<Producto> filtrarDescripcion (const std::vector<Producto>& productos, const std::string& filtroDescrip){
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