#include "Citizen.h"

Citizen::Citizen(QSettings *conf) : layout(new (std::nothrow) QBoxLayout(QBoxLayout::Down)), linename(new (std::nothrow) QLineEdit()),
linelastname(new (std::nothrow) QLineEdit()), linepatronymic(new (std::nothrow) QLineEdit()),
calendar(new (std::nothrow) QCalendarWidget()), comboboxrank(new (std::nothrow) QComboBox()),
butaddcitizen(new (std::nothrow) QPushButton("Добавить")), butchangecitizen(new (std::nothrow) QPushButton("Изменить")),
butdeletecitizen(new (std::nothrow) QPushButton("Удалить")), butrefreshlist(new (std::nothrow) QPushButton("Обновить список")),
butprinttofile(new (std::nothrow) QPushButton("Генерировать отчет")), table(new (std::nothrow) QTableWidget(0, 4)),
db(new (std::nothrow) QSqlDatabase()), query(nullptr),
settings(conf), file(nullptr)
{
	if(!layout)
	{
		qDebug() << "Недостаточно памяти для создания лейаута!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!linename)
	{
		qDebug() << "Недостаточно памяти для создания поля ввода имени!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!linelastname)
	{
		qDebug() << "Недостаточно памяти для создания поля ввода фамилии!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!linepatronymic)
	{
		qDebug() << "Недостаточно памяти для создания поля ввода отчества!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!comboboxrank)
	{
		qDebug() << "Недостаточно памяти для создания комбобокса!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!butaddcitizen)
	{
		qDebug() << "Недостаточно памяти для создания кнопки добавления!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!butchangecitizen)
	{
		qDebug() << "Недостаточно памяти для создания кнопки изменения!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!butdeletecitizen)
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

	linename->setPlaceholderText("Имя");
	linelastname->setPlaceholderText("Фамилия");
	linepatronymic->setPlaceholderText("Отчество");

	butaddcitizen->setMaximumSize(150, 25);
	butchangecitizen->setMaximumSize(150, 25);
	butdeletecitizen->setMaximumSize(150, 25);
	butrefreshlist->setMaximumSize(150, 25);
	butprinttofile->setMaximumSize(150, 25);

	calendar->setMaximumSize(680, 200);

	table->setMaximumSize(680, 150);
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	table->setSelectionMode(QAbstractItemView::SingleSelection);

	*db = QSqlDatabase::addDatabase("QMYSQL", "conn6");

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
		linelastname->setEnabled(false);
		linepatronymic->setEnabled(false);
		comboboxrank->setEnabled(false);
		calendar->setEnabled(false);
		butaddcitizen->setEnabled(false);
		butdeletecitizen->setEnabled(false);
		butchangecitizen->setEnabled(false);
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
		linelastname->setEnabled(false);
		linepatronymic->setEnabled(false);
		comboboxrank->setEnabled(false);
		calendar->setEnabled(false);
		butaddcitizen->setEnabled(false);
		butdeletecitizen->setEnabled(false);
		butchangecitizen->setEnabled(false);
		butrefreshlist->setEnabled(false);
		butprinttofile->setEnabled(false);
		table->setEnabled(false);

		QMessageBox::warning(this, "Ошибка", "Ошибка создания объекта запроса к базе данных!");

		return;
	}

	table->setHorizontalHeaderLabels({"Номер гражданина", "ФИО гражданина", "Дата рождения", "Звание"});
	table->setEditTriggers(0);

	query->exec(QString("select Name from `Rank`"));

	while(query->next())
	{
		comboboxrank->addItem(query->value(0).toString());
	}

	layout->addWidget(linename);
	layout->addWidget(linelastname);
	layout->addWidget(linepatronymic);
	layout->addWidget(calendar);
	layout->addWidget(comboboxrank);
	layout->addWidget(butaddcitizen);
	layout->addWidget(butchangecitizen);
	layout->addWidget(butdeletecitizen);
	layout->addWidget(butrefreshlist);
	layout->addWidget(butprinttofile);
	layout->addWidget(table);

	QObject::connect(butaddcitizen, SIGNAL(clicked()), this, SLOT(clickButAddCitizen()));
	QObject::connect(butchangecitizen, SIGNAL(clicked()), this, SLOT(clickButChangeCitizen()));
	QObject::connect(butdeletecitizen, SIGNAL(clicked()), this, SLOT(clickButDeleteCitizen()));
	QObject::connect(butrefreshlist, SIGNAL(clicked()), this, SLOT(clickButRefreshList()));
	QObject::connect(butprinttofile, SIGNAL(clicked()), this, SLOT(clickButPrintToFile()));
}

Citizen::~Citizen()
{
	if(db)
	{
		db->close();

    QSqlDatabase::removeDatabase("conn6");

		delete db;
	}

	if(query){ delete query; }
	if(settings){ delete settings; }

	//if(file){ delete file; }

	delete linename;
	delete linelastname;
	delete linepatronymic;

	delete comboboxrank;

	delete calendar;

	delete butaddcitizen;
	delete butchangecitizen;
	delete butdeletecitizen;
	delete butrefreshlist;
	delete butprinttofile;

	delete table;

	delete layout;
}

void Citizen::clickButAddCitizen()
{
	if(linename->text() == "")
	{
		QMessageBox::warning(this, "Ошибка", "Имя не должно быть пустым!");

		return;
	}

	if(linelastname->text() == "")
	{
		QMessageBox::warning(this, "Ошибка", "Фамилия не должно быть пустым!");

		return;
	}

	if(linepatronymic->text() == "")
	{
		QMessageBox::warning(this, "Ошибка", "Отчество не должно быть пустым!");

		return;
	}

	if(comboboxrank->count() == 0)
	{
		QMessageBox::warning(this, "Ошибка", "Не выбрано ни одного звания!");

		return;
	}

	query->prepare(QString("insert into Citizen value(null, :FirstName, :LastName, :Patronymic, :Data, (select Id from `Rank` where Name = :Rank))"));

	query->bindValue(":FirstName", linename->text());
	query->bindValue(":LastName", linelastname->text());
	query->bindValue(":Patronymic", linepatronymic->text());
	query->bindValue(":Data", calendar->selectedDate().toString(Qt::ISODate));
	query->bindValue(":Rank", comboboxrank->currentText());

	query->exec();

	if(query->lastError().type() != QSqlError::NoError)
	{
		qDebug() << "Не удалось добавить данные в таблице граждан!\n";
		qDebug() << "Error code: " << query->lastError().nativeErrorCode() << " Error: " << query->lastError().text();

		QMessageBox::warning(this, "Ошибка", "Гражданин не был добавлен!");
	}

	if(comboboxrank->currentText() == "Командир роты")
	{
		query->prepare(QString("insert into Commander_of_company value(null, (select Id from Citizen where FirstName = :FirstName and LastName = :LastName and Patronymic = :Patronymic))"));

		query->bindValue(":FirstName", linename->text());
		query->bindValue(":LastName", linelastname->text());
		query->bindValue(":Patronymic", linepatronymic->text());

		query->exec();

		if(query->lastError().type() != QSqlError::NoError)
		{
			qDebug() << "Не удалось добавить данные в таблице командира рот!\n";
			qDebug() << "Error code: " << query->lastError().nativeErrorCode() << " Error: " << query->lastError().text();

			QMessageBox::warning(this, "Ошибка", "Командир рот не был добавлен!");
		}
	}

	if(comboboxrank->currentText() == "Командир части")
	{
		query->prepare(QString("insert into Commander_of_unit value(null, (select Id from Citizen where FirstName = :FirstName and LastName = :LastName and Patronymic = :Patronymic))"));

		query->bindValue(":FirstName", linename->text());
		query->bindValue(":LastName", linelastname->text());
		query->bindValue(":Patronymic", linepatronymic->text());

		query->exec();

		if(query->lastError().type() != QSqlError::NoError)
		{
			qDebug() << "Не удалось добавить данные в таблице командира части!\n";
			qDebug() << "Error code: " << query->lastError().nativeErrorCode() << " Error: " << query->lastError().text();

			QMessageBox::warning(this, "Ошибка", "Командир части не был добавлен!");
		}
	}
}

void Citizen::clickButChangeCitizen()
{
	bool commander_of_unit = false;
	bool commander_of_company = false;

	if(table->selectedItems().size() == 0)
	{
		QMessageBox::warning(this, "Ошибка", "Вы должны выбрать строку, которую хотите изменить!");

		return;
	}

	if(linename->text() == "")
	{
		QMessageBox::warning(this, "Ошибка", "Имя не должно быть пустым!");

		return;
	}

	if(linelastname->text() == "")
	{
		QMessageBox::warning(this, "Ошибка", "Фамилия не должно быть пустым!");

		return;
	}

	if(linepatronymic->text() == "")
	{
		QMessageBox::warning(this, "Ошибка", "Отчество не должно быть пустым!");

		return;
	}

	if(comboboxrank->count() == 0)
	{
		QMessageBox::warning(this, "Ошибка", "Не выбрано ни одного звания!");

		return;
	}

	if(table->selectedItems()[3]->text() == "Командир роты")
	{
		commander_of_company = true;
	}

	if(table->selectedItems()[3]->text() == "Командир части")
	{
		commander_of_unit = true;
	}

	query->prepare(QString("update Citizen set FirstName = :FirstName, LastName = :LastName, Patronymic = :Patronymic, Date_of_birth = :Date, Rank_id = (select Id from `Rank` where Name = :Rank) where Citizen.Id = :Id"));

	query->bindValue(":LastName", linelastname->text());
	query->bindValue(":FirstName", linename->text());
	query->bindValue(":Patronymic", linepatronymic->text());
	query->bindValue(":Date", calendar->selectedDate().toString(Qt::ISODate));
	query->bindValue(":Rank", comboboxrank->currentText());
	query->bindValue(":Id", table->selectedItems()[0]->text().toInt());

	query->exec();

	if(query->lastError().type() != QSqlError::NoError)
	{
		qDebug() << "Не удалось обновить данные в таблице частей!\n";
		qDebug() << "Error code: " << query->lastError().nativeErrorCode() << " Error: " << query->lastError().text();

		QMessageBox::warning(this, "Ошибка", "Часть не была обновлена!");
	}

	if((commander_of_unit) || (commander_of_company))
	{
		if((commander_of_unit) && (comboboxrank->currentText() == "Командир роты"))
		{
			query->prepare(QString("insert into Commander_of_company value(null, (select Id from Citizen where FirstName = :FirstName and LastName = :LastName and Patronymic = :Patronymic))"));

			query->bindValue(":FirstName", linename->text());
			query->bindValue(":LastName", linelastname->text());
			query->bindValue(":Patronymic", linepatronymic->text());

			query->exec();

			if(query->lastError().type() != QSqlError::NoError)
			{
				qDebug() << "Не удалось добавить данные в таблице командира роты!\n";
				qDebug() << "Error code: " << query->lastError().nativeErrorCode() << " Error: " << query->lastError().text();

				QMessageBox::warning(this, "Ошибка", "Командир роты не был добавлен!");
			}

			query->prepare(QString("delete from Commander_of_unit where Id_citizen = :Id"));

			query->bindValue(":Id", table->selectedItems()[0]->text().toInt());

			query->exec();

			if(query->lastError().type() != QSqlError::NoError)
			{
				qDebug() << "Не удалось удалить данные в таблице чатей!\n";
				qDebug() << "Error code: " << query->lastError().nativeErrorCode() << " Error: " << query->lastError().text();

				QMessageBox::warning(this, "Ошибка", "Часть не была удалена!");
			}
		}
		if((commander_of_company) && (comboboxrank->currentText() == "Командир части"))
		{
			query->prepare(QString("insert into Commander_of_unit value(null, (select Id from Citizen where FirstName = :FirstName and LastName = :LastName and Patronymic = :Patronymic))"));

			query->bindValue(":FirstName", linename->text());
			query->bindValue(":LastName", linelastname->text());
			query->bindValue(":Patronymic", linepatronymic->text());

			query->exec();

			if(query->lastError().type() != QSqlError::NoError)
			{
				qDebug() << "Не удалось добавить данные в таблице командира части!\n";
				qDebug() << "Error code: " << query->lastError().nativeErrorCode() << " Error: " << query->lastError().text();

				QMessageBox::warning(this, "Ошибка", "Командир части не был добавлен!");
			}

			query->prepare(QString("delete from Commander_of_company where Id_of_citizen = :Id"));

			query->bindValue(":Id", table->selectedItems()[0]->text().toInt());

			query->exec();

			if(query->lastError().type() != QSqlError::NoError)
			{
				qDebug() << "Не удалось удалить данные в таблице командира роты!\n";
				qDebug() << "Error code: " << query->lastError().nativeErrorCode() << " Error: " << query->lastError().text();

				QMessageBox::warning(this, "Ошибка", "Командир роты не была удалена!");
			}
		}

		if((commander_of_company) && ((comboboxrank->currentText() != "Командир части") && (comboboxrank->currentText() != "Командир роты")))
		{
			query->prepare(QString("delete from Commander_of_company where Id_of_citizen = :Id"));

			query->bindValue(":Id", table->selectedItems()[0]->text().toInt());

			query->exec();

			if(query->lastError().type() != QSqlError::NoError)
			{
				qDebug() << "Не удалось удалить данные в таблице командира роты!\n";
				qDebug() << "Error code: " << query->lastError().nativeErrorCode() << " Error: " << query->lastError().text();

				QMessageBox::warning(this, "Ошибка", "Командир роты не был удален!");
			}
		}

		if((commander_of_unit) && ((comboboxrank->currentText() != "Командир части") && (comboboxrank->currentText() != "Командир роты")))
		{
			query->prepare(QString("delete from Commander_of_unit where Id_citizen = :Id"));

			query->bindValue(":Id", table->selectedItems()[0]->text().toInt());

			query->exec();

			if(query->lastError().type() != QSqlError::NoError)
			{
				qDebug() << "Не удалось удалить данные в таблице командира частей!\n";
				qDebug() << "Error code: " << query->lastError().nativeErrorCode() << " Error: " << query->lastError().text();

				QMessageBox::warning(this, "Ошибка", "Командир части не был удален!");
			}
		}
	}

	if(!((commander_of_unit) || (commander_of_company)) && ((comboboxrank->currentText() == "Командир части") || (comboboxrank->currentText() == "Командир роты")))
	{
		if(comboboxrank->currentText() == "Командир части")
		{
			query->prepare(QString("insert into Commander_of_unit value(null, (select Id from Citizen where FirstName = :FirstName and LastName = :LastName and Patronymic = :Patronymic))"));

			query->bindValue(":FirstName", linename->text());
			query->bindValue(":LastName", linelastname->text());
			query->bindValue(":Patronymic", linepatronymic->text());

			query->exec();

			if(query->lastError().type() != QSqlError::NoError)
			{
				qDebug() << "Не удалось добавить данные в таблице командира части!\n";
				qDebug() << "Error code: " << query->lastError().nativeErrorCode() << " Error: " << query->lastError().text();

				QMessageBox::warning(this, "Ошибка", "Командир части не был добавлен!");
			}
		}

		if(comboboxrank->currentText() == "Командир роты")
		{
			query->prepare(QString("insert into Commander_of_company value(null, (select Id from Citizen where FirstName = :FirstName and LastName = :LastName and Patronymic = :Patronymic))"));

			query->bindValue(":FirstName", linename->text());
			query->bindValue(":LastName", linelastname->text());
			query->bindValue(":Patronymic", linepatronymic->text());

			query->exec();

			if(query->lastError().type() != QSqlError::NoError)
			{
				qDebug() << "Не удалось добавить данные в таблице командира рот!\n";
				qDebug() << "Error code: " << query->lastError().nativeErrorCode() << " Error: " << query->lastError().text();

				QMessageBox::warning(this, "Ошибка", "Командир роты не был добавлен!");
			}
		}
	}

}

void Citizen::clickButDeleteCitizen()
{
	if(table->selectedItems().size() == 0)
	{
		QMessageBox::warning(this, "Ошибка", "Вы должны выбрать строку, которую хотите удалить!");

		return;
	}

	if(table->selectedItems()[3]->text() == "Командир роты")
	{
		query->prepare(QString("delete from Commander_of_company where Id_of_citizen = :Id"));

		query->bindValue(":Id", table->selectedItems()[0]->text().toInt());

		query->exec();

		if(query->lastError().type() != QSqlError::NoError)
		{
			qDebug() << "Не удалось удалить данные в таблице рот!\n";
			qDebug() << "Error code: " << query->lastError().nativeErrorCode() << " Error: " << query->lastError().text();

			QMessageBox::warning(this, "Ошибка", "Рота не была удалена!");
		}
	}

	if(table->selectedItems()[3]->text() == "Командир части")
	{
		query->prepare(QString("delete from Commander_of_unit where Id_citizen = :Id"));

		query->bindValue(":Id", table->selectedItems()[0]->text().toInt());

		query->exec();

		if(query->lastError().type() != QSqlError::NoError)
		{
			qDebug() << "Не удалось удалить данные в таблице чатей!\n";
			qDebug() << "Error code: " << query->lastError().nativeErrorCode() << " Error: " << query->lastError().text();

			QMessageBox::warning(this, "Ошибка", "Часть не была удалена!");
		}
	}

	query->prepare(QString("delete from Citizen where Id = :Id"));

	query->bindValue(":Id", table->selectedItems()[0]->text().toInt());

	query->exec();

	if(query->lastError().type() != QSqlError::NoError)
	{
		qDebug() << "Не удалось удалить данные в таблице граждан!\n";
		qDebug() << "Error code: " << query->lastError().nativeErrorCode() << " Error: " << query->lastError().text();

		QMessageBox::warning(this, "Ошибка", "Гражданин не была удалена!");
	}
}

void Citizen::clickButRefreshList()
{
	int counter_data = 0;

	table->clear();
	comboboxrank->clear();


	query->exec(QString("select Name from `Rank`"));

	while(query->next())
	{
		comboboxrank->addItem(query->value(0).toString());
	}

	table->setHorizontalHeaderLabels({"Номер гражданина", "ФИО гражданина", "Дата рождения", "Звание"});
	table->setRowCount(0);

	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	table->setSelectionMode(QAbstractItemView::SingleSelection);

	table->setEditTriggers(0);

	query->exec(QString("select Citizen.Id, CONCAT(Citizen.LastName, ' ', Citizen.FirstName, ' ', Citizen.Patronymic), Citizen.Date_of_birth, `Rank`.Name from Citizen join `Rank` on `Rank`.Id = Citizen.Rank_id"));

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

void Citizen::clickButPrintToFile()
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

	file->write(QString("Номер гражданина\tФИО гражданина\tДата рождения\tЗвание\n").toUtf8());

	query->exec(QString("select Citizen.Id, CONCAT(Citizen.LastName, ' ', Citizen.FirstName, ' ', Citizen.Patronymic), Citizen.Date_of_birth, `Rank`.Name from Citizen join `Rank` on `Rank`.Id = Citizen.Rank_id"));

	while(query->next())
	{
		file->write(QString(query->value(0).toString() + '\t' + query->value(1).toString() + '\t' + query->value(2).toString() + '\t' + query->value(3).toString() + '\n').toUtf8());
	}

	file->close();

	delete file;

	QMessageBox::warning(this, "Успех", "Отчет успешно выгружен!");
}
