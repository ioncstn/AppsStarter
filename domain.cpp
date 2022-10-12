#include "domain.h"

std::string App::getPath() const
{
    return path;
}

bool App::getChecked() const
{
    return checked;
}

void App::setChecked(bool newState)
{
    checked = newState;
}
