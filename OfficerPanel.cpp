#include "OfficerPanel.h"

OfficerPanel::OfficerPanel(QSettings *conf) : layout(new (std::nothrow) QBoxLayout(QBoxLayout::Down)), tab(new (std::nothrow) QTabWidget()),
settings(conf), db(new (std::nothrow) QSqlDatabase()),
units(nullptr), companies(nullptr),
rank(nullptr), citizen(nullptr),
devices(nullptr), task(nullptr)
{
	if(!layout)
	{
		qDebug() << "Недостаточно памяти для создания лейаута!\n";
		qDebug() << "Error code: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!tab)
	{
		qDebug() << "Недостаточно памяти для создания таб виджета!\n";
		qDebug() << "Error code: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!db)
	{
		qDebug() << "Недостаточно памяти для создания объекта базы данных!\n";
		qDebug() << "Error code: " << errno << " Message: " << strerror(errno);

		return;
	}

	units = new (std::nothrow) Units(settings);

	if(!units)
	{
		qDebug() << "Недостаточно памяти для создания вкладки частей!\n";
		qDebug() << "Error code: " << errno << " Message: " << strerror(errno);

		return;
	}

	companies = new (std::nothrow) Companies(settings);

	if(!companies)
	{
		qDebug() << "Недостаточно памяти для создания вкладки рот!\n";
		qDebug() << "Error code: " << errno << " Message: " << strerror(errno);

		return;
	}

	rank = new (std::nothrow) Rank(settings);

	if(!rank)
	{
		qDebug() << "Недостаточно памяти для создания вкладки званий!\n";
		qDebug() << "Error code: " << errno << " Message: " << strerror(errno);

		return;
	}

	citizen = new (std::nothrow) Citizen(settings);

	if(!citizen)
	{
		qDebug() << "Недостаточно памяти для создания вкладки званий!\n";
		qDebug() << "Error code: " << errno << " Message: " << strerror(errno);

		return;
	}

	devices = new (std::nothrow) Devices(settings);

	if(!citizen)
	{
		qDebug() << "Недостаточно памяти для создания вкладки оборудование!\n";
		qDebug() << "Error code: " << errno << " Message: " << strerror(errno);

		return;
	}

	task = new (std::nothrow) Task(settings);

	if(!task)
	{
		qDebug() << "Недостаточно памяти для создания вкладки задачи!\n";
		qDebug() << "Error code: " << errno << " Message: " << strerror(errno);

		return;
	}

	tab->addTab(units, "Части");
	tab->addTab(companies, "Роты");
	tab->addTab(rank, "Звания");
	tab->addTab(citizen, "Граждане");
	tab->addTab(devices, "Оборудование");
	tab->addTab(task, "Задачи");

	setWindowTitle("Панель офицера");
	setLayout(layout);
	setFixedSize(700, 700);

	layout->addWidget(tab);
}

OfficerPanel::~OfficerPanel()
{
	if(db){ delete db; }

	delete tab;

	delete tab;
}
