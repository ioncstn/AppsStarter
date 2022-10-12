#pragma once

#include "repository.h"

class ServiceApps {
private:
	RepositoryApps& repository;

public:
	ServiceApps(RepositoryApps& repo) : repository(repo) {};

	void addApp(std::string, bool);

	void deleteApp(std::string);

	void modifyApp(std::string, bool);

	std::vector<App> getAllApps();
};