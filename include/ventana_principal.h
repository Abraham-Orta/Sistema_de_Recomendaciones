#ifndef VENTANA_PRINCIPAL_H
#define VENTANA_PRINCIPAL_H

#include <QWidget>
#include "perfil_usuario.h"
#include "producto.h"
#include <vector>
#include <QGridLayout>

class VentanaPrincipal : public QWidget {
    Q_OBJECT
public:
    explicit VentanaPrincipal(perfil_usuario& usuario, QWidget *parent = nullptr);

private:
    void actualizarRecomendaciones();
    void mostrarProductos(const std::vector<Producto>& productosMostrados);
    perfil_usuario& usuarioRegistrado;
    std::vector<Producto> productos;
    QGridLayout* gridLayout;
};

#endif // VENTANA_PRINCIPAL_H