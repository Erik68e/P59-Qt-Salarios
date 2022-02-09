#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include <QObject>
#include <QDebug>

#include "obrero.h"

#define MATUTINO 2.65
#define VESPERTINO 2.73
#define NOCTURNO 2.87

#define HORA_EXTRA 50
#define IESS 9.5

class Controlador : public QObject
{
    Q_OBJECT
public:
    explicit Controlador(QObject *parent = nullptr);
    bool agregarObrero(QString nombre, int horas, TipoJornada jornada);
    bool calcularSalario();

    Obrero *obrero() const;

    QString ttlBr();
    QString ttlIv();
    QString ttlTo();

signals:

private:
    Obrero *m_obrero;

    double m_ttlBruto = 0;
    double m_ttlIESS = 0;
    double m_ttlNeto = 0;
};

#endif // CONTROLADOR_H
