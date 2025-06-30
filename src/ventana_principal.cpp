#include "ventana_principal.h"
#include "filtros.h"
#include "lista_productos.h"
#include "ventana_perfil.h"
#include "recomendaciones.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QListWidget>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>

void VentanaPrincipal::actualizarRecomendaciones() {
    recomendarProductos(usuarioRegistrado.productos_recomendados, productos, usuarioRegistrado.productos_comprados, usuarioRegistrado.productos_favoritos, 25);
}

VentanaPrincipal::VentanaPrincipal(perfil_usuario& usuario, QWidget *parent)
    : QWidget(parent), usuarioRegistrado(usuario)
{
    setWindowTitle("Tienda en Línea");
    resize(700, 500);

    productos = obtenerListaProductos();

    // Layout principal vertical
    auto *layoutPrincipal = new QVBoxLayout(this);

    // Layout horizontal para las opciones
    auto *layoutOpciones = new QHBoxLayout;

    // Combo de categorías
    auto *comboCategorias = new QComboBox(this);
    comboCategorias->addItem("Todas");
    comboCategorias->addItem("Recomendaciones");
    comboCategorias->addItem("Electrónica");
    comboCategorias->addItem("Hogar y cocina");
    comboCategorias->addItem("Moda y Accesorios");
    comboCategorias->addItem("Deportes y Aire Libre");
    comboCategorias->addItem("Cuidado personal y belleza");
    layoutOpciones->addWidget(new QLabel("Categoría:", this));
    layoutOpciones->addWidget(comboCategorias);

    // Botón Comprar
    auto *botonComprar = new QPushButton("Comprar", this);
    layoutOpciones->addWidget(botonComprar);

    // Botón Me gusta
    auto *botonMeGusta = new QPushButton("Me gusta", this);
    layoutOpciones->addWidget(botonMeGusta);

    // Botón Información usuario
    auto *botonInfoUsuario = new QPushButton("Información usuario", this);
    layoutOpciones->addWidget(botonInfoUsuario);

    // Botón Cerrar Sesión
    auto *botonCerrarSesion = new QPushButton("Cerrar Sesión", this);
    layoutOpciones->addWidget(botonCerrarSesion);

    // Agregar layout de opciones al principal
    layoutPrincipal->addLayout(layoutOpciones);

    // Lista de productos debajo
    lista = new QListWidget(this);
    layoutPrincipal->addWidget(lista);

    setLayout(layoutPrincipal);

    actualizarRecomendaciones();

    // Mostrar todos los productos al inicio
    auto productosFiltrados = filtrarPorCategoria(productos, "Todas");
    lista->clear();
    for (const auto& prod : productosFiltrados) {
        lista->addItem(QString::fromStdString(prod.nombre + " - $" + std::to_string(prod.precio)));
    }

    // Conectar cambio de categoría
    connect(comboCategorias, &QComboBox::currentTextChanged, this, [this](const QString &categoria) {
        if (categoria == "Recomendaciones") {
            lista->clear();
            for (NodoString* nodo = usuarioRegistrado.productos_recomendados.cabeza; nodo != nullptr; nodo = nodo->siguiente) {
                for (const auto& prod : productos) {
                    if (prod.id == nodo->valor) {
                        lista->addItem(QString::fromStdString(prod.nombre + " - $" + std::to_string(prod.precio)));
                        break;
                    }
                }
            }
        } else {
            auto productosFiltrados = filtrarPorCategoria(productos, categoria.toStdString());
            lista->clear();
            for (const auto& prod : productosFiltrados) {
                lista->addItem(QString::fromStdString(prod.nombre + " - $" + std::to_string(prod.precio)));
            }
        }
    });

    // Botón Comprar
    connect(botonComprar, &QPushButton::clicked, this, [this, comboCategorias]() {
        int idx = lista->currentRow();
        if (idx >= 0) {
            auto categoriaActual = comboCategorias->currentText().toStdString();
            if (categoriaActual == "Recomendaciones") {
                int i = 0;
                for (NodoString* nodo = usuarioRegistrado.productos_recomendados.cabeza; nodo != nullptr; nodo = nodo->siguiente) {
                    if (i == idx) {
                        usuarioRegistrado.productos_comprados.agregar(nodo->valor);
                        break;
                    }
                    i++;
                }
            } else {
                auto productosFiltrados = filtrarPorCategoria(productos, categoriaActual);
                usuarioRegistrado.productos_comprados.agregar(productosFiltrados[idx].id);
            }
            actualizarRecomendaciones();
            QMessageBox::information(this, "Compra", "¡Producto comprado!");
        } else {
            QMessageBox::warning(this, "Compra", "Selecciona un producto para comprar.");
        }
    });

    // Botón Me gusta
    connect(botonMeGusta, &QPushButton::clicked, this, [this, comboCategorias]() {
        int idx = lista->currentRow();
        if (idx >= 0) {
            auto categoriaActual = comboCategorias->currentText().toStdString();
            if (categoriaActual == "Recomendaciones") {
                int i = 0;
                for (NodoString* nodo = usuarioRegistrado.productos_recomendados.cabeza; nodo != nullptr; nodo = nodo->siguiente) {
                    if (i == idx) {
                        usuarioRegistrado.productos_favoritos.agregar(nodo->valor);
                        break;
                    }
                    i++;
                }
            } else {
                auto productosFiltrados = filtrarPorCategoria(productos, categoriaActual);
                usuarioRegistrado.productos_favoritos.agregar(productosFiltrados[idx].id);
            }
            actualizarRecomendaciones();
            QMessageBox::information(this, "Me gusta", "¡Producto agregado a favoritos!");
        } else {
            QMessageBox::warning(this, "Me gusta", "Selecciona un producto para dar me gusta.");
        }
    });

    // Botón Información usuario
    connect(botonInfoUsuario, &QPushButton::clicked, this, [this]() {
        VentanaPerfil ventanaPerfil(usuarioRegistrado, this);
        ventanaPerfil.setMinimumSize(300, 200);
        ventanaPerfil.exec();
    });

    // Botón Cerrar Sesión
    connect(botonCerrarSesion, &QPushButton::clicked, this, &VentanaPrincipal::close);
}