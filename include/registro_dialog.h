#ifndef REGISTRO_DIALOG_H
#define REGISTRO_DIALOG_H

#include <QDialog>
#include <QLineEdit>
#include "perfil_usuario.h"

class RegistroDialog : public QDialog {
    Q_OBJECT
public:
    explicit RegistroDialog(QWidget *parent = nullptr);

    perfil_usuario obtenerPerfil() const;

protected:
    void accept() override; // Sobrescribimos accept para validar

private:
    QLineEdit *nombre;
    QLineEdit *apellido;
    QLineEdit *id;
    QLineEdit *contrasena;
};

#endif // REGISTRO_DIALOG_H