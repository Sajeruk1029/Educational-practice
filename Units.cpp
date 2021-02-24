#include "Units.h"

Units::Units(QSettings *conf) : layout(new (std::nothrow) QBoxLayout(QBoxLayout::Down)), linelocation(new (std::nothrow) QLineEdit()),
comboboxcommander(new (std::nothrow) QComboBox()), butaddunit(new (std::nothrow) QPushButton("Добавить")),
butchangeunit(new (std::nothrow) QPushButton("Изменить")), butdeleteunit(new (std::nothrow) QPushButton("Удалить")),
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

	if(!linelocation)
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

	if(!butaddunit)
	{
		qDebug() << "Недостаточно памяти для создания кнопки добавления!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!butchangeunit)
	{
		qDebug() << "Недостаточно памяти для создания кнопки изменения!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!butdeleteunit)
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

	linelocation->setPlaceholderText("Местоположение");

	butaddunit->setMaximumSize(150, 25);
	butchangeunit->setMaximumSize(150, 25);
	butdeleteunit->setMaximumSize(150, 25);
	butrefreshlist->setMaximumSize(150, 25);
	butprinttofile->setMaximumSize(150, 25);

	//table->setMaximumSize(480, 100);
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	table->setSelectionMode(QAbstractItemView::SingleSelection);

	*db = QSqlDatabase::addDatabase("QMYSQL", "conn3");

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

		linelocation->setEnabled(false);
		comboboxcommander->setEnabled(false);
		butaddunit->setEnabled(false);
		butdeleteunit->setEnabled(false);
		butchangeunit->setEnabled(false);
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

		linelocation->setEnabled(false);
		comboboxcommander->setEnabled(false);
		butaddunit->setEnabled(false);
		butdeleteunit->setEnabled(false);
		butchangeunit->setEnabled(false);
		butrefreshlist->setEnabled(false);
		butprinttofile->setEnabled(false);
		table->setEnabled(false);

		QMessageBox::warning(this, "Ошибка", "Ошибка создания объекта запроса к базе данных!");

		return;
	}

	table->setHorizontalHeaderLabels({"Номер части", "Местоположение", "Командир части"});
	table->setEditTriggers(0);

	query->exec(QString("select Citizen.LastName, Citizen.FirstName, Citizen.Patronymic from Citizen join Commander_of_unit on Commander_of_unit.Id_citizen = Citizen.Id"));

	while(query->next())
	{
		comboboxcommander->addItem((query->value(0).toString() + " " + query->value(1).toString() + " " + query->value(2).toString()));
	}

	layout->addWidget(linelocation);
	layout->addWidget(comboboxcommander);
	layout->addWidget(butaddunit);
	layout->addWidget(butchangeunit);
	layout->addWidget(butdeleteunit);
	layout->addWidget(butrefreshlist);
	layout->addWidget(butprinttofile);
	layout->addWidget(table);

	QObject::connect(butaddunit, SIGNAL(clicked()), this, SLOT(clickButAddUnit()));
	QObject::connect(butchangeunit, SIGNAL(clicked()), this, SLOT(clickButChangeUnit()));
	QObject::connect(butdeleteunit, SIGNAL(clicked()), this, SLOT(clickButDeleteUnit()));
	QObject::connect(butrefreshlist, SIGNAL(clicked()), this, SLOT(clickButRefreshList()));
	QObject::connect(butprinttofile, SIGNAL(clicked()), this, SLOT(clickButPrintToFile()));
}

Units::~Units()
{
	if(db)
	{
		db->close();

    QSqlDatabase::removeDatabase("conn3");

		delete db;
	}

	if(query){ delete query; }
	if(settings){ delete settings; }

	//if(file){ delete file; }

	delete linelocation;

	delete comboboxcommander;

	delete butaddunit;
	delete butchangeunit;
	delete butdeleteunit;
	delete butrefreshlist;
	delete butprinttofile;

	delete table;

	delete layout;
}

void Units::clickButAddUnit()
{
	if(linelocation->text() == "")
	{
		QMessageBox::warning(this, "Ошибка", "Местоположение не должно быть пустым!");

		return;
	}

	if(comboboxcommander->count() == 0)
	{
		QMessageBox::warning(this, "Ошибка", "Не выбрано ни одного командира части!");

		return;
	}

	query->prepare(QString("insert into Unit value(null, :Location, (select Commander_of_unit.Id from Commander_of_unit join Citizen on Commander_of_unit.Id_citizen = Citizen.Id where Citizen.LastName = :LastName and Citizen.FirstName = :FirstName and Citizen.Patronymic = :Patronymic))"));

	query->bindValue(":Location", linelocation->text());
	query->bindValue(":LastName", comboboxcommander->currentText().split(' ')[0]);
	query->bindValue(":FirstName", comboboxcommander->currentText().split(' ')[1]);
	query->bindValue(":Patronymic", comboboxcommander->currentText().split(' ')[2]);

	query->exec();

	if(query->lastError().type() != QSqlError::NoError)
	{
		qDebug() << "Не удалось добавить данные в таблице частей!\n";
		qDebug() << "Error code: " << query->lastError().nativeErrorCode() << " Error: " << query->lastError().text();

		QMessageBox::warning(this, "Ошибка", "Часть не была добавлена!");
	}
}

