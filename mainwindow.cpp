#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_controlador = new Controlador();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::limpiar()
{
    // Coloca los valores por defecto
    ui->in_nombre->setText("");
    ui->in_horas->setValue(0);
    ui->in_matutina->setChecked(true);
    ui->in_nombre->setFocus();
}

void MainWindow::calcular()
{
    // Obteber datos de la GUI
    QString nombre = ui->in_nombre->text();
    int horas = ui->in_horas->value();
    TipoJornada jornada;

    if (ui->in_matutina->isChecked()){
        jornada = TipoJornada::Matutina;
    } else if (ui->in_vespertina->isChecked()){
        jornada = TipoJornada::Vespertina;
    } else {
        jornada = TipoJornada::Nocturna;
    }

    // Validar datos (Mensaje de warning)
    if(nombre == "" || horas == 0){
        QMessageBox msgBox;

        QMessageBox::warning(
                    this,
                    "Advertencia",
                    "Alguno de los campos se encuentra vacio");
        return;
    }

    // Agregar obrero al controlador
    m_controlador->agregarObrero(nombre, horas, jornada);

    // Calcular
    if (m_controlador->calcularSalario()){
        ui->out_resultado->appendPlainText(m_controlador->obrero()->toString());
        // Limpiar la interfaz
        limpiar();
        ui->statusbar->showMessage("Calculos procesados para " + nombre, 2000);

    }else{
        QMessageBox::critical(
                    this,
                    "Error",
                    "Error al calcular el salario.\n"
                    "No se agrega el objeto obrero al controlador.");
    }
}

void MainWindow::guardar()
{
    /* Abrir cuadro de dialogo para
     * seleccionar una ubicacion para
     * guardar un archivo */
    QString nombreArchivo = QFileDialog::getSaveFileName(this,
                                                         "Guardar datos",
                                                         QDir::home().absolutePath(),
                                                         "Archivos de texto (*.txt)");
    qDebug() << nombreArchivo;

    // Crear un objeto QFile
    QFile archivo(nombreArchivo);
    // Abrir archivo para escritura
    if(archivo.open(QFile::WriteOnly | QFile::Truncate)){
        QTextStream salida(&archivo);
        salida << ui->out_resultado->toPlainText();
        ui->statusbar->showMessage("Datos almacenados en " + nombreArchivo, 3000);

    }else{
        QMessageBox::warning(
                    this,
                    "Guardar informacion",
                    "No se pudo guardar la informacion");
    }
}

void MainWindow::on_actionCalcular_triggered()
{
    calcular();
}


void MainWindow::on_btn_calcular_clicked()
{
    calcular();
}

void MainWindow::on_actionGuardar_triggered()
{
    guardar();
}

