#ifndef CITIZEN_H
#define CITIZEN_H

#include <QObject>

#include <QWidget>

#include <QBoxLayout>

#include <QLineEdit>
#include <QComboBox>
#include <QCalendarWidget>
#include <QPushButton>
#include <QTableWidget>

#include <QMessageBox>
#include <QFileDialog>

#include <QTableWidgetItem>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

#include <QSettings>

#include <QDebug>

#include <QFile>

#include <new>

#include <cerrno>

#include <cstring>

class Citizen : public QWidget
{
	Q_OBJECT

	public:
		explicit Citizen(QSettings*);
		~Citizen();

	private slots:
		void clickButAddCitizen();
		void clickButChangeCitizen();
		void clickButDeleteCitizen();
		void clickButRefreshList();
		void clickButPrintToFile();

	private:
		QBoxLayout *layout;

		QLineEdit *linename;
		QLineEdit *linelastname;
		QLineEdit *linepatronymic;

		QCalendarWidget *calendar;

		QComboBox *comboboxrank;

		QPushButton *butaddcitizen;
		QPushButton *butchangecitizen;
		QPushButton *butdeletecitizen;
		QPushButton *butrefreshlist;
		QPushButton *butprinttofile;

		QTableWidget *table;

		QSqlDatabase *db;
		QSqlQuery *query;

		QSettings *settings;

		QFile *file;
};

#endif