void Units::clickButChangeUnit()
{
	if(table->selectedItems().size() == 0)
	{
		QMessageBox::warning(this, "Ошибка", "Вы должны выбрать строку, которую хотите изменить!");

		return;
	}

	if(linelocation->text() == "")
	{
		QMessageBox::warning(this, "Ошибка", "Местоположение не должно быть пустым!");

		return;
	}

	if(comboboxcommander->count() == 0)
	{
		QMessageBox::warning(this, "Ошибка", "Не выбрано ни одного командира части!");

		return;
	}

	query->prepare(QString("update Unit set Unit_location = :Location, Id_commander_of_unit = (select Commander_of_unit.Id from Commander_of_unit join Citizen on Commander_of_unit.Id_citizen = Citizen.Id where Citizen.LastName = :LastName and Citizen.FirstName = :FirstName and Citizen.Patronymic = :Patronymic) where Id = :Id"));

	query->bindValue(":Location", linelocation->text());
	query->bindValue(":LastName", comboboxcommander->currentText().split(' ')[0]);
	query->bindValue(":FirstName", comboboxcommander->currentText().split(' ')[1]);
	query->bindValue(":Patronymic", comboboxcommander->currentText().split(' ')[2]);
	query->bindValue(":Id", table->selectedItems()[0]->text().toInt());

	query->exec();

	if(query->lastError().type() != QSqlError::NoError)
	{
		qDebug() << "Не удалось обновить данные в таблице частей!\n";
		qDebug() << "Error code: " << query->lastError().nativeErrorCode() << " Error: " << query->lastError().text();

		QMessageBox::warning(this, "Ошибка", "Часть не была обновлена!");
	}
}

void Units::clickButDeleteUnit()
{
	if(table->selectedItems().size() == 0)
	{
		QMessageBox::warning(this, "Ошибка", "Вы должны выбрать строку, которую хотите удалить!");

		return;
	}

	query->prepare(QString("delete from Unit where Id = :Id"));

	query->bindValue(":Id", table->selectedItems()[0]->text().toInt());

	query->exec();

	if(query->lastError().type() != QSqlError::NoError)
	{
		qDebug() << "Не удалось удалить данные в таблице частей!\n";
		qDebug() << "Error code: " << query->lastError().nativeErrorCode() << " Error: " << query->lastError().text();

		QMessageBox::warning(this, "Ошибка", "Часть не была удалена!");
	}
}

void Units::clickButRefreshList()
{
	int counter_data = 0;

	table->clear();
	comboboxcommander->clear();

	query->exec(QString("select Citizen.LastName, Citizen.FirstName, Citizen.Patronymic from Citizen join Commander_of_unit on Commander_of_unit.Id_citizen = Citizen.Id"));

	while(query->next())
	{
		comboboxcommander->addItem((query->value(0).toString() + " " + query->value(1).toString() + " " + query->value(2).toString()));
	}

	table->setHorizontalHeaderLabels({"Номер части", "Местоположение", "Командир части"});
	table->setRowCount(0);

	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	table->setSelectionMode(QAbstractItemView::SingleSelection);

	table->setEditTriggers(0);

	query->exec(QString("select Unit.Id, Unit.Unit_location, CONCAT(Citizen.LastName, ' ', Citizen.FirstName, ' ', Citizen.Patronymic) from Unit join Commander_of_unit on Commander_of_unit.Id = Unit.Id_commander_of_unit join Citizen on Citizen.Id = Commander_of_unit.Id_citizen"));

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

void Units::clickButPrintToFile()
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

	file->write(QString("Номер части\tMeстоположение\tКомандир части\n").toUtf8());

	query->exec(QString("select Unit.Id, Unit.Unit_location, CONCAT(Citizen.LastName, ' ', Citizen.FirstName, ' ', Citizen.Patronymic) from Unit join Commander_of_unit on Commander_of_unit.Id = Unit.Id_commander_of_unit join Citizen on Citizen.Id = Commander_of_unit.Id_citizen"));

	while(query->next())
	{
		file->write(QString(query->value(0).toString() + '\t' + query->value(1).toString() + '\t' + query->value(2).toString() + '\n').toUtf8());
	}

	file->close();

	delete file;

	QMessageBox::warning(this, "Успех", "Отчет успешно выгружен!");
}
