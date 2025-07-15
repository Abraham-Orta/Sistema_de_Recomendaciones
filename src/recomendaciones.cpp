#include "recomendaciones.h"
/*#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <cmath> // Para std::abs
#include "producto.h"
#include "nodo_string.h"
#include "perfil_usuario.h"*/// Necesario para PreferenciasProducto

// Función auxiliar para verificar si un ID está en ListaEnlazadaString
bool estaEnLista(const ListaEnlazadaString& lista, const std::string& id) {
    for (NodoString* nodo = lista.cabeza; nodo != nullptr; nodo = nodo->siguiente) {
        if (nodo->valor == id) return true;
    }
    return false;
}

void recomendarProductos(
    ListaEnlazadaString& recomendados,
    const std::vector<Producto>& todos,
    const ListaEnlazadaString& comprados,
    const ListaEnlazadaString& favoritos,
    const PreferenciasProducto& preferencias,
    size_t maxRecomendaciones = 25)
{
    recomendados.limpiar();

    // --- Paso 1: Recopilar datos históricos y preferencias ---
    std::map<std::string, int> frecuencia_categoria_historial;
    std::map<std::string, int> frecuencia_marca_historial;
    double calificacion_total_historial = 0.0;
    int conteo_calificacion_historial = 0;

    // Llenar datos históricos
    for (const auto& producto_actual : todos) {
        if (estaEnLista(comprados, producto_actual.id) || estaEnLista(favoritos, producto_actual.id)) {
            frecuencia_categoria_historial[producto_actual.categoria]++;
            frecuencia_marca_historial[producto_actual.marca]++;
            calificacion_total_historial += producto_actual.calificacion;
            conteo_calificacion_historial++;
        }
    }

    double calificacion_promedio_historial = (conteo_calificacion_historial > 0) ? calificacion_total_historial / conteo_calificacion_historial : 0.0;

    // --- Paso 2: Asignar puntuación a todos los productos ---
    std::vector<std::pair<Producto, double>> productos_puntuados;

    // Definir pesos (estos pueden ser ajustados para afinar las recomendaciones)
    const double PESO_MARCA_PREFERIDA = 100.0; // Muy alto para priorizar marcas preferidas
    const double PESO_CATEGORIA_HISTORIAL = 50.0;
    const double PESO_MARCA_HISTORIAL = 40.0;
    const double PESO_SIMILITUD_CALIDAD = 30.0;
    const double UMBRAL_SIMILITUD_CALIDAD = 1.0; // Diferencia máxima para obtener un boost de calidad

    for (const auto& producto_actual : todos) {
        // Omitir productos que ya han sido comprados o marcados como favoritos
        if (estaEnLista(comprados, producto_actual.id) || estaEnLista(favoritos, producto_actual.id)) {
            continue;
        }

        double puntuacion = 0.0; // Puntuación base para cada producto

        // 1. Recomendaciones por Marcas Preferidas (Prioridad alta)
        if (estaEnLista(preferencias.marcas, producto_actual.marca)) {
            puntuacion += PESO_MARCA_PREFERIDA;
        }

        // 2. Recomendaciones por Historial de Interacciones
        if (conteo_calificacion_historial > 0) { // Solo aplicar si hay historial
            // Misma Categoría (del historial)
            if (frecuencia_categoria_historial.count(producto_actual.categoria)) {
                // Boost proporcional a la frecuencia de la categoría en el historial
                puntuacion += PESO_CATEGORIA_HISTORIAL * (frecuencia_categoria_historial[producto_actual.categoria] / (double)conteo_calificacion_historial);
            }

            // Misma Marca (del historial)
            if (frecuencia_marca_historial.count(producto_actual.marca)) {
                puntuacion += PESO_MARCA_HISTORIAL * (frecuencia_marca_historial[producto_actual.marca] / (double)conteo_calificacion_historial);
            }

            // Calidad Similar
            if (calificacion_promedio_historial > 0) {
                double diferencia_calidad = std::abs(producto_actual.calificacion - calificacion_promedio_historial);
                // Si la diferencia de calidad es menor o igual al umbral, aplicar boost
                if (diferencia_calidad <= UMBRAL_SIMILITUD_CALIDAD) {
                    // El boost es mayor cuanto menor sea la diferencia
                    puntuacion += PESO_SIMILITUD_CALIDAD * (1.0 - (diferencia_calidad / UMBRAL_SIMILITUD_CALIDAD));
                }
            }
        } else { // Si no hay historial, usar preferencias explícitas de categoría
            if (estaEnLista(preferencias.categorias, producto_actual.categoria)) {
                puntuacion += PESO_CATEGORIA_HISTORIAL; // Dar un boost por categorías preferidas
            }
        }

        productos_puntuados.push_back({producto_actual, puntuacion});
    }

    // --- Paso 3: Ordenar y seleccionar las mejores recomendaciones ---
    std::sort(productos_puntuados.begin(), productos_puntuados.end(),
              [](const auto& a, const auto& b) {
                  return a.second > b.second; // Ordenar por puntuación descendente
              });

    size_t conteo_anadido = 0;
    for (const auto& par : productos_puntuados) {
        if (conteo_anadido >= maxRecomendaciones) {
            break;
        }
        recomendados.agregar(par.first.id);
        conteo_anadido++;
    }
}
