#ifndef loginWindow_H
#define loginWindow_H

#include <QApplication>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLineEdit>
#include "mydatastore.h"

class loginWindow : public QWidget {
	Q_OBJECT

public:
	loginWindow(MyDataStore ds);

private slots:
	

private:
	
}
