#include "dialogo_registro_nuevo.h"
#include "preferencias_dialogo.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

DialogoRegistroNuevo::DialogoRegistroNuevo(ArbolUsuarios* arbol, QWidget *parent)
    : QDialog(parent), arbolUsuarios(arbol)
{
    setWindowTitle("Registro de Nuevo Usuario");
    resize(400, 300);

    nombre = new QLineEdit(this);
    apellido = new QLineEdit(this);
    id = new QLineEdit(this);
    usuario = new QLineEdit(this);
    contrasena = new QLineEdit(this);
    contrasena->setEchoMode(QLineEdit::Password);

    auto *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Nombre:", this));
    layout->addWidget(nombre);
    layout->addWidget(new QLabel("Apellido:", this));
    layout->addWidget(apellido);
    layout->addWidget(new QLabel("ID:", this));
    layout->addWidget(id);
    layout->addWidget(new QLabel("Usuario:", this));
    layout->addWidget(usuario);
    layout->addWidget(new QLabel("Contraseña:", this));
    layout->addWidget(contrasena);

    auto *botonRegistrar = new QPushButton("Registrar", this);
    auto *botonCancelar = new QPushButton("Cancelar", this);

    connect(botonRegistrar, &QPushButton::clicked, this, &DialogoRegistroNuevo::accept);
    connect(botonCancelar, &QPushButton::clicked, this, &DialogoRegistroNuevo::reject);

    auto *layoutBotones = new QHBoxLayout;
    layoutBotones->addWidget(botonRegistrar);
    layoutBotones->addWidget(botonCancelar);

    layout->addLayout(layoutBotones);
    setLayout(layout);
}

void DialogoRegistroNuevo::accept() {
    if (nombre->text().isEmpty() || apellido->text().isEmpty() || id->text().isEmpty() ||
        usuario->text().isEmpty() || contrasena->text().isEmpty()) {
        QMessageBox::warning(this, "Error", "Todos los campos son obligatorios.");
        return;
    }

    perfil_usuario nuevoPerfil;
    nuevoPerfil.nombre = nombre->text().toStdString();
    nuevoPerfil.apellido = apellido->text().toStdString();
    nuevoPerfil.id = id->text().toStdString();
    nuevoPerfil.usuario = usuario->text().toStdString();
    nuevoPerfil.contraseña = contrasena->text().toStdString();

    arbolUsuarios->insertar(nuevoPerfil);

    PreferenciasDialogo dialogoPreferencias(this);
    if (dialogoPreferencias.exec() == QDialog::Accepted) {
        auto categorias = dialogoPreferencias.getCategoriasSeleccionadas();
        auto marcas = dialogoPreferencias.getMarcasSeleccionadas();
        
        NodoUsuario* nodo = arbolUsuarios->buscar(nuevoPerfil.usuario);
        if (nodo) {
            for (const auto& cat : categorias) {
                nodo->perfil.preferencias.agregarCategoria(cat);
            }
            for (const auto& marca : marcas) {
                nodo->perfil.preferencias.agregarMarca(marca);
            }
        }
    }

    QMessageBox::information(this, "Éxito", "Usuario registrado correctamente.");
    QDialog::accept();
}
