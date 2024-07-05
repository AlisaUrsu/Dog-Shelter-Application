#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <sstream>
#include <fstream>
#include <algorithm>


class Dog {
private:
	std::string breed;
	std::string name;
	int age;
	std::string photograph;

public:

	explicit Dog(std::string breed = "", std::string name = "", int age = -1, std::string photograph = "");
	~Dog();

	std::string getBreed() const;
	std::string getName() const;
	int getAge() const;
	std::string getPhotograph() const;
	std::string toString() const;
	//std::vector<std::string> tokenize(const std::string& str, char delimiter);
	bool operator==(const Dog& dog) const;
	friend std::istream& operator>>(std::istream& inputStream, Dog& dog);
	friend std::ostream& operator<<(std::ostream& outputStream, const Dog& dog);
};