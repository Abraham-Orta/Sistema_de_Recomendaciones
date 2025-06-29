#ifndef DIALOGO_REGISTRO_NUEVO_H
#define DIALOGO_REGISTRO_NUEVO_H

#include <QDialog>
#include <QLineEdit>
#include "arbol_usuarios.h"

class DialogoRegistroNuevo : public QDialog {
    Q_OBJECT

public:
    explicit DialogoRegistroNuevo(ArbolUsuarios* arbol, QWidget *parent = nullptr);

protected:
    void accept() override;

private:
    QLineEdit *nombre;
    QLineEdit *apellido;
    QLineEdit *id;
    QLineEdit *usuario;
    QLineEdit *contrasena;
    ArbolUsuarios* arbolUsuarios;
};

#endif // DIALOGO_REGISTRO_NUEVO_H
