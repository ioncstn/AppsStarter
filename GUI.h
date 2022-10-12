#pragma once

#include <QtWidgets/QMainWindow>
#include "service.h"
#include <qformlayout.h>
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qtablewidget.h>   
#include <qcheckbox.h>
#include <qmessagebox.h>
#include <qtreeview.h>
#include <QFileSystemModel>
#include "ui_GUI.h"
#include <windows.h>
#include <locale>
#include <codecvt>

class GUI : public QWidget
{
    Q_OBJECT

public:
    GUI(ServiceApps srv, QWidget *parent = Q_NULLPTR);

private:

    void buildApp();

    void fillTable(QTableWidget*);

    Ui::GUIClass ui;
    ServiceApps& service;
};
