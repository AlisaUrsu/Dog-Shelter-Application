#include "Dog.h"


Dog::Dog(std::string breed, std::string name, int age, std::string photograph) {
	/*if (age < 0)
		throw "Age cannot be smaller than 0!";*/
	this->breed = std::move(breed);
	this->name = std::move(name);
	this->age = age;
	this->photograph = std::move(photograph);
}

Dog::~Dog()
{
}

std::string Dog::getBreed() const {
	return this->breed;
}

std::string Dog::getName() const {
	return this->name;
}

int Dog::getAge() const {
	return this->age;
}

std::string Dog::getPhotograph() const {
	return this->photograph;
}

std::string Dog::toString() const {
	auto strAge = std::to_string(this->age);
	return this->breed + " - " + this->name + " Age: " + strAge + "\nPhotograph: " + this->photograph + "\n";
}

bool Dog::operator==(const Dog& dog) const {
	return this->name == dog.name;
}

std::vector<std::string> tokenize(const std::string& str, char delimiter) {
	std::vector<std::string> result;
	std::stringstream ss(str);
	std::string token;
	while (getline(ss, token, delimiter))
		result.push_back(token);
	return result;
}

std::istream& operator>>(std::istream& inputStream, Dog& dog) {
	std::string line;
	std::getline(inputStream, line);
	std::vector<std::string> tokens;
	if (line.empty())
		return inputStream;
	tokens = tokenize(line, ',');
	dog.breed = tokens[0];
	dog.name = tokens[1];
	dog.age = std::stoi(tokens[2]);
	dog.photograph = tokens[3];
	return inputStream;
}

std::ostream& operator<<(std::ostream& outputStream, const Dog& dog) {

	outputStream << dog.getBreed() << "," << dog.getName() << "," << std::to_string(dog.getAge()) << "," << dog.getPhotograph();
	return outputStream;
}
