#include "repository.h"

void RepositoryApps::loadFromFile()
{
	std::ifstream fin(filePath);
	std::string line;
	while (std::getline(fin, line)) {
		auto it = line.begin();
		auto nextIt = std::find(it, line.end(), '|');
		std::string path(it, nextIt);
		it = nextIt + 1;
		char checked = line[line.size() - 1];
		bool check = true;
		if (checked == '0') {
			check = false;
		}
		//std::string checked(it, line.end());
		//bool check = std::stoi(checked);
		App app(path, check);
		apps.push_back(app);
	}
	fin.close();
}

void RepositoryApps::uploadToFile()
{
	std::ofstream fout(filePath);
	for (App const& app : apps) {
		char ch = '|';
		fout << app.getPath() << ch;
		int check = 1;
		if (app.getChecked() == false) {
			check = 0;
		}
		fout << check << std::endl;
	}
}

void RepositoryApps::addApp(App app)
{
	for (App const& a : apps) {
		if (a == app) {
			throw std::exception("app already here u cheeky!\n");
		}
	}
	apps.push_back(app);
	uploadToFile();
}

void RepositoryApps::deleteApp(App app)
{
	auto it = std::find(apps.begin(), apps.end(), app);
	if (it == apps.end()) {
		throw std::exception("app is not here!\n");
	}
	apps.erase(it);
	uploadToFile();
}

void RepositoryApps::modifyApp(App app)
{
	for (App& a : apps) {
		if (a == app) {
			a.setChecked(app.getChecked());
			uploadToFile();
			return;
		}
	}
}

std::vector<App> RepositoryApps::getAllApps()
{
	return apps;
}

