#ifndef ADMINPANEL_H
#define ADMINPANEL_H

#include <QObject>

#include <QWidget>

#include <QBoxLayout>

#include <QTabWidget>

#include <QtSql/QSqlDatabase>

#include <QSettings>

#include <QDebug>

#include <cstring>

#include <new>

#include "Connection.h"
#include "Accounts.h"

class AdminPanel : public QWidget
{
	public:
		explicit AdminPanel(QSettings*, bool);
		~AdminPanel();

	private:
		QBoxLayout *layout;

		QTabWidget *tab;

		QSettings *settings;

		Connection *connection;
		Accounts *accounts;
};

#endif
