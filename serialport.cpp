#include "serialport.h"

serialport::serialport(QObject *parent)
    :QObject(parent)
{
    //1. 配置串口
    InitPort();

    //2. 打开串口
    openSerialPort();
}

QStringList serialport::InitPort()
{
    QStringList portList= {};

    //刷新串口
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        QSerialPort serial;
        serial.setPort(info);
        if(serial.open(QIODevice::ReadWrite))
        {
            portList<<info.portName();
            serial.close();
        }
    }

    //默认使用第一个有效串口
    if(portList.size()>0)
    {
        //默认设置第一个有效串口
        m_serial.setPortName(portList.at(0));
    }
    else
    {
        QMessageBox(QMessageBox::Critical,"Error","no availablePorts");
    }

    //设置波特率 默认 115200bps
    m_serial.setBaudRate(QSerialPort::Baud115200);

    //停止位 默认 1
    m_serial.setStopBits(QSerialPort::OneStop);

    //数据位 默认8
    m_serial.setDataBits(QSerialPort::Data8);

    return portList;
}

//打开串口
void serialport::openSerialPort()
{
    //先配置完毕后，打开串口，开启方式以读写方式打开
    m_serial.open(QIODevice::ReadWrite);
    if(m_serial.isOpen()) //串口打开成功
    {
        qDebug()<<"Serial port successfully opened";
        //串口成功打开后，有信号readyRead时,就会调用readData函数数据。
        connect(&m_serial,&QSerialPort::readyRead,this,&serialport::readOperation);
    }
    else
    {
        qDebug()<<"Serial port opening failed";
    }
}

//关闭串口
void serialport::closeSerialPort()
{
    if(m_serial.isOpen())
    {
        m_serial.close();
        qDebug()<<"serial port is closed";
    }
}

void serialport::writeOperation(QString data)
{
    qint64 ret = m_serial.write(data.toUtf8());

    if(ret<0)
    {
        qDebug()<<"Write serial port failure";
    }
    else
    {
        qDebug()<<"Write serial port success";
    }
}

//串口读操作
void serialport::readOperation()
{
    //读取串口数据
    readdata = m_serial.readAll();
    qDebug()<<QString::fromUtf8(readdata);
}


