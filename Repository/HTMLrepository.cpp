#include "HTMLrepository.h"


HTMLRepository::HTMLRepository(const std::vector<Dog>& adoptionList, const std::string& fileName) {
	this->adoptionList = adoptionList;
	this->fileName = fileName;
}

HTMLRepository::~HTMLRepository()
{
}

std::vector<Dog>& HTMLRepository::getAllUserRepo() {
	return this->adoptionList;
}

int HTMLRepository::getUserNrElements() {
	return this->adoptionList.size();
}

int HTMLRepository::getUserCap() {
	return this->adoptionList.capacity();
}

void HTMLRepository::addUserRepo(const Dog& dog) {
	this->adoptionList.push_back(dog);
	this->saveToFile();
}

void HTMLRepository::saveToFile() {
	std::ofstream fout(this->fileName);
	fout << "<!DOCTYPE html>\n<html>\n<head>\n\t<title>Adoption List</title>\n</head>\n<body>\n";
	fout << "<table border=\"1\">\n";
	fout << "\t<tr>\n\t\t<td>Breed</td>\n\t\t<td>Name</td>\n\t\t<td>Age</td>\n\t\t<td>Photograph</td>\n\t</tr>\n";
	for (const Dog& dog : this->adoptionList) {
		fout << "\t<tr>\n\t\t<td>" << dog.getBreed() << "</td>\n\t\t<td>" << dog.getName() << "</td>\n\t\t<td>" << dog.getAge() << "</td>\n\t\t<td><a href=\"" << dog.getPhotograph() << "\">" << dog.getPhotograph() << "</a></td>\n\t</tr>\n";
	}
	fout << "</table></body></html>";
	fout.close();
}

std::string& HTMLRepository::getFileName() {
	return this->fileName;
}
