#ifndef TASK_H
#define TASK_H

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

class Task : public QWidget
{
	Q_OBJECT

	public:
		explicit Task(QSettings*);
		~Task();

	private slots:
		void clickButAddTask();
		void clickButChangeTask();
		void clickButDeleteTask();
		void clickButRefreshList();
		void clickButPrintToFile();

	private:
		QBoxLayout *layout;

		QLineEdit *linename;
		QLineEdit *linedescription;

		QComboBox *comboboxcitizen;

		QPushButton *butaddtask;
		QPushButton *butchangetask;
		QPushButton *butdeletetask;
		QPushButton *butrefreshlist;
		QPushButton *butprinttofile;

		QTableWidget *table;

		QSqlDatabase *db;
		QSqlQuery *query;

		QSettings *settings;

		QFile *file;
};

#endif
