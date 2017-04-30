#include "mainApp.h"
#include "hash.h"
#include <QHBoxLayout>
#include <QGridLayout>
#include <QMessageBox>
#include <QWidget>


using namespace std;

mainAPP::mainAPP(MyDataStore* ds, User* curr, bool backdoor) : ds_(ds),
currentUser(curr), backdoor_(backdoor)
{
    showRec = new QPushButton("Show Recomndations");
    quit = new QPushButton("quit");

    recomndations = new QListWidget;
    QGridLayout *grid = new QGridLayout;
    QHBoxLayout *topLine = new QHBoxLayout;
    QHBoxLayout *bottomLine = new QHBoxLayout;

    topLine->addWidget(showRec);
    topLine->addWidget(quit);
    bottomLine->addWidget(recomndations);

    grid->addLayout(topLine, 0, 0);
    grid->addLayout(bottomLine, 1, 0);

    setLayout(grid);
    std::string str = currentUser->getName();
	QString qstr = QString::fromStdString(str);
    setWindowTitle(qstr);

    connect(quit, SIGNAL(clicked()), this, SLOT(quitClicked()));

    
}

mainAPP::~mainAPP(){

}

void mainAPP::showRecomendations(){
    
}

void mainAPP::quitClicked(){
	close();
}
