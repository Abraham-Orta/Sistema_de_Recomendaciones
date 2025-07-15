#include "ventana_inicial.h"
#include "registro_dialog.h"
#include "dialogo_registro_nuevo.h"
#include "ventana_principal.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QLabel>
#include <QFont>
#include <Qt>
#include <QFile> // Incluir QFile
#include <QApplication> // Incluir QApplication

VentanaInicial::VentanaInicial(ArbolUsuarios* arbol, QWidget *parent)
    : QWidget(parent), arbolUsuarios(arbol)
{
    setWindowTitle("Bienvenido");
    resize(650, 400); 

    // Título de la tienda
    QLabel *tituloTienda = new QLabel("Tienda Guayana", this);
    QFont font = tituloTienda->font();
    font.setPointSize(45); // Tamaño de fuente grande
    font.setBold(true);    // Negrita
    tituloTienda->setFont(font);
    tituloTienda->setAlignment(Qt::AlignCenter); // Centrar el texto

    auto *botonLogin = new QPushButton("Iniciar Sesión", this);
    auto *botonRegistro = new QPushButton("Registrarse", this);

    // Botón para cambiar el tema
    botonTema = new QPushButton("Cambiar Tema", this);

    connect(botonLogin, &QPushButton::clicked, this, &VentanaInicial::abrirDialogoLogin);
    connect(botonRegistro, &QPushButton::clicked, this, &VentanaInicial::abrirDialogoRegistro);
    connect(botonTema, &QPushButton::clicked, this, &VentanaInicial::toggleTema); // Conectar el botón de tema

    auto *layout = new QVBoxLayout(this);
    layout->addWidget(tituloTienda); // Añadir el título al layout
    layout->addStretch(); // Espacio flexible para empujar los botones hacia abajo
    layout->addWidget(botonLogin);
    layout->addWidget(botonRegistro);
    layout->addWidget(botonTema); // Añadir el botón de tema al layout
    layout->addStretch(); // Espacio flexible al final
    setLayout(layout);
}

void VentanaInicial::abrirDialogoLogin() {
    RegistroDialog dialogoLogin(arbolUsuarios, this);
    if (dialogoLogin.exec() == QDialog::Accepted) {
        NodoUsuario* nodo = arbolUsuarios->buscar(dialogoLogin.obtenerUsuario());
        if (nodo && nodo->perfil.contraseña == dialogoLogin.obtenerContraseña()) {
            hide();
            VentanaPrincipal *tienda = new VentanaPrincipal(nodo->perfil);
            tienda->setAttribute(Qt::WA_DeleteOnClose);
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

void VentanaInicial::toggleTema() {
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
