#ifndef VENTANA_PERFIL_H
#define VENTANA_PERFIL_H

#include <QDialog>
#include "perfil_usuario.h"

class VentanaPerfil : public QDialog {
    Q_OBJECT
public:
    explicit VentanaPerfil(const perfil_usuario& perfil, QWidget *parent = nullptr);
};

#endif // VENTANA_PERFIL_H