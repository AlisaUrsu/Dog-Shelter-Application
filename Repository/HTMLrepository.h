#pragma once
#include "repositoryUser.h"

class HTMLRepository : public UserRepository {
public:
	HTMLRepository(const std::vector<Dog>& adoptionList, const std::string& fileName);
	~HTMLRepository();
	std::vector<Dog>& getAllUserRepo() override;
	int getUserNrElements() override;
	int getUserCap() override;
	void addUserRepo(const Dog& dog) override;
	void saveToFile() override;
	std::string& getFileName() override;
};