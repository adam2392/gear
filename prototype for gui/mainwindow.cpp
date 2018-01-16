#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingsdialog.h"
#include "console.h"

#include <stdio.h>
#include <QtSerialPort/QSerialPort>
#include "QMessageBox" //to create a message for warnings
#include <QDebug>
#include <QLabel>
#include <QStatusBar>
#include <QComboBox>
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //******* Set up
    ui->setupUi(this);

    //create serialport object
    serial = new QSerialPort(this);

    //create settings object
    settings = new SettingsDialog;

    // 01: Creation of Console
    console = new Console;
    console->setEnabled(false);

    //initialize the connections of the actions
    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionQuit->setEnabled(true);
    ui->actionConfigure->setEnabled(true);
    initActionsConnections();

    /************** Adding Widgets *********************/
    //02: Formatting Widgets
    // create new status
    status = new QLabel;

    // add widgets to the status bar
    ui->statusBar->addWidget(status);

    //creation and attribution of slider
    slider = new QSlider();
    slider->resize(255, 20);
    slider->setOrientation(Qt::Horizontal);
    slider->setRange(0, 255); //0-255 is range we can read

    //creation and attribution of the lcd
    lcd = new QLCDNumber();
    lcd->setSegmentStyle(QLCDNumber::Flat);
    lcd->resize(255, 50);

//    gridbox->addWidget(slider, 0, 1, 1, 1);
//    gridbox->addWidget(lcd, 1, 0, 1, 2);

    //03: Adding widgets to layout
    //add console as a widget to the main widget
    //layout with slider and lcd underneath console
    ui->centralWidget->layout()->addWidget(console);    //add the console to it

    ui->centralWidget->layout()->addWidget(slider);
    ui->centralWidget->layout()->addWidget(lcd);
    /************** Connection Events ***********************/
    //handle serial port errors
    connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError)));
    //serial connect to read data onto the console
    connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
    //serial connect to write data
    connect(console, SIGNAL(getData(QByteArray)), this, SLOT(writeData(QByteArray)));

    //connection between the slider event and the transmission function
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(transmitCmd(int)));
    //connection between the slider event and the lcd value
    connect(slider, SIGNAL(valueChanged(int)), lcd, SLOT(display(int)));

    //connection to sync commands with the microcontroller over serial
    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(syncCommands()));
}

void MainWindow::syncCommands()
{
    //*** 00: initialize vars
    QStringList move_commands;
    QStringList other_commands;

//    QByteArray asciicommands
    QByteArray buffermove;
    QByteArray bufferother;

    //*** 01: read in commands from the different combo boxes
    //right foot
    move_commands << ui->comboBox->currentText() << "\n" << ui->comboBox_2->currentText() << "\n"
                     << ui->comboBox_3->currentText() << "\n" << ui->comboBox_4->currentText() << "\n";
    other_commands << ui->comboBox_5->currentText() << "\n" << ui->comboBox_6->currentText() << "\n"
                    << ui->comboBox_7->currentText() << "\n" << ui->comboBox_8->currentText() << "\n";

    // get ascii codes for all commands
//    char movecommands[8];
//    char othercommands[8];
//    char forward_command = commandToAscii(ui->comboBox->currentText());
//    char right_command = commandToAscii(ui->comboBox_2->currentText());
//    char left_command = commandToAscii(ui->comboBox_3->currentText());
//    char back_command = commandToAscii(ui->comboBox_4->currentText());
//    char jump_command = commandToAscii(ui->comboBox_5->currentText());;
//    char aim_command = commandToAscii(ui->comboBox_6->currentText());;
//    char reload_command = commandToAscii(ui->comboBox_7->currentText());;
//    char crouch_command = commandToAscii(ui->comboBox_8->currentText());;

//    movecommands[0] = (forward_command);
//    movecommands[1] = ()
//    movecommands[1] = (right_command);
//    movecommands[2] = (left_command);
//    movecommands[3] = (back_command);
//    othercommands[0] = (jump_command);
//    othercommands[1] = (aim_command);
//    othercommands[2] = (reload_command);
//    othercommands[3] = (crouch_command);

//    buffermove = movecommands;
//    MainWindow::writeData(buffermove.data());
//    bufferother = othercommands;
//    MainWindow::writeData(bufferother.data());

//    qDebug() << "Ascii commands: "<< forward_command <<  "\n" << right_command << "\n" << left_command << "\n" << back_command
//             << "\n" << int(jump_command) << "\n" << int(aim_command) << "\n" << int(reload_command) << "\n" << int(crouch_command) << "\n";
    qDebug() << "All data" << move_commands;
    qDebug() << "2nd All Data" << other_commands;

    //**** 02: Write into serial window
    for(int i=0; i<move_commands.length(); i++)
    {
        buffermove = move_commands[i].toLatin1();       //convert to bytes
        MainWindow::writeData(buffermove.data());          //write data to serial port
//        qDebug() << "The data written by rightfeetsensors:" << buffermove.data();    //debug output
//        qDebug() << "The data written by leftfeetsensors:" << bufferother.data();
    }
    for(int i=0; i<other_commands.length(); i++)
    {
        bufferother = other_commands[i].toLatin1();
        MainWindow::writeData(bufferother.data());
    }
}

