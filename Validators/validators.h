#pragma once
#include <string>

class ValidationException : public::std::exception {
private:
	std::string message;
public:
	ValidationException(std::string& _message);
	const char* what() const noexcept override;
};

class ValidateDog {
public:
	ValidateDog();
	~ValidateDog();
	void validateName(std::string& name);
	void validateBreed(std::string& breed);
	void validateAgeString(std::string& ageString);
	void validateAge(int& age);
	void validatePhotograph(std::string& photograph);
	bool validateString(std::string& string);
};