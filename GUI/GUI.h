#pragma once

#include <QtWidgets/QMainWindow>
//#include "ui_A89.h"
#include "service.h"
#include "serviceUser.h"
#include "validators.h"
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QLineEdit>
#include <QRadioButton>


class DogListModel : public QAbstractListModel {
private:
	Repository& repository;
public:
	explicit DogListModel(Repository& repo) : repository{ repo } {};
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
};

class GUI : public QWidget {
private:
	ValidateDog& validator;
	Repository& repository;
	Service& service;
	ServiceUser& userService;

	void initGUI();

	QLabel* titleWidget;
	QPushButton* adminButton;
	QPushButton* userButton;

	void showAdmin();
	void showUser();
	void connectSignalAndSlots();
public:
	explicit GUI(ValidateDog& v, Repository& r, Service& s, ServiceUser& us);
	~GUI() override;
};

class AdminGUI : public QWidget {
private:
	ValidateDog& validator;
	Repository& repository;
	Service& service;

	void initAdminGUI();

	QLabel* titleWidget;
	QListWidget* dogsListWidget;
	QLineEdit* breedLineEdit, *nameLineEdit,  * ageLineEdit, * photographLineEdit;
	QPushButton* addButton, * deleteButton, * updateButton, * chartButton;
	DogListModel* listModel;

	void populateList();
	void connectSignalsAndSlots();
	int getSelectedIndex() const;
	void addDog();
	void deleteDog();
	void updateDog();
	void showChart();

	QWidget* chartWindow;

public:
	explicit AdminGUI(QWidget* parent, ValidateDog& v, Repository& r, Service& s);
	~AdminGUI() override;
};

class UserGUI : public QWidget {
private:
	ValidateDog& validator;
	Service& service;
	ServiceUser& userService;

	void initUserGUI();

	QLabel* titleWidget;
	QListWidget* dogsListWidget, * adoptionListWidget;
	QLineEdit* breedLineEdit, * nameLineEdit, * ageLineEdit, * photographLineEdit, * breedFilterLineEdit, * ageFilterLineEdit;;
	QPushButton* addButton, * filterButton, * openListButton;
	QRadioButton* CSVButton, *HTMLButton;

	bool repoTypeSelected;
	bool filter;
	void populateDogList();
	void populateAdoptionList();
	void connectSignalAndSlots();
	int getSelectedIndex() const;
	void addDog();
	void filterDogs();
public:
	explicit UserGUI(QWidget* parent, ValidateDog& v, Service& s, ServiceUser& us);
	~UserGUI() override;
};