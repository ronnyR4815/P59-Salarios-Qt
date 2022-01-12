#include "acercade.h"
#include "ui_acercade.h"

Acercade::Acercade(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Acercade)
{
    ui->setupUi(this);
}

Acercade::~Acercade()
{
    delete ui;
}

void Acercade::setVersion(const QString &newVersion)
{
    m_version = newVersion;
    ui->title->setText("Salarios " + m_version);
}

void Acercade::setValor(int newValor)
{
    valor = newValor;
}
