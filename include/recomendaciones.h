// recomendaciones.h
#ifndef RECOMENDACIONES_H
#define RECOMENDACIONES_H

#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <cmath> // Para std::abs
#include "producto.h"
#include "nodo_string.h"
#include "perfil_usuario.h" // Necesario para PreferenciasProducto

// Función auxiliar para verificar si un ID está en ListaEnlazadaString
bool estaEnLista(const ListaEnlazadaString& lista, const std::string& id);


void recomendarProductos(
    ListaEnlazadaString& recomendados,
    const std::vector<Producto>& todos,
    const ListaEnlazadaString& comprados,
    const ListaEnlazadaString& favoritos,
    const PreferenciasProducto& preferencias,
    size_t maxRecomendaciones);

#endif // RECOMENDACIONES_H