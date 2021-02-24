#include "Companies.h"

Companies::Companies(QSettings *conf) : layout(new (std::nothrow) QBoxLayout(QBoxLayout::Down)), linenumber(new (std::nothrow) QLineEdit()),
comboboxcommander(new (std::nothrow) QComboBox()), comboboxunit(new (std::nothrow) QComboBox()),
butaddcompany(new (std::nothrow) QPushButton("Добавить")), butchangecompany(new (std::nothrow) QPushButton("Изменить")),
butdeletecompany(new (std::nothrow) QPushButton("Удалить")), butrefreshlist(new (std::nothrow) QPushButton("Обновить список")),
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

	if(!linenumber)
	{
		qDebug() << "Недостаточно памяти для создания поля ввода местоположения!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!comboboxcommander)
	{
		qDebug() << "Недостаточно памяти для создания комбобокса!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!comboboxunit)
	{
		qDebug() << "Недостаточно памяти для создания комбобокса!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}
	if(!butaddcompany)
	{
		qDebug() << "Недостаточно памяти для создания кнопки добавления!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!butchangecompany)
	{
		qDebug() << "Недостаточно памяти для создания кнопки изменения!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!butdeletecompany)
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

	linenumber->setPlaceholderText("Количество человек");
	linenumber->setInputMask("00000000");

	butaddcompany->setMaximumSize(150, 25);
	butchangecompany->setMaximumSize(150, 25);
	butdeletecompany->setMaximumSize(150, 25);
	butrefreshlist->setMaximumSize(150, 25);
	butprinttofile->setMaximumSize(150, 25);

	//table->setMaximumSize(480, 100);
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	table->setSelectionMode(QAbstractItemView::SingleSelection);

	*db = QSqlDatabase::addDatabase("QMYSQL", "conn4");

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

		linenumber->setEnabled(false);
		comboboxcommander->setEnabled(false);
		comboboxunit->setEnabled(false);
		butaddcompany->setEnabled(false);
		butdeletecompany->setEnabled(false);
		butchangecompany->setEnabled(false);
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

		linenumber->setEnabled(false);
		comboboxcommander->setEnabled(false);
		comboboxunit->setEnabled(false);
		butaddcompany->setEnabled(false);
		butdeletecompany->setEnabled(false);
		butchangecompany->setEnabled(false);
		butrefreshlist->setEnabled(false);
		butprinttofile->setEnabled(false);
		table->setEnabled(false);

		QMessageBox::warning(this, "Ошибка", "Ошибка создания объекта запроса к базе данных!");

		return;
	}

	table->setHorizontalHeaderLabels({"Номер роты", "Количество человек", "Часть", "Командир роты"});
	table->setEditTriggers(0);

	query->exec(QString("select Citizen.LastName, Citizen.FirstName, Citizen.Patronymic from Citizen join Commander_of_company on Commander_of_company.Id_of_citizen = Citizen.Id"));

	while(query->next())
	{
		comboboxcommander->addItem((query->value(0).toString() + " " + query->value(1).toString() + " " + query->value(2).toString()));
	}

	query->exec(QString("select Unit.Unit_location from Unit"));

	while(query->next())
	{
		comboboxunit->addItem(query->value(0).toString());
	}

	layout->addWidget(comboboxcommander);
	layout->addWidget(linenumber);
	layout->addWidget(comboboxunit);
	layout->addWidget(butaddcompany);
	layout->addWidget(butchangecompany);
	layout->addWidget(butdeletecompany);
	layout->addWidget(butrefreshlist);
	layout->addWidget(butprinttofile);
	layout->addWidget(table);

	QObject::connect(butaddcompany, SIGNAL(clicked()), this, SLOT(clickButAddCompany()));
	QObject::connect(butchangecompany, SIGNAL(clicked()), this, SLOT(clickButChangeCompany()));
	QObject::connect(butdeletecompany, SIGNAL(clicked()), this, SLOT(clickButDeleteCompany()));
	QObject::connect(butrefreshlist, SIGNAL(clicked()), this, SLOT(clickButRefreshList()));
	QObject::connect(butprinttofile, SIGNAL(clicked()), this, SLOT(clickButPrintToFile()));
}

Companies::~Companies()
{
	if(db)
	{
		db->close();

    QSqlDatabase::removeDatabase("conn4");

		delete db;
	}

	if(query){ delete query; }
	if(settings){ delete settings; }

	//if(file){ delete file; }

	delete linenumber;

	delete comboboxcommander;
	delete comboboxunit;

	delete butaddcompany;
	delete butchangecompany;
	delete butdeletecompany;
	delete butrefreshlist;
	delete butprinttofile;

	delete table;

	delete layout;
}

void Companies::clickButAddCompany()
{
	if(linenumber->text() == "")
	{
		QMessageBox::warning(this, "Ошибка", "Количество человек не должно быть пустым!");

		return;
	}

	if(linenumber->text().toInt() == 0)
	{
		QMessageBox::warning(this, "Ошибка", "Количество человек должно быть больше 0!");

		return;
	}

	if(comboboxunit->count() == 0)
	{
		QMessageBox::warning(this, "Ошибка", "Не выбрано ни одной части!");

		return;
	}

	if(comboboxcommander->count() == 0)
	{
		QMessageBox::warning(this, "Ошибка", "Не выбрано ни одного командира!");

		return;
	}

	query->prepare(QString("insert into Company values(null, :Number, (select Id from Unit where Unit.Unit_location = :Location), (select Commander_of_company.Id from Commander_of_company join Citizen on Commander_of_company.Id_of_citizen = Citizen.Id where Citizen.LastName = :LastName and Citizen.FirstName = :FirstName and Citizen.Patronymic = :Patronymic))"));

	query->bindValue(":Number", linenumber->text().toInt());
	query->bindValue(":LastName", comboboxcommander->currentText().split(' ')[0]);
	query->bindValue(":FirstName", comboboxcommander->currentText().split(' ')[1]);
	query->bindValue(":Patronymic", comboboxcommander->currentText().split(' ')[2]);
	query->bindValue(":Location", comboboxunit->currentText());

	query->exec();

	if(query->lastError().type() != QSqlError::NoError)
	{
		qDebug() << "Не удалось добавить данные в таблице рот!\n";
		qDebug() << "Error code: " << query->lastError().nativeErrorCode() << " Error: " << query->lastError().text();

		QMessageBox::warning(this, "Ошибка", "Рота не была добавлена!");
	}
}

void Companies::clickButChangeCompany()
{
	if(table->selectedItems().size() == 0)
	{
		QMessageBox::warning(this, "Ошибка", "Вы должны выбрать строку, которую хотите изменить!");

		return;
	}

	if(linenumber->text() == "")
	{
		QMessageBox::warning(this, "Ошибка", "Количество человек не должно быть пустым!");

		return;
	}

	if(linenumber->text().toInt() == 0)
	{
		QMessageBox::warning(this, "Ошибка", "Количество человек должно быть больше 0!");

		return;
	}

	if(comboboxcommander->count() == 0)
	{
		QMessageBox::warning(this, "Ошибка", "Не выбрано ни одного командира!");

		return;
	}

	query->prepare(QString("update Company set Company.Person_number = :Number, Company.Id_of_unit = (select Id from Unit where Unit.Unit_location = :Location), Id_commander_of_company = (select Commander_of_company.Id from Commander_of_company join Citizen on Commander_of_company.Id_of_citizen = Citizen.Id where Citizen.LastName = :LastName and Citizen.FirstName = :FirstName and Citizen.Patronymic = :Patronymic) where Id = :Id"));

	query->bindValue(":Number", linenumber->text().toInt());
	query->bindValue(":Location", comboboxunit->currentText());
	query->bindValue(":LastName", comboboxcommander->currentText().split(' ')[0]);
	query->bindValue(":FirstName", comboboxcommander->currentText().split(' ')[1]);
	query->bindValue(":Patronymic", comboboxcommander->currentText().split(' ')[2]);
	query->bindValue(":Id", table->selectedItems()[0]->text().toInt());

	query->exec();

	if(query->lastError().type() != QSqlError::NoError)
	{
		qDebug() << "Не удалось обновить данные в таблице рот!\n";
		qDebug() << "Error code: " << query->lastError().nativeErrorCode() << " Error: " << query->lastError().text();

		QMessageBox::warning(this, "Ошибка", "Рота не была обновлена!");
	}
}

void Companies::clickButDeleteCompany()
{
	if(table->selectedItems().size() == 0)
	{
		QMessageBox::warning(this, "Ошибка", "Вы должны выбрать строку, которую хотите удалить!");

		return;
	}

	query->prepare(QString("delete from Company where Id = :Id"));

	query->bindValue(":Id", table->selectedItems()[0]->text().toInt());

	query->exec();

	if(query->lastError().type() != QSqlError::NoError)
	{
		qDebug() << "Не удалось удалить данные в таблице рот!\n";
		qDebug() << "Error code: " << query->lastError().nativeErrorCode() << " Error: " << query->lastError().text();

		QMessageBox::warning(this, "Ошибка", "Рота не была удалена!");
	}
}

void Companies::clickButRefreshList()
{
	int counter_data = 0;

	table->clear();

	comboboxcommander->clear();
	comboboxunit->clear();

	query->exec(QString("select Citizen.LastName, Citizen.FirstName, Citizen.Patronymic from Citizen join Commander_of_company on Commander_of_company.Id_of_citizen = Citizen.Id"));

	while(query->next())
	{
		comboboxcommander->addItem((query->value(0).toString() + " " + query->value(1).toString() + " " + query->value(2).toString()));
	}

	query->exec(QString("select Unit.Unit_location from Unit"));

	while(query->next())
	{
		comboboxunit->addItem(query->value(0).toString());
	}

	table->setHorizontalHeaderLabels({"Номер роты", "Количество человек", "Часть", "Командир роты"});
	table->setRowCount(0);

	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	table->setSelectionMode(QAbstractItemView::SingleSelection);

	table->setEditTriggers(0);

	query->exec(QString("select Company.Id, Company.Person_number, Unit.Unit_location, CONCAT(Citizen.LastName, ' ', Citizen.FirstName, ' ', Citizen.Patronymic) from Company join Commander_of_company on Commander_of_company.Id = Company.Id_commander_of_company join Citizen on Citizen.Id = Commander_of_company.Id_of_citizen join Unit on Unit.Id = Company.Id_of_unit"));

	while(query->next())
	{
		table->setRowCount(table->rowCount() + 1);

		for(int counter = 0; counter < 4; ++counter)
		{
			table->setItem(counter_data, counter, new QTableWidgetItem(query->value(counter).toString()));
			qDebug() << query->value(counter).toString();
		}

		++counter_data;
	}
}

void Companies::clickButPrintToFile()
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

	file->write(QString("Номер роты\tколичество человек\tЧасть\tКомандир роты\n").toUtf8());

	query->exec(QString("select Company.Id, Company.Person_number, Unit.Unit_location, CONCAT(Citizen.LastName, ' ', Citizen.FirstName, ' ', Citizen.Patronymic) from Company join Commander_of_company on Commander_of_company.Id = Company.Id_commander_of_company join Citizen on Citizen.Id = Commander_of_company.Id_of_citizen join Unit on Unit.Id = Company.Id_of_unit"));

	while(query->next())
	{
		file->write(QString(query->value(0).toString() + '\t' + query->value(1).toString() + '\t' + query->value(2).toString() + '\t' + query->value(3).toString() + '\n').toUtf8());
	}

	file->close();

	delete file;

	QMessageBox::warning(this, "Успех", "Отчет успешно выгружен!");
}
