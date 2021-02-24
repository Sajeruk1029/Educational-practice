#include "Connection.h"

Connection::Connection(QSettings *conf) : layout(new (std::nothrow) QBoxLayout(QBoxLayout::Down)), linehost(new (std::nothrow) QLineEdit()),
lineuser(new (std::nothrow) QLineEdit()), linepassword(new (std::nothrow) QLineEdit()),
butcheck(new (std::nothrow) QPushButton("Проверка")), butsave(new (std::nothrow) QPushButton("Сохранение")),
db(nullptr), settings(conf)
{
	if(!layout)
	{
		qDebug() << "Недостаточно памяти для создания лейяута!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!linehost)
	{
		qDebug() << "Недостаточно памяти для создания поля ввода хоста!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!lineuser)
	{
		qDebug() << "Недостаточно памяти для создания поля ввода пользователя!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!linepassword)
	{
		qDebug() << "Недостаточно памяти для создания поля ввода пароля!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!butcheck)
	{
		qDebug() << "Недостаточно памяти для создания кнопки проверки!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!butsave)
	{
		qDebug() << "Недостаточно памяти для создания кнопки сохранения!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	setLayout(layout);
	setFixedSize(680, 200);

	linehost->setPlaceholderText("Хост");
	lineuser->setPlaceholderText("Логин");
	linepassword->setPlaceholderText("Пароль");

	linepassword->setEchoMode(QLineEdit::EchoMode::Password);

	butcheck->setMaximumSize(100, 50);
	butsave->setMaximumSize(100, 50);
	butsave->setEnabled(false);

	layout->addWidget(linehost);
	layout->addWidget(lineuser);
	layout->addWidget(linepassword);
	layout->addWidget(butcheck);
	layout->addWidget(butsave);

	QObject::connect(butcheck, SIGNAL(clicked()), this, SLOT(clickButCheck()));
	QObject::connect(butsave, SIGNAL(clicked()), this, SLOT(clickButSave()));
}

Connection::~Connection()
{
	if(db){ delete db; }
	if(settings){ delete settings; }

	delete linehost;
	delete lineuser;
	delete linepassword;

	delete butcheck;
	delete butsave;

	delete layout;
}

void Connection::clickButCheck()
{
	db = new (std::nothrow) QSqlDatabase();

	if(!db)
	{
		qDebug() << "Недостаточно памяти для создания объекта базы данных!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	*db = QSqlDatabase::addDatabase("QMYSQL", "conn");

	db->setHostName(linehost->text());
	db->setUserName(lineuser->text());
	db->setPassword(linepassword->text());

	if(!db->open())
	{
		qDebug() << "Ошибка подключения к базе данных!\n";
		qDebug() << "Error code: " << db->lastError().nativeErrorCode() << " Error: " << db->lastError().text();

		QMessageBox::warning(this, "Ошибка", "Ошибка подключения к базе данных! Данные подключения неверны!");

		butsave->setEnabled(false);
	}
	else
	{
		QMessageBox::warning(this, "Успех", "Данные подключения верны!");

		butsave->setEnabled(true);

		db->close();
	}

	QSqlDatabase::removeDatabase("conn");

	delete db;
	db = nullptr;
}

void Connection::clickButSave()
{
	settings->beginGroup("BD");

	settings->setValue("HOST", linehost->text());
	settings->setValue("USER", lineuser->text());
	settings->setValue("PASSWORD", linepassword->text());

	settings->endGroup();
}