char MainWindow::commandToAscii(QString command) {
    char asciicommand;
    //convert commands to some ASCII
    if(command == "q") {              //Q
        asciicommand = int('q');
    }
    else if(command == "w") {         //W
        asciicommand = int('w');
    }
    else if(command == ("e")) {         //E
        asciicommand = int('e');
    }
    else if(command == ("r")) {         //R
        asciicommand = int('r');
    }
    else if(command == ("a")) {         //A
        asciicommand = int('a');
    }
    else if(command == ("s")) {         //S
        asciicommand = int('s');
    }
    else if(command == ("d")) {         //D
        asciicommand = int('d');
    }
    else if(command == ("space")) {     //SPACE
        asciicommand = int(' ');
    }
    else if(command == ("shift")) {     //SHIFT
        asciicommand = int(15);
    }
    else if(command == ("r")) {         //R
        asciicommand = int('r');
    }
    else if(command == ("up_arrow")) {         //UPARROW
        asciicommand = int('U');
    }
    else if(command == ("down_arrow")) {         //DOWNARROW
        asciicommand = int('D');
    }
    else if(command == ("left_arrow")) {         //LEFTARROW
        asciicommand = int('L');
    }
    else if(command == ("right_arrow")) {         //RIGHTARROW
        asciicommand = int('R');
    }
    else if(command == ("right_mouse")) {         //RIGHTMOUSE
        asciicommand = -4;
    }
    else {
        asciicommand = 'error';
        qDebug() << "Error inside asciicommand function!";
    }
    asciicommand = char(asciicommand);
    //debug print which command corresponded to which ascii command
    qDebug() << "inside function: "<<command << asciicommand;

    return asciicommand;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete settings;
    serial->close(); //close port at end of program for serial
}

/* Function: openSerialPort
   Description: Initializing the port and setting the port settings.
*/
void MainWindow::openSerialPort()
{
    SettingsDialog::Settings p = settings->settings();
    qDebug() << "This is the name of the port." << p.name;
    serial->setPortName(p.name);
    serial->setBaudRate(p.baudRate);
    serial->setDataBits(p.dataBits);
    serial->setParity(p.parity);
    serial->setStopBits(p.stopBits);
    serial->setFlowControl(p.flowControl);
    if (serial->open(QIODevice::ReadWrite)) {
        console->setEnabled(true);
        console->setLocalEchoEnabled(p.localEchoEnabled);
        ui->actionConnect->setEnabled(false);
        ui->actionDisconnect->setEnabled(true);
        ui->actionConfigure->setEnabled(false);
        showStatusMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                          .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                          .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));
    } else {
        QMessageBox::critical(this, tr("Error"), serial->errorString());

        showStatusMessage(tr("Open error"));
    }
//    port = new QSerialPort("cu.usbmodem1411");     //create port
}

/* Function: closeSerialPort
   Description: to close the serial port using the GUI.
*/
void MainWindow::closeSerialPort()
{
    if (serial->isOpen())
        serial->close();
    console->setEnabled(false);
    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionConfigure->setEnabled(true);
    showStatusMessage(tr("Disconnected"));
}


/* Function: about
   Description: Show a GUI description about the application.
*/
void MainWindow::about()
{
    QMessageBox::about(this, tr("About the Gaming Shoe"),
                       tr("The <b>Gaming Shoe</b> is an application for a better "
                          "gaming experience. We will use the Qt Serial Port "
                          "module in this GUI application."));
}

void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        closeSerialPort();
    }
}

/* Function: initActionsConnections
   Description: initiate actions for all the connections on the GUI.
*/
void MainWindow::initActionsConnections()
{
    connect(ui->actionConnect, SIGNAL(triggered()), this, SLOT(openSerialPort()));
    connect(ui->actionDisconnect, SIGNAL(triggered()), this, SLOT(closeSerialPort()));
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionConfigure, SIGNAL(triggered()), settings, SLOT(show()));
    connect(ui->actionClear, SIGNAL(triggered()), console, SLOT(clear()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui->actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::showStatusMessage(const QString &message)
{
    status->setText(message);
}

void MainWindow::writeData(const QByteArray &data)
{
    serial->write(data);
    console->putData(data);
}

void MainWindow::readData()
{
    QByteArray data = serial->readAll();
    console->putData(data);
}

void MainWindow::transmitCmd(int value)
{
    //if value wasn't between 0-255, no transmission
    if(value < 0 || value > 255)
        return;
//    char *buffer = (char*) new int(value);

    //send buffer to serial port
//    serial->write(buffer);
}
