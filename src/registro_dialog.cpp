#include "registro_dialog.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

RegistroDialog::RegistroDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Registro de Usuario");
    resize(600, 400);

    nombre = new QLineEdit(this);
    apellido = new QLineEdit(this);
    id = new QLineEdit(this);
    contrasena = new QLineEdit(this);
    contrasena->setEchoMode(QLineEdit::Password);

    auto *etiquetaNombre = new QLabel("Nombre:", this);
    auto *etiquetaApellido = new QLabel("Apellido:", this);
    auto *etiquetaId = new QLabel("ID:", this);
    auto *etiquetaContrasena = new QLabel("Contraseña:", this);

    auto *botonRegistrar = new QPushButton("Registrar", this);
    auto *botonCancelar = new QPushButton("Cancelar", this);

    connect(botonRegistrar, &QPushButton::clicked, this, &RegistroDialog::accept);
    connect(botonCancelar, &QPushButton::clicked, this, &RegistroDialog::reject);

    auto *layoutFormulario = new QVBoxLayout;
    layoutFormulario->addWidget(etiquetaNombre);
    layoutFormulario->addWidget(nombre);
    layoutFormulario->addWidget(etiquetaApellido);
    layoutFormulario->addWidget(apellido);
    layoutFormulario->addWidget(etiquetaId);
    layoutFormulario->addWidget(id);
    layoutFormulario->addWidget(etiquetaContrasena);
    layoutFormulario->addWidget(contrasena);

    auto *layoutBotones = new QHBoxLayout;
    layoutBotones->addWidget(botonRegistrar);
    layoutBotones->addWidget(botonCancelar);

    layoutFormulario->addLayout(layoutBotones);
    setLayout(layoutFormulario);
}

void RegistroDialog::accept() {
    if (nombre->text().isEmpty() ||
        apellido->text().isEmpty() ||
        id->text().isEmpty() ||
        contrasena->text().isEmpty()) {
        QMessageBox::warning(this, "Campos incompletos", "Por favor, completa todos los campos para registrarte.");
        return;
    }
    QDialog::accept();
}

perfil_usuario RegistroDialog::obtenerPerfil() const {
    perfil_usuario perfil;
    perfil.nombre = nombre->text().toStdString();
    perfil.apellido = apellido->text().toStdString();
    perfil.id = id->text().toStdString();
    perfil.contraseña = contrasena->text().toStdString();
    return perfil;
}