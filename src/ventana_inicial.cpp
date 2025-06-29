#include "ventana_inicial.h"
#include "registro_dialog.h"
#include "dialogo_registro_nuevo.h"
#include "ventana_principal.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>

VentanaInicial::VentanaInicial(ArbolUsuarios* arbol, QWidget *parent)
    : QWidget(parent), arbolUsuarios(arbol)
{
    setWindowTitle("Bienvenido");
    resize(300, 150);

    auto *botonLogin = new QPushButton("Iniciar Sesión", this);
    auto *botonRegistro = new QPushButton("Registrarse", this);

    connect(botonLogin, &QPushButton::clicked, this, &VentanaInicial::abrirDialogoLogin);
    connect(botonRegistro, &QPushButton::clicked, this, &VentanaInicial::abrirDialogoRegistro);

    auto *layout = new QVBoxLayout(this);
    layout->addWidget(botonLogin);
    layout->addWidget(botonRegistro);
    setLayout(layout);
}

void VentanaInicial::abrirDialogoLogin() {
    RegistroDialog dialogoLogin(arbolUsuarios, this);
    if (dialogoLogin.exec() == QDialog::Accepted) {
        perfil_usuario* usuario = arbolUsuarios->buscar(dialogoLogin.obtenerUsuario());
        if (usuario && usuario->contraseña == dialogoLogin.obtenerContraseña()) {
            hide(); // Ocultamos la ventana inicial en lugar de cerrarla
            VentanaPrincipal *tienda = new VentanaPrincipal(*usuario);
            tienda->setAttribute(Qt::WA_DeleteOnClose); // Asegurarse de que se destruya al cerrar
            connect(tienda, &VentanaPrincipal::destroyed, this, &VentanaInicial::show);
            tienda->show();
        } else {
            QMessageBox::warning(this, "Error", "Usuario o contraseña incorrectos.");
        }
    }
}

void VentanaInicial::abrirDialogoRegistro() {
    DialogoRegistroNuevo dialogoRegistro(arbolUsuarios, this);
    dialogoRegistro.exec();
}
