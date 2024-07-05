#include "validators.h"

ValidationException::ValidationException(std::string& _message) :message(_message) {

}

const char* ValidationException::what() const noexcept {
	return message.c_str();
}

ValidateDog::ValidateDog()
{
}

ValidateDog::~ValidateDog()
{
}

void ValidateDog::validateName(std::string& name) {
	std::string errors;
	if (!validateString(name))
		errors += std::string("The name input cannont contain any digits!");
	if (name.length() == 0)
		errors += std::string("The input cannot be empty!");
	if (!errors.empty())
		throw ValidationException(errors);
}

void ValidateDog::validateBreed(std::string& breed) {
	std::string errors;
	if (!validateString(breed))
		errors += std::string("The breed input cannont contain any digits!");
	if (breed.length() == 0)
		errors += std::string("The input cannot be empty!");
	if (!errors.empty())
		throw ValidationException(errors);
}

void ValidateDog::validateAgeString(std::string& ageString) {
	std::string errors;
	if (ageString.empty())
		errors += std::string("The input cannot be empty!");
	if (ageString.find_first_not_of("0123456789") != std::string::npos)
		errors += std::string("The age input must contain only digits!");
	if (!errors.empty())
		throw ValidationException(errors);

}

void ValidateDog::validateAge(int& age) {
	std::string errors;
	if (age < 0)
		errors += std::string("The age cannot be less than 0!");
	if (!errors.empty())
		throw ValidationException(errors);
}

void ValidateDog::validatePhotograph(std::string& photograph) {
	std::string errors;
	if (photograph.empty())
		errors += std::string("The input cannot be empty!");
	if (!errors.empty())
		throw ValidationException(errors);
}

bool ValidateDog::validateString(std::string& string) {
	for (char i : string)
		if (isdigit(i) != false)
			return false;
	return true;
}
