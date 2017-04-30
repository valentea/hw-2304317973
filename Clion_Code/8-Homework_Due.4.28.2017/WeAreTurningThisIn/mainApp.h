#ifndef mainAPP_H
#define mainAPP_H

#include <QPushButton>
#include <QLineEdit>
#include <QWidget>
#include <QObject>
#include <QListWidget>

#include "mydatastore.h"
#include "user.h"

using namespace std;

class mainAPP : public QWidget {
	Q_OBJECT

public:
	mainAPP(MyDataStore* ds, User* curr, bool backdoor);
	~mainAPP();

private slots:
	void showRecomendations();
	void quitClicked();
	

private:
	MyDataStore* ds_;
	User* currentUser;
	bool backdoor_;
    QPushButton *showRec;
    QListWidget *recomndations;
    QPushButton *quit;
};

#endif
