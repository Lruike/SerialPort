#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QStringList>
#include <QDebug>
#include <QMessageBox>

class serialport : public QObject
{
    Q_OBJECT

public:
    serialport(QObject *parent = nullptr);

    /*
        函数功能: 初始化串口设置
        默认 波特率: 115200bps; 停止位: 1;  奇偶校验: 无奇偶校验;  数据位：8;  串口选择第一个有效串口。
        参数：待初始化串口对象
        返回值: 系统有效串口列表
    */
    QStringList InitPort();

    /*
        函数功能: 打开串口
    */
    void openSerialPort();

    /*
        函数功能: 关闭串口
    */
    void closeSerialPort();

    void writeOperation(QString data);//写串口操作

    QByteArray readdata;//串口读取到的数据

    void readOperation();//串口读操作
private:
    QSerialPort m_serial; //串口对象

};

#endif // SERIALPORT_H
