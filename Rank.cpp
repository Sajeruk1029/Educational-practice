#include "Rank.h"

Rank::Rank(QSettings *conf) : layout(new (std::nothrow) QBoxLayout(QBoxLayout::Down)), linename(new (std::nothrow) QLineEdit()),
linecompetenc(new (std::nothrow) QLineEdit()), butaddrank(new (std::nothrow) QPushButton("Добавить")),
butchangerank(new (std::nothrow) QPushButton("Изменить")), butdeleterank(new (std::nothrow) QPushButton("Удалить")),
butrefreshlist(new (std::nothrow) QPushButton("Обновить список")), butprinttofile(new (std::nothrow) QPushButton("Генерировать отчет")),
table(new (std::nothrow) QTableWidget(0, 3)), db(new (std::nothrow) QSqlDatabase()),
query(nullptr), settings(conf),
file(nullptr)
{
	if(!layout)
	{
		qDebug() << "Недостаточно памяти для создания лейаута!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!linename)
	{
		qDebug() << "Недостаточно памяти для создания поля ввода наименования!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!linecompetenc)
	{
		qDebug() << "Недостаточно памяти для поля ввода компетенций!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!butaddrank)
	{
		qDebug() << "Недостаточно памяти для создания кнопки добавления!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!butchangerank)
	{
		qDebug() << "Недостаточно памяти для создания кнопки изменения!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!butdeleterank)
	{
		qDebug() << "Недостаточно памяти для создания кнопки удаления!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!butrefreshlist)
	{
		qDebug() << "Недостаточно памяти для создания кнопки обновления списка!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!butprinttofile)
	{
		qDebug() << "Недостаточно памяти для создания кнопки генерации отчета!\n";
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
		qDebug() << "Недостаточно памяти для создания объекта базы данных!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	setLayout(layout);
	setFixedSize(680, 680);

	linename->setPlaceholderText("Наименование");
	linecompetenc->setPlaceholderText("Компетенции");

	butaddrank->setMaximumSize(150, 25);
	butchangerank->setMaximumSize(150, 25);
	butdeleterank->setMaximumSize(150, 25);
	butrefreshlist->setMaximumSize(150, 25);
	butprinttofile->setMaximumSize(150, 25);

	//table->setMaximumSize(480, 100);
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	table->setSelectionMode(QAbstractItemView::SingleSelection);

	*db = QSqlDatabase::addDatabase("QMYSQL", "conn5");

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

		linename->setEnabled(false);
		linecompetenc->setEnabled(false);
		butaddrank->setEnabled(false);
		butdeleterank->setEnabled(false);
		butchangerank->setEnabled(false);
		butrefreshlist->setEnabled(false);
		butprinttofile->setEnabled(false);
		table->setEnabled(false);

		QMessageBox::warning(this, "Ошибка", "Ошибка открытия соединения с базой данных!");

		return;
	}


	query = new (std::nothrow) QSqlQuery(*db);

	if(!query)
	{
		qDebug() << "Недостаточно памяти для создания объекта запроса!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		linename->setEnabled(false);
		linecompetenc->setEnabled(false);
		butaddrank->setEnabled(false);
		butdeleterank->setEnabled(false);
		butchangerank->setEnabled(false);
		butrefreshlist->setEnabled(false);
		butprinttofile->setEnabled(false);
		table->setEnabled(false);

		QMessageBox::warning(this, "Ошибка", "Ошибка создания объекта запроса к базе данных!");

		return;
	}

	table->setHorizontalHeaderLabels({"Номер звания", "Наименование", "Компетенции"});
	table->setEditTriggers(0);

	layout->addWidget(linename);
	layout->addWidget(linecompetenc);
	layout->addWidget(butaddrank);
	layout->addWidget(butchangerank);
	layout->addWidget(butdeleterank);
	layout->addWidget(butrefreshlist);
	layout->addWidget(butprinttofile);
	layout->addWidget(table);

	QObject::connect(butaddrank, SIGNAL(clicked()), this, SLOT(clickButAddRank()));
	QObject::connect(butchangerank, SIGNAL(clicked()), this, SLOT(clickButChangeRank()));
	QObject::connect(butdeleterank, SIGNAL(clicked()), this, SLOT(clickButDeleteRank()));
	QObject::connect(butrefreshlist, SIGNAL(clicked()), this, SLOT(clickButRefreshList()));
	QObject::connect(butprinttofile, SIGNAL(clicked()), this, SLOT(clickButPrintToFile()));
}

Rank::~Rank()
{
	if(db)
	{
		db->close();

    QSqlDatabase::removeDatabase("conn5");

		delete db;
	}

	if(query){ delete query; }
	if(settings){ delete settings; }

	//if(file){ delete file; }

	delete linename;
	delete linecompetenc;

	delete butaddrank;
	delete butchangerank;
	delete butdeleterank;
	delete butrefreshlist;
	delete butprinttofile;

	delete table;

	delete layout;
}

void Rank::clickButAddRank()
{
	if(linename->text() == "")
	{
		QMessageBox::warning(this, "Ошибка", "Наименование не должно быть пустым!");

		return;
	}

	if(linecompetenc->text() == "")
	{
		QMessageBox::warning(this, "Ошибка", "Компетенции не должны быть пустыми!");

		return;
	}

	query->prepare(QString("insert into `Rank` value(null, :Name, :Competence)"));

	query->bindValue(":Name", linename->text());
	query->bindValue(":Competence", linecompetenc->text());

	query->exec();

	if(query->lastError().type() != QSqlError::NoError)
	{
		qDebug() << "Не удалось добавить данные в таблице частей!\n";
		qDebug() << "Error code: " << query->lastError().nativeErrorCode() << " Error: " << query->lastError().text();

		QMessageBox::warning(this, "Ошибка", "Часть не была добавлена!");
	}
}

void Rank::clickButChangeRank()
{
	if(table->selectedItems().size() == 0)
	{
		QMessageBox::warning(this, "Ошибка", "Вы должны выбрать строку, которую хотите изменить!");

		return;
	}

	if(linename->text() == "")
	{
		QMessageBox::warning(this, "Ошибка", "Наименование не должно быть пустым!");

		return;
	}

	if(linecompetenc->text() == "")
	{
		QMessageBox::warning(this, "Ошибка", "Компетенции не должны быть пустыми!");

		return;
	}

	query->prepare(QString("update `Rank` set Name = :Name, Competence = :Competence where Id = :Id"));

	query->bindValue(":Name", linename->text());
	query->bindValue(":Competence", linecompetenc->text());
	query->bindValue(":Id", table->selectedItems()[0]->text().toInt());

	query->exec();

	if(query->lastError().type() != QSqlError::NoError)
	{
		qDebug() << "Не удалось обновить данные в таблице званий!\n";
		qDebug() << "Error code: " << query->lastError().nativeErrorCode() << " Error: " << query->lastError().text();

		QMessageBox::warning(this, "Ошибка", "Звание не было обновлено!");
	}
}

void Rank::clickButDeleteRank()
{
	if(table->selectedItems().size() == 0)
	{
		QMessageBox::warning(this, "Ошибка", "Вы должны выбрать строку, которую хотите удалить!");

		return;
	}

	query->prepare(QString("delete from `Rank` where Id = :Id"));

	query->bindValue(":Id", table->selectedItems()[0]->text().toInt());

	query->exec();

	if(query->lastError().type() != QSqlError::NoError)
	{
		qDebug() << "Не удалось удалить данные в таблице званий!\n";
		qDebug() << "Error code: " << query->lastError().nativeErrorCode() << " Error: " << query->lastError().text();

		QMessageBox::warning(this, "Ошибка", "Звание не была удалена!");
	}
}

void Rank::clickButRefreshList()
{
	int counter_data = 0;

	table->clear();

	table->setHorizontalHeaderLabels({"Номер звания", "Наименование", "Компетенции"});
	table->setRowCount(0);

	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	table->setSelectionMode(QAbstractItemView::SingleSelection);

	table->setEditTriggers(0);

	query->exec(QString("select * from `Rank`"));

	while(query->next())
	{
		table->setRowCount(table->rowCount() + 1);

		for(int counter = 0; counter < 3; ++counter)
		{
			table->setItem(counter_data, counter, new QTableWidgetItem(query->value(counter).toString()));
		}

		++counter_data;
	}
}

void Rank::clickButPrintToFile()
{
	file = new (std::nothrow) QFile(QFileDialog::getSaveFileName(this, "Выгрузить отчет", "~/", "Текстовые файлы(*.txt)"));

	if(!file)
	{
		qDebug() << "Недостаточно памяти для создания объекта файла!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(file->fileName() == "")
	{
		delete file;
		file = nullptr;

		return;
	}

	file->setFileName(file->fileName() + ".txt");

	qDebug() << file->fileName();

	if(!file->open(QIODevice::WriteOnly | QIODevice::Text))
	{
		qDebug() << "Ошибка при открытии файла!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		delete file;
		file = nullptr;

		QMessageBox::warning(this, "Ошибка", "Ошибка открытия файла!");

		return;
	}

	file->write(QString("Номер звания\tНаименование\tКомпетенции\n").toUtf8());

	query->exec(QString("select * from `Rank`"));

	while(query->next())
	{
		file->write(QString(query->value(0).toString() + '\t' + query->value(1).toString() + '\t' + query->value(2).toString() + '\n').toUtf8());
	}

	file->close();

	delete file;

	QMessageBox::warning(this, "Успех", "Отчет успешно выгружен!");
}
