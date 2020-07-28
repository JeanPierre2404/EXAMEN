#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>
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


private slots:
    void on_actionAcerca_de_triggered();
    void on_cmdAgregar_clicked();

private:
    Ui::Principal *ui;
    QList<datos*> m_datos;

    void inicializarDato();
    void inicializarWidget();
};
#endif // PRINCIPAL_H
