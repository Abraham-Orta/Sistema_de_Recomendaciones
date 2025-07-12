
#ifndef PREFERENCIAS_DIALOGO_H
#define PREFERENCIAS_DIALOGO_H

#include <QDialog>
#include <QCheckBox>
#include <vector>

class PreferenciasDialogo : public QDialog {
    Q_OBJECT

public:
    explicit PreferenciasDialogo(QWidget *parent = nullptr);
    std::vector<std::string> getCategoriasSeleccionadas() const;
    std::vector<std::string> getMarcasSeleccionadas() const;

private:
    std::vector<QCheckBox*> checkboxesCategorias;
    
    std::vector<QCheckBox*> checkboxesMarcas;
};

#endif // PREFERENCIAS_DIALOGO_H
