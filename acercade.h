#ifndef ACERCADE_H
#define ACERCADE_H

#include <QDialog>

namespace Ui {
class Acercade;
}

class Acercade : public QDialog
{
    Q_OBJECT

public:
    explicit Acercade(QWidget *parent = nullptr);
    ~Acercade();

    void setVersion(const QString &newVersion);

    void setValor(int newValor);

private:
    Ui::Acercade *ui;
    QString m_version;
    int valor;
};

#endif // ACERCADE_H
