#include "GUI.h"
#include <QBoxLayout>
#include <QFormLayout>
#include <QApplication>
#include <QErrorMessage>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QMessageBox>

int DogListModel::rowCount(const QModelIndex& parent) const{
    return this->repository.getNrElements();
}

QVariant DogListModel::data(const QModelIndex& index, int role) const{
    int row = index.row();
    Dog dog = this->repository.getAllRepo()[row];
    if (role == Qt::DisplayRole)
        return QString::fromStdString(dog.getName());
    return QVariant();
}

void GUI::initGUI() {
    auto* layout = new QVBoxLayout();
    QFont titleFont = this->titleWidget->font();
    this->titleWidget->setText("<p style='text-align:center;font-family:Franklin Gothic Demi;color:#5A3B26;margin:10px;font-size:55px'> WELCOME TO THE DOG SHELTER APP!</p><p style='text-align:center;color:#181817;font-size:23px;font-family:Roboto Black'> SELECT YOUR MODE!</font></p>");
    layout->addWidget(this->titleWidget);
    auto* vertLayout = new QVBoxLayout();
    vertLayout->setContentsMargins(400,0, 400, 20);
    this->adminButton->setObjectName("adminButton");
    this->adminButton->setStyleSheet("QPushButton#adminButton {background-color: #8C7462;border-style: groove;border-width: 3px;border-color: #5A3B26;font-family: Roboto Black;letter-spacing: 1px;font-size: 15px;color:white;padding: 6px;} ");
    this->userButton->setObjectName("userButton");
    this->userButton->setStyleSheet("QPushButton#userButton {background-color: #8C7462;border-style: groove;border-width: 3px;border-color: #5A3B26;font-family: Roboto Black;letter-spacing: 1px;font-size: 15px;color:white;padding: 6px;} ");
    this->adminButton->setText("Admin Mode");
    this->userButton->setText("User Mode");
    vertLayout->addWidget(this->adminButton);
    vertLayout->addWidget(this->userButton);
    layout->addLayout(vertLayout);
    this->setLayout(layout);
    this->setObjectName("centralWidget");
    this->setStyleSheet("#centralWidget {background-image: url(paws.jpg)}");
    this->setFixedSize(1100, 600);
  
}

void GUI::showAdmin(){
    auto* admin = new AdminGUI(this, this->validator, this->repository, this->service);
    admin->show();
}

void GUI::showUser(){
    auto* user = new UserGUI(this, this->validator, this->service, this->userService);
    user->show();
}

void GUI::connectSignalAndSlots(){
    QObject::connect(this->adminButton, &QPushButton::clicked, this, &GUI::showAdmin);
    QObject::connect(this->userButton, &QPushButton::clicked, this, &GUI::showUser);
}

GUI::GUI(ValidateDog& v, Repository& r, Service& s, ServiceUser& us) : validator{ v }, repository{ r }, service{ s }, userService{ us } {
    this->titleWidget = new QLabel(this);
    this->adminButton = new QPushButton(this);
    this->userButton = new QPushButton(this);
    this->initGUI();
    this->connectSignalAndSlots();
}

GUI::~GUI() = default;

