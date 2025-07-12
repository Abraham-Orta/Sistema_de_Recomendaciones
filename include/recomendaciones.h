// recomendaciones.h
#ifndef RECOMENDACIONES_H
#define RECOMENDACIONES_H

#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include "producto.h"

#include "nodo_string.h"

void recomendarProductos(
    ListaEnlazadaString& recomendados,
    const std::vector<Producto>& todos,
    const ListaEnlazadaString& comprados,
    const ListaEnlazadaString& favoritos,
    const PreferenciasProducto& preferencias,
    size_t maxRecomendaciones = 5)
{
    // 1. Limpiar recomendaciones anteriores
    recomendados.limpiar();

    // Si no hay historial, usar preferencias
    if (comprados.cabeza == nullptr && favoritos.cabeza == nullptr) {
        size_t count = 0;
        for (NodoString* nodoCat = preferencias.categorias.cabeza; nodoCat != nullptr; nodoCat = nodoCat->siguiente) {
            for (const auto& prod : todos) {
                if (prod.categoria == nodoCat->valor) {
                    recomendados.agregar(prod.id);
                    count++;
                    if (count >= maxRecomendaciones) return;
                }
            }
        }
        for (NodoString* nodoMarca = preferencias.marcas.cabeza; nodoMarca != nullptr; nodoMarca = nodoMarca->siguiente) {
            for (const auto& prod : todos) {
                if (prod.marca == nodoMarca->valor) {
                    bool yaRecomendado = false;
                    for (NodoString* rec = recomendados.cabeza; rec != nullptr; rec = rec->siguiente) {
                        if (rec->valor == prod.id) {
                            yaRecomendado = true;
                            break;
                        }
                    }
                    if (!yaRecomendado) {
                        recomendados.agregar(prod.id);
                        count++;
                        if (count >= maxRecomendaciones) return;
                    }
                }
            }
        }
        return;
    }


    // 2. Obtener las categorías de interés del usuario
    std::vector<std::string> categorias;
    for (NodoString* nodo = comprados.cabeza; nodo != nullptr; nodo = nodo->siguiente) {
        for (const auto& p : todos) {
            if (p.id == nodo->valor) {
                categorias.push_back(p.categoria);
                break;
            }
        }
    }
    for (NodoString* nodo = favoritos.cabeza; nodo != nullptr; nodo = nodo->siguiente) {
        for (const auto& p : todos) {
            if (p.id == nodo->valor) {
                categorias.push_back(p.categoria);
                break;
            }
        }
    }

    // 2. Contar frecuencia de cada categoría
    std::map<std::string, int> frecuencia;
    for (const auto& cat : categorias)
        frecuencia[cat]++;

    // 3. Ordenar categorías por frecuencia
    std::vector<std::string> categoriasOrdenadas;
    for (const auto& par : frecuencia)
        categoriasOrdenadas.push_back(par.first);
    std::sort(categoriasOrdenadas.begin(), categoriasOrdenadas.end(),
        [&frecuencia](const std::string& a, const std::string& b) {
            return frecuencia[a] > frecuencia[b];
        });

    // 4. Recomendar productos de las categorías más frecuentes que no estén en comprados/favoritos
    size_t count = 0;
    for (const auto& cat : categoriasOrdenadas) {
        for (const auto& prod : todos) {
            bool yaTiene = false;
            for (NodoString* nodo = comprados.cabeza; nodo != nullptr; nodo = nodo->siguiente)
                if (nodo->valor == prod.id) yaTiene = true;
            for (NodoString* nodo = favoritos.cabeza; nodo != nullptr; nodo = nodo->siguiente)
                if (nodo->valor == prod.id) yaTiene = true;
            if (prod.categoria == cat && !yaTiene) {
                recomendados.agregar(prod.id);
                count++;
                if (count >= maxRecomendaciones)
                    return;
            }
        }
    }
}

#endif // RECOMENDACIONES_H