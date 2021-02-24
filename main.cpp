#include <QApplication>

#include <QSettings>

#include <QFile>

#include <QDebug>

#include <new>

#include <cstring>

#include <cerrno>

#include "AuthPanel.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	AuthPanel *authpanel = new (std::nothrow) AuthPanel();

	if(!authpanel)
	{
		qDebug() << "Недостатоно памяти для создания комбинационного объекта!\n";
		qDebug() << "Errno" << errno << " Message: " << strerror(errno);

		app.exit();
	}

	return app.exec();
}