void AdminGUI::initAdminGUI() {
    auto* layout = new QVBoxLayout(this);
    auto* horLayout = new QHBoxLayout();
    horLayout->setSpacing(50);
    horLayout->setContentsMargins(30, 30, 30, 30);
    this->titleWidget->setText("<p style='text-align:center;color:#5A3B26;font-size:45px;font-family:Franklin Gothic Demi'> ADMIN MODE</p>");
    layout->addWidget(this->titleWidget);

    auto* vertLayout = new QVBoxLayout();
    vertLayout->setSpacing(40);

    auto* formLayout = new QGridLayout();
    formLayout->setSpacing(10);
    this->breedLineEdit->setObjectName("breedLineEdit");
    this->breedLineEdit->setStyleSheet("QLineEdit#breedLineEdit {border-style: outset;border-width: 3px;border-color: #5A3B26; font-family: Josefin Sans Thin Medium;font-size: 19px;color:#181817; padding: 3px}");
    this->nameLineEdit->setObjectName("nameLineEdit");
    this->nameLineEdit->setStyleSheet("QLineEdit#nameLineEdit {border-style: outset;border-width: 3px;border-color: #5A3B26;font-family: Josefin Sans Thin Medium;font-size: 19px;color:#181817; padding: 3px}");
    this->ageLineEdit->setObjectName("ageLineEdit");
    this->ageLineEdit->setStyleSheet("QLineEdit#ageLineEdit {border-style: outset;border-width: 3px;border-color: #5A3B26;font-family: Josefin Sans Thin Medium;font-size: 19px;color:#181817; padding: 3px}");
    this->photographLineEdit->setObjectName("photographLineEdit");
    this->photographLineEdit->setStyleSheet("QLineEdit#photographLineEdit {border-style: outset;border-width: 3px;border-color: #5A3B26;font-family: Josefin Sans Thin Medium;font-size: 19px;color:#181817; padding: 3px}");
    auto* breedLabel = new QLabel("Breed");
    breedLabel->setObjectName("breedLabel");
    breedLabel->setStyleSheet("QLabel#breedLabel {text-align:center;color:#181817;font-size:19px;font-family:Roboto Black}");
    auto* nameLabel = new QLabel("Name");
    nameLabel->setObjectName("nameLabel");
    nameLabel->setStyleSheet("QLabel#nameLabel {text-align:center;color:#181817;font-size:19px;font-family:Roboto Black}");
    auto* ageLabel = new QLabel("Age");
    ageLabel->setObjectName("ageLabel");
    ageLabel->setStyleSheet("QLabel#ageLabel {text-align:center;color:#181817;font-size:19px;font-family:Roboto Black}");
    auto* photographLabel = new QLabel("Photograph");
    photographLabel->setObjectName("photographLabel");
    photographLabel->setStyleSheet("QLabel#photographLabel {text-align:center;color:#181817;font-size:19px;font-family:Roboto Black}");
    formLayout->addWidget(breedLabel, 0, 0);
    formLayout->addWidget(this->breedLineEdit, 0, 1);
    formLayout->addWidget(nameLabel, 1, 0);
    formLayout->addWidget(this->nameLineEdit, 1, 1);
    formLayout->addWidget(ageLabel, 2, 0);
    formLayout->addWidget(this->ageLineEdit, 2, 1);
    formLayout->addWidget(photographLabel, 3, 0);
    formLayout->addWidget(this->photographLineEdit, 3, 1);
    

    vertLayout->addLayout(formLayout);

    auto* buttonsLayout = new QGridLayout();
    buttonsLayout->setSpacing(10);
    buttonsLayout->setContentsMargins(50, 0, 50, 20);
    this->addButton->setObjectName("addButton");
    this->deleteButton->setObjectName("deleteButton");
    this->updateButton->setObjectName("updateButton");
    this->chartButton->setObjectName("chartButton");

    this->addButton->setStyleSheet("QPushButton#addButton{background-color: #8C7462; border-style: groove; border-width: 3px; border-color: #5A3B26; font-family: Roboto Black; letter-spacing: 1px; font-size: 14px; color:white; padding: 6px;} ");
    this->deleteButton->setStyleSheet("QPushButton#deleteButton{background-color: #8C7462; border-style: groove; border-width: 3px; border-color: #5A3B26; font-family: Roboto Black; letter-spacing: 1px; font-size: 14px; color:white; padding: 6px;} ");
    this->updateButton->setStyleSheet("QPushButton#updateButton{background-color: #8C7462; border-style: groove; border-width: 3px; border-color: #5A3B26; font-family: Roboto Black; letter-spacing: 1px; font-size: 14px; color:white; padding: 6px;} ");
    this->chartButton->setStyleSheet("QPushButton#chartButton{background-color: #8C7462; border-style: groove; border-width: 3px; border-color: #5A3B26; font-family: Roboto Black; letter-spacing: 1px; font-size: 14px; color:white; padding: 6px;} ");

    buttonsLayout->addWidget(this->addButton, 0, 0);
    buttonsLayout->addWidget(this->deleteButton, 0, 1);
    buttonsLayout->addWidget(this->updateButton, 1, 0);
    buttonsLayout->addWidget(this->chartButton, 1, 1);

    vertLayout->addLayout(buttonsLayout);

    horLayout->addLayout(vertLayout);
    horLayout->addWidget(this->dogsListWidget);
    this->dogsListWidget->setObjectName("dogsListWidget");
    this->dogsListWidget->setStyleSheet("QListWidget {background-color: #8C7462;border-style: groove;border-width: 4px;border-color: #5A3B26;font-family: Josefin Sans Thin Medium;letter-spacing: 1px;font-size: 19px;color:white;padding: 16px;}");
    //this->dogsListWidget->setStyleSheet("QListView::item:hover background: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1,stop : 0 #FAFBFE, stop: 1 #DCDEF1);}");
    layout->addLayout(horLayout);
    this->setObjectName("centralWidget");
    this->setStyleSheet("#centralWidget {background-image: url(paws.jpg)}");
    this->setFixedSize(1100, 600);
}

