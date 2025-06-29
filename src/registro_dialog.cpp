#include "registro_dialog.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

RegistroDialog::RegistroDialog(ArbolUsuarios* arbol, QWidget *parent)
    : QDialog(parent), arbolUsuarios(arbol)
{
    setWindowTitle("Inicio de Sesión");
    resize(300, 150);

    usuario = new QLineEdit(this);
    contrasena = new QLineEdit(this);
    contrasena->setEchoMode(QLineEdit::Password);

    auto *etiquetaUsuario = new QLabel("Usuario:", this);
    auto *etiquetaContrasena = new QLabel("Contraseña:", this);

    auto *botonLogin = new QPushButton("Login", this);
    auto *botonCancelar = new QPushButton("Cancelar", this);

    connect(botonLogin, &QPushButton::clicked, this, &RegistroDialog::accept);
    connect(botonCancelar, &QPushButton::clicked, this, &RegistroDialog::reject);

    auto *layoutFormulario = new QVBoxLayout;
    layoutFormulario->addWidget(etiquetaUsuario);
    layoutFormulario->addWidget(usuario);
    layoutFormulario->addWidget(etiquetaContrasena);
    layoutFormulario->addWidget(contrasena);

    auto *layoutBotones = new QHBoxLayout;
    layoutBotones->addWidget(botonLogin);
    layoutBotones->addWidget(botonCancelar);

    layoutFormulario->addLayout(layoutBotones);
    setLayout(layoutFormulario);
}

void RegistroDialog::accept() {
    if (usuario->text().isEmpty() || contrasena->text().isEmpty()) {
        QMessageBox::warning(this, "Campos incompletos", "Por favor, ingresa usuario y contraseña.");
        return;
    }
    QDialog::accept();
}

std::string RegistroDialog::obtenerUsuario() const {
    return usuario->text().toStdString();
}

std::string RegistroDialog::obtenerContraseña() const {
    return contrasena->text().toStdString();
}