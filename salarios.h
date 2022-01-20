#ifndef SALARIOS_H
#define SALARIOS_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QDebug>

#include "controlador.h"
#include "acerca.h"

#define VERSION " 1.1"

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

    void on_actionGuardar_triggered();

    void on_actionCalcular_triggered();

    void on_actionNuevo_triggered();

    void on_actionSalir_triggered();

    void on_actionAbrir_triggered();

    //void openTxt (const QString & fileName1);

    void on_actionAcerca_de_Salarios_triggered();

private:
    Ui::Salarios *ui;
    Controlador *m_controlador;
    void limpiar();
    void calcular();
    void guardar();
    void abrir();
};
#endif // SALARIOS_H
