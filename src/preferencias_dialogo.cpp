
#include "preferencias_dialogo.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

PreferenciasDialogo::PreferenciasDialogo(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Seleccionar Preferencias");
    resize(400, 400);

    auto *layoutPrincipal = new QVBoxLayout(this);

    // Categorías
    layoutPrincipal->addWidget(new QLabel("Categorías de interés:", this));
    std::vector<std::string> categorias = {"Electrónica", "Hogar y cocina", "Moda y Accesorios", "Deportes y Aire Libre", "Cuidado personal y belleza"};
    for (const auto& cat : categorias) {
        QCheckBox* checkbox = new QCheckBox(QString::fromStdString(cat), this);
        checkboxesCategorias.push_back(checkbox);
        layoutPrincipal->addWidget(checkbox);
    }

    // Marcas
    layoutPrincipal->addWidget(new QLabel("Marcas de preferencia:", this));
    std::vector<std::string> marcas = {"Samsung", "Apple", "Nike", "Adidas", "Sony", "LG", "Philips", "Zara", "H&M", "Puma"};
    for (const auto& marca : marcas) {
        QCheckBox* checkbox = new QCheckBox(QString::fromStdString(marca), this);
        checkboxesMarcas.push_back(checkbox);
        layoutPrincipal->addWidget(checkbox);
    }

    auto *botonAceptar = new QPushButton("Aceptar", this);
    connect(botonAceptar, &QPushButton::clicked, this, &PreferenciasDialogo::accept);
    layoutPrincipal->addWidget(botonAceptar);

    setLayout(layoutPrincipal);
}

std::vector<std::string> PreferenciasDialogo::getCategoriasSeleccionadas() const {
    std::vector<std::string> seleccionadas;
    for (const auto& checkbox : checkboxesCategorias) {
        if (checkbox->isChecked()) {
            seleccionadas.push_back(checkbox->text().toStdString());
        }
    }
    return seleccionadas;
}

std::vector<std::string> PreferenciasDialogo::getMarcasSeleccionadas() const {
    std::vector<std::string> seleccionadas;
    for (const auto& checkbox : checkboxesMarcas) {
        if (checkbox->isChecked()) {
            seleccionadas.push_back(checkbox->text().toStdString());
        }
    }
    return seleccionadas;
}
