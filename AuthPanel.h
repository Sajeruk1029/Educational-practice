#ifndef AUTHPANEL_H
#define AUTHPANEL_H

#include <QObject>

#include <QWidget>

#include <QBoxLayout>

#include <QLineEdit>
#include <QPushButton>

#include <QMessageBox>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

#include <QSettings>

#include <QFile>

#include <QDebug>

#include <new>

#include <cstring>

#include <cerrno>

#include "AdminPanel.h"
#include "OfficerPanel.h"

class AuthPanel : public QWidget
{

	Q_OBJECT

	public:
		explicit AuthPanel();
		~AuthPanel();

	private slots:
		void butClickLogin();

	private:
    QBoxLayout *layout;

		QLineEdit *linelogin;
		QLineEdit *linepassword;

		QPushButton *butlogin;

		QSqlDatabase *db;
		QSqlQuery *query;

		QSettings *settings;

		AdminPanel *adminpanel;
		OfficerPanel *officerpanel;

};

#endif
