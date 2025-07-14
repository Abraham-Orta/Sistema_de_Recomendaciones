#ifndef VENTANA_INICIAL_H
#define VENTANA_INICIAL_H

#include <QWidget>
#include <QPushButton>
#include "arbol_usuarios.h"

class VentanaInicial : public QWidget {
    Q_OBJECT

public:
    explicit VentanaInicial(ArbolUsuarios* arbol, QWidget *parent = nullptr);

private slots:
    void abrirDialogoLogin();
    void abrirDialogoRegistro();
    void toggleTema(); // Nueva función para cambiar el tema

private:
    ArbolUsuarios* arbolUsuarios;
    QPushButton* botonTema; // Declaración del botón de tema
};

#endif // VENTANA_INICIAL_H
