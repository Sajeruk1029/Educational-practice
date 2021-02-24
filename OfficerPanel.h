#ifndef OFFICERPANEL_H
#define OFFICERPANEL_H

#include <QObject>

#include <QWidget>

#include <QBoxLayout>

#include <QTabWidget>

#include <QtSql/QSqlDatabase>

#include <QSettings>

#include <QDebug>

#include <new>

#include <cstring>

#include "Units.h"
#include "Companies.h"
#include "Rank.h"
#include "Citizen.h"
#include "Devices.h"
#include "Task.h"

class OfficerPanel : public QWidget
{

	public:
		explicit OfficerPanel(QSettings*);
		~OfficerPanel();

	private:
		QBoxLayout *layout;

		QTabWidget *tab;

		QSettings *settings;

		QSqlDatabase *db;

		Units *units;
		Companies *companies;
		Rank *rank;
		Citizen *citizen;
		Devices *devices;
		Task *task;
};

#endif
