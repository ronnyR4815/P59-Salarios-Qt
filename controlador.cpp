#include "controlador.h"

Controlador::Controlador(QObject *parent) : QObject(parent)
{
    this->m_obrero = nullptr;
    this->m_total_SalBruto = 0;
    this->m_total_IESS = 0;
    this->m_total_SalNeto = 0;
}

bool Controlador::agregarObrero(QString nombre, int horas, TipoJornada jornada)
{
    this->m_obrero = new Obrero(nombre,horas,jornada);
    return true;
}

bool Controlador::calcularSalario()
{
    // Validar que el obrero no sea nulo
    if (m_obrero == nullptr)
        return false;

    // Deternimar el valor hora
    double valorHora = 0;
    switch(m_obrero->jornada()){
    case TipoJornada::Vespertina:
        valorHora = VESPERTINO;
        break;
    case TipoJornada::Matutina:
        valorHora = MATITUNO;
        break;
    case TipoJornada::Nocturna:
        valorHora = NOCTURNO;
        break;
    default:
        return false;
    }

    // Calculo de la horas extra
    int horas = m_obrero->horas();
    int horasExtra = 0;

    if (m_obrero->horas() > 40){
        horasExtra = m_obrero->horas() - 40;
        horas = 40;
    }

    // Calculo del salario
    double salarioBruto = horas * valorHora + horasExtra * (HORA_EXTRA * valorHora / 100);

    // Calculo del descuento
    double descuento = salarioBruto * IESS / 100;

    // Calculo del salario neto (a recibir)
    double salarioNeto = salarioBruto - descuento;

    // Calcular totales
    m_total_SalBruto += salarioBruto;
    m_total_IESS += descuento;
    m_total_SalNeto += salarioNeto;

    // Establecer valores al objeto
    m_obrero->setSalarioBruto(salarioBruto);
    m_obrero->setDescuento(descuento);
    m_obrero->setSalarioNeto(salarioNeto);
    // Retirnar true (todo se calculo correctamente)
    return true;
}

Obrero *Controlador::obrero() const
{
    return m_obrero;
}

double Controlador::total_SalBruto() const
{
    return m_total_SalBruto;
}

double Controlador::total_IESS() const
{
    return m_total_IESS;
}

double Controlador::total_SalNeto() const
{
    return m_total_SalNeto;
}

void Controlador::setTotal_SalBruto(double newTotal_SalBruto)
{
    m_total_SalBruto = newTotal_SalBruto;
}

void Controlador::setTotal_IESS(double newTotal_IESS)
{
    m_total_IESS = newTotal_IESS;
}

void Controlador::setTotal_SalNeto(double newTotal_SalNeto)
{
    m_total_SalNeto = newTotal_SalNeto;
}