void AdminGUI::populateList(){
    this->dogsListWidget->clear();
    std::vector<Dog> dogs = this->service.getAllService();
    for (Dog& dog : dogs)
        this->dogsListWidget->addItem(QString::fromStdString(dog.getName() + " - " + dog.getBreed() + " Age: " + std::to_string(dog.getAge())));
}

void AdminGUI::connectSignalsAndSlots(){
    QObject::connect(this->dogsListWidget, &QListWidget::itemSelectionChanged, [this]() {
        int selectedIndex = this->getSelectedIndex();
        if (selectedIndex < 0)
            return;
        Dog dog = this->service.getAllService()[selectedIndex];
        this->breedLineEdit->setText(QString::fromStdString(dog.getBreed()));
        this->nameLineEdit->setText(QString::fromStdString(dog.getName()));
        this->ageLineEdit->setText(QString::fromStdString(std::to_string(dog.getAge())));
        this->photographLineEdit->setText(QString::fromStdString(dog.getPhotograph()));
        });
    QObject::connect(this->addButton, &QPushButton::clicked, this, &AdminGUI::addDog);
    QObject::connect(this->deleteButton, &QPushButton::clicked, this, &AdminGUI::deleteDog);
    QObject::connect(this->updateButton, &QPushButton::clicked, this, &AdminGUI::updateDog);
    QObject::connect(this->chartButton, &QPushButton::clicked, this, &AdminGUI::showChart);
}

int AdminGUI::getSelectedIndex() const{
    QModelIndexList selectedIndexes = this->dogsListWidget->selectionModel()->selectedIndexes();
    if (selectedIndexes.empty()) {
        this->breedLineEdit->clear();
        this->nameLineEdit->clear();
        this->ageLineEdit->clear();
        this->photographLineEdit->clear();
        return -1;
    }
    int selectedIndex = selectedIndexes.at(0).row();
    return selectedIndex;
}

void AdminGUI::addDog(){
    std::string breed = this->breedLineEdit->text().toStdString();
    std::string name = this->nameLineEdit->text().toStdString();
    std::string ageStr = this->ageLineEdit->text().toStdString();
    std::string photograph = this->photographLineEdit->text().toStdString();
    int age;
    try {
        this->validator.validateBreed(breed);
        this->validator.validateName(name);
        this->validator.validateAgeString(ageStr);
        age = stoi(ageStr);
        this->validator.validateAge(age);
        this->validator.validatePhotograph(photograph);
        this->service.addService(breed, name, age, photograph);
        this->populateList();
    }
    catch (ValidationException& exc) {
        auto* error = new QMessageBox();
        error->setIcon(QMessageBox::Critical);
        error->setText(exc.what());
        error->setWindowTitle("Invalid input!");
        error->exec();
    }
    catch (RepositoryException& rexc) {
        auto* error = new QMessageBox();
        error->setIcon(QMessageBox::Critical);
        error->setText(rexc.what());
        error->setWindowTitle("Error at adding dog!");
        error->exec();
    }

}

