#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>

#include "controlador.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionCalcular_triggered();
    void on_btn_calcular_clicked();

    void on_actionGuardar_triggered();

    void on_actionNuevo_triggered();

    void on_actionAbrir_triggered();

private:
    Ui::MainWindow *ui;
    Controlador *m_controlador;

    void limpiar();
    void calcular();
    void guardar();
    void abrir();
};
#endif // MAINWINDOW_H
