#include <QObject>
#include <iostream>
#include <string>
#include <QApplication>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <QComboBox>
#include <QString>
#include <QGridLayout>
#include <QtGui>
#include <QLineEdit>
#include <QListWidget>
#include "mydatastore.h"

using namespace std;

class mainWindow : public QObject {

    Q_OBJECT
private:
	QMainWindow *window = new QMainWindow();
public:
	mainWindow(){
    window->setWindowTitle("Amazon");
    QWidget *centralWidget = new QWidget();


    QGridLayout *mainGrid = new QGridLayout(); 

    QHBoxLayout *topRow = new QHBoxLayout(); 
    QLabel *amazon = new QLabel("AMAZON.CPP! Valente: CSCI 104");
    QComboBox *currentUsr = new QComboBox();
        //vector<string> users = ds->userNames();
        /*for(int i = 0; i < users.size(); i++){
            QString temp = QString::fromStdString(users[i]);
            currentUsr->addItem(temp);
        }*/
    topRow->addWidget(amazon);
    topRow->addWidget(currentUsr);

    QHBoxLayout *searchRow = new QHBoxLayout();
    QLineEdit *searchTextBox = new QLineEdit();
    QPushButton *andSearch = new QPushButton("AND");
    QPushButton *orSearch = new QPushButton("OR");
    searchRow->addWidget(searchTextBox);
    searchRow->addWidget(andSearch);
    searchRow->addWidget(orSearch);

    QGridLayout *utilButtons = new QGridLayout();
    QComboBox *sortType = new QComboBox();
        sortType->addItem("Alphibetcial Sort");
        sortType->addItem("Rating Sort");
    QHBoxLayout *reviewAndCart = new QHBoxLayout();
        QPushButton *viewReviews = new QPushButton("View Reviews");
        QPushButton *addToCart = new QPushButton("Add Item to Cart");
        reviewAndCart->addWidget(viewReviews);
        reviewAndCart->addWidget(addToCart);
    QPushButton *viewCart = new QPushButton("View User Cart");
    utilButtons->addWidget(sortType);
    utilButtons->addLayout(reviewAndCart, 1, 0);
    utilButtons->addWidget(viewCart);

    QListWidget *searchResults = new QListWidget();

    QHBoxLayout *newDataFileSave = new QHBoxLayout();
    QLineEdit *dataFileName = new QLineEdit();
    QPushButton *saveButton = new QPushButton("Save New DataBase");
    newDataFileSave->addWidget(dataFileName);
    newDataFileSave->addWidget(saveButton);

    QPushButton *quitProgram = new QPushButton("CLOSE PROGRAM");

    mainGrid->addLayout(topRow, 0, 0, 1, -1, 0);
    mainGrid->addLayout(searchRow, 1, 0, 1, -1, 0);
    mainGrid->addWidget(searchResults, 2, 0);
    mainGrid->addLayout(utilButtons, 2, 1);
    mainGrid->addLayout(newDataFileSave, 3, 0, 1, -1, 0);
    mainGrid->addWidget(quitProgram, 4, 0, 2, -1, 0);

    centralWidget->setLayout(mainGrid);
    window->setCentralWidget(centralWidget);
	};

	void showWindow(){
		window->show();
	}

public slots:

    void setCurentUser() {
        cout << "test" << endl;
    }


};