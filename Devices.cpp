#include "Devices.h"

Devices::Devices(QSettings *conf) : layout(new (std::nothrow) QBoxLayout(QBoxLayout::Down)), linename(new (std::nothrow) QLineEdit()),
linetarget(new (std::nothrow) QLineEdit()), linenumber(new (std::nothrow) QLineEdit()),
comboboxhave(new (std::nothrow) QComboBox()), comboboxcompany(new (std::nothrow) QComboBox()),
butadddevices(new (std::nothrow) QPushButton("Добавить")), butchangedevices(new (std::nothrow) QPushButton("Изменить")),
butdeletedevices(new (std::nothrow) QPushButton("Удалить")), butrefreshlist(new (std::nothrow) QPushButton("Обновить список")),
butprinttofile(new (std::nothrow) QPushButton("Генерировать отчет")), table(new (std::nothrow) QTableWidget(0, 6)),
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
		qDebug() << "Недостаточно памяти для создания поля ввода наименования!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!linetarget)
	{
		qDebug() << "Недостаточно памяти для создания поля ввода назначения!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!linenumber)
	{
		qDebug() << "Недостаточно памяти для создания поля ввода количества!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!comboboxhave)
	{
		qDebug() << "Недостаточно памяти для создания комбобокса!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!comboboxcompany)
	{
		qDebug() << "Недостаточно памяти для создания комбобокса!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!butadddevices)
	{
		qDebug() << "Недостаточно памяти для создания кнопки добавления!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!butchangedevices)
	{
		qDebug() << "Недостаточно памяти для создания кнопки изменения!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!butdeletedevices)
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
	linetarget->setPlaceholderText("Назначение оборудование");
	linenumber->setPlaceholderText("Количество");

	linenumber->setInputMask("00000000");

	butadddevices->setMaximumSize(150, 25);
	butchangedevices->setMaximumSize(150, 25);
	butdeletedevices->setMaximumSize(150, 25);
	butrefreshlist->setMaximumSize(150, 25);
	butprinttofile->setMaximumSize(150, 25);

	//table->setMaximumSize(480, 100);
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	table->setSelectionMode(QAbstractItemView::SingleSelection);

	*db = QSqlDatabase::addDatabase("QMYSQL", "conn7");

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
		linetarget->setEnabled(false);
		linenumber->setEnabled(false);
		comboboxhave->setEnabled(false);
		comboboxcompany->setEnabled(false);
		butadddevices->setEnabled(false);
		butdeletedevices->setEnabled(false);
		butchangedevices->setEnabled(false);
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
		linetarget->setEnabled(false);
		linenumber->setEnabled(false);
		comboboxhave->setEnabled(false);
		comboboxcompany->setEnabled(false);
		butadddevices->setEnabled(false);
		butdeletedevices->setEnabled(false);
		butchangedevices->setEnabled(false);
		butrefreshlist->setEnabled(false);
		butprinttofile->setEnabled(false);
		table->setEnabled(false);

		QMessageBox::warning(this, "Ошибка", "Ошибка создания объекта запроса к базе данных!");

		return;
	}

	table->setHorizontalHeaderLabels({"Номер", "Наименование", "Назначение", "Наличие", "Количество", "Ответственная рота"});
	table->setEditTriggers(0);

	table->setColumnWidth(0, 50);
	table->setColumnWidth(1, 100);
	table->setColumnWidth(2, 150);
	table->setColumnWidth(3, 100);
	table->setColumnWidth(4, 100);
	table->setColumnWidth(5, 160);

	query->exec(QString("select Id from Company"));

	while(query->next())
	{
		comboboxcompany->addItem(query->value(0).toString());
	}

	comboboxhave->addItem("Имеется");
	comboboxhave->addItem("Не имеется");

	layout->addWidget(linename);
	layout->addWidget(linetarget);
	layout->addWidget(comboboxhave);
	layout->addWidget(linenumber);
	layout->addWidget(comboboxcompany);
	layout->addWidget(butadddevices);
	layout->addWidget(butchangedevices);
	layout->addWidget(butdeletedevices);
	layout->addWidget(butrefreshlist);
	layout->addWidget(butprinttofile);
	layout->addWidget(table);

	QObject::connect(butadddevices, SIGNAL(clicked()), this, SLOT(clickButAddDevices()));
	QObject::connect(butchangedevices, SIGNAL(clicked()), this, SLOT(clickButChangeDevices()));
	QObject::connect(butdeletedevices, SIGNAL(clicked()), this, SLOT(clickButDeleteDevices()));
	QObject::connect(butrefreshlist, SIGNAL(clicked()), this, SLOT(clickButRefreshList()));
	QObject::connect(butprinttofile, SIGNAL(clicked()), this, SLOT(clickButPrintToFile()));
}

Devices::~Devices()
{
	if(db)
	{
		db->close();

    QSqlDatabase::removeDatabase("conn7");

		delete db;
	}

	if(query){ delete query; }
	if(settings){ delete settings; }

	//if(file){ delete file; }

	delete linename;
	delete linetarget;
	delete linenumber;

	delete comboboxcompany;
	delete comboboxhave;

	delete butadddevices;
	delete butchangedevices;
	delete butdeletedevices;
	delete butrefreshlist;
	delete butprinttofile;

	delete table;

	delete layout;
}

void Devices::clickButAddDevices()
{
	if(linename->text() == "")
	{
		QMessageBox::warning(this, "Ошибка", "Имя не должно быть пустым!");

		return;
	}

	if(linetarget->text() == "")
	{
		QMessageBox::warning(this, "Ошибка", "Назначение не должно быть пустым!");

		return;
	}

	if(linenumber->text() == "")
	{
		QMessageBox::warning(this, "Ошибка", "Количество не должно быть пустым!");

		return;
	}

	if((linenumber->text().toInt() == 0) && (comboboxhave->currentText() == "Имеется"))
	{
		QMessageBox::warning(this, "Ошибка", "Количество и наличие конфликтуют!");

		return;
	}

	if((linenumber->text().toInt() > 0) && (comboboxhave->currentText() != "Имеется"))
	{
		QMessageBox::warning(this, "Ошибка", "Количество и наличие конфликтуют!");

		return;
	}

	if(comboboxcompany->count() == 0)
	{
		QMessageBox::warning(this, "Ошибка", "Не выбрано ни одной роты!");

		return;
	}

	query->prepare(QString("insert into Device values(null, :Name, :Target, :Have, :Number)"));

	query->bindValue(":Name", linename->text());
	query->bindValue(":Target", linetarget->text());
	query->bindValue(":Have", ((comboboxhave->currentText() == "Имеется")? true : false));
	query->bindValue(":Number", linenumber->text().toInt());

	query->exec();

	if(query->lastError().type() != QSqlError::NoError)
	{
		qDebug() << "Не удалось добавить данные в таблице оборудования!\n";
		qDebug() << "Error code: " << query->lastError().nativeErrorCode() << " Error: " << query->lastError().text();

		QMessageBox::warning(this, "Ошибка", "Оборудование не было добавлено!");
	}

	query->prepare(QString("insert into Device_and_company values(null, (select Id from Device where Name = :Name and Target_of_device = :Target), :IdCompany)"));

	query->bindValue(":Name", linename->text());
	query->bindValue(":Target", linetarget->text());
	query->bindValue(":IdCompany", comboboxcompany->currentText().toInt());

	query->exec();

	if(query->lastError().type() != QSqlError::NoError)
	{
		qDebug() << "1";
		qDebug() << "Не удалось добавить данные в таблице оборудования и рот!\n";
		qDebug() << "Error code: " << query->lastError().nativeErrorCode() << " Error: " << query->lastError().text();

		QMessageBox::warning(this, "Ошибка", "Оборудование не было привязано к роте!");
	}
}

void Devices::clickButChangeDevices()
{
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

	if(linetarget->text() == "")
	{
		QMessageBox::warning(this, "Ошибка", "Назначение не должно быть пустым!");

		return;
	}

	if(linenumber->text() == "")
	{
		QMessageBox::warning(this, "Ошибка", "Количество не должно быть пустым!");

		return;
	}

	if((linenumber->text().toInt() == 0) && (comboboxhave->currentText() == "Имеется"))
	{
		QMessageBox::warning(this, "Ошибка", "Количество и наличие конфликтуют!");

		return;
	}

	if((linenumber->text().toInt() > 0) && (comboboxhave->currentText() != "Имеется"))
	{
		QMessageBox::warning(this, "Ошибка", "Количество и наличие конфликтуют!");

		return;
	}

	query->prepare(QString("update Device set Name = :Name, Target_of_device = :Target, Have = :Have, Number = :Number where Id = :Id"));

	query->bindValue(":Name", linename->text());
	query->bindValue(":Target", linetarget->text());
	query->bindValue(":Have", ((comboboxhave->currentText() == "Имеется")? true : false));
	query->bindValue(":Number", linenumber->text().toInt());
	query->bindValue(":Id", table->selectedItems()[0]->text().toInt());

	query->exec();

	if(query->lastError().type() != QSqlError::NoError)
	{
		qDebug() << "Не удалось обновить данные в таблице оборудования!\n";
		qDebug() << "Error code: " << query->lastError().nativeErrorCode() << " Error: " << query->lastError().text();

		QMessageBox::warning(this, "Ошибка", "Оборудование не было обновлено!");
	}

	query->prepare(QString("update Device_and_company set Id_of_device = :IdDevice, Id_of_company = :IdCompany where Id_of_device = :IdDevice"));

	query->bindValue(":IdDevice", table->selectedItems()[0]->text().toInt());
	query->bindValue(":IdCompany", comboboxcompany->currentText().toInt());

	query->exec();

	if(query->lastError().type() != QSqlError::NoError)
	{
		qDebug() << "Не удалось обновить данные в таблице оборудования и рот!\n";
		qDebug() << "Error code: " << query->lastError().nativeErrorCode() << " Error: " << query->lastError().text();

		QMessageBox::warning(this, "Ошибка", "Оборудование не было привязано к роте!");
	}
}

void Devices::clickButDeleteDevices()
{
	if(table->selectedItems().size() == 0)
	{
		QMessageBox::warning(this, "Ошибка", "Вы должны выбрать строку, которую хотите удалить!");

		return;
	}

	query->prepare(QString("delete from Device_and_company where Id = :Id"));

	query->bindValue(":Id", table->selectedItems()[0]->text().toInt());

	query->exec();

	if(query->lastError().type() != QSqlError::NoError)
	{
		qDebug() << "Не удалось удалить данные в таблице оборудования и рот!\n";
		qDebug() << "Error code: " << query->lastError().nativeErrorCode() << " Error: " << query->lastError().text();

		QMessageBox::warning(this, "Ошибка", "Оборудование не было удалено!");
	}

	query->prepare(QString("delete from Device where Id = :Id"));

	query->bindValue(":Id", table->selectedItems()[0]->text().toInt());

	query->exec();

	if(query->lastError().type() != QSqlError::NoError)
	{
		qDebug() << "Не удалось удалить данные в таблице оборудования!\n";
		qDebug() << "Error code: " << query->lastError().nativeErrorCode() << " Error: " << query->lastError().text();

		QMessageBox::warning(this, "Ошибка", "Оборудование не было удалено!");
	}
}

void Devices::clickButRefreshList()
{
	int counter_data = 0;

	table->clear();
	comboboxcompany->clear();

	query->exec(QString("select Id from Company"));

	while(query->next())
	{
		comboboxcompany->addItem(query->value(0).toString());
	}

	table->setHorizontalHeaderLabels({"Номер", "Наименование", "Назначение", "Наличие", "Количество", "Ответственная рота"});
	table->setRowCount(0);

	table->setColumnWidth(0, 50);
	table->setColumnWidth(1, 100);
	table->setColumnWidth(2, 150);
	table->setColumnWidth(3, 100);
	table->setColumnWidth(4, 100);
	table->setColumnWidth(5, 160);

	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	table->setSelectionMode(QAbstractItemView::SingleSelection);

	table->setEditTriggers(0);

	query->exec(QString("select Device.Id, Device.Name, Device.Target_of_device, Device.Have, Device.Number, Device_and_company.Id_of_company from Device join Device_and_company on Device_and_company.Id_of_device = Device.id"));

	while(query->next())
	{
		table->setRowCount(table->rowCount() + 1);

		for(int counter = 0; counter < 6; ++counter)
		{
			if(counter == 3)
			{
				table->setItem(counter_data, counter, new QTableWidgetItem((query->value(counter).toString() == "0")? "Не имеется" : "Имеется"));
			}
			else
			{
				table->setItem(counter_data, counter, new QTableWidgetItem(query->value(counter).toString()));
			}
		}

		++counter_data;
	}
}

void Devices::clickButPrintToFile()
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

	file->write(QString("Номер\tНаименование\tНазначение\tНаличие\tКоличество\tОтветственная рота\n").toUtf8());

	query->exec(QString("select Device.Id, Device.Name, Device.Target_of_device, Device.Have, Device.Number, Device_and_company.Id_of_company from Device join Device_and_company on Device_and_company.Id_of_device = Device.id"));

	while(query->next())
	{
		file->write(QString(query->value(0).toString() + '\t' + query->value(1).toString() + '\t' + query->value(2).toString() + '\t' + ((query->value(3).toString() == "0")? "Не имеется" : "Имеется") + '\t' + query->value(4).toString() + '\t' + query->value(5).toString() + '\n').toUtf8());
	}

	file->close();

	delete file;

	QMessageBox::warning(this, "Успех", "Отчет успешно выгружен!");
}
