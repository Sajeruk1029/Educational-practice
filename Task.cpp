#include "Task.h"

Task::Task(QSettings *conf) : layout(new (std::nothrow) QBoxLayout(QBoxLayout::Down)), linename(new (std::nothrow) QLineEdit()),
linedescription(new (std::nothrow) QLineEdit()), comboboxcitizen(new (std::nothrow) QComboBox()),
butaddtask(new (std::nothrow) QPushButton("Добавить")), butchangetask(new (std::nothrow) QPushButton("Изменить")),
butdeletetask(new (std::nothrow) QPushButton("Удалить")), butrefreshlist(new (std::nothrow) QPushButton("Обновить список")),
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

	if(!linedescription)
	{
		qDebug() << "Недостаточно памяти для создания поля ввода описания!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!comboboxcitizen)
	{
		qDebug() << "Недостаточно памяти для создания комбобокса!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!butaddtask)
	{
		qDebug() << "Недостаточно памяти для создания кнопки добавления!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!butchangetask)
	{
		qDebug() << "Недостаточно памяти для создания кнопки изменения!\n";
		qDebug() << "Errno: " << errno << " Message: " << strerror(errno);

		return;
	}

	if(!butdeletetask)
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
	linedescription->setPlaceholderText("Описание");

	butaddtask->setMaximumSize(150, 25);
	butchangetask->setMaximumSize(150, 25);
	butdeletetask->setMaximumSize(150, 25);
	butrefreshlist->setMaximumSize(150, 25);
	butprinttofile->setMaximumSize(150, 25);

	//table->setMaximumSize(480, 100);
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	table->setSelectionMode(QAbstractItemView::SingleSelection);

	*db = QSqlDatabase::addDatabase("QMYSQL", "conn8");

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
		linedescription->setEnabled(false);
		comboboxcitizen->setEnabled(false);
		butaddtask->setEnabled(false);
		butdeletetask->setEnabled(false);
		butchangetask->setEnabled(false);
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
		linedescription->setEnabled(false);
		comboboxcitizen->setEnabled(false);
		butaddtask->setEnabled(false);
		butdeletetask->setEnabled(false);
		butchangetask->setEnabled(false);
		butrefreshlist->setEnabled(false);
		butprinttofile->setEnabled(false);
		table->setEnabled(false);

		QMessageBox::warning(this, "Ошибка", "Ошибка создания объекта запроса к базе данных!");

		return;
	}

	table->setHorizontalHeaderLabels({"Номер задачи", "Наименование", "Описание", "Ответственный"});
	table->setEditTriggers(0);

	query->exec(QString("select CONCAT(Citizen.LastName, ' ', Citizen.FirstName, ' ', Citizen.Patronymic) from Citizen"));

	while(query->next())
	{
		comboboxcitizen->addItem(query->value(0).toString());
	}

	layout->addWidget(linename);
	layout->addWidget(linedescription);
	layout->addWidget(comboboxcitizen);
	layout->addWidget(butaddtask);
	layout->addWidget(butchangetask);
	layout->addWidget(butdeletetask);
	layout->addWidget(butrefreshlist);
	layout->addWidget(butprinttofile);
	layout->addWidget(table);

	QObject::connect(butaddtask, SIGNAL(clicked()), this, SLOT(clickButAddTask()));
	QObject::connect(butchangetask, SIGNAL(clicked()), this, SLOT(clickButChangeTask()));
	QObject::connect(butdeletetask, SIGNAL(clicked()), this, SLOT(clickButDeleteTask()));
	QObject::connect(butrefreshlist, SIGNAL(clicked()), this, SLOT(clickButRefreshList()));
	QObject::connect(butprinttofile, SIGNAL(clicked()), this, SLOT(clickButPrintToFile()));
}

Task::~Task()
{
	if(db)
	{
		db->close();

    QSqlDatabase::removeDatabase("conn8");

		delete db;
	}

	if(query){ delete query; }
	if(settings){ delete settings; }

	//if(file){ delete file; }

	delete linename;
	delete linedescription;

	delete comboboxcitizen;

	delete butaddtask;
	delete butchangetask;
	delete butdeletetask;
	delete butrefreshlist;
	delete butprinttofile;

	delete table;

	delete layout;
}

void Task::clickButAddTask()
{
	if(linename->text() == "")
	{
		QMessageBox::warning(this, "Ошибка", "Наименование не должно быть пустым!");

		return;
	}

	if(linedescription->text() == "")
	{
		QMessageBox::warning(this, "Ошибка", "Описание не должно быть пустым!");

		return;
	}

	if(comboboxcitizen->count() == 0)
	{
		QMessageBox::warning(this, "Ошибка", "Не выбрано ни одного гражданина!");

		return;
	}

	query->prepare(QString("insert into Task value(null, :Name, :Description, (select Citizen.Id from Citizen where Citizen.LastName = :LastName and Citizen.FirstName = :FirstName and Citizen.Patronymic = :Patronymic))"));

	query->bindValue(":Name", linename->text());
	query->bindValue(":Description", linename->text());
	query->bindValue(":LastName", comboboxcitizen->currentText().split(' ')[0]);
	query->bindValue(":FirstName", comboboxcitizen->currentText().split(' ')[1]);
	query->bindValue(":Patronymic", comboboxcitizen->currentText().split(' ')[2]);

	query->exec();

	if(query->lastError().type() != QSqlError::NoError)
	{
		qDebug() << "Не удалось добавить данные в таблице задач!\n";
		qDebug() << "Error code: " << query->lastError().nativeErrorCode() << " Error: " << query->lastError().text();

		QMessageBox::warning(this, "Ошибка", "Задача не была добавлена!");
	}
}

void Task::clickButChangeTask()
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

	if(linedescription->text() == "")
	{
		QMessageBox::warning(this, "Ошибка", "Описание не должно быть пустым!");

		return;
	}

	if(comboboxcitizen->count() == 0)
	{
		QMessageBox::warning(this, "Ошибка", "Не выбрано ни одного гражданина!");

		return;
	}

	query->prepare(QString("update Task set Name = :Name, Description = :Description, Id_of_citizen = (select Citizen.Id from Citizen where Citizen.LastName = :LastName and Citizen.FirstName = :FirstName and Citizen.Patronymic = :Patronymic) where Id = :Id"));

	query->bindValue(":Name", linename->text());
	query->bindValue(":Description", linedescription->text());
	query->bindValue(":LastName", comboboxcitizen->currentText().split(' ')[0]);
	query->bindValue(":FirstName", comboboxcitizen->currentText().split(' ')[1]);
	query->bindValue(":Patronymic", comboboxcitizen->currentText().split(' ')[2]);
	query->bindValue(":Id", table->selectedItems()[0]->text().toInt());

	query->exec();

	if(query->lastError().type() != QSqlError::NoError)
	{
		qDebug() << "Не удалось обновить данные в таблице задач!\n";
		qDebug() << "Error code: " << query->lastError().nativeErrorCode() << " Error: " << query->lastError().text();

		QMessageBox::warning(this, "Ошибка", "Задача не была обновлена!");
	}
}

