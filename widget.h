#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "myserialport.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_btnsend_clicked();

private:
    Ui::Widget *ui;
    MySerialPort m_serial;
};
#endif // WIDGET_H
