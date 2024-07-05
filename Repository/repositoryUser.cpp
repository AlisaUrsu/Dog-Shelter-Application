#include "repositoryUser.h"


UserRepository::UserRepository() = default;

UserRepository::UserRepository(std::vector<Dog>& userRepoArray) {
	this->adoptionList = userRepoArray;
}


UserRepository::~UserRepository()
{
}

UserRepositoryException::UserRepositoryException(std::string& message) : message(message) {

}

const char* UserRepositoryException::what() const noexcept {
	return message.c_str();
}
