#include "service.h"

void ServiceApps::addApp(std::string path, bool checked)
{
    App app(path, checked);
    repository.addApp(app);
}

void ServiceApps::deleteApp(std::string path)
{
    App app(path, true);
    repository.deleteApp(app);
}

void ServiceApps::modifyApp(std::string path, bool checked)
{
    App app(path, checked);
    repository.modifyApp(app);
}

std::vector<App> ServiceApps::getAllApps()
{
    return repository.getAllApps();
}
