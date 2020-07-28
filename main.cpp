#include "principal.h"

#include <QApplication>

#include <QTranslator>
#include <QInputDialog>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Creo objeto para manejar las traducciones
       QTranslator traduccion;
    // Solicito al usuario que seleccione un idioma del programa
       QStringList idiomas;
       idiomas << "Español" << "Ingles";
       QString idiomaSeleccionado = QInputDialog::getItem(NULL,
                                  "Idioma",
                                  "Seleccione un idioma",
                                  idiomas);

     // Dependiendo del idioma que elija se cargara el archivo de traducción (.qm)
       if(idiomaSeleccionado == "Español"){
           traduccion.load(":/Tareas_es_EC.qm");
       }else if( idiomaSeleccionado == "Ingles"){
           traduccion.load(":/Tareas_en_US.qm");
       }

       // Si es diferente de español, se instala la traducción en TODA la aplicación
           if (idiomaSeleccionado != "Español"){
               a.installTranslator(&traduccion);
           }


    Principal w;
    w.show();
    return a.exec();
}
