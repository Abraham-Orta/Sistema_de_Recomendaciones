#include "ventana_principal.h"
#include "lista_productos.h"
#include "ventana_perfil.h"
#include <QVBoxLayout>
#include <QListWidget>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <vector>

VentanaPrincipal::VentanaPrincipal(const perfil_usuario& usuario, QWidget *parent)
    : QWidget(parent), usuarioRegistrado(usuario)
{
    setWindowTitle("Tienda en Línea");
    resize(600, 400);

    // Lista de productos
    productos = obtenerListaProductos();

    auto *layout = new QVBoxLayout(this);
    lista = new QListWidget(this);

    for (const auto& prod : productos) {
        lista->addItem(QString::fromStdString(prod.nombre + " - $" + std::to_string(prod.precio)));
    }

    layout->addWidget(new QLabel("Productos disponibles:", this));
    layout->addWidget(lista);

    // Botón para mostrar información del usuario
    auto *botonInfoUsuario = new QPushButton("Información usuario", this);
    layout->addWidget(botonInfoUsuario);

    connect(botonInfoUsuario, &QPushButton::clicked, this, [this]() {
        VentanaPerfil ventanaPerfil(usuarioRegistrado, this);
        ventanaPerfil.setMinimumSize(300, 200);
        ventanaPerfil.exec();
    });

    // Botón para comprar producto
    auto *botonComprar = new QPushButton("Comprar", this);
    layout->addWidget(botonComprar);

    connect(botonComprar, &QPushButton::clicked, this, [this]() {
        int idx = lista->currentRow();
        if (idx >= 0) {
            productosComprados.push_back(productos[idx]);
            QMessageBox::information(this, "Compra", "¡Producto comprado!");
        } else {
            QMessageBox::warning(this, "Compra", "Selecciona un producto para comprar.");
        }
    });

    // Botón para dar me gusta
    auto *botonMeGusta = new QPushButton("Me gusta", this);
    layout->addWidget(botonMeGusta);

    connect(botonMeGusta, &QPushButton::clicked, this, [this]() {
        int idx = lista->currentRow();
        if (idx >= 0) {
            productosFavoritos.push_back(productos[idx]);
            QMessageBox::information(this, "Me gusta", "¡Producto agregado a favoritos!");
        } else {
            QMessageBox::warning(this, "Me gusta", "Selecciona un producto para dar me gusta.");
        }
    });

    setLayout(layout);
}