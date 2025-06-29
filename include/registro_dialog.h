#ifndef REGISTRO_DIALOG_H
#define REGISTRO_DIALOG_H

#include <QDialog>
#include <QLineEdit>
#include "perfil_usuario.h"
#include "arbol_usuarios.h"

class RegistroDialog : public QDialog {
    Q_OBJECT
public:
    explicit RegistroDialog(ArbolUsuarios* arbol, QWidget *parent = nullptr);

    std::string obtenerUsuario() const;
    std::string obtenerContraseña() const;

protected:
    void accept() override;

private:
    QLineEdit *usuario;
    QLineEdit *contrasena;
    ArbolUsuarios* arbolUsuarios;
};

#endif