#ifndef ACCOUNTS_H
#define ACCOUNTS_H

#include <QObject>

#include <QWidget>

#include <QBoxLayout>

#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QTableWidget>

#include <QMessageBox>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

#include <QSettings>

#include <QDebug>

#include <QTableWidgetItem>

#include <new>

#include <cstring>

class Accounts : public QWidget
{
	Q_OBJECT

	public:
		explicit Accounts(QSettings*);
		~Accounts();

	private slots:
		void clickButChangePassword();
		void clickButDeleteAccount();
		void clickButAddAccount();
		void clickButRefreshList();

	private:
		QBoxLayout *layout;

		QLineEdit *linelogin;
		QLineEdit *linepassword;
		QLineEdit *lineconfirmpassword;

		QComboBox *comboboxtype;

		QPushButton *butchangepassword;
		QPushButton *butdeleteaccount;
		QPushButton *butaddaccount;
		QPushButton *butrefreshlist;

		QTableWidget *table;

		QSqlDatabase *db;
		QSqlQuery *query;

		QSettings *settings;
};

#endif
