#include <QApplication>
#include "registro_dialog.h"
#include "ventana_principal.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    RegistroDialog registro;
    if (registro.exec() == QDialog::Accepted) {
        perfil_usuario nuevoUsuario = registro.obtenerPerfil();
        VentanaPrincipal tienda(nuevoUsuario);
        tienda.show();
        return app.exec();
    }

    return 0;
}