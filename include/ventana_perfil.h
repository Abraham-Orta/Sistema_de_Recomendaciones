#ifndef VENTANA_PERFIL_H
#define VENTANA_PERFIL_H

#include <QDialog>
#include <QListWidget>
#include <QLabel>
#include <vector>
#include "perfil_usuario.h"
#include "producto.h"

class VentanaPerfil : public QDialog {
    Q_OBJECT
public:
    explicit VentanaPerfil(const perfil_usuario& perfil, const std::vector<Producto>& todosLosProductos, QWidget *parent = nullptr);

private:
    QListWidget* listaComprados;
    QListWidget* listaFavoritos;
    QLabel* labelComprados;
    QLabel* labelFavoritos;
};

#endif // VENTANA_PERFIL_H