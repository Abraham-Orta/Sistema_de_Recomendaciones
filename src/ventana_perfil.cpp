#include "ventana_perfil.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>
#include <iomanip>
#include <sstream>
#include <QFormLayout>
#include <QGroupBox>

VentanaPerfil::VentanaPerfil(const perfil_usuario& perfil, const std::vector<Producto>& todosLosProductos, QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Perfil de Usuario");
    resize(600, 800); 
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QGroupBox *userDetailsGroup = new QGroupBox("Detalles del Usuario", this);
    QFormLayout *formLayout = new QFormLayout(userDetailsGroup);
    formLayout->addRow("<b>Nombre:</b>", new QLabel(QString::fromStdString(perfil.nombre), this));
    formLayout->addRow("<b>Apellido:</b>", new QLabel(QString::fromStdString(perfil.apellido), this));
    formLayout->addRow("<b>ID:</b>", new QLabel(QString::fromStdString(perfil.id), this));
    formLayout->addRow("<b>Usuario:</b>", new QLabel(QString::fromStdString(perfil.usuario), this));
    formLayout->addRow("<b>Contraseña:</b>", new QLabel(QString::fromStdString(perfil.contraseña), this));
    mainLayout->addWidget(userDetailsGroup);

    QGroupBox *compradosGroup = new QGroupBox("Productos Comprados", this);
    QVBoxLayout *compradosLayout = new QVBoxLayout(compradosGroup);
    tablaComprados = new QTableWidget(this);
    tablaComprados->setColumnCount(4);
    tablaComprados->setHorizontalHeaderLabels({"ID", "Nombre", "Categoría", "Precio"});
    llenarTabla(tablaComprados, perfil.productos_comprados, todosLosProductos);
    compradosLayout->addWidget(tablaComprados);
    mainLayout->addWidget(compradosGroup);

    QGroupBox *favoritosGroup = new QGroupBox("Productos Favoritos", this);
    QVBoxLayout *favoritosLayout = new QVBoxLayout(favoritosGroup);
    tablaFavoritos = new QTableWidget(this);
    tablaFavoritos->setColumnCount(4);
    tablaFavoritos->setHorizontalHeaderLabels({"ID", "Nombre", "Categoría", "Precio"});
    llenarTabla(tablaFavoritos, perfil.productos_favoritos, todosLosProductos);
    favoritosLayout->addWidget(tablaFavoritos);
    mainLayout->addWidget(favoritosGroup);

    setLayout(mainLayout);
}

void VentanaPerfil::llenarTabla(QTableWidget* tabla, const ListaEnlazadaString& idsProductos, const std::vector<Producto>& todosLosProductos) {
    tabla->setRowCount(0);
    if (idsProductos.cabeza == nullptr) {
        tabla->setRowCount(1);
        QTableWidgetItem* item = new QTableWidgetItem("No hay productos en esta lista.");
        item->setTextAlignment(Qt::AlignCenter);
        tabla->setItem(0, 0, item);
        tabla->setSpan(0, 0, 1, 4);
        return;
    }

    int row = 0;
    for (NodoString* nodo = idsProductos.cabeza; nodo != nullptr; nodo = nodo->siguiente) {
        for (const auto& prod : todosLosProductos) {
            if (prod.id == nodo->valor) {
                tabla->insertRow(row);
                tabla->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(prod.id)));
                tabla->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(prod.nombre)));
                tabla->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(prod.categoria)));
                std::stringstream ss;
                ss << std::fixed << std::setprecision(2) << prod.precio;
                QTableWidgetItem* precioItem = new QTableWidgetItem(QString::fromStdString(ss.str()));
                precioItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
                tabla->setItem(row, 3, precioItem);
                row++;
                break;
            }
        }
    }
    tabla->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
