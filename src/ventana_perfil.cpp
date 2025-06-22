#include "ventana_perfil.h"
#include <QVBoxLayout>
#include <QLabel>

VentanaPerfil::VentanaPerfil(const perfil_usuario& perfil, QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Perfil de Usuario");
    auto *layout = new QVBoxLayout(this);

    layout->addWidget(new QLabel(QString::fromStdString("Nombre: " + perfil.nombre), this));
    layout->addWidget(new QLabel(QString::fromStdString("Apellido: " + perfil.apellido), this));
    layout->addWidget(new QLabel(QString::fromStdString("ID: " + perfil.id), this));
    layout->addWidget(new QLabel(QString::fromStdString("Contraseña: " + perfil.contraseña), this));

    setLayout(layout);
}