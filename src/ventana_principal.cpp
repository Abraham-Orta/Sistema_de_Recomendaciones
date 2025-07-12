#include "ventana_principal.h"
#include "filtros.h"
#include "lista_productos.h"
#include "ventana_perfil.h"
#include "recomendaciones.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QScrollArea>
#include <QGridLayout>
#include <QWidget>

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
        QPixmap pixmap(QString::fromStdString(":/" + prod.ruta_imagen));
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
        QLabel* precio = new QLabel(QString::fromStdString("$" + std::to_string(prod.precio)));
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

    

    // Botón Información usuario
    auto *botonInfoUsuario = new QPushButton("Información usuario", this);
    layoutOpciones->addWidget(botonInfoUsuario);

    // Botón Cerrar Sesión
    auto *botonCerrarSesion = new QPushButton("Cerrar Sesión", this);
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

    // Mostrar todos los productos al inicio
    mostrarProductos(filtrarPorCategoria(productos, "Todas"));

    // Conectar cambio de categoría
    connect(comboCategorias, &QComboBox::currentTextChanged, this, [this](const QString &categoria) {
        if (categoria == "Recomendaciones") {
            std::vector<Producto> recomendados;
            for (NodoString* nodo = usuarioRegistrado.productos_recomendados.cabeza; nodo != nullptr; nodo = nodo->siguiente) {
                for (const auto& prod : productos) {
                    if (prod.id == nodo->valor) {
                        recomendados.push_back(prod);
                        break;
                    }
                }
            }
            mostrarProductos(recomendados);
        } else {
            mostrarProductos(filtrarPorCategoria(productos, categoria.toStdString()));
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