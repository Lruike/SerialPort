#include "widget.h"
#include "ui_widget.h"
#include <QStringList>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    m_serial.initPort();
    m_serial.printPortInfo();
    m_serial.openSerialPort();

}

Widget::~Widget()
{
    delete ui;
    m_serial.closeSerialPort();
}


void Widget::on_btnsend_clicked()
{
    QByteArray senddata = ui->pte->toPlainText().toUtf8();
    m_serial.writeOperation(QString::fromUtf8(senddata));
}
