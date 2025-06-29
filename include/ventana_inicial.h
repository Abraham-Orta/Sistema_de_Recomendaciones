#ifndef VENTANA_INICIAL_H
#define VENTANA_INICIAL_H

#include <QWidget>
#include "arbol_usuarios.h"

class VentanaInicial : public QWidget {
    Q_OBJECT

public:
    explicit VentanaInicial(ArbolUsuarios* arbol, QWidget *parent = nullptr);

private slots:
    void abrirDialogoLogin();
    void abrirDialogoRegistro();

private:
    ArbolUsuarios* arbolUsuarios;
};

#endif // VENTANA_INICIAL_H
