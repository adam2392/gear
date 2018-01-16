/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAbout;
    QAction *actionAboutQt;
    QAction *actionConnect;
    QAction *actionDisconnect;
    QAction *actionConfigure;
    QAction *actionClear;
    QAction *actionQuit;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_4;
    QComboBox *comboBox;
    QLabel *label_5;
    QComboBox *comboBox_4;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_6;
    QLabel *label_4;
    QLabel *label_2;
    QComboBox *comboBox_2;
    QLabel *label;
    QComboBox *comboBox_3;
    QLabel *label_9;
    QLabel *label_3;
    QComboBox *comboBox_5;
    QComboBox *comboBox_6;
    QComboBox *comboBox_7;
    QComboBox *comboBox_8;
    QLabel *label_10;
    QPushButton *pushButton;
    QLabel *title;
    QMenuBar *menuBar;
    QMenu *menuCalls;
    QMenu *menuTools;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(569, 402);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionAboutQt = new QAction(MainWindow);
        actionAboutQt->setObjectName(QStringLiteral("actionAboutQt"));
        actionConnect = new QAction(MainWindow);
        actionConnect->setObjectName(QStringLiteral("actionConnect"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/connect.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionConnect->setIcon(icon);
        actionDisconnect = new QAction(MainWindow);
        actionDisconnect->setObjectName(QStringLiteral("actionDisconnect"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/disconnect.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDisconnect->setIcon(icon1);
        actionConfigure = new QAction(MainWindow);
        actionConfigure->setObjectName(QStringLiteral("actionConfigure"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/settings.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionConfigure->setIcon(icon2);
        actionClear = new QAction(MainWindow);
        actionClear->setObjectName(QStringLiteral("actionClear"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images/clear.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionClear->setIcon(icon3);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/images/application-exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionQuit->setIcon(icon4);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setEditable(false);

        gridLayout_4->addWidget(comboBox, 2, 0, 1, 1);

        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_5, 4, 0, 1, 1);

        comboBox_4 = new QComboBox(centralWidget);
        comboBox_4->setObjectName(QStringLiteral("comboBox_4"));

        gridLayout_4->addWidget(comboBox_4, 2, 3, 1, 1);

        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_7, 4, 2, 1, 1);

        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_8, 4, 3, 1, 1);

        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_6, 4, 1, 1, 1);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_4, 1, 3, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_2, 1, 1, 1, 1);

        comboBox_2 = new QComboBox(centralWidget);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));
        comboBox_2->setEditable(false);

        gridLayout_4->addWidget(comboBox_2, 2, 1, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label, 1, 0, 1, 1);

        comboBox_3 = new QComboBox(centralWidget);
        comboBox_3->setObjectName(QStringLiteral("comboBox_3"));

        gridLayout_4->addWidget(comboBox_3, 2, 2, 1, 1);

        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_9, 0, 0, 1, 4);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_3, 1, 2, 1, 1);

        comboBox_5 = new QComboBox(centralWidget);
        comboBox_5->setObjectName(QStringLiteral("comboBox_5"));

        gridLayout_4->addWidget(comboBox_5, 5, 0, 1, 1);

        comboBox_6 = new QComboBox(centralWidget);
        comboBox_6->setObjectName(QStringLiteral("comboBox_6"));

        gridLayout_4->addWidget(comboBox_6, 5, 1, 1, 1);

        comboBox_7 = new QComboBox(centralWidget);
        comboBox_7->setObjectName(QStringLiteral("comboBox_7"));

        gridLayout_4->addWidget(comboBox_7, 5, 2, 1, 1);

        comboBox_8 = new QComboBox(centralWidget);
        comboBox_8->setObjectName(QStringLiteral("comboBox_8"));

        gridLayout_4->addWidget(comboBox_8, 5, 3, 1, 1);

        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_10, 3, 0, 1, 4);


        gridLayout->addLayout(gridLayout_4, 1, 0, 1, 8);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 0, 0, 1, 1);

        title = new QLabel(centralWidget);
        title->setObjectName(QStringLiteral("title"));

        gridLayout->addWidget(title, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 569, 22));
        menuCalls = new QMenu(menuBar);
        menuCalls->setObjectName(QStringLiteral("menuCalls"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QStringLiteral("menuTools"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuCalls->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuCalls->addAction(actionConnect);
        menuCalls->addAction(actionDisconnect);
        menuCalls->addSeparator();
        menuCalls->addAction(actionQuit);
        menuTools->addAction(actionConfigure);
        menuTools->addAction(actionClear);
        menuHelp->addAction(actionAbout);
        menuHelp->addAction(actionAboutQt);
        mainToolBar->addAction(actionConnect);
        mainToolBar->addAction(actionDisconnect);
        mainToolBar->addAction(actionConfigure);
        mainToolBar->addAction(actionClear);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Simple Terminal", 0));
        actionAbout->setText(QApplication::translate("MainWindow", "&About", 0));
#ifndef QT_NO_TOOLTIP
        actionAbout->setToolTip(QApplication::translate("MainWindow", "About program", 0));
#endif // QT_NO_TOOLTIP
        actionAbout->setShortcut(QApplication::translate("MainWindow", "Alt+A", 0));
        actionAboutQt->setText(QApplication::translate("MainWindow", "About Qt", 0));
        actionConnect->setText(QApplication::translate("MainWindow", "C&onnect", 0));
#ifndef QT_NO_TOOLTIP
        actionConnect->setToolTip(QApplication::translate("MainWindow", "Connect to serial port", 0));
#endif // QT_NO_TOOLTIP
        actionConnect->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0));
        actionDisconnect->setText(QApplication::translate("MainWindow", "&Disconnect", 0));
#ifndef QT_NO_TOOLTIP
        actionDisconnect->setToolTip(QApplication::translate("MainWindow", "Disconnect from serial port", 0));
#endif // QT_NO_TOOLTIP
        actionDisconnect->setShortcut(QApplication::translate("MainWindow", "Ctrl+D", 0));
        actionConfigure->setText(QApplication::translate("MainWindow", "&Configure", 0));
#ifndef QT_NO_TOOLTIP
        actionConfigure->setToolTip(QApplication::translate("MainWindow", "Configure serial port", 0));
#endif // QT_NO_TOOLTIP
        actionConfigure->setShortcut(QApplication::translate("MainWindow", "Alt+C", 0));
        actionClear->setText(QApplication::translate("MainWindow", "C&lear", 0));
#ifndef QT_NO_TOOLTIP
        actionClear->setToolTip(QApplication::translate("MainWindow", "Clear data", 0));
#endif // QT_NO_TOOLTIP
        actionClear->setShortcut(QApplication::translate("MainWindow", "Alt+L", 0));
        actionQuit->setText(QApplication::translate("MainWindow", "&Quit", 0));
        actionQuit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "up_arrow", 0)
         << QApplication::translate("MainWindow", "down_arrow", 0)
         << QApplication::translate("MainWindow", "q", 0)
         << QApplication::translate("MainWindow", "w", 0)
        );
        label_5->setText(QApplication::translate("MainWindow", "jump", 0));
        comboBox_4->clear();
        comboBox_4->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "down_arrow", 0)
         << QApplication::translate("MainWindow", "q", 0)
         << QApplication::translate("MainWindow", "e", 0)
         << QApplication::translate("MainWindow", "r", 0)
         << QApplication::translate("MainWindow", "a", 0)
         << QApplication::translate("MainWindow", "s", 0)
         << QApplication::translate("MainWindow", "d", 0)
        );
        label_7->setText(QApplication::translate("MainWindow", "reload", 0));
        label_8->setText(QApplication::translate("MainWindow", "crouch", 0));
        label_6->setText(QApplication::translate("MainWindow", "aim", 0));
        label_4->setText(QApplication::translate("MainWindow", "back", 0));
        label_2->setText(QApplication::translate("MainWindow", "right", 0));
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "right_arrow", 0)
         << QApplication::translate("MainWindow", "q", 0)
         << QApplication::translate("MainWindow", "e", 0)
         << QApplication::translate("MainWindow", "r", 0)
         << QApplication::translate("MainWindow", "a", 0)
         << QApplication::translate("MainWindow", "d", 0)
        );
        label->setText(QApplication::translate("MainWindow", "forward", 0));
        comboBox_3->clear();
        comboBox_3->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "left_arrow", 0)
         << QApplication::translate("MainWindow", "q", 0)
         << QApplication::translate("MainWindow", "e", 0)
         << QApplication::translate("MainWindow", "r", 0)
         << QApplication::translate("MainWindow", "a", 0)
         << QApplication::translate("MainWindow", "s", 0)
         << QApplication::translate("MainWindow", "d", 0)
        );
        label_9->setText(QApplication::translate("MainWindow", "Basic Movement", 0));
        label_3->setText(QApplication::translate("MainWindow", "left", 0));
        comboBox_5->clear();
        comboBox_5->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "space", 0)
         << QApplication::translate("MainWindow", "shift", 0)
        );
        comboBox_6->clear();
        comboBox_6->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "space", 0)
         << QApplication::translate("MainWindow", "shift", 0)
         << QApplication::translate("MainWindow", "right_mouse", 0)
        );
        comboBox_7->clear();
        comboBox_7->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "space", 0)
         << QApplication::translate("MainWindow", "shift", 0)
         << QApplication::translate("MainWindow", "r", 0)
        );
        comboBox_8->clear();
        comboBox_8->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "space", 0)
         << QApplication::translate("MainWindow", "shift", 0)
         << QApplication::translate("MainWindow", "g", 0)
        );
        label_10->setText(QApplication::translate("MainWindow", "Other Commands", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Sync Commands To Shoe", 0));
        title->setText(QApplication::translate("MainWindow", "For FPS Games", 0));
        menuCalls->setTitle(QApplication::translate("MainWindow", "Calls", 0));
        menuTools->setTitle(QApplication::translate("MainWindow", "Tools", 0));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
