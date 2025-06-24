#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "filtros.h"

TEST_CASE("Filtrar productos por categoría", "[filtrarPorCategoria]") {
    std::vector<Producto> productos = {
        {"Laptop", "Portátil", "Dell", "Electrónica", "P001", 15000.0},
        {"Cafetera", "Cafetera automática", "DeLonghi", "Hogar y cocina", "H001", 3500.0},
        {"Camiseta", "Camiseta de algodón", "H&M", "Moda y Accesorios", "M001", 250.0}
    };

    SECTION("Filtrar Electrónica") {
        auto resultado = filtrarPorCategoria(productos, "Electrónica");
        REQUIRE(resultado.size() == 1);
        REQUIRE(resultado[0].nombre == "Laptop");
    }

    SECTION("Filtrar Hogar y cocina") {
        auto resultado = filtrarPorCategoria(productos, "Hogar y cocina");
        REQUIRE(resultado.size() == 1);
        REQUIRE(resultado[0].nombre == "Cafetera");
    }

    SECTION("Filtrar Moda y Accesorios") {
        auto resultado = filtrarPorCategoria(productos, "Moda y Accesorios");
        REQUIRE(resultado.size() == 1);
        REQUIRE(resultado[0].nombre == "Camiseta");
    }

    SECTION("Filtrar Todas") {
        auto resultado = filtrarPorCategoria(productos, "Todas");
        REQUIRE(resultado.size() == 3);
    }

    SECTION("Filtrar categoría inexistente") {
        auto resultado = filtrarPorCategoria(productos, "No existe");
        REQUIRE(resultado.size() == 0);
    }
}