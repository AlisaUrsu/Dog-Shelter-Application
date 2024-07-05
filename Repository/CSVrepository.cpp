#include "CSVrepository.h"


CSVRepository::CSVRepository(const std::vector<Dog>& adoptionList, const std::string& fileName) {
	this->adoptionList = adoptionList;
	this->fileName = fileName;
}

CSVRepository::~CSVRepository()
{
}

std::vector<Dog>& CSVRepository::getAllUserRepo() {
	return this->adoptionList;
}

int CSVRepository::getUserNrElements() {
	return this->adoptionList.size();
}

int CSVRepository::getUserCap() {
	return this->adoptionList.capacity();
}

void CSVRepository::addUserRepo(const Dog& dog) {
	this->adoptionList.push_back(dog);
	this->saveToFile();
}

void CSVRepository::saveToFile() {
	std::ofstream fout(this->fileName);
	if (!this->adoptionList.empty()) {
		for (const Dog& dog : this->adoptionList) {
			fout << dog << std::endl;
		}
	}
	fout.close();
}

std::string& CSVRepository::getFileName() {
	return this->fileName;

}
