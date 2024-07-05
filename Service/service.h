#pragma once
#include "repository.h"
#include "Dog.h"
#include <vector>

class Service {
private:
	Repository& repository;
public:
	Service(Repository& repo);
	~Service();
	std::vector<Dog> getAllService();
	int getNrElementsService();
	int getCapacityService();
	void addService(std::string breed, std::string name, int age, std::string photograph);
	void deleteService(std::string name);
	void updateService(std::string name, std::string newBreed, std::string newName, int newAge, std::string newPhotograph);
	int findByNameService(const std::string& name);
	std::vector<std::string> getAllBreeds();
	int numberOfDogsPerBreed(const std::string& breed);
};
