#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>

#include <QWidget>

#include <QBoxLayout>

#include <QLineEdit>
#include <QPushButton>

#include <QMessageBox>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>

#include <QSettings>

#include <QDebug>

#include <cstring>

#include <new>

class Connection : public QWidget
{
	Q_OBJECT

	public:
		explicit Connection(QSettings*);
		~Connection();

	private slots:
		void clickButCheck();
		void clickButSave();

	private:
		QBoxLayout *layout;

		QLineEdit *linehost;
		QLineEdit *lineuser;
		QLineEdit *linepassword;

		QPushButton *butcheck;
		QPushButton *butsave;

		QSqlDatabase *db;

		QSettings *settings;
};

#endif
