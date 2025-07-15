#ifndef VENTANA_PRINCIPAL_H
#define VENTANA_PRINCIPAL_H

#include <QWidget>
#include <QComboBox> // Added for QComboBox
#include <QPushButton>
#include <QLineEdit>
#include <QTimer>
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
    void aplicarFiltrosYMostrarProductos(); // Nueva función para aplicar todos los filtros
    perfil_usuario& usuarioRegistrado;
    std::vector<Producto> productos;
    QGridLayout* gridLayout;
    QComboBox* comboPrecios; // Nuevo QComboBox para precios
    QComboBox* comboCategorias; // Nuevo QComboBox para categorías
    QPushButton* botonTema; // Nuevo QPushButton para cambiar el tema
    QLineEdit* lineEditDescripcion; // Nuevo QLineEdit para la descripción
    QTimer* debounceTimer;

#include "filtrar_descripcion.h"

private slots:
    void toggleTema(); // Nueva función para cambiar el tema
};

#endif // VENTANA_PRINCIPAL_H