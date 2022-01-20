#include "salarios.h"
#include "ui_salarios.h"


Salarios::Salarios(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Salarios)
{
    ui->setupUi(this);
    m_controlador = new Controlador();
}

Salarios::~Salarios()
{
    delete ui;
}

void Salarios::on_cmdCalcular_clicked()
{
   calcular();
}


void Salarios::limpiar()
{
    ui->inNombre->setText("");
    ui->inHoras->setValue(0);
    ui->inMatutino->setChecked(true);
    ui->inNombre->setFocus();

}

void Salarios::calcular()
{
    // Obtener datos de la GUI
    QString nombre = ui->inNombre->text();
    int horas = ui -> inHoras -> value();
    TipoJornada jornada;
    if(ui->inMatutino->isChecked()){
        jornada = TipoJornada::Matutina;
    }else if(ui->inVespertina->isChecked()){
        jornada = TipoJornada::Vespertina;
    }else{
        jornada = TipoJornada::Nocturna;
    }
    //Validar datos correctos
    if(nombre == "" || horas == 0){
        /*
        QMessageBox msgBox;
        msgBox.setText("El nombre o el numero de horas esta vacio");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
        */
        QMessageBox::warning(this,"Advertencia", "El nombre o el numero de horas esta vacio");
        return;
    }
    //Agregar obrero al controlador
    m_controlador->agregarObrero(nombre,horas,jornada);
    //Calcular
    if(m_controlador->calcularSalario()){
        //Muestra los resultados de los calculos del obrero
        ui->outResultado->appendPlainText(m_controlador->obrero()->toString());
        ui->outSubtotal->setText(m_controlador->ttlBr());
        ui->outIva->setText(m_controlador->ttlIv());
        ui->outTotal->setText(m_controlador->ttlTo());
        // Limpiar la interfaz
        limpiar();
        // Mostrar mensage por 5 segundos en la barra de estado
        ui->statusbar->showMessage("Calculos procesados para " + nombre,5000);
    }else{
        QMessageBox::critical(this,
                              "Error",
                              "Error al calcular el salario.");
    }

}

void Salarios::guardar()
{
    // Abrir cuadro de dialogo para seleccionar ubicacion y nombre del archivo
    QString nombreArchivo = QFileDialog::getSaveFileName(this,
                                                         "Guardar datos",
                                                         QDir::home().absolutePath(),
                                                         "Archivo de salarios (*.slr)");
    qDebug() << nombreArchivo;
    // Crear un objeto QFile
    QFile archivo(nombreArchivo);
    // Abrir para escritura
    if(archivo.open(QFile::WriteOnly | QFile::Truncate)){
        // Crear un stream de texto
        QTextStream salida(&archivo);
        // Enviar los datos del resultado a la salida
        salida << ui->outResultado->toPlainText();
        salida << "_______________________" << endl;
        salida << "Subtotal: " << endl;
        salida << ui->outSubtotal->text();
        salida << "IVA: " << endl;
        salida << ui->outIva->text();
        salida << "Total: " << endl;
        salida << ui->outTotal->text();
        // Mostrar 5 segundos que todo fue bien
        ui->statusbar->showMessage("Datos almacenados en " + nombreArchivo,5000);
    }else{
        // Mensaje de error si no se puede abrir el archivo
        QMessageBox::warning(this,
                             "Guardar datos",
                             "No se pudo guardar los datos");
    }
    //Cerrar archivo
    archivo.close();
}
// Abrir archivos primera forma
/*
void Salarios::abrir()
{
    // Obtener la ruta del archivo
       QString fileName = QFileDialog::getOpenFileName(this,
                                                       tr("Excel file"),
                                                       "./",
                                                       tr ("Archivos Texto (*.txt)"));
    if(!fileName.isEmpty()){
       qDebug () << "Formato = txt";
       openTxt(fileName);
    }
}
// Abrir * .txt
void Salarios::openTxt(const QString &fileName1)
{
    QFile file (fileName1); // Cree un nuevo objeto QFile
    if (!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox :: warning (this, tr ("Abrir archivo txt"),
                               tr ("No se puede leer el archivo% 1: | n% 2.")
                               .arg(fileName1), (file.errorString()));
        return ;
    }
    QTextStream in (& file); // Nuevo objeto de flujo de texto
    ui->outResultado->setPlainText(in.readAll());
}
*/
// Abrir archivos segunda forma
void Salarios::abrir()
{
    // Abrir cuadro de dialogo para seleccionar ubicacion y nombre del archivo
    QString nombreArchivo = QFileDialog::getSaveFileName(this,
                                                         "Guardar datos",
                                                         QDir::home().absolutePath(),
                                                         "Archivo de salarios (*.slr)");
    qDebug() << nombreArchivo;
    // Crear un objeto QFile
    QFile archivo(nombreArchivo);
    // Abrir para LECTURA
    if(archivo.open(QFile::ReadOnly)){
        // Crear un stream de texto
        QTextStream entrada(&archivo);
        // Leer todo el contenido del archivo
        QString datos = "", hasta = "";
        while(entrada.atEnd() == false && hasta != "_______________________") {
           hasta = entrada.readLine();
           datos += hasta + "\n";
        }



        // Cargar todo el contenido a la area del texto
        ui->outResultado->clear();
        ui->outResultado->setPlainText(datos);
        ui->outSubtotal->text();
        ui->outIva->text();
        ui->outTotal->text();
        // Mostrar 5 segundos que todo fue bien
        ui->statusbar->showMessage("Datos almacenados en " + nombreArchivo,5000);
    }else{
        // Mensaje de error si no se puede abrir el archivo
        QMessageBox::warning(this,
                             "Abrir datos",
                             "No se pudo abrir el archivo");
    }
    //Cerrar archivo
    archivo.close();
}
void Salarios::on_actionGuardar_triggered()
{
    guardar();
}

void Salarios::on_actionCalcular_triggered()
{
    calcular();
}

void Salarios::on_actionNuevo_triggered()
{
    limpiar();
    ui->outResultado->clear();
    ui->outSubtotal->clear();
    ui->outSubtotal->setText("0.00");
    ui->outIva->clear();
    ui->outIva->setText("0.00");
    ui->outTotal->clear();
    ui->outTotal->setText("0.00");
}

void Salarios::on_actionSalir_triggered()
{
    close();
}

void Salarios::on_actionAbrir_triggered()
{
    abrir();
}

void Salarios::on_actionAcerca_de_Salarios_triggered()
{
    // Crear un objeto de la ventana que queremos invocar
    Acerca *dialogo = new Acerca(this);
    // Enviar parametro a la ventana
    dialogo->setN_version(VERSION);
    // Mostrar la ventana
    dialogo->exec(); //Modal
    // Obtener datos de la ventana
    dialogo->valor();
}
