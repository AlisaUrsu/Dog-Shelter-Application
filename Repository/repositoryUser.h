#pragma once
#include "Dog.h"
#include "repository.h"

class UserRepository {
protected:
	std::vector<Dog> adoptionList;
	std::string fileName;

public:
	explicit UserRepository(std::vector<Dog>& userRepoArray);
	UserRepository();
	virtual std::vector<Dog>& getAllUserRepo() = 0;
	virtual int getUserNrElements() = 0;
	virtual int getUserCap() = 0;
	virtual void addUserRepo(const Dog& dog) = 0;
	virtual void saveToFile() = 0;
	virtual std::string& getFileName() = 0;
	~UserRepository();
};

class UserRepositoryException : public std::exception {
private:
	std::string message;
public:
	UserRepositoryException(std::string& message);
	const char* what() const noexcept override;
};


