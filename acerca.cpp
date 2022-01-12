#include "acerca.h"
#include "ui_acerca.h"

Acerca::Acerca(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Acerca)
{
    ui->setupUi(this);
    m_valor = 5;
}

Acerca::~Acerca()
{
    delete ui;
}

void Acerca::setN_version(const QString &newN_version)
{
    n_version = newN_version;
    this -> ui->lblnombre->setText("Salarios" + n_version);
}

int Acerca::valor() const
{
    return m_valor;
}
