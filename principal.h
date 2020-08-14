#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include "datos.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Principal; }
QT_END_NAMESPACE

class Principal : public QMainWindow
{
    Q_OBJECT

public:
    Principal(QWidget *parent = nullptr);
    ~Principal();


 public slots:
    void registrar();

    void limpiar();

private slots:
    void on_actionAcerca_de_triggered();

    void on_cmdAgregar_clicked();

    void on_actionFinalizar_2_triggered();

    void on_outDetalles_itemClicked(QTableWidgetItem *item);

private:
    Ui::Principal *ui;
    QList<datos*> m_datos;

    void inicializarDato();
    void inicializarWidget();

    int filas;
};
#endif // PRINCIPAL_H
