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
#include <limits>
#include <iomanip>
#include <QFile>
#include <QApplication>

void VentanaPrincipal::mostrarProductos(const std::vector<Producto>& productosMostrados) {
    std::map<std::string, QWidget*> newDisplayedProductWidgets;
    int fila = 0;
    int col = 0;

    // Paso 1: Procesar los productos que deben mostrarse
    for (const auto& prod : productosMostrados) {
        QWidget* tarjeta = nullptr;

        // Intentar reutilizar un widget existente
        auto it = displayedProductWidgets.find(prod.id);
        if (it != displayedProductWidgets.end()) {
            tarjeta = it->second;
            // Mover el widget al nuevo mapa temporal
            newDisplayedProductWidgets[prod.id] = tarjeta;
            // Eliminarlo del mapa viejo para saber cuáles eliminar después
            displayedProductWidgets.erase(it);
        } else {
            // Crear una nueva tarjeta si no existe
            tarjeta = new QWidget;
            tarjeta->setFixedWidth(230);
            QVBoxLayout* layoutTarjeta = new QVBoxLayout(tarjeta);
            layoutTarjeta->setAlignment(Qt::AlignCenter);

            // Imagen
            QLabel* imagen = new QLabel;
            imagen->setFixedSize(220, 220);
            imagen->setAlignment(Qt::AlignCenter);
            QPixmap pixmap(QString::fromStdString(":/"+prod.ruta_imagen));
            if (pixmap.isNull()) {
                pixmap.load(":/img/placeholder.jpg");
            }
            imagen->setPixmap(pixmap.scaled(220, 220, Qt::KeepAspectRatio, Qt::SmoothTransformation));
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

            newDisplayedProductWidgets[prod.id] = tarjeta;
        }

        // Añadir o mover el widget al gridLayout
        gridLayout->addWidget(tarjeta, fila, col);
        col++;
        if (col == 4) {
            col = 0;
            fila++;
        }
    }

    // Paso 2: Eliminar los widgets que ya no deben mostrarse
    for (auto const& [id, widget] : displayedProductWidgets) {
        gridLayout->removeWidget(widget);
        delete widget;
    }

    // Paso 3: Actualizar el mapa de widgets mostrados
    displayedProductWidgets = std::move(newDisplayedProductWidgets);

    // Paso 4: Reorganizar los espaciadores
    // Limpiar todos los espaciadores existentes
    for (int i = gridLayout->count() - 1; i >= 0; --i) {
        QLayoutItem* item = gridLayout->itemAt(i);
        if (item && item->spacerItem()) {
            gridLayout->removeItem(item);
            delete item;
        }
    }

    // Añadir nuevos espaciadores
    if (col > 0) { // Si la última fila no está completa
        gridLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum), fila, col, 1, 4 - col);
    }
    gridLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding), fila + 1, 0, 1, 4);
}

void VentanaPrincipal::actualizarRecomendaciones() {
    recomendarProductos(usuarioRegistrado.productos_recomendados, productos, usuarioRegistrado.productos_comprados, usuarioRegistrado.productos_favoritos, usuarioRegistrado.preferencias, 25);
}

VentanaPrincipal::VentanaPrincipal(perfil_usuario& usuario, QWidget *parent)
    : QWidget(parent), usuarioRegistrado(usuario)
{
    setWindowTitle("Tienda Guayana");
    resize(950, 650);

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

    //Casilla de descripción
    QLabel *labelDescripcion = new QLabel("Buscar: ", this);
    layoutOpciones->addWidget(labelDescripcion);

    lineEditDescripcion = new QLineEdit (this);
    lineEditDescripcion->setPlaceholderText("Buscar descripción...");
    lineEditDescripcion->setMinimumWidth(150);
    layoutOpciones->addWidget(lineEditDescripcion);

    // Botón Información usuario
    QPushButton *botonInfoUsuario = new QPushButton("Información usuario", this);
    layoutOpciones->addWidget(botonInfoUsuario);

    // Botón Cerrar Sesión
    QPushButton *botonCerrarSesion = new QPushButton("Cerrar Sesión", this);
    layoutOpciones->addWidget(botonCerrarSesion);

    // Botón Tema
    botonTema = new QPushButton("Cambiar Tema", this);
    layoutOpciones->addWidget(botonTema);

    // Agregar layout de opciones al principal
    layoutPrincipal->addLayout(layoutOpciones);

    // ScrollArea para los productos
    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setMinimumSize(920, 460); // Establecer tamaño mínimo para el QScrollArea
    QWidget* widgetContenedor = new QWidget;
    gridLayout = new QGridLayout(widgetContenedor);
    gridLayout->setAlignment(Qt::AlignCenter); // Centrar el contenido del grid
    scrollArea->setWidget(widgetContenedor);
    layoutPrincipal->addWidget(scrollArea);

    setLayout(layoutPrincipal);

    actualizarRecomendaciones();

    // Inicializar y conectar el debounceTimer
    debounceTimer = new QTimer(this);
    debounceTimer->setSingleShot(true); // Asegura que el timer se dispare solo una vez
    debounceTimer->setInterval(300); // 300 ms de retraso
    connect(debounceTimer, &QTimer::timeout, this, &VentanaPrincipal::aplicarFiltrosYMostrarProductos);

    // Conectar cambios de categoría y precio a la función de filtrado
    connect(comboCategorias, &QComboBox::currentTextChanged, this, &VentanaPrincipal::aplicarFiltrosYMostrarProductos);
    connect(comboPrecios, &QComboBox::currentTextChanged, this, &VentanaPrincipal::aplicarFiltrosYMostrarProductos);
    // Conectar el QLineEdit al debounceTimer
    connect(lineEditDescripcion, &QLineEdit::textChanged, debounceTimer, QOverload<>::of(&QTimer::start));

    // Llamada inicial para mostrar productos
    aplicarFiltrosYMostrarProductos();

    // Conectar botón Información usuario
    connect(botonInfoUsuario, &QPushButton::clicked, this, [this]() {
        VentanaPerfil ventanaPerfil(usuarioRegistrado, productos, this);
        ventanaPerfil.setMinimumSize(300, 200);
        ventanaPerfil.exec();
    });

    // Conectar botón Cerrar Sesión
    connect(botonCerrarSesion, &QPushButton::clicked, this, &VentanaPrincipal::close);

    // Conectar botón Tema
    connect(botonTema, &QPushButton::clicked, this, &VentanaPrincipal::toggleTema);
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

    // 3. Filtrar por descripción
    if (!lineEditDescripcion->text().isEmpty()){
        productosFiltrados = filtrarDescripcion (productosFiltrados, lineEditDescripcion->text().toStdString());
    }

    mostrarProductos(productosFiltrados);
}

void VentanaPrincipal::toggleTema() {
    static bool isDarkTheme = false; // Empezar con el tema claro (styles_light.qss)
    QFile file;
    if (isDarkTheme) {
        file.setFileName(":/styles_light.qss");
    } else {
        file.setFileName(":/styles.qss");
    }

    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QString styleSheet = QLatin1String(file.readAll());
        qApp->setStyleSheet(styleSheet);
        file.close();
        isDarkTheme = !isDarkTheme;
    } else {
        QMessageBox::warning(this, "Error", "No se pudo cargar la hoja de estilo.");
    }
}
