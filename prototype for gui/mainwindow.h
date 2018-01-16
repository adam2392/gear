#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtCore/QtGlobal>

#include <QLCDNumber>
#include <QSlider>
#include <QVBoxLayout>
#include <QPushButton>

QT_BEGIN_NAMESPACE

class QLabel;

namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

class Console;
class SettingsDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void syncCommands();
    void transmitCmd(int value);

    //functions for serial port and about
    void openSerialPort();
    void closeSerialPort();
    void about();

    char commandToAscii(QString command);
    //functions for I/O on serial port
    void writeData(const QByteArray &data);
    void readData();

    //functions to handle the error
    void handleError(QSerialPort::SerialPortError error);

private:
    void initActionsConnections();

private:
    void showStatusMessage(const QString &message);

    Ui::MainWindow *ui;
    QLabel *status;

    Console *console;
    SettingsDialog *settings;
    QSerialPort *serial;

    QSlider *slider;
    QLCDNumber *lcd;
};

#endif // MAINWINDOW_H

