#ifndef MYSERIALPORT_H
#define MYSERIALPORT_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QStringList>
#include <QDebug>
#include <QMessageBox>

class MySerialPort : public QObject
{
    Q_OBJECT
public:
    explicit MySerialPort(QObject *parent = nullptr);

    /*
        功能: 初始化串口设置
        默认 波特率: 115200bps; 停止位: 1;  奇偶校验: 无奇偶校验;  数据位：8;  串口选择第一个有效串口。
        返回值: 0 成功; -2没有有效串口
    */
    int initPort();

    /*
        功能:打印串口信息
    */
    void printPortInfo();

    /*
        函数功能: 打开串口
    */
    void openSerialPort();

    /*
        函数功能: 关闭串口
    */
    void closeSerialPort();

    /*
        函数功能: 写数据到串口操作
    */
    void writeOperation(QString data);


    /*
        函数功能: 从串口读数据
    */
    void readOperation();//串口读操作


signals:

private:
    QSerialPort m_serial; //串口对象
    QByteArray m_readdata;//串口读取的数据

};

#endif // MYSERIALPORT_H
