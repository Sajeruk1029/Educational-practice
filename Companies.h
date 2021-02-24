#ifndef COMPANIES_H
#define COMPANIES_H

#include <QObject>

#include <QWidget>

#include <QBoxLayout>

#include <QLineEdit>
#include <QComboBox>
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

class Companies : public QWidget
{
	Q_OBJECT

	public:
		explicit Companies(QSettings*);
		~Companies();

	private slots:
		void clickButAddCompany();
		void clickButChangeCompany();
		void clickButDeleteCompany();
		void clickButRefreshList();
		void clickButPrintToFile();

	private:
		QBoxLayout *layout;

		QLineEdit *linenumber;

		QComboBox *comboboxcommander;
		QComboBox *comboboxunit;

		QPushButton *butaddcompany;
		QPushButton *butchangecompany;
		QPushButton *butdeletecompany;
		QPushButton *butrefreshlist;
		QPushButton *butprinttofile;

		QTableWidget *table;

		QSqlDatabase *db;
		QSqlQuery *query;

		QSettings *settings;

		QFile *file;
};

#endif

