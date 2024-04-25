#include "myserialport.h"

MySerialPort::MySerialPort(QObject *parent) : QObject(parent)
{
}
//初始化和配置串口
int MySerialPort::initPort()
{
    QStringList portlist={};
    int i = 1;

    //遍历系统有效串口
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        QSerialPort serialtemp;
        serialtemp.setPort(info);

        if(serialtemp.open(QIODevice::ReadWrite))
        {
            portlist<<info.portName();
            serialtemp.close();
            qDebug()<<QString("有效端口:%1").arg(i)<<info.portName();
        }
    }

    //默认使用第一个有效串口
    if(portlist.size()>0)
    {
        m_serial.setPortName(portlist.at(0));
    }
    else
    {
        QMessageBox(QMessageBox::Critical,"Error","no availablePorts");
        return -2;
    }

    //固定串口其他配置
    //设置波特率 默认 115200bps
    m_serial.setBaudRate(QSerialPort::Baud115200);

    //停止位 默认 1
    m_serial.setStopBits(QSerialPort::OneStop);

    //数据位 默认8
    m_serial.setDataBits(QSerialPort::Data8);

    //奇偶校验
    m_serial.setParity(QSerialPort::NoParity);

    return 0;
}

void MySerialPort::printPortInfo()
{
    qDebug()<<"串口选择:"<<m_serial.portName()
           <<"波特率"<<m_serial.baudRate()
          <<"停止位"<<m_serial.stopBits()
         <<"数据位"<<m_serial.dataBits()
        <<"奇偶校验"<<m_serial.parity();
}

//打开串口
void MySerialPort::openSerialPort()
{
    //配置好串口，就可以打开它，以读写方式打开
    m_serial.open(QIODevice::ReadWrite);
    if(m_serial.isOpen())
    {
        qDebug()<<"Serial port successfully opened"<<m_serial.portName();
        //串口打开成功后，有信号readyRead时,就会调用readData函数数据。
        connect(&m_serial,&QSerialPort::readyRead,this,&MySerialPort::readOperation);
    }
    else
    {
        qDebug()<<"Serial port opening failed";
    }
}

//关闭串口
void MySerialPort::closeSerialPort()
{
    if(m_serial.isOpen())
    {
        m_serial.close();
        qDebug()<<"serial port is closed";
    }
}

//写数据到串口
void MySerialPort::writeOperation(QString data)
{
    qint64 ret = m_serial.write(data.toLocal8Bit());

    if(ret<0)
    {
        qDebug()<<"Write serial port failure";
    }
}
//读串口操作
void MySerialPort::readOperation()
{
    m_readdata.clear();
    //读取串口数据
    m_readdata = m_serial.readAll();
    qDebug()<<QString::fromLocal8Bit(m_readdata);//推荐使用QString::fromLocal8Bit和对应的toLocal8Bit
}


