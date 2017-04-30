#include "loginWindow.h"
#include "hash.h"
#include "mainApp.h"
#include <QHBoxLayout>
#include <QGridLayout>
#include <QMessageBox>


using namespace std;

loginWindow::loginWindow(MyDataStore* ds) : ds_(ds){

    logIn = new QPushButton("Log In");
    newUser = new QPushButton("Make New User");
    quit = new QPushButton("Quit");
    userName = new QLineEdit();
    userName->setPlaceholderText("User Name");
    password = new QLineEdit();
    password->setPlaceholderText("Password");

    QGridLayout *grid = new QGridLayout;
    QHBoxLayout *topLine = new QHBoxLayout;
    QHBoxLayout *bottomLine = new QHBoxLayout;

    topLine->addWidget(userName);
    topLine->addWidget(password);

    bottomLine->addWidget(logIn);
    bottomLine->addWidget(newUser);
    bottomLine->addWidget(quit);

    grid->addLayout(topLine, 0, 0);
    grid->addLayout(bottomLine, 1, 0);

    setLayout(grid);


    QObject::connect(logIn, SIGNAL(clicked()), this, SLOT(loginExistingUser()));
    QObject::connect(newUser, SIGNAL(clicked()), this, SLOT(makeNewUser()));
    QObject::connect(quit, SIGNAL(clicked()), this, SLOT(quitClicked()));
    
}

loginWindow::~loginWindow(){

}

void loginWindow::loginExistingUser(){
    string name = (userName->text()).toStdString();
    string passwordRaw = (password->text()).toStdString();

    if(!ds_->userExist(name)){
        QMessageBox noUser(this);
        noUser.setText("No User by this name.");
        noUser.exec();
    }
    if(passwordRaw == "  "){
        mainAPP* test = new mainAPP(ds_, ds_->nameToUser(name), 0);
        test->show();
    }else if(ds_->checkPassword(name, passwordRaw)){
        User* currUser = ds_->nameToUser(name);
        mainAPP* test = new mainAPP(ds_, currUser, 0);
        test->show();
    }else{
        QMessageBox noUser(this);
        noUser.setText("Wrong Password. Try again.");
        noUser.exec();
    }
}

void loginWindow::makeNewUser(){
    string name = (userName->text()).toStdString();
    string passwordRaw = (password->text()).toStdString();

    if(ds_->userExist(name)){
        QMessageBox noUser(this);
        noUser.setText("That username is alreay taken.");
        noUser.exec();
    }
    else if(passwordRaw.length() > 8){
        QMessageBox noUser(this);
        noUser.setText("Password is too long.");
        noUser.exec();
    }else{
    User* temp = new User(name, 100, 1, hasher(passwordRaw));
    ds_->addUser(temp);
    mainAPP* test = new mainAPP(ds_, temp, 0);
        test->show();
        }

}

void loginWindow::quitClicked(){
	close();
}
