#include <QApplication>
#include <QFile>
#include <QString>
#include "ventana_inicial.h"
#include "arbol_usuarios.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Cargar y aplicar la hoja de estilos
    QFile styleSheetFile(":/styles.qss");
    if (styleSheetFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString styleSheet = QLatin1String(styleSheetFile.readAll());
        app.setStyleSheet(styleSheet);
        styleSheetFile.close();
    }

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