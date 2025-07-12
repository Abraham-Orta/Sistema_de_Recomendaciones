
#include "preferencias_dialogo.h"

PreferenciasDialogo::PreferenciasDialogo(QWidget *parent) : QDialog(parent) {
    setupUI();
}

void PreferenciasDialogo::setupUI() {
    QVBoxLayout *layout = new QVBoxLayout(this);
    
    // Aquí agregarías los checkboxes para las categorías y marcas
    // Por ejemplo:
    checkboxesCategorias.push_back(new QCheckBox("Electrónica", this));
    checkboxesCategorias.push_back(new QCheckBox("Ropa", this));
    checkboxesCategorias.push_back(new QCheckBox("Hogar", this));

    for (auto checkbox : checkboxesCategorias) {
        layout->addWidget(checkbox);
    }

    checkboxesMarcas.push_back(new QCheckBox("Sony", this));
    checkboxesMarcas.push_back(new QCheckBox("Samsung", this));
    checkboxesMarcas.push_back(new QCheckBox("Nike", this));

    for (auto checkbox : checkboxesMarcas) {
        layout->addWidget(checkbox);
    }

    QPushButton *botonAceptar = new QPushButton("Aceptar", this);
    connect(botonAceptar, &QPushButton::clicked, this, &QDialog::accept);
    layout->addWidget(botonAceptar);

    setLayout(layout);
}

std::vector<std::string> PreferenciasDialogo::getCategoriasSeleccionadas() const {
    std::vector<std::string> seleccionadas;
    for (const auto checkbox : checkboxesCategorias) {
        if (checkbox->isChecked()) {
            seleccionadas.push_back(checkbox->text().toStdString());
        }
    }
    return seleccionadas;
}

std::vector<std::string> PreferenciasDialogo::getMarcasSeleccionadas() const {
    std::vector<std::string> seleccionadas;
    for (const auto checkbox : checkboxesMarcas) {
        if (checkbox->isChecked()) {
            seleccionadas.push_back(checkbox->text().toStdString());
        }
    }
    return seleccionadas;
}
