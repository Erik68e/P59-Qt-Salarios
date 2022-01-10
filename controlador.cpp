#include "controlador.h"

Controlador::Controlador(QObject *parent) : QObject(parent)
{
    this -> m_obrero = nullptr;
}

bool Controlador::agregarObrero(QString nombre, int horas, TipoJornada jornada)
{
    this -> m_obrero = new Obrero(nombre,horas,jornada);
    return true;
}


bool Controlador::calcularSalario()
{
    if(m_obrero == nullptr)
        return false;

    // Determinar el valor hora
    double valorHora = 0;
    switch (m_obrero -> jornada()) {
        case TipoJornada::Vespertina:
            valorHora = VESPERTINO;
        break;
        case TipoJornada::Matutina:
            valorHora = MATUTINO;
        break;
        case TipoJornada::Nocturna:
            valorHora = NOCTURNO;
        break;
        default:
            return false;
    }
    // Calculo de las horas extra
    int horas = m_obrero -> horas();
    int horasExtra = 0;
    if(m_obrero -> horas() > 40){
        horasExtra = m_obrero -> horas() - 40;
        horas = 40;
    }
    // Calculo del salario
    double salarioBruto = horas * valorHora + horasExtra * (HORA_EXTRA * valorHora / 100);
    //Calcular de descuento
    double descuento = salarioBruto * IESS / 100;
    // Calculo del salario neto
    double salarioNeto = salarioBruto - descuento;
    //Establecer valores al objeto
    m_obrero -> setSalarioBruto(salarioBruto);
    m_obrero -> setDescuento(descuento);
    m_obrero -> setSalarioNeto(salarioNeto);
    // Retornar true (si todo es correcto)
    return true;
}

Obrero *Controlador::obrero() const
{
    return m_obrero;
}
