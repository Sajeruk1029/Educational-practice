#ifndef UNITS_H
#define UNITS_H

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

class Units : public QWidget
{
	Q_OBJECT

	public:
		explicit Units(QSettings*);
		~Units();

	private slots:
		void clickButAddUnit();
		void clickButChangeUnit();
		void clickButDeleteUnit();
		void clickButRefreshList();
		void clickButPrintToFile();

	private:
		QBoxLayout *layout;

		QLineEdit *linelocation;

		QComboBox *comboboxcommander;

		QPushButton *butaddunit;
		QPushButton *butchangeunit;
		QPushButton *butdeleteunit;
		QPushButton *butrefreshlist;
		QPushButton *butprinttofile;

		QTableWidget *table;

		QSqlDatabase *db;
		QSqlQuery *query;

		QSettings *settings;

		QFile *file;
};

#endif

