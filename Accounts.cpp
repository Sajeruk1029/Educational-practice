#include "Accounts.h"

Accounts::Accounts(QSettings *conf) : layout(new (std::nothrow) QBoxLayout(QBoxLayout::Down)), linelogin(new (std::nothrow) QLineEdit()),
linepassword(new (std::nothrow) QLineEdit()), lineconfirmpassword(new (std::nothrow) QLineEdit()),
comboboxtype(new (std::nothrow) QComboBox()), butchangepassword(new (std::nothrow) QPushButton("Изменить пароль")),
butdeleteaccount(new (std::nothrow) QPushButton("Удалить аккаунт")), butaddaccount(new (std::nothrow) QPushButton("Добавить аккаунт")),
butrefreshlist(new (std::nothrow) QPushButton("Обновить список")), table(new (std::nothrow) QTableWidget(0, 4)),
db(new (std::nothrow) QSqlDatabase()), query(nullptr),
settings(conf)
{
	if(!layout)
	{
		qDebug() << "Недостаточно памяти для создания лейаута!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!linelogin)
	{
		qDebug() << "Недостаточно памяти для создания поля логина!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!linepassword)
	{
		qDebug() << "Недостаточно памяти для создания поля пароля!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!lineconfirmpassword)
	{
		qDebug() << "Недостаточно памяти для создания поля подтверждения пароля!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!comboboxtype)
	{
		qDebug() << "Недостаточно памяти для создания выпадающего списка типов!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!butchangepassword)
	{
		qDebug() << "Недостаточно памяти для создания кнопки изменения пароля!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!butdeleteaccount)
	{
		qDebug() << "Недостаточно памяти для создания кнопки удаления аккаунта!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!butaddaccount)
	{
		qDebug() << "Недостаточно памяти для создания кнопки добавления аккаунта!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!butrefreshlist)
	{
		qDebug() << "Недостаточно памяти для создания кнопки обновления списка!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!table)
	{
		qDebug() << "Недостаточно памяти для создания таблицы!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!db)
	{
		qDebug() << "Недостаточно памяти для создания объекта!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	setLayout(layout);
	setFixedSize(680, 680);

	linelogin->setPlaceholderText("Логин");
	linepassword->setPlaceholderText("Пароль");
	lineconfirmpassword->setPlaceholderText("Подтверждение пароля/Новый пароль");

	linepassword->setEchoMode(QLineEdit::EchoMode::Password);
	lineconfirmpassword->setEchoMode(QLineEdit::EchoMode::Password);

	comboboxtype->addItem("Администратор");
	comboboxtype->addItem("Офицер");

	comboboxtype->setCurrentIndex(0);

	butchangepassword->setMaximumSize(200, 50);
	butdeleteaccount->setMaximumSize(200, 50);
	butaddaccount->setMaximumSize(200, 50);
	butrefreshlist->setMaximumSize(200, 50);

	table->setHorizontalHeaderLabels({"Номер аккаунта", "Логин", "Пароль", "Тип"});
	table->setEditTriggers(0);

	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	table->setSelectionMode(QAbstractItemView::SingleSelection);

	layout->addWidget(linelogin);
	layout->addWidget(linepassword);
	layout->addWidget(lineconfirmpassword);
	layout->addWidget(comboboxtype);
	layout->addWidget(butchangepassword);
	layout->addWidget(butdeleteaccount);
	layout->addWidget(butaddaccount);
	layout->addWidget(butrefreshlist);
	layout->addWidget(table);

	QObject::connect(butchangepassword, SIGNAL(clicked()), this, SLOT(clickButChangePassword()));
	QObject::connect(butdeleteaccount, SIGNAL(clicked()), this, SLOT(clickButDeleteAccount()));
	QObject::connect(butaddaccount, SIGNAL(clicked()), this, SLOT(clickButAddAccount()));
	QObject::connect(butrefreshlist, SIGNAL(clicked()), this, SLOT(clickButRefreshList()));

	*db = QSqlDatabase::addDatabase("QMYSQL", "conn2");

	settings->beginGroup("BD");

	db->setHostName(settings->value("HOST").toString());
	db->setUserName(settings->value("USER").toString());
	db->setPassword(settings->value("PASSWORD").toString());
	db->setDatabaseName("education_practice");

	settings->endGroup();

	if(!db->open())
	{
		qDebug() << "Ошибка открытия соединения с базой данных!\n";
		qDebug() << "Error code: " << db->lastError().nativeErrorCode() << " Error: " << db->lastError().text();

		linelogin->setEnabled(false);
		linepassword->setEnabled(false);
		lineconfirmpassword->setEnabled(false);
		comboboxtype->setEnabled(false);
		butchangepassword->setEnabled(false);
		butdeleteaccount->setEnabled(false);
		butaddaccount->setEnabled(false);
		butrefreshlist->setEnabled(false);
		table->setEnabled(false);

		QMessageBox::warning(this, "Ошибка", "Ошибка открытия соединения с базой данных!");

		return;
	}

	query = new (std::nothrow) QSqlQuery(*db);

	if(!query)
	{
		qDebug() << "Недостаточно памяти для создания запроса к базе данных!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		linelogin->setEnabled(false);
		linepassword->setEnabled(false);
		lineconfirmpassword->setEnabled(false);
		comboboxtype->setEnabled(false);
		butchangepassword->setEnabled(false);
		butdeleteaccount->setEnabled(false);
		butaddaccount->setEnabled(false);
		butrefreshlist->setEnabled(false);
		table->setEnabled(false);

		QMessageBox::warning(this, "Ошибка", "Ошибка не удалось создать объект запроса к базе данных!");

		return;
	}

}

Accounts::~Accounts()
{
	if(query){ delete query; }
	if(db)
	{
		db->close();

		QSqlDatabase::removeDatabase("conn2");

		delete db;
	}

	delete linelogin;
	delete linepassword;
	delete lineconfirmpassword;

	delete comboboxtype;

	delete butchangepassword;
	delete butdeleteaccount;
	delete butaddaccount;
	delete butrefreshlist;

	delete table;

	delete layout;
}

void Accounts::clickButChangePassword()
{
	if(linelogin->text() == "")
	{
		QMessageBox::warning(this, "Ошибка", "Поле логина не должно быть пустым!");

		return;
	}

	if(linepassword->text() == "")
	{
		QMessageBox::warning(this, "Ошибка", "Поле пароля не должно быть пустым!");

		return;
	}

	if(lineconfirmpassword->text() == "")
	{
		QMessageBox::warning(this, "Ошибка", "Поле нового пароля не должно быть пустым!");

		return;
	}

	query->prepare(QString("update User set Password = :NewPassword where Login = :Login and Password = :Password"));

	query->bindValue(":NewPassword", lineconfirmpassword->text());
	query->bindValue(":Login", linelogin->text());
	query->bindValue(":Password", linepassword->text());

	query->exec();

	if(query->lastError().type() != QSqlError::NoError)
	{
		qDebug() << "Не удалось обновить данные в таблице пользователей!\n";
		qDebug() << "Error code: " << query->lastError().nativeErrorCode() << " Error: " << query->lastError().text();

		QMessageBox::warning(this, "Ошибка", "Пароль не был обновлен!");
	}
	//else
	//{
		//QMessageBox::warning(this, "Успех", "Пароль был успешно обновлен!");
	//}
}

void Accounts::clickButDeleteAccount()
{
	if(linelogin->text() == "")
	{
		QMessageBox::warning(this, "Ошибка", "Поле логина не должно быть пустым!");

		return;
	}

	if(linepassword->text() == "")
	{
		QMessageBox::warning(this, "Ошибка", "Поле пароля не должно быть пустым!");

		return;
	}

	query->prepare(QString("delete from User where Password = :NewPassword and Login = :Login and Password = :Password"));

	query->bindValue(":NewPassword", lineconfirmpassword->text());
	query->bindValue(":Login", linelogin->text());
	query->bindValue(":Password", linepassword->text());

	query->exec();

	if(query->lastError().type() != QSqlError::NoError)
	{
		qDebug() << "Не удалось удалить данные в таблице пользователей!\n";
		qDebug() << "Error code: " << query->lastError().nativeErrorCode() << " Error: " << query->lastError().text();

		QMessageBox::warning(this, "Ошибка", "Учетная запись не была добавлена!");
	}
}

void Accounts::clickButAddAccount()
{
	if(linepassword->text() != lineconfirmpassword->text())
	{
		QMessageBox::warning(this, "Ошибка", "Пароли не совпадают!");

		return;
	}

	if(linelogin->text() == "")
	{
		QMessageBox::warning(this, "Ошибка", "Поле логина не должно быть пустым!");

		return;
	}

	if(linepassword->text() == "")
	{
		QMessageBox::warning(this, "Ошибка", "Поле пароля не должно быть пустым!");

		return;
	}

	query->prepare(QString("insert into User values(null, :Login, :Password, :Type)"));

	query->bindValue(":Login", linelogin->text());
	query->bindValue(":Password", linepassword->text());
	query->bindValue(":Type", comboboxtype->currentText());


	query->exec();

	if(query->lastError().type() != QSqlError::NoError)
	{
		qDebug() << "Не удалось добавить данные в таблице пользователей!\n";
		qDebug() << "Error code: " << query->lastError().nativeErrorCode() << " Error: " << query->lastError().text();

		QMessageBox::warning(this, "Ошибка", "Учетная запись не была добавлена!");
	}
}

void Accounts::clickButRefreshList()
{
	int counter_data = 0;

	table->clear();

	table->setHorizontalHeaderLabels({"Номер аккаунта", "Логин", "Пароль", "Тип"});
	table->setRowCount(0);

	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	table->setSelectionMode(QAbstractItemView::SingleSelection);

	table->setEditTriggers(0);

	query->exec(QString("select * from User"));

	while(query->next())
	{
		table->setRowCount(table->rowCount() + 1);

		for(int counter = 0; counter < 4; ++counter)
		{
			table->setItem(counter_data, counter, new QTableWidgetItem(query->value(counter).toString()));
		}

		++counter_data;
	}
}
