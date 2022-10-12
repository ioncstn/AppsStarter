#pragma once

#include <vector>
#include <fstream>
#include <exception>
#include "domain.h"


class RepositoryApps {
private:
	std::vector<App> apps;
	std::string filePath;

public:
	RepositoryApps(std::string f) : filePath(f) { loadFromFile(); };

	void loadFromFile();

	void uploadToFile();

	void addApp(App app);

	void deleteApp(App app);

	void modifyApp(App app);

	std::vector<App> getAllApps();

};