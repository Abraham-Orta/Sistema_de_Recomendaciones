#include "registro_dialog.h"
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

RegistroDialog::RegistroDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Registro de Usuario");
    resize(300, 200);

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

    connect(botonRegistrar, &QPushButton::clicked, this, &QDialog::accept);
    connect(botonCancelar, &QPushButton::clicked, this, &QDialog::reject);

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

perfil_usuario RegistroDialog::obtenerPerfil() const {
    perfil_usuario perfil;
    perfil.nombre = nombre->text().toStdString();
    perfil.apellido = apellido->text().toStdString();
    perfil.id = id->text().toStdString();
    perfil.contraseña = contrasena->text().toStdString();
    return perfil;
}