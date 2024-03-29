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
        // Imprimir en el cuadro de texto
        ui->out_resultado->appendPlainText(m_controlador->obrero()->toString());

        /* Calculo totales */
        ui->out_sal_bruto->setText(QString::number(m_controlador->total_SalBruto()));
        ui->out_IESS->setText(QString::number(m_controlador->total_IESS()));
        ui->out_sal_neto->setText(QString::number(m_controlador->total_SalNeto()));

        // Limpiar la interfaz
        limpiar();
        ui->statusbar->showMessage("Calculos procesados para " + nombre, 3000);

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
                                                         "Guardar archivo",
                                                         QDir::home().absoluteFilePath("downloads"),
                                                         "Archivos de salarios (*.slr)");

    // Crear un objeto QFile
    QFile archivo(nombreArchivo);
    // Abrir archivo para escritura
    if(archivo.open(QFile::WriteOnly | QFile::Truncate)){
        // Crear un "stream" de texto (flujo)
        QTextStream salida(&archivo);
        // Enviar los datos del resultado a la salida
        salida << ui->out_resultado->toPlainText();
        salida << "\n---------------------------\n";
        salida << ui->out_sal_bruto->text() << endl;
        salida << ui->out_IESS->text() << endl;
        salida << ui->out_sal_neto->text() << endl;
        // Mostrar informacion por 3 segundos que todo salio bien
        ui->statusbar->showMessage("Datos almacenados en " + nombreArchivo, 3000);

    }else{
        // Mensaje de error si no se puede abrir el archivo
        QMessageBox::warning(
                    this,
                    "Guardar informacion",
                    "No se pudo guardar la informacion");
    }
    // Cerrar el archivo
    archivo.close();
}

void MainWindow::abrir()
{
    /* Abrir cuadro de dialogo para
     * seleccionar una ubicacion para
     * guardar un archivo */
    QString nombreArchivo = QFileDialog::getOpenFileName(this,
                                                         "Abrir archivo",
                                                         QDir::home().absoluteFilePath("downloads"),
                                                         "Archivos de salarios (*.slr)");

    // Crear un objeto QFile
    QFile archivo(nombreArchivo);
    // Abrir archivo para escritura
    if(archivo.open(QFile::ReadOnly | QFile::Text)){
        // Crear un "stream" de texto (flujo)
        QTextStream entrada(&archivo);
        // Leer todo el contenido del archivo
        QString datos = "", total_bruto = "",
                total_IESS = "", total_neto = "";

        while(!entrada.atEnd()){
            datos += entrada.readLine() + "\n";
            if(datos.contains("-")){
                total_bruto = entrada.readLine();
                total_IESS = entrada.readLine();
                total_neto = entrada.readLine();
            }
        }

        // Cargar el contenido al area de texto
        ui->out_resultado->clear();
        ui->out_resultado->setPlainText(datos);
        // Cargar contenido a los LineEdit totales
        ui->out_sal_bruto->setText(total_bruto);
        ui->out_IESS->setText(total_IESS);
        ui->out_sal_neto->setText(total_neto);

        // Mostrar informacion por 3 segundos que todo salio bien
        ui->statusbar->showMessage("Datos almacenados en " + nombreArchivo, 3000);

    }else{
        // Mensaje de error si no se puede abrir el archivo
        QMessageBox::warning(
                    this,
                    "Abrir archivo",
                    "No se pudo abrir el archivo");
    }
    // Cerrar el archivo
    archivo.close();
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

void MainWindow::on_actionNuevo_triggered()
{
    limpiar();
    ui->out_resultado->clear();
    // Colocar valores de 0 en los LineEdit
    ui->out_sal_bruto->setText("0.00");
    ui->out_IESS->setText("0.00");
    ui->out_sal_neto->setText("0.00");
    // Inicializar en 0 las variables originales
    m_controlador->setTotal_SalBruto(0);
    m_controlador->setTotal_IESS(0);
    m_controlador->setTotal_SalNeto(0);
}

void MainWindow::on_actionAbrir_triggered()
{
    abrir();
}

void MainWindow::on_actionAcerca_de_triggered()
{
    // Crear objeto de la ventana que queremos invocar
    Acercade *dialogo = new Acercade(this);
    // Enviar parametro a ventana
    dialogo->setVersion(VERSION);
    // Mostrar ventana de dialogo MODAL
    dialogo->exec();
    // Obtener datos del dialogo
}

void MainWindow::on_actionSalir_triggered()
{
    exit(0);
}

