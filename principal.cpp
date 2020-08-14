#include "principal.h"
#include "ui_principal.h"

#include <QMessageBox>
#include <QTableWidget>
#include <QDate>
#include <QFileDialog>
#include <QDebug>
#include <QColor>
Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);

    connect(ui->cmdAgregar, SIGNAL(released()), this , SLOT(registrar()));

    connect(ui->actionSalir, SIGNAL(triggered(bool)),
            this, SLOT(close()));

    inicializarDato();

    filas = -1;

}

Principal::~Principal()
{
    delete ui;
}

void Principal::registrar()
{
    QString importancia;
    if(ui->inAlta->isChecked()){
        importancia = tr("Alto");
    }else if(ui->inMedio->isChecked()){
        importancia = tr("Media");
    }else{
        importancia = tr("Baja");
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
//
        //CAMBIANDO DE COLOR LAS PRIORIDADES
    if(ui->inAlta->isChecked()){
        for(int i=0;i<4;i++){
            QColor color(224, 46, 32);//ROJO
            ui->outDetalles->item(Posicion,i)->setBackgroundColor(color);
        }
    }
    else if (ui->inMedio->isChecked()) {
        for(int i=0;i<4;i++){
            QColor color1(224,119,32);//NARANJA
            ui->outDetalles->item(Posicion,i)->setBackgroundColor(color1);
        }
    }else if (ui->inBajo->isChecked()){
        for(int i=0;i<4;i++){
            QColor color2(255, 233, 0);//AMARILLO
            ui->outDetalles->item(Posicion,i)->setBackgroundColor(color2);
        }
    }

}

void Principal::limpiar()
{
    ui->inNombreTarea->setText("");
    ui->inAlta->setChecked(true);
    ui->inFecha->clear();
}


void Principal::on_actionAcerca_de_triggered()
{
    QMessageBox::information(this,"acerca de",
                             "Tareas-Pendientes\n Autor: Jean Pierre Casa\n Creado el domi.,27 de jul del 2020 \n QT 4.12.2\n Mi github:https: aqui pongo mi link \n Copyright 2008-2020 Compufuture.");

}

void Principal::inicializarDato()
{
    m_datos.append(new datos(1,tr("Estudiante")));
    m_datos.append(new datos(2,tr("Universidad")));
    m_datos.append(new datos(3,tr("Familia")));
    m_datos.append(new datos(4,tr("Otras")));
    inicializarWidget();
}

void Principal::inicializarWidget()
{
    for(int i = 0;i< m_datos.length(); ++i){
        ui->inTipo->addItem(m_datos.at(i)->tipo());
        // crearn la cabecera
        QStringList cabecera = {tr("Tarea"), tr("Fecha"), tr("Prioridad"), tr("Tipo")};
        ui->outDetalles->setColumnCount(4);
        ui->outDetalles->setHorizontalHeaderLabels(cabecera);
    }
}

void Principal::on_cmdAgregar_clicked()
{
    //IMPORTANTE: EN ESTO ES NECESARIO PONER LA UBICACION DEL ARCHIVO DONDE SE GUARDEN LAS TAREAS
    QString fileName = ("C:/Users/erick/Desktop/Tarea/Tareas/tareas.txt");
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

       limpiar();
}


//BORRANDO LA FILA DE LA LISTA DE TAREAS
void Principal::on_actionFinalizar_2_triggered()
{
    ui->outDetalles->removeRow(filas);
    ui->statusbar->showMessage(tr("Fila eliminada"), 5000);
}

void Principal::on_outDetalles_itemClicked(QTableWidgetItem *item)
{
   filas = item->row();
}
