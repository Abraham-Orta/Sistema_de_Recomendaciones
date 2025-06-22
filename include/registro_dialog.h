#ifndef REGISTRO_DIALOG_H
#define REGISTRO_DIALOG_H

#include <QDialog>
#include "perfil_usuario.h"

class QLineEdit;

class RegistroDialog : public QDialog {
    Q_OBJECT
public:
    explicit RegistroDialog(QWidget *parent = nullptr);

    perfil_usuario obtenerPerfil() const;

private:
    QLineEdit *nombre;
    QLineEdit *apellido;
    QLineEdit *id;
    QLineEdit *contrasena;
};

#endif // REGISTRO_DIALOG_H