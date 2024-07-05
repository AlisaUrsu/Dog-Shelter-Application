#pragma once
#include "repositoryUser.h"

class CSVRepository : public UserRepository {
public:
	CSVRepository(const std::vector<Dog>& adoptionList, const std::string& fileName);
	~CSVRepository();
	std::vector<Dog>& getAllUserRepo() override;
	int getUserNrElements() override;
	int getUserCap() override;
	void addUserRepo(const Dog& dog) override;
	void saveToFile() override;
	std::string& getFileName() override;

};