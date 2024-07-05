#pragma once
#include "Dog.h"

class Repository {
private:
	std::vector<Dog> listOfDogs;
	std::string fileName;
public:
	void loadFromFile();
	void saveToFile();
	explicit Repository(std::vector<Dog>& listOfDogs, std::string& fileName);
	~Repository();
	std::vector<Dog>& getAllRepo();
	int getNrElements();
	int getCapacity();
	int findByName(const std::string& name);
	void addRepo(const Dog& dog);
	void deleteRepo(int index);
	void updateRepo(const Dog& newDog, int index);
	void generateRepo();
};

class RepositoryException : public std::exception {
private:
	std::string message;
public:
	explicit RepositoryException(std::string& _message);

	const char* what() const noexcept override;
};