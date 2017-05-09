#include "mainApp.h"
#include "hash.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
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
    connect(showRec, SIGNAL(clicked()), this, SLOT(showRecomendations()));

    
}

mainAPP::~mainAPP(){

}

void mainAPP::showRecomendations(){
   vector<pair<string, double> > recs = ds_->makeSuggestion(currentUser->getName());
   ofstream ofile("rec.txt");
   ofile << currentUser->getName() << "\n";
   for(auto temp : recs){
   std::ostringstream strs;
strs << temp.first;
std::string str = strs.str();
      ofile << str << " " << temp.first << "\n";
      string dontLook = str + " " + temp.first + "\n";
      QString qstr = QString::fromStdString(dontLook);
      recomndations->addItem(qstr);
   }
   ofile.close();
   
   
}

void mainAPP::quitClicked(){
	close();
}
