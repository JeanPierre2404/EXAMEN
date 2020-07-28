#include "datos.h"

datos::datos(QObject *parent) : QObject(parent)
{
    m_fila = 0;
    m_tipo = "";
}

datos::datos(int fila, QString tipo)
{
    m_fila = fila;
    m_tipo = tipo;
}

int datos::fila() const
{
    return m_fila;
}

QString datos::tipo() const
{
    return m_tipo;
}