void AdminGUI::deleteDog(){
    try {
        std::string name = this->nameLineEdit->text().toStdString();
        this->validator.validateName(name);
        this->service.deleteService(name);
        this->populateList();
    }
    catch (ValidationException& exc) {
        auto* error = new QMessageBox();
        error->setIcon(QMessageBox::Critical);
        error->setText(exc.what());
        error->setWindowTitle("Invalid input!");
        error->exec();
    }
    catch (RepositoryException& rexc) {
        auto* error = new QMessageBox();
        error->setIcon(QMessageBox::Critical);
        error->setText(rexc.what());
        error->setWindowTitle("Error at deleting dog!");
        error->exec();
    }
}

void AdminGUI::updateDog(){
    int index = this->getSelectedIndex();
    try {
        if (index < 0) {
            auto* error = new QMessageBox();
            error->setIcon(QMessageBox::Critical);
            error->setText("No dog selected!");
            error->setWindowTitle("Selection error!");
            error->exec();
        }
        else {
            std::string name = this->service.getAllService()[index].getName();
            std::string newBreed = this->breedLineEdit->text().toStdString();
            std::string newName = this->nameLineEdit->text().toStdString();
            std::string newAgeStr = this->ageLineEdit->text().toStdString();
            std::string newPhotograph = this->photographLineEdit->text().toStdString();
            int newAge;
            this->validator.validateBreed(newBreed);
            this->validator.validateName(newName);
            this->validator.validateAgeString(newAgeStr);
            newAge = stoi(newAgeStr);
            this->validator.validateAge(newAge);
            this->validator.validatePhotograph(newPhotograph);
            this->service.updateService(name, newBreed, newName, newAge, newPhotograph);
            this->populateList();
        }
    }
    catch (ValidationException& exc) {
        auto* error = new QMessageBox();
        error->setIcon(QMessageBox::Critical);
        error->setText(exc.what());
        error->setWindowTitle("Invalid input!");
        error->exec();
    }
    catch (RepositoryException& rexc) {
        auto* error = new QMessageBox();
        error->setIcon(QMessageBox::Critical);
        error->setText(rexc.what());
        error->setWindowTitle("Error at updating dog!");
        error->exec();
    }
}

void AdminGUI::showChart(){
    this->chartWindow = new QWidget{};
    auto* chartLayout = new QVBoxLayout(this->chartWindow);
    this->chartWindow->setObjectName("chartWindow");
    this->chartWindow->setStyleSheet("QWidget#chartWindow {background-image: url(paws.jpg)}");
    this->chartWindow->setFixedSize(1100, 600);
    std::vector<std::string> breeds = this->service.getAllBreeds();
    auto* chart = new QChart();
    QBarCategoryAxis* axis_x = new QBarCategoryAxis();
    axis_x->setTitleText("Breeds");
    QStringList categories;
    for (int i = 1; i <= breeds.size(); i++)
        categories << QString::fromStdString(std::to_string(i));

    axis_x->append(categories);
    chart->addAxis(axis_x, Qt::AlignBottom);

    QValueAxis* axis_y = new QValueAxis();
    chart->addAxis(axis_y, Qt::AlignLeft);
    axis_y->setRange(0, 5);
    axis_y->setTitleText("Number of dogs");

    for (std::string& breed : breeds) {
        QBarSeries* series = new QBarSeries();
        QBarSet* set = new QBarSet(QString::fromStdString(breed));
        int nr = this->service.numberOfDogsPerBreed(breed);
        *set << nr;
        series->append(set);
        chart->addSeries(series);
        series->attachAxis(axis_y);
    }
    
    chart->setTitle("Number of dogs per breed");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignLeft);
    chart->legend()->setBackgroundVisible(true);
    chart->legend()->setBorderColor(QColor::fromRgb(170, 140, 250));
    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    chartLayout->addWidget(chartView);
    this->chartWindow->resize(1100, 600);
    this->chartWindow->show();
}

AdminGUI::AdminGUI(QWidget* parent, ValidateDog& v, Repository& r, Service& s) :validator{ v }, repository{ r }, service{ s }{
    this->titleWidget = new QLabel(this);
    this->dogsListWidget = new QListWidget{};
    this->breedLineEdit = new QLineEdit{};
    this->nameLineEdit = new QLineEdit{};
    this->ageLineEdit = new QLineEdit{};
    this->photographLineEdit = new QLineEdit{};
    this->addButton = new QPushButton("Add");
    this->deleteButton = new QPushButton("Delete");
    this->updateButton = new QPushButton("Update");
    this->chartButton = new QPushButton("Display chart");
    setParent(parent);
    setWindowFlag(Qt::Window);
    this->initAdminGUI();
    this->populateList();
    this->connectSignalsAndSlots();
    this->listModel = new DogListModel{ this->repository };
}

