#ifndef loginWindow_H
#define loginWindow_H

#include <QPushButton>
#include <QLineEdit>
#include <QWidget>
#include <QObject>

#include "mydatastore.h"
#include "user.h"

using namespace std;

class loginWindow : public QWidget {
	Q_OBJECT

public:
	loginWindow(MyDataStore ds);
	~loginWindow();

private slots:
	void loginExistingUser();
	void makeNewUser();
	void quitClicked();
	

private:
	MyDataStore ds_;
	QPushButton *logIn;
    QPushButton *newUser;
    QPushButton *quit;
    QLineEdit *userName;
    QLineEdit *password;
};

#endif