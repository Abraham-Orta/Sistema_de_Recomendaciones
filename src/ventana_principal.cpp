#include "ventana_principal.h"
#include "filtros.h"
#include "lista_productos.h"
#include "ventana_perfil.h"
#include "recomendaciones.h"
#include "Filtrar_Precios.h" // Incluir la función de filtrado por precio
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QScrollArea>
#include <QGridLayout>
#include <QWidget>
#include <limits> // Para std::numeric_limits
#include <iomanip> // Para std::fixed y std::setprecision

void VentanaPrincipal::mostrarProductos(const std::vector<Producto>& productosMostrados) {
    // Limpiar el layout anterior
    QLayoutItem* item;
    while ((item = gridLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    int fila = 0;
    int col = 0;
    for (const auto& prod : productosMostrados) {
        // Crear la tarjeta del producto
        QWidget* tarjeta = new QWidget;
        QVBoxLayout* layoutTarjeta = new QVBoxLayout(tarjeta);

        // Imagen
        QLabel* imagen = new QLabel;
        QPixmap pixmap(QString::fromStdString(":/"+prod.ruta_imagen));
        if (pixmap.isNull()) {
            // Si no hay imagen, mostrar un placeholder
            pixmap.load(":/img/placeholder.jpg");
        }
        imagen->setPixmap(pixmap.scaled(150, 150, Qt::KeepAspectRatio));
        layoutTarjeta->addWidget(imagen);

        // Nombre
        QLabel* nombre = new QLabel(QString::fromStdString(prod.nombre));
        layoutTarjeta->addWidget(nombre);

        // Precio
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << prod.precio;
        QLabel* precio = new QLabel(QString::fromStdString("$" + ss.str()));
        layoutTarjeta->addWidget(precio);

        // Botones
        QHBoxLayout* layoutBotones = new QHBoxLayout;
        QPushButton* botonComprar = new QPushButton("Comprar");
        QPushButton* botonMeGusta = new QPushButton("Me gusta");
        layoutBotones->addWidget(botonComprar);
        layoutBotones->addWidget(botonMeGusta);
        layoutTarjeta->addLayout(layoutBotones);

        // Conectar botones
        connect(botonComprar, &QPushButton::clicked, this, [this, prod]() {
            usuarioRegistrado.productos_comprados.agregar(prod.id);
            actualizarRecomendaciones();
            QMessageBox::information(this, "Compra", "¡Producto comprado!");
        });
        connect(botonMeGusta, &QPushButton::clicked, this, [this, prod]() {
            usuarioRegistrado.productos_favoritos.agregar(prod.id);
            actualizarRecomendaciones();
            QMessageBox::information(this, "Me gusta", "¡Producto agregado a favoritos!");
        });

        gridLayout->addWidget(tarjeta, fila, col);
        col++;
        if (col == 4) {
            col = 0;
            fila++;
        }
    }
}

void VentanaPrincipal::actualizarRecomendaciones() {
    recomendarProductos(usuarioRegistrado.productos_recomendados, productos, usuarioRegistrado.productos_comprados, usuarioRegistrado.productos_favoritos, usuarioRegistrado.preferencias, 25);
}

VentanaPrincipal::VentanaPrincipal(perfil_usuario& usuario, QWidget *parent)
    : QWidget(parent), usuarioRegistrado(usuario)
{
    setWindowTitle("Tienda en Línea");
    resize(700, 500);

    productos = obtenerListaProductos();

    // Layout principal vertical
    QVBoxLayout *layoutPrincipal = new QVBoxLayout(this);

    // Layout horizontal para las opciones
    QHBoxLayout *layoutOpciones = new QHBoxLayout;

    // Combo de categorías
    comboCategorias = new QComboBox(this);
    comboCategorias->addItem("Todas");
    comboCategorias->addItem("Recomendaciones");
    comboCategorias->addItem("Electrónica");
    comboCategorias->addItem("Hogar y cocina");
    comboCategorias->addItem("Moda y Accesorios");
    comboCategorias->addItem("Deportes y Aire Libre");
    comboCategorias->addItem("Cuidado personal y belleza");
    layoutOpciones->addWidget(new QLabel("Categoría:", this));
    layoutOpciones->addWidget(comboCategorias);

    // Combo de precios
    comboPrecios = new QComboBox(this);
    comboPrecios->addItem("Todos los precios");
    comboPrecios->addItem("Menos de 900.0$");
    comboPrecios->addItem("900.0$ a 1300.0$");
    comboPrecios->addItem("1300.0$ a 2500.0$");
    comboPrecios->addItem("2500.0$ a 25000.0$");
    comboPrecios->addItem("Más de 25000.0$");
    layoutOpciones->addWidget(new QLabel("Precio:", this));
    layoutOpciones->addWidget(comboPrecios);

    // Botón Información usuario
    QPushButton *botonInfoUsuario = new QPushButton("Información usuario", this);
    layoutOpciones->addWidget(botonInfoUsuario);

    // Botón Cerrar Sesión
    QPushButton *botonCerrarSesion = new QPushButton("Cerrar Sesión", this);
    layoutOpciones->addWidget(botonCerrarSesion);

    // Agregar layout de opciones al principal
    layoutPrincipal->addLayout(layoutOpciones);

    // ScrollArea para los productos
    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    QWidget* widgetContenedor = new QWidget;
    gridLayout = new QGridLayout(widgetContenedor);
    scrollArea->setWidget(widgetContenedor);
    layoutPrincipal->addWidget(scrollArea);

    setLayout(layoutPrincipal);

    actualizarRecomendaciones();

    // Conectar cambios de categoría y precio a la función de filtrado
    connect(comboCategorias, &QComboBox::currentTextChanged, this, &VentanaPrincipal::aplicarFiltrosYMostrarProductos);
    connect(comboPrecios, &QComboBox::currentTextChanged, this, &VentanaPrincipal::aplicarFiltrosYMostrarProductos);

    // Llamada inicial para mostrar productos
    aplicarFiltrosYMostrarProductos();

    // Botón Información usuario
    connect(botonInfoUsuario, &QPushButton::clicked, this, [this]() {
        VentanaPerfil ventanaPerfil(usuarioRegistrado, productos, this);
        ventanaPerfil.setMinimumSize(300, 200);
        ventanaPerfil.exec();
    });

    // Botón Cerrar Sesión
    connect(botonCerrarSesion, &QPushButton::clicked, this, &VentanaPrincipal::close);
}

void VentanaPrincipal::aplicarFiltrosYMostrarProductos() {
    std::vector<Producto> productosFiltrados = productos; // Empezar con todos los productos

    // 1. Filtrar por categoría
    QString categoriaSeleccionada = comboCategorias->currentText();
    if (categoriaSeleccionada == "Recomendaciones") {
        std::vector<Producto> recomendados;
        for (NodoString* nodo = usuarioRegistrado.productos_recomendados.cabeza; nodo != nullptr; nodo = nodo->siguiente) {
            for (const auto& prod : productos) {
                if (prod.id == nodo->valor) {
                    recomendados.push_back(prod);
                    break;
                }
            }
        }
        productosFiltrados = recomendados;
    } else {
        std::vector<Producto> tempFiltrados;
        if (categoriaSeleccionada != "Todas") {
            for (const auto& producto : productosFiltrados) {
                if (producto.categoria == categoriaSeleccionada.toStdString()) {
                    tempFiltrados.push_back(producto);
                }
            }
            productosFiltrados = tempFiltrados;
        }
    }

    // 2. Filtrar por precio usando la función FiltrarPorPrecio
    productosFiltrados = FiltrarPorPrecio(productosFiltrados, comboPrecios->currentText().toStdString());

    mostrarProductos(productosFiltrados);
}
