#include "ventana_principal.h"
#include "filtros.h"
#include "lista_productos.h"
#include "ventana_perfil.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QListWidget>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>

VentanaPrincipal::VentanaPrincipal(const perfil_usuario& usuario, QWidget *parent)
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

    // Agregar layout de opciones al principal
    layoutPrincipal->addLayout(layoutOpciones);

    // Lista de productos debajo
    lista = new QListWidget(this);
    layoutPrincipal->addWidget(lista);

    setLayout(layoutPrincipal);

    // Mostrar todos los productos al inicio
    auto productosFiltrados = filtrarPorCategoria(productos, "Todas");
    lista->clear();
    for (const auto& prod : productosFiltrados) {
        lista->addItem(QString::fromStdString(prod.nombre + " - $" + std::to_string(prod.precio)));
    }

    // Conectar cambio de categoría
    connect(comboCategorias, &QComboBox::currentTextChanged, this, [this](const QString &categoria) {
        auto productosFiltrados = filtrarPorCategoria(productos, categoria.toStdString());
        lista->clear();
        for (const auto& prod : productosFiltrados) {
            lista->addItem(QString::fromStdString(prod.nombre + " - $" + std::to_string(prod.precio)));
        }
    });

    // Botón Comprar
    connect(botonComprar, &QPushButton::clicked, this, [this]() {
        int idx = lista->currentRow();
        if (idx >= 0) {
            productosComprados.push_back(productos[idx]);
            QMessageBox::information(this, "Compra", "¡Producto comprado!");
        } else {
            QMessageBox::warning(this, "Compra", "Selecciona un producto para comprar.");
        }
    });

    // Botón Me gusta
    connect(botonMeGusta, &QPushButton::clicked, this, [this]() {
        int idx = lista->currentRow();
        if (idx >= 0) {
            productosFavoritos.push_back(productos[idx]);
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
}