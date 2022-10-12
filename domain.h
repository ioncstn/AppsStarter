#pragma once
#include <string>

class App {
private:
	std::string path;
	bool checked;

public:

	App(std::string p, bool c) : path(p), checked(c) {};

	std::string getPath() const;

	bool getChecked() const;

	void setChecked(bool newState);

	bool operator==(App const& other) const {
		if (other.getPath() == this->path) {
			return true;
		}
		return false;
	}

};