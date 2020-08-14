#ifndef DATOS_H
#define DATOS_H

#include <QObject>



class datos : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int fila READ fila)
    Q_PROPERTY(QString tipo READ tipo)

public:
    explicit datos(QObject *parent = nullptr);
    datos(int fila, QString tipo);
    //Geters

    int fila() const;
    QString tipo() const;

    QString nombreTarea()const;
    QDate fecha()const;

signals:

private:
    int m_fila;
    QString m_tipo;

    QString m_nombreTarea;
    //QDate m_fecha;
};

#endif // DATOS_H
