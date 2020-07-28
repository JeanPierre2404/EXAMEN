#include "principal.h"
#include "ui_principal.h"

#include <QMessageBox>
#include <QTableWidget>
#include <QDate>
#include <QFileDialog>
#include <QDebug>
Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);

    /*QStringList cabecera = {"N", "Nombre", "Fecha", "Tipo"};
    ui->outDetalles->setColumnCount(4);
    ui->outDetalles->setHorizontalHeaderLabels(cabecera);*/

    connect(ui->cmdAgregar, SIGNAL(released()), this , SLOT(registrar()));


    connect(ui->actionSalir, SIGNAL(triggered(bool)),
            this, SLOT(close()));

    inicializarDato();


}

Principal::~Principal()
{
    delete ui;
}

void Principal::registrar()
{
    QString importancia;
    if(ui->inAlta->isChecked()){
        importancia = "Alto";
    }else if(ui->inMedio->isChecked()){
        importancia = "Media";
    }else{
        importancia = "Baja";
    }
    QDate Fecha = ui->inFecha->date();
    QString nombreDeTarea = ui->inNombreTarea->text();
    int index = ui->inTipo->currentIndex();
    datos *i = m_datos.at(index);
    int Posicion = ui->outDetalles->rowCount();
    ui->outDetalles->insertRow(Posicion);

    ui->outDetalles->setItem(Posicion,0, new QTableWidgetItem(QString(nombreDeTarea)));
    ui->outDetalles->setItem(Posicion,1,new QTableWidgetItem(Fecha.toString()));
    ui->outDetalles->setItem(Posicion,2, new QTableWidgetItem(QString(importancia)));
    ui->outDetalles->setItem(Posicion,3, new QTableWidgetItem(i->tipo()));

}


void Principal::on_actionAcerca_de_triggered()
{
    QMessageBox::information(this,"acerca de",
                             "Tareas-Pendientes\n Autor: Jean Pierre Casa\n Creado el domi.,27 de jul del 2020 \n QT 4.12.2\n Mi github:https: aqui pongo mi link \n Copyright 2008-2020 Compufuture.");

}

void Principal::inicializarDato()
{
    m_datos.append(new datos(1,"Estudiante"));
    m_datos.append(new datos(2,"Universidad"));
    m_datos.append(new datos(3,"Familia"));
    m_datos.append(new datos(4,"Otras"));
    inicializarWidget();
}

void Principal::inicializarWidget()
{
    for(int i = 0;i< m_datos.length(); ++i){
        ui->inTipo->addItem(m_datos.at(i)->tipo());
        // crearn la cabecera
        QStringList cabecera = {"Tarea", "Fecha", "Prioridad", "Tipo"};
        ui->outDetalles->setColumnCount(4);
        ui->outDetalles->setHorizontalHeaderLabels(cabecera);
    }
}

void Principal::on_cmdAgregar_clicked()
{
    QString fileName = ("C:/Users/erick/Desktop/Tarea/Guardado/tareas.txt");
       QFile data(fileName);
       if (data.open(QFile::WriteOnly | QFile::Truncate))
       {
           QTextStream salida(&data);
           QStringList Lista;
           for( int columna = 0; columna < ui->outDetalles->columnCount(); ++columna ){
               Lista << "\" " + ui->outDetalles->horizontalHeaderItem(columna)->data(Qt::DisplayRole).toString() + "\" ";
           }
           salida << Lista.join(";") << "\n";
           for( int fila = 0; fila < ui->outDetalles->rowCount(); ++fila)
           {
               Lista.clear();
               for( int columna = 0; columna < ui->outDetalles->columnCount(); ++columna){
                   QTableWidgetItem* item = ui->outDetalles->item(fila,columna);
                   if (!item || item->text().isEmpty()){
                       ui->outDetalles->setItem(fila,columna,new QTableWidgetItem("0"));
                   }
                   Lista << "\" "+ui->outDetalles->item( fila, columna )->text()+"\" ";
               }
               salida<< Lista.join( ";" )+"\n";
           }
           ui->statusbar->showMessage("Datos almacenados en: " + fileName, 5000);
           data.close();
       }
}


