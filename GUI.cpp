#include "GUI.h"

GUI::GUI(ServiceApps srv, QWidget *parent)
    : QWidget(parent), service(srv)
{
    ui.setupUi(this);
    buildApp();
}

void GUI::buildApp()
{
    QFormLayout* mainLayout = new QFormLayout;
    this->setLayout(mainLayout);

    QTableWidget* appsTable = new QTableWidget;
    appsTable->setColumnCount(2);
    QTableWidgetItem* header1 = new QTableWidgetItem("APP");
    appsTable->setHorizontalHeaderItem(0, header1);
    QTableWidgetItem* header2 = new QTableWidgetItem("TURN ON");
    appsTable->setHorizontalHeaderItem(1, header2);
    fillTable(appsTable);
    mainLayout->addWidget(appsTable);

    QPushButton* addButton = new QPushButton("ADD");
    mainLayout->addWidget(addButton);

    QPushButton* deleteButton = new QPushButton("DELETE");
    mainLayout->addWidget(deleteButton);

    QPushButton* toggleActiveButton = new QPushButton("ALL ON / OFF");
    mainLayout->addWidget(toggleActiveButton);

    QPushButton* turnOnButton = new QPushButton("RUN APPS");
    mainLayout->addWidget(turnOnButton);

    QObject::connect(addButton, &QPushButton::clicked, [this, appsTable]() {
        QWidget* tempWindow = new QWidget;
        tempWindow->setMinimumWidth(400);
        tempWindow->setMinimumHeight(400);
        QFormLayout* tempLayout = new QFormLayout;
        tempWindow->setLayout(tempLayout);

        QTreeView* tempTree = new QTreeView;
        QFileSystemModel* tempModel = new QFileSystemModel;
        tempModel->setRootPath("C:/");
        tempTree->setModel(tempModel);
        tempLayout->addWidget(tempTree);

        QPushButton* selectButton = new QPushButton("select");
        tempLayout->addWidget(selectButton);

        QObject::connect(selectButton, &QPushButton::clicked, [tempWindow, tempModel, tempTree, this, appsTable]() {
            auto index = tempTree->currentIndex();
            std::string path = tempModel->filePath(tempTree->currentIndex()).toStdString();
            auto begin = path.begin();
            if (path.end() - path.begin() >= 4) {
                begin = path.end() - 4;
            }
            std::string type(begin, path.end());
            if (type != ".exe") {
                QMessageBox* tempWarn = new QMessageBox;
                tempWarn->setText("select an exe file.");
                tempWarn->show();
            }
            else {
                try {
                    service.addApp(path, true);
                    fillTable(appsTable);
                    tempWindow->close();
                }
                catch (std::exception ex) {
                    QMessageBox* tempWarn = new QMessageBox;
                    tempWarn->setText(ex.what());
                    tempWarn->show();
                }
            }
            });

        tempWindow->show();
        });

    QObject::connect(deleteButton, &QPushButton::clicked, [this, appsTable]() {
        auto current = appsTable->currentItem();
        if (current == Q_NULLPTR) {
            QMessageBox* tempWindow = new QMessageBox;
            tempWindow->setText("select a cell");
            tempWindow->show();
        }
        auto index = appsTable->currentIndex();
        auto apps = service.getAllApps();
        service.deleteApp(apps[index.row()].getPath());
        fillTable(appsTable);
        });

    QObject::connect(toggleActiveButton, &QPushButton::clicked, [this, appsTable]() {
        auto apps = service.getAllApps();
        bool checked = true;
        for (App const& app : apps) {
            if (app.getChecked() == false) {
                checked = false;
                break;
            }
        }
        if (checked == false) {
            for (App const& app : apps) {
                if (app.getChecked() == false) {
                    service.modifyApp(app.getPath(), true);
                }
            }
        }
        else {
            for (App const& app : apps) {
                if (app.getChecked() == true) {
                    service.modifyApp(app.getPath(), false);
                }
            }
        }
        fillTable(appsTable);
        });

    QObject::connect(turnOnButton, &QPushButton::clicked, [this]() {
        auto apps = service.getAllApps();
        for (App const& app : apps) {
            if (app.getChecked() == true) {
                STARTUPINFO info = { sizeof(info) };
                PROCESS_INFORMATION processInfo;
                std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
                std::wstring path = converter.from_bytes(app.getPath());
                const wchar_t* appPath = path.c_str();
                if (CreateProcess(appPath, 0, NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo))
                {
                    WaitForSingleObject(processInfo.hProcess, INFINITE);
                    CloseHandle(processInfo.hProcess);
                    CloseHandle(processInfo.hThread);
                }
            }
        }
        });
}

void GUI::fillTable(QTableWidget* table)
{
    table->clearContents();
    auto apps = service.getAllApps();
    table->setRowCount(apps.size());
    int i = 0;
    for (App const& app : apps) {
        QTableWidgetItem* appItem = new QTableWidgetItem(QString::fromStdString(app.getPath()));
        table->setItem(i, 0, appItem);
        QCheckBox* state = new QCheckBox;
        if (app.getChecked() == true) {
            state->setCheckState(Qt::CheckState::Checked);
        }
        else {
            state->setCheckState(Qt::CheckState::Unchecked);
        }
        QObject::connect(state, &QCheckBox::stateChanged, [this, app, state]() {
            bool check = false;
            if (state->checkState() == Qt::CheckState::Checked) {
                check = true;
            }
            service.modifyApp(app.getPath(), check);
            });
        table->setCellWidget(i, 1, state);
        i++;
    }
}