AdminGUI::~AdminGUI() = default;

void UserGUI::initUserGUI(){
    auto* layout = new QVBoxLayout(this);
    auto* vertLayout = new QVBoxLayout();
    layout->setSpacing(30);
    layout->setContentsMargins(30, 30, 30, 30);
    vertLayout->setSpacing(18);

    this->titleWidget->setText("<p style='text-align:center;color:#5A3B26;font-size:45px;font-family:Franklin Gothic Demi'> USER MODE</p>");
    layout->addWidget(this->titleWidget);

    auto* buttonsLayout = new QVBoxLayout();
    buttonsLayout->setSpacing(2);
    auto* typeTitle = new QLabel("Select the type of the file you want for saving your adopted dogs!");
    typeTitle->setObjectName("typeTitle");
    typeTitle->setStyleSheet("QLabel#typeTitle {color:#181817;font-size:17px;font-family:Roboto Black;padding-bottom: -40px}");
    this->CSVButton->setObjectName("CSVButton");
    this->HTMLButton->setObjectName("HTMLButton");
    this->openListButton->setObjectName("openButton");
    this->CSVButton->setStyleSheet("QRadioButton#CSVButton {font-family: Roboto Black; letter-spacing: 1px; font-size: 15px; color:#8C7462} ");
    this->HTMLButton->setStyleSheet("QRadioButton#HTMLButton {font-family: Roboto Black; letter-spacing: 1px; font-size: 15px; color:#8C7462} ");
    this->openListButton->setStyleSheet("QPushButton#openButton{background-color: #8C7462; border-style: groove; border-width: 3px; border-color: #5A3B26; font-family: Roboto Black; letter-spacing: 1px; font-size: 12px; color:white; padding: 6px;} ");
    buttonsLayout->addWidget(typeTitle);
    buttonsLayout->addWidget(this->CSVButton);
    buttonsLayout->addWidget(this->HTMLButton);
    buttonsLayout->addWidget(this->openListButton);

    vertLayout->addLayout(buttonsLayout);

    auto* gridLayout = new QGridLayout();
    gridLayout->setSpacing(5);
    this->breedLineEdit->setObjectName("breedLineEdit");
    this->breedLineEdit->setStyleSheet("QLineEdit#breedLineEdit {border-style: outset;border-width: 2.5px;border-color: #5A3B26; font-family: Josefin Sans Thin Medium;font-size: 15px;color:#181817; padding: 2.5px}");
    this->nameLineEdit->setObjectName("nameLineEdit");
    this->nameLineEdit->setStyleSheet("QLineEdit#nameLineEdit {border-style: outset;border-width: 2.5px;border-color: #5A3B26;font-family: Josefin Sans Thin Medium;font-size: 15px;color:#181817; padding: 2.5px}");
    this->ageLineEdit->setObjectName("ageLineEdit");
    this->ageLineEdit->setStyleSheet("QLineEdit#ageLineEdit {border-style: outset;border-width: 2.5px;border-color: #5A3B26;font-family: Josefin Sans Thin Medium;font-size: 15px;color:#181817; padding: 2.5px}");
    this->photographLineEdit->setObjectName("photographLineEdit");
    this->photographLineEdit->setStyleSheet("QLineEdit#photographLineEdit {border-style: outset;border-width: 2.5px;border-color: #5A3B26;font-family: Josefin Sans Thin Medium;font-size: 15px;color:#181817; padding: 2.5px}");
    auto* breedLabel = new QLabel("Breed");
    breedLabel->setObjectName("breedLabel");
    breedLabel->setStyleSheet("QLabel#breedLabel {text-align:center;color:#181817;font-size:16px;font-family:Roboto Black}");
    auto* nameLabel = new QLabel("Name");
    nameLabel->setObjectName("nameLabel");
    nameLabel->setStyleSheet("QLabel#nameLabel {text-align:center;color:#181817;font-size:16px;font-family:Roboto Black}");
    auto* ageLabel = new QLabel("Age");
    ageLabel->setObjectName("ageLabel");
    ageLabel->setStyleSheet("QLabel#ageLabel {text-align:center;color:#181817;font-size:16px;font-family:Roboto Black}");
    auto* photographLabel = new QLabel("Photograph");
    photographLabel->setObjectName("photographLabel");
    photographLabel->setStyleSheet("QLabel#photographLabel {text-align:center;color:#181817;font-size:16px;font-family:Roboto Black}");
    this->addButton->setObjectName("addButton");
    this->addButton->setStyleSheet("QPushButton#addButton{background-color: #8C7462; border-style: groove; border-width: 3px; border-color: #5A3B26; font-family: Roboto Black; letter-spacing: 1px; font-size: 12px; color:white; padding: 6px;} ");
    gridLayout->addWidget(breedLabel, 0, 0);
    gridLayout->addWidget(this->breedLineEdit, 0, 1);
    gridLayout->addWidget(nameLabel, 1, 0);
    gridLayout->addWidget(this->nameLineEdit, 1, 1);
    gridLayout->addWidget(ageLabel, 2, 0);
    gridLayout->addWidget(this->ageLineEdit, 2, 1);
    gridLayout->addWidget(photographLabel, 3, 0);
    gridLayout->addWidget(this->photographLineEdit, 3, 1);
    gridLayout->addWidget(this->addButton);
    vertLayout->addLayout(gridLayout);

    auto gridLayout2 = new QGridLayout();
    gridLayout2->setSpacing(5);
    auto* filterTitle = new QLabel("Filter the dogs by breed and age");
    filterTitle->setObjectName("filterTitle");
    filterTitle->setStyleSheet("QLabel#filterTitle {text-align:center;color:#181817;font-size:17px;font-family:Roboto Black; padding-bottom: -20px}");
    vertLayout->addWidget(filterTitle);
    this->breedFilterLineEdit->setObjectName("breedFilterLineEdit");
    this->breedFilterLineEdit->setStyleSheet("QLineEdit#breedFilterLineEdit {border-style: outset;border-width: 3px;border-color: #5A3B26; font-family: Josefin Sans Thin Medium;font-size: 15px;color:#181817; padding: 3px}");
    this->ageFilterLineEdit->setObjectName("ageFilterLineEdit");
    this->ageFilterLineEdit->setStyleSheet("QLineEdit#ageFilterLineEdit {border-style: outset;border-width: 3px;border-color: #5A3B26; font-family: Josefin Sans Thin Medium;font-size: 15px;color:#181817; padding: 3px}");
    auto* ageFilterLabel = new QLabel("Age");
    ageFilterLabel->setObjectName("ageFilterLabel");
    ageFilterLabel->setStyleSheet("QLabel#ageFilterLabel {text-align:center;color:#181817;font-size:16px;font-family:Roboto Black; padding-right: 36px}");
    auto* breedFilterLabel = new QLabel("Breed");
    breedFilterLabel->setObjectName("breedFilterLabel");
    breedFilterLabel->setStyleSheet("QLabel#breedFilterLabel {text-align:center;color:#181817;font-size:16px;font-family:Roboto Black; padding-right: 36px}");
    this->filterButton->setObjectName("filterButton");
    this->filterButton->setStyleSheet("QPushButton#filterButton{background-color: #8C7462; border-style: groove; border-width: 3px; border-color: #5A3B26; font-family: Roboto Black; letter-spacing: 1px; font-size: 12px; color:white; padding: 6px;} ");
    gridLayout2->addWidget(breedFilterLabel, 0, 0);
    gridLayout2->addWidget(this->breedFilterLineEdit, 0, 1);
    gridLayout2->addWidget(ageFilterLabel, 1, 0);
    gridLayout2->addWidget(this->ageFilterLineEdit, 1, 1);
    gridLayout2->addWidget(this->filterButton);
    vertLayout->addLayout(gridLayout2);
   

    auto* vertLayout2 = new QVBoxLayout();
    vertLayout2->setSpacing(10);
    this->dogsListWidget->setObjectName("dogsListWidget");
    this->dogsListWidget->setStyleSheet("QListWidget {background-color: #8C7462;border-style: groove;border-width: 4px;border-color: #5A3B26;font-family: Josefin Sans Thin Medium;letter-spacing: 1px;font-size: 17px;color:white;padding: 16px;}");
    this->adoptionListWidget->setObjectName("adoptionListWidget");
    this->adoptionListWidget->setStyleSheet("QListWidget {background-color: #8C7462;border-style: groove;border-width: 4px;border-color: #5A3B26;font-family: Josefin Sans Thin Medium;letter-spacing: 1px;font-size: 17px;color:white;padding: 16px;}");
    vertLayout2->addWidget(this->dogsListWidget);
    vertLayout2->addWidget(this->adoptionListWidget);

    auto* horLayout = new QHBoxLayout();
    horLayout->setSpacing(30);
    horLayout->addLayout(vertLayout);
    horLayout->addLayout(vertLayout2);

    layout->addLayout(horLayout);
    this->setLayout(layout);
    this->setObjectName("centralWidget");
    this->setStyleSheet("#centralWidget {background-image: url(paws.jpg)}");
    this->setFixedSize(1100, 600);
}

