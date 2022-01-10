#ifndef SALARIOS_H
#define SALARIOS_H

#include <QMainWindow>

#include "controlador.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Salarios; }
QT_END_NAMESPACE

class Salarios : public QMainWindow
{
    Q_OBJECT

public:
    Salarios(QWidget *parent = nullptr);
    ~Salarios();

private slots:
    void on_cmdCalcular_clicked();
private:
    Ui::Salarios *ui;
    Controlador *m_controlador;
};
#endif // SALARIOS_H
