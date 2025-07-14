#ifndef VENTANA_PERFIL_H
#define VENTANA_PERFIL_H

#include <QDialog>
#include <QTableWidget>
#include <vector>
#include "perfil_usuario.h"
#include "producto.h"

class VentanaPerfil : public QDialog {
    Q_OBJECT

public:
    explicit VentanaPerfil(const perfil_usuario& perfil, const std::vector<Producto>& todosLosProductos, QWidget *parent = nullptr);

private:
    void llenarTabla(QTableWidget* tabla, const ListaEnlazadaString& idsProductos, const std::vector<Producto>& todosLosProductos);

    QTableWidget* tablaComprados;
    QTableWidget* tablaFavoritos;
};

#endif // VENTANA_PERFIL_H
