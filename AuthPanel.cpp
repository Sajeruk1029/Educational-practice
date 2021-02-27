#include "AuthPanel.h"

AuthPanel::AuthPanel(QString path) : layout(new (std::nothrow) QBoxLayout(QBoxLayout::Down)), linelogin(new (std::nothrow) QLineEdit()),
linepassword(new (std::nothrow) QLineEdit()), butlogin(new (std::nothrow) QPushButton("Войти")),
db(new (std::nothrow) QSqlDatabase()), query(nullptr),
settings(nullptr), adminpanel(nullptr), officerpanel(nullptr)
{
	if(!QFile(path + "config.ini").exists())
	{
		settings = new (std::nothrow) QSettings(path + "config.ini", QSettings::IniFormat);

		if(!settings)
		{
			qDebug() << "Недостаточно памяти для создания объекта настроек!\n";
			qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

			return;
		}

		settings->beginGroup("BD");

		settings->setValue("HOST", "");
		settings->setValue("USER", "");
		settings->setValue("PASSWORD", "");

		settings->endGroup();

		settings->sync();

		adminpanel = new (std::nothrow) AdminPanel(settings, false);

		if(!adminpanel)
		{
			qDebug() << "Недостаточно памяти для создания окна администрации!\n";
			qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

			return;
		}

		adminpanel->show();
	}
	else
	{
		settings = new (std::nothrow) QSettings(path + "config.ini", QSettings::IniFormat);

  	if(!layout)
  	{
    	qDebug() << "Недостаточно памяти для создания лейяута!\n";
			qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

    	return;
  	}

		if(!linelogin)
  	{
    	qDebug() << "Недостаточно памяти для создания поля для логина!\n";
			qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

    	return;
  	}

		if(!linepassword)
  	{
    	qDebug() << "Недостаточно памяти для создания поля для пароля!\n";
			qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

    	return;
  	}

  	if(!butlogin)
  	{
    	qDebug() << "Недостаточно памяти для создания кнопки для пароля!\n";
			qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

    	return;
  	}

		if(!db)
		{
			qDebug() << "Недостаточно памяти для создания объекта базы данных!\n";
			qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

			return;
		}

		if(!settings)
		{
			qDebug() << "Недостаточно памяти для создания объекта настроек!\n";
			qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

			return;
		}

  	setWindowTitle("Панель входа");
  	setFixedSize(300, 100);
  	setLayout(layout);

  	linelogin->setPlaceholderText("Логин");

  	linepassword->setPlaceholderText("Пароль");
  	linepassword->setEchoMode(QLineEdit::EchoMode::Password);

  	layout->addWidget(linelogin);
  	layout->addWidget(linepassword);
  	layout->addWidget(butlogin);

		settings->beginGroup("BD");

  	*db = QSqlDatabase::addDatabase("QMYSQL", "conn");

		//qDebug() << settings->value("HOST").toString();
		//qDebug() << settings->value("USER").toString();
		//qDebug() << settings->value("PASSWORD").toString();

  	db->setHostName(settings->value("HOST").toString());
  	db->setUserName(settings->value("USER").toString());
  	db->setPassword(settings->value("PASSWORD").toString());
  	db->setDatabaseName("education_practice");

		settings->endGroup();

		this->show();

  	if(!db->open())
  	{
    	qDebug() << "Ошибка открытия соединения с базой данных!";
			qDebug() << "Error code: " << db->lastError().nativeErrorCode() << " Error: " << db->lastError().text();

    	delete db;
			db = nullptr;

			linelogin->setEnabled(false);
			linepassword->setEnabled(false);
			butlogin->setEnabled(false);

			QMessageBox::warning(this, "Ошибка", "Ошибка открытия соединения с базой данных!");
  	}

		//delete settings;
		//settings = nullptr;

  	QObject::connect(butlogin, SIGNAL(clicked()), this, SLOT(butClickLogin()));
	}
}

AuthPanel::~AuthPanel()
{
  if(query){ delete query; }

	if(db)
	{
		db->close();

		QSqlDatabase::removeDatabase("conn");

		delete db;

		db = nullptr;
	}

  if(linelogin){ delete linelogin; }
  if(linepassword){ delete linepassword; }
  if(butlogin){ delete butlogin; }

  if(layout){ delete layout; }
}

void AuthPanel::butClickLogin()
{
	query = new (std::nothrow) QSqlQuery(*db);

	if(!query)
	{
		qDebug() << "Недостаточно памяти для создания объекта запроса!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		query = nullptr;

		return;
	}

	query->prepare(QString("select Type from User where Login = :Login and Password = :Password"));

	query->bindValue(":Login", linelogin->text());
	query->bindValue(":Password", linepassword->text());

	query->exec();

	if(query->next())
	{
		QMessageBox::warning(this, "Успех!", "Вход успешно выполнен!");

		if(query->value(0).toString() == "Администратор")
		{
			adminpanel = new (std::nothrow) AdminPanel(settings, true);

			if(!adminpanel)
			{
				qDebug() << "Недостаточно памяти для создания окна администрации!\n";
				qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

				return;
			}

			adminpanel->show();
			this->close();
		}
		else
		{
			officerpanel = new (std::nothrow) OfficerPanel(settings);

			if(!officerpanel)
			{
				qDebug() << "Недостаточно памяти для создания окна офицера!\n";
				qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

				return;
			}

			officerpanel->show();
			this->close();
		}
	}
	else
	{
		QMessageBox::warning(this, "Ошибка!", "Вход не выполнен! Неверный логин или пароль!");

		delete query;
		query = nullptr;
	}
}
