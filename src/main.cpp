#include <QApplication>
#include "ventana_inicial.h"
#include "arbol_usuarios.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    ArbolUsuarios arbolUsuarios;

    // Usuario de prueba
    perfil_usuario usuarioPrueba;
    usuarioPrueba.nombre = "Abraham";
    usuarioPrueba.apellido = "Orta";
    usuarioPrueba.id = "1";
    usuarioPrueba.usuario = "abraham33";
    usuarioPrueba.contraseña = "1234";
    arbolUsuarios.insertar(usuarioPrueba);

    VentanaInicial ventanaInicial(&arbolUsuarios);
    ventanaInicial.show();

    return app.exec();
}