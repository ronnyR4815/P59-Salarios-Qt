#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include <QObject>

#include "obrero.h"

#define MATITUNO 2.65
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
    double total_SalBruto() const;
    double total_IESS() const;
    double total_SalNeto() const;
    void setTotal_SalBruto(double newTotal_SalBruto);
    void setTotal_IESS(double newTotal_IESS);
    void setTotal_SalNeto(double newTotal_SalNeto);

signals:

private:
    Obrero *m_obrero;
    double m_total_SalBruto;
    double m_total_IESS;
    double m_total_SalNeto;
};

#endif // CONTROLADOR_H