void UserGUI::populateDogList(){
    this->dogsListWidget->clear();
    std::vector<Dog> dogs = this->service.getAllService();
    for (Dog& dog : dogs)
        this->dogsListWidget->addItem(QString::fromStdString(dog.getName() + " - " + dog.getBreed() + " Age: " + std::to_string(dog.getAge())));
}

void UserGUI::populateAdoptionList(){
    this->adoptionListWidget->clear();
    std::vector<Dog> dogs = this->userService.getAllServiceUser();
    for (Dog& dog : dogs)
        this->adoptionListWidget->addItem(QString::fromStdString(dog.getName()));
}

void UserGUI::connectSignalAndSlots(){
    QObject::connect(this->dogsListWidget, &QListWidget::itemSelectionChanged, [this]() {
        
        int selectedIndex = this->getSelectedIndex();
        if (selectedIndex < 0)
            return;
        Dog dog = this->service.getAllService()[selectedIndex];
        
        this->breedLineEdit->setText(QString::fromStdString(dog.getBreed()));
        this->nameLineEdit->setText(QString::fromStdString(dog.getName()));
        this->ageLineEdit->setText(QString::fromStdString(std::to_string(dog.getAge())));
        this->photographLineEdit->setText(QString::fromStdString(dog.getPhotograph()));
        std::string link = std::string("start ").append(dog.getPhotograph());
        system(link.c_str());
        });

    QObject::connect(this->CSVButton, &QRadioButton::clicked, [this]() {
        this->userService.repositoryType("csv");
        this->repoTypeSelected = true;
        });
    QObject::connect(this->HTMLButton, &QRadioButton::clicked, [this]() {
        this->userService.repositoryType("html");
        this->repoTypeSelected = true;
        });
    QObject::connect(this->openListButton, &QPushButton::clicked, [this]() {
        if (!this->repoTypeSelected) {
            auto* error = new QMessageBox();

            error->setIcon(QMessageBox::Warning);
            error->setText("Please select a file type!");
            error->setWindowTitle("File type warning");
            error->exec();
        }
        else {
            std::string link = std::string("start ").append(this->userService.getFileService());
            system(link.c_str());
        }
        });
    QObject::connect(this->addButton, &QPushButton::clicked, this, &UserGUI::addDog);
    QObject::connect(this->filterButton, &QPushButton::clicked, this, &UserGUI::filterDogs);
}

