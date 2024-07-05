#include "repository.h"


void Repository::loadFromFile() {
	if (!this->fileName.empty()) {
		Dog dogFromFile;
		std::ifstream fin(this->fileName);
		while (fin >> dogFromFile) {
			if (std::find(this->listOfDogs.begin(), this->listOfDogs.end(), dogFromFile) == this->listOfDogs.end())
				this->listOfDogs.push_back(dogFromFile);
		}
		fin.close();
	}


}

void Repository::saveToFile() {
	if (!this->fileName.empty()) {
		std::ofstream fout(this->fileName);
		for (const Dog& dog : this->listOfDogs) {
			fout << dog << "\n";
		}
		fout.close();
	}

}

Repository::Repository(std::vector<Dog>& listOfDogs, std::string& fileName) {
	this->fileName = fileName;
	this->listOfDogs = listOfDogs;
}

Repository::~Repository()
{
}

std::vector<Dog>& Repository::getAllRepo() {
	if (this->listOfDogs.empty()) {
		std::string errors;
		errors += std::string("The database is empty!");
		if (!errors.empty())
			throw RepositoryException(errors);
	}
	return this->listOfDogs;
}

int Repository::getNrElements() {
	if (this->listOfDogs.empty()) {
		std::string errors;
		errors += std::string("The database is empty!");
		if (!errors.empty())
			throw RepositoryException(errors);
	}
	return this->listOfDogs.size();
}

int Repository::getCapacity() {
	return this->listOfDogs.capacity();
}

int Repository::findByName(const std::string& name) {
	int searchedIndex = -1;
	std::vector<Dog>::iterator i;
	i = std::find_if(this->listOfDogs.begin(), this->listOfDogs.end(), [&name](Dog& dog)
		{return dog.getName() == name; });
	if (i != this->listOfDogs.end())
		searchedIndex = i - this->listOfDogs.begin();
	return searchedIndex;
}

void Repository::addRepo(const Dog& dog) {
	int result = this->findByName(dog.getName());
	if (result != -1) {
		std::string errors;
		errors += std::string("The dog already is registered in the database!");
		if (!errors.empty())
			throw RepositoryException(errors);
	}
	else {
		this->listOfDogs.push_back(dog);
		this->saveToFile();
		std::cout << std::endl << "Dog added successfully!" << std::endl;
	}

}

void Repository::deleteRepo(int index) {
	if (index != -1) {
		this->listOfDogs.erase(this->listOfDogs.begin() + index);
		this->saveToFile();
		std::cout << std::endl << "Dog deleted successfully!" << std::endl;
	}
	else {
		std::string errors;
		errors += std::string("The dog does not exist!");
		if (!errors.empty())
			throw RepositoryException(errors);
	}
}

void Repository::updateRepo(const Dog& newDog, int index) {
	if (index != -1) {
		this->listOfDogs[index] = newDog;
		this->saveToFile();
		std::cout << std::endl << "Dog updated successfully!" << std::endl;
	}
	else {
		std::string errors;
		errors += std::string("The dog does not exist!");
		if (!errors.empty())
			throw RepositoryException(errors);
	}
}

void Repository::generateRepo() {
	this->loadFromFile();
}

RepositoryException::RepositoryException(std::string& _message) {
	this->message = _message;
}

const char* RepositoryException::what() const noexcept {
	return message.c_str();
}
