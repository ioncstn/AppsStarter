#include "GUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RepositoryApps repo("apps.txt");
    ServiceApps srv(repo);
    GUI w(srv);
    w.show();
    return a.exec();
}
