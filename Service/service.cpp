#include "service.h"

Service::Service(Repository& repo) : repository(repo) {
}

Service::~Service()
{
}

std::vector<Dog> Service::getAllService() {
	return this->repository.getAllRepo();
}

int Service::getNrElementsService() {
	return this->repository.getNrElements();
}

int Service::getCapacityService() {
	return this->repository.getCapacity();
}

void Service::addService(std::string breed, std::string name, int age, std::string photograph) {
	Dog dog = Dog(breed, name, age, photograph);
	this->repository.addRepo(dog);
}

void Service::deleteService(std::string name) {
	int result = this->repository.findByName(name);
	this->repository.deleteRepo(result);
}

void Service::updateService(std::string name, std::string newBreed, std::string newName, int newAge, std::string newPhotograph) {
	int result = this->repository.findByName(name);
	Dog newDog = Dog(newBreed, newName, newAge, newPhotograph);
	this->repository.updateRepo(newDog, result);
}

int Service::findByNameService(const std::string& name) {
    return this->repository.findByName(name);
}

std::vector<std::string> Service::getAllBreeds() {
    std::vector<std::string> breeds;
    std::vector<Dog> data;
    data = this->repository.getAllRepo();
    for (const Dog& dog : data) {
        if (std::find(breeds.begin(), breeds.end(), dog.getBreed()) == breeds.end())
            breeds.push_back(dog.getBreed());
    }
    return breeds;
}

int Service::numberOfDogsPerBreed(const std::string& breed) {
    int count = 0;
    std::vector<Dog> data;
    data = this->repository.getAllRepo();
    for (const Dog& dog : data) {
        if (dog.getBreed() == breed) {
            count += 1;
        }
    }
    return count;
}
