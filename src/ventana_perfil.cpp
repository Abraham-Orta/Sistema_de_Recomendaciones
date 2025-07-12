#include "ventana_perfil.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <iomanip> // Para std::fixed y std::setprecision
#include <sstream> // Para std::stringstream
#include <QFormLayout> // Nuevo include para QFormLayout
#include <QGroupBox>   // Nuevo include para QGroupBox

VentanaPerfil::VentanaPerfil(const perfil_usuario& perfil, const std::vector<Producto>& todosLosProductos, QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Perfil de Usuario");
    resize(450, 800); // Mantener el tamaño por ahora, se puede ajustar si es necesario
    QVBoxLayout *mainLayout = new QVBoxLayout(this); // Layout principal

    // Sección de Detalles del Usuario
    QGroupBox *userDetailsGroup = new QGroupBox("Detalles del Usuario", this);
    QFormLayout *formLayout = new QFormLayout(userDetailsGroup);

    QLabel *nombreLabel = new QLabel("<b>Nombre:</b>", this);
    formLayout->addRow(nombreLabel, new QLabel(QString::fromStdString(perfil.nombre), this));

    QLabel *apellidoLabel = new QLabel("<b>Apellido:</b>", this);
    formLayout->addRow(apellidoLabel, new QLabel(QString::fromStdString(perfil.apellido), this));

    QLabel *idLabel = new QLabel("<b>ID:</b>", this);
    formLayout->addRow(idLabel, new QLabel(QString::fromStdString(perfil.id), this));

    QLabel *usuarioLabel = new QLabel("<b>Usuario:</b>", this);
    formLayout->addRow(usuarioLabel, new QLabel(QString::fromStdString(perfil.usuario), this));

    QLabel *contrasenaLabel = new QLabel("<b>Contraseña:</b>", this);
    formLayout->addRow(contrasenaLabel, new QLabel(QString::fromStdString(perfil.contraseña), this));

    mainLayout->addWidget(userDetailsGroup);

    // Sección de Productos Comprados
    QGroupBox *compradosGroup = new QGroupBox("Productos Comprados", this);
    QVBoxLayout *compradosLayout = new QVBoxLayout(compradosGroup);
    listaComprados = new QListWidget(this);
    if (perfil.productos_comprados.cabeza == nullptr) {
        listaComprados->addItem("Ningún producto comprado.");
    } else {
        for (NodoString* nodo = perfil.productos_comprados.cabeza; nodo != nullptr; nodo = nodo->siguiente) {
            // Buscar el producto por ID en todosLosProductos
            for (const auto& prod : todosLosProductos) {
                if (prod.id == nodo->valor) {
                    std::stringstream ss;
                    ss << std::fixed << std::setprecision(2) << prod.precio;
                    listaComprados->addItem(QString::fromStdString(prod.nombre + " (" + prod.categoria + ") - $" + ss.str()));
                    break;
                }
            }
        }
    }
    compradosLayout->addWidget(listaComprados);
    mainLayout->addWidget(compradosGroup);

    // Sección de Productos Favoritos
    QGroupBox *favoritosGroup = new QGroupBox("Productos Favoritos", this);
    QVBoxLayout *favoritosLayout = new QVBoxLayout(favoritosGroup);
    listaFavoritos = new QListWidget(this);
    if (perfil.productos_favoritos.cabeza == nullptr) {
        listaFavoritos->addItem("Ningún producto favorito.");
    } else {
        for (NodoString* nodo = perfil.productos_favoritos.cabeza; nodo != nullptr; nodo = nodo->siguiente) {
            // Buscar el producto por ID en todosLosProductos
            for (const auto& prod : todosLosProductos) {
                if (prod.id == nodo->valor) {
                    std::stringstream ss;
                    ss << std::fixed << std::setprecision(2) << prod.precio;
                    listaFavoritos->addItem(QString::fromStdString(prod.nombre + " (" + prod.categoria + ") - $" + ss.str()));
                    break;
                }
            }
        }
    }
    favoritosLayout->addWidget(listaFavoritos);
    mainLayout->addWidget(favoritosGroup);

    setLayout(mainLayout);
}