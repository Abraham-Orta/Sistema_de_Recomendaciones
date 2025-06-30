#ifndef VENTANA_PRINCIPAL_H
#define VENTANA_PRINCIPAL_H

#include <QWidget>
#include <QListWidget>
#include "perfil_usuario.h"
#include "producto.h"
#include <vector>

class VentanaPrincipal : public QWidget {
    Q_OBJECT
public:
    explicit VentanaPrincipal(perfil_usuario& usuario, QWidget *parent = nullptr);


private:
    void actualizarRecomendaciones();
    perfil_usuario& usuarioRegistrado;
    std::vector<Producto> productos;
    QListWidget *lista;
};

#endif // VENTANA_PRINCIPAL_H