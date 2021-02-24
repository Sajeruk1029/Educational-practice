#ifndef RANK_H
#define RANK_H

#include <QObject>

#include <QWidget>

#include <QBoxLayout>

#include <QLineEdit>
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

class Rank : public QWidget
{
	Q_OBJECT

	public:
		explicit Rank(QSettings*);
		~Rank();

	private slots:
		void clickButAddRank();
		void clickButChangeRank();
		void clickButDeleteRank();
		void clickButRefreshList();
		void clickButPrintToFile();

	private:
		QBoxLayout *layout;

		QLineEdit *linename;
		QLineEdit *linecompetenc;

		QPushButton *butaddrank;
		QPushButton *butchangerank;
		QPushButton *butdeleterank;
		QPushButton *butrefreshlist;
		QPushButton *butprinttofile;

		QTableWidget *table;

		QSqlDatabase *db;
		QSqlQuery *query;

		QSettings *settings;

		QFile *file;
};

#endif