int UserGUI::getSelectedIndex() const{
    QModelIndexList selectedIndexes = this->dogsListWidget->selectionModel()->selectedIndexes();
    if (selectedIndexes.empty()) {
        this->breedLineEdit->clear();
        this->nameLineEdit->clear();
        this->ageLineEdit->clear();
        this->photographLineEdit->clear();
        return -1;
    }
    int selectedIndex = selectedIndexes.at(0).row();
    return selectedIndex;
}

void UserGUI::addDog(){
    if (!this->repoTypeSelected) {
        auto* error = new QMessageBox();
        error->setIcon(QMessageBox::Warning);
        error->setText("Please select the type of file!");
        error->setWindowTitle("File type warning");
        error->exec();
    }
    else {
        std::string breed = this->breedLineEdit->text().toStdString();
        std::string name = this->nameLineEdit->text().toStdString();
        std::string ageStr = this->ageLineEdit->text().toStdString();
        std::string photograph = this->photographLineEdit->text().toStdString();
        int age;
        try {
            this->validator.validateBreed(breed);
            this->validator.validateName(name);
            this->validator.validateAgeString(ageStr);
            age = stoi(ageStr);
            this->validator.validateAge(age);
            this->validator.validatePhotograph(photograph);
            Dog dog = Dog(breed, name, age, photograph);
            this->userService.addServiceUser(dog);
            if (!this->filter)
                this->populateDogList();
            else
                this->adoptionListWidget->addItem(this->dogsListWidget->takeItem(this->getSelectedIndex()));
            this->populateAdoptionList();
        }
        catch (ValidationException& exc) {
            auto* error = new QMessageBox();
            error->setIcon(QMessageBox::Critical);
            error->setText(exc.what());
            error->setWindowTitle("Invalid input!");
            error->exec();
        }
        catch (RepositoryException& rexc) {
            auto* error = new QMessageBox();
            error->setIcon(QMessageBox::Critical);
            error->setText(rexc.what());
            error->setWindowTitle("Error at adding dog!");
            error->exec();
        }
    }
}

