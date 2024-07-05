#pragma once
#include "repository.h"
#include "repositoryUser.h"
#include "CSVrepository.h"
#include "HTMLrepository.h"
#include "Dog.h"
#include <vector>
#include <iostream>

class ServiceUser {
private:
	UserRepository* userRepository;
	Repository& repo;
public:
	ServiceUser(UserRepository* userRepo, Repository& adminRepo);
	ServiceUser(Repository& repository);
	~ServiceUser();
	std::vector<Dog> getAllServiceUser();
	int getNrElementsServiceUser();
	int getCapacityServiceUser();
	void addServiceUser(Dog dog);
	void filter(std::vector<Dog>& filterDogs, std::string string, int age);
	void repositoryType(const std::string& fileType);
	std::string& getFileService();

};