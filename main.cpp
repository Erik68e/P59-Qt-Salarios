#include "salarios.h"
#include "obrero.h"
#include "controlador.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Salarios w;
    w.show();

    //Obrero *objObrero1 = new Obrero("Juan",47,TipoJornada::Vespertina);
    /*
    qDebug() << objObrero1 -> nombre() << objObrero1 -> horas();
    switch(objObrero1->jornada()){
        case TipoJornada::Matutina:
            qDebug() << "matutina";
        break;
        case TipoJornada::Vespertina:
            qDebug() << "vespertina";
        break;
        case TipoJornada::Nocturna:
            qDebug() << "nocturna";
        break;
    }
    */

    Controlador *obj = new Controlador();

    obj -> agregarObrero("Juan",47,TipoJornada::Vespertina);

    if(obj -> calcularSalario()){
        qDebug() << obj -> obrero() -> toString();
    }else{

    }

    return a.exec();
}
