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
                                                         "Archivo de texto (*.txt)");
    qDebug() << nombreArchivo;
    // Crear un objeto QFile
    QFile archivo(nombreArchivo);
    // Abrir para escritura
    if(archivo.open(QFile::WriteOnly | QFile::Truncate)){
        // Crear un stream de texto
        QTextStream salida(&archivo);
        // Enviar los datos del resultado a la salida
        salida << ui->outResultado->toPlainText();
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
}

void Salarios::on_actionSalir_triggered()
{
    close();
}

void Salarios::on_actionAbrir_triggered()
{
    abrir();
}