void Task::clickButDeleteTask()
{
	if(table->selectedItems().size() == 0)
	{
		QMessageBox::warning(this, "Ошибка", "Вы должны выбрать строку, которую хотите удалить!");

		return;
	}

	query->prepare(QString("delete from Task where Id = :Id"));

	query->bindValue(":Id", table->selectedItems()[0]->text().toInt());

	query->exec();

	if(query->lastError().type() != QSqlError::NoError)
	{
		qDebug() << "Не удалось удалить данные в таблице задач!\n";
		qDebug() << "Error code: " << query->lastError().nativeErrorCode() << " Error: " << query->lastError().text();

		QMessageBox::warning(this, "Ошибка", "Задача не была удалена!");
	}
}

void Task::clickButRefreshList()
{
	int counter_data = 0;

	table->clear();
	comboboxcitizen->clear();

	query->exec(QString("select CONCAT(Citizen.LastName, ' ', Citizen.FirstName, ' ', Citizen.Patronymic) from Citizen"));

	while(query->next())
	{
		comboboxcitizen->addItem(query->value(0).toString());
	}

	table->setHorizontalHeaderLabels({"Номер задачи", "Наименование", "Описание", "Ответственный"});
	table->setRowCount(0);

	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	table->setSelectionMode(QAbstractItemView::SingleSelection);

	table->setEditTriggers(0);

	query->exec(QString("select Task.Id, Task.Name, Task.Description, CONCAT(Citizen.LastName, ' ', Citizen.FirstName, ' ', Citizen.Patronymic) from Task join Citizen on Citizen.Id = Task.Id_of_citizen"));

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

void Task::clickButPrintToFile()
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

	file->write(QString("Номер задачи\tНаименование\tОписание\tОтветственый\n").toUtf8());

	query->exec(QString("select Task.Id, Task.Name, Task.Description, CONCAT(Citizen.LastName, ' ', Citizen.FirstName, ' ', Citizen.Patronymic) from Task join Citizen on Citizen.Id = Task.Id_of_citizen"));

	while(query->next())
	{
		file->write(QString(query->value(0).toString() + '\t' + query->value(1).toString() + '\t' + query->value(2).toString() + '\t' + query->value(2).toString() + '\n').toUtf8());
	}

	file->close();

	delete file;

	QMessageBox::warning(this, "Успех", "Отчет успешно выгружен!");
}
