#include "GUI.h"
#include <QtWidgets/QApplication>
#include "service.h"
#include "Dog.h"
#include "validators.h"
#include "serviceUser.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
	std::vector<Dog> dogs;
	dogs.reserve(10);
	std::string file = R"(D:\School\An 1\OOP\Labs\A89\dogs.txt)";
	Repository repo{ dogs, file };
	repo.generateRepo();
	Service service{ repo };
	ServiceUser serviceUser{ repo };
	ValidateDog validator{};
	GUI gui{ validator, repo, service, serviceUser };
	gui.show();
    return a.exec();
}