void UserGUI::filterDogs(){
    try {
        std::string breedFilter = this->breedFilterLineEdit->text().toStdString();
        std::string ageFilterStr = this->ageFilterLineEdit->text().toStdString();
        int age;
        if (breedFilter.empty() && ageFilterStr.empty()) {
            this->filter = false;
            this->populateDogList();
        }
        else {
            this->validator.validateString(breedFilter);
            this->validator.validateAgeString(ageFilterStr);
            age = stoi(ageFilterStr);
            this->validator.validateAge(age);
            std::vector<Dog> validDogs;
            this->userService.filter(validDogs, breedFilter, age);
            if (validDogs.empty()) {
                std::string error;
                error += std::string("The list of valid dogs is empty!");
                if (!error.empty())
                    throw UserRepositoryException(error);
            }
            else {
                this->filter = true;
                this->dogsListWidget->clear();
                for (Dog& dog : validDogs)
                    this->dogsListWidget->addItem(QString::fromStdString(dog.getName()));
            }
        }
    }
    catch (ValidationException& exc) {
        auto* error = new QMessageBox();
        error->setIcon(QMessageBox::Critical);
        error->setText(exc.what());
        error->setWindowTitle("Validation error!");
        error->exec();
    }
    catch (UserRepositoryException& urexc) {
        auto* error = new QMessageBox();
        error->setIcon(QMessageBox::Critical);
        error->setText(urexc.what());
        error->setWindowTitle("Filter error!");
        error->exec();
    }
}

UserGUI::UserGUI(QWidget* parent, ValidateDog& v, Service& s, ServiceUser& us):validator{v}, service{s}, userService{us}{
    this->titleWidget = new QLabel(this);
    this->dogsListWidget = new QListWidget{};
    this->adoptionListWidget = new QListWidget{};
    this->breedLineEdit = new QLineEdit{};
    this->nameLineEdit = new QLineEdit{};
    this->ageLineEdit = new QLineEdit{};
    this->photographLineEdit = new QLineEdit{};
    this->breedFilterLineEdit = new QLineEdit{};
    this->ageFilterLineEdit = new QLineEdit{};
    this->addButton = new QPushButton("Adopt This Dog!");
    this->filterButton = new QPushButton("Filter");
    this->openListButton = new QPushButton("Open File");
    this->CSVButton = new QRadioButton("CSV");
    this->HTMLButton = new QRadioButton("HTML");
    this->repoTypeSelected = false;
    this->filter = false;
    setParent(parent);
    setWindowFlag(Qt::Window);
    this->initUserGUI();
    this->populateDogList();
    this->connectSignalAndSlots();
}

UserGUI::~UserGUI()
{
}

