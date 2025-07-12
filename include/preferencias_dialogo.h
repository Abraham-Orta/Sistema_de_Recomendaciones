
#ifndef PREFERENCIAS_DIALOGO_H
#define PREFERENCIAS_DIALOGO_H

#include <QDialog>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <vector>
#include <string>

class PreferenciasDialogo : public QDialog {
    Q_OBJECT

public:
    explicit PreferenciasDialogo(QWidget *parent = nullptr);
    std::vector<std::string> getCategoriasSeleccionadas() const;
    std::vector<std::string> getMarcasSeleccionadas() const;

private:
    void setupUI();
    
    std::vector<QCheckBox*> checkboxesCategorias;
    std::vector<QCheckBox*> checkboxesMarcas;
    std::vector<std::string> categoriasSeleccionadas;
    std::vector<std::string> marcasSeleccionadas;
};

#endif // PREFERENCIAS_DIALOGO_H
