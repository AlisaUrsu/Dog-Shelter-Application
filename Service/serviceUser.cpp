#include "serviceUser.h"
#include <algorithm>

ServiceUser::ServiceUser(UserRepository* userRepo, Repository& adminRepo) : repo(adminRepo) {
	this->userRepository = userRepo;
}

ServiceUser::ServiceUser(Repository& repository) :repo(repository) {
}

ServiceUser::~ServiceUser()
{
}

std::vector<Dog> ServiceUser::getAllServiceUser() {
	if (this->userRepository->getAllUserRepo().empty()) {
		std::string errors;
		errors += std::string("The list of adoption is empty!");
		if (!errors.empty())
			throw UserRepositoryException(errors);
	}
	return this->userRepository->getAllUserRepo();
}

int ServiceUser::getNrElementsServiceUser() {
	if (this->userRepository->getAllUserRepo().empty()) {
		std::string errors;
		errors += std::string("The list of adoption is empty!");
		if (!errors.empty())
			throw UserRepositoryException(errors);
	}
	return this->userRepository->getUserNrElements();
}

int ServiceUser::getCapacityServiceUser() {
	return this->userRepository->getUserCap();
}

void ServiceUser::addServiceUser(Dog dog) {
	this->userRepository->addUserRepo(dog);
	std::string name = dog.getName();
	int result = this->repo.findByName(name);
	this->repo.deleteRepo(result);
}

void ServiceUser::filter(std::vector<Dog>& filterDogs, std::string string, int age) {
	std::vector<Dog> data;
	data.reserve(this->repo.getNrElements());
	data = this->repo.getAllRepo();
	if (string[0] == '\0')
		std::copy_if(data.begin(), data.end(), std::back_inserter(filterDogs), [&age](Dog& dog) {return dog.getAge() < age; });
	else
		std::copy_if(data.begin(), data.end(), std::back_inserter(filterDogs), [&string, &age](Dog& dog) {return dog.getBreed() == string && dog.getAge() < age; });
}

void ServiceUser::repositoryType(const std::string& fileType) {
	if (fileType == "csv" || fileType == "CSV") {
		std::vector<Dog> userVector;
		std::string userFile = R"(D:\School\An 1\OOP\Labs\A89\adoption_list.csv)";
		auto* repo = new CSVRepository{ userVector, userFile };
		this->userRepository = repo;
	}
	else if (fileType == "html" || fileType == "HTML") {
		std::string userFile = R"(D:\School\An 1\OOP\Labs\A89\adoption_list.html)";
		std::vector<Dog> userVector;
		auto* repo = new HTMLRepository{ userVector, userFile };
		this->userRepository = repo;
	}
	else {
		std::string errors;
		errors += std::string("The filename is invalid!");
		if (!errors.empty())
			throw UserRepositoryException(errors);
	}
}

std::string& ServiceUser::getFileService() {
	return this->userRepository->getFileName();
}
