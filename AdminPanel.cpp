#include "AdminPanel.h"

AdminPanel::AdminPanel(QSettings *conf, bool success) : layout(new (std::nothrow) QBoxLayout(QBoxLayout::Down)), tab(new (std::nothrow) QTabWidget()),
settings(conf), connection(new (std::nothrow) Connection(conf)),
accounts((success)? new (std::nothrow) Accounts(settings) : nullptr)
{
	if(!layout)
	{
		qDebug() << "Недостаточно памяти для создания лейяута!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!tab)
	{
		qDebug() << "Недостаточно памяти для создания таб виджета!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!connection)
	{
		qDebug() << "Недостаточно памяти для создания вкладки подключение!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	setWindowTitle("Панель администратора");
	setFixedSize(700, 700);
	setLayout(layout);

	tab->addTab(connection, "Подключение");

	if(success)
	{
		tab->addTab(accounts, "Аккаунты");
	}

	layout->addWidget(tab);
}

AdminPanel::~AdminPanel()
{
	if(connection){ delete connection; }

	delete tab;

	delete layout;
}


