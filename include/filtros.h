// filtros.h
#ifndef FILTROS_H
#define FILTROS_H

#include <vector>
#include <string>
#include <algorithm> //Para implementar transform
#include <cctype> // Para implementar tolower() y así poder captar tanto caracteres en mayúsculas como minúsculas
#include "producto.h"

std::vector<Producto> filtrarPorCategoria(const std::vector<Producto>& productos, const std::string& categoria);

std::vector<Producto> FiltrarPorPrecio (const std::vector<Producto>& productos, const std::string& rangoPrecio);

std::vector<Producto> filtrarDescripcion (const std::vector<Producto>& productos, const std::string& filtroDescrip);

#endif // FILTROS_H