#ifndef DEVICES_H
#define DEVICES_H

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

class Devices : public QWidget
{
	Q_OBJECT

	public:
		explicit Devices(QSettings*);
		~Devices();

	private slots:
		void clickButAddDevices();
		void clickButChangeDevices();
		void clickButDeleteDevices();
		void clickButRefreshList();
		void clickButPrintToFile();

	private:
		QBoxLayout *layout;

		QLineEdit *linename;
		QLineEdit *linetarget;
		QLineEdit *linenumber;

		QComboBox *comboboxhave;
		QComboBox *comboboxcompany;

		QPushButton *butadddevices;
		QPushButton *butchangedevices;
		QPushButton *butdeletedevices;
		QPushButton *butrefreshlist;
		QPushButton *butprinttofile;

		QTableWidget *table;

		QSqlDatabase *db;
		QSqlQuery *query;

		QSettings *settings;

		QFile *file;
};

#endif
