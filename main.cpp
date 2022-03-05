#include "UAC.h"
#include <QCoreApplication>
#include <QDebug>
#include <QSettings>

void GETUAC() {
	if (UAC::runAsAdmin()) {
		exit(0);
	}
}

void INITREG() {
	qDebug() << "Init Reg";

	QSettings *backgroundReg = new QSettings("HKEY_CLASSES_ROOT\\Directory\\Background\\shell", QSettings::NativeFormat);
	backgroundReg->beginGroup("AddToPath");
	backgroundReg->setValue(".", "Add To Path");
	backgroundReg->beginGroup("command");
	backgroundReg->setValue(".", ("\"" + QCoreApplication::applicationFilePath().replace("/", "\\") + "\"" + " \"%V\"").toStdString().c_str());
	backgroundReg->endGroup();
	backgroundReg->endGroup();

	QSettings *directoryReg = new QSettings("HKEY_CLASSES_ROOT\\Directory\\shell", QSettings::NativeFormat);
	directoryReg->beginGroup("AddToPath");
	directoryReg->setValue(".", "Add To Path");
	directoryReg->beginGroup("command");
	directoryReg->setValue(".", ("\"" + QCoreApplication::applicationFilePath().replace("/", "\\") + "\"" + " \"%V\"").toStdString().c_str());
	directoryReg->endGroup();
	directoryReg->endGroup();

	backgroundReg->deleteLater();
	directoryReg->deleteLater();
}

void ADDTOPATH(const QString &path) {
	qDebug() << "Add To Path: " << path;
	QSettings *reg = new QSettings("HKEY_LOCAL_MACHINE\\System\\CurrentControlSet\\Control\\Session Manager\\Environment", QSettings::NativeFormat);
	auto value = reg->value("Path").toString();
	value += ";" + path;
	qDebug() << value;
	reg->setValue("Path", value);
	reg->deleteLater();
	exit(0);
}

int main(int argc, char *argv[]) {
	QCoreApplication app(argc, argv);

	GETUAC();// Get UAC

	if (argc < 2) {
		INITREG();// Init REG
		exit(0);
	}

	QString path = QString::fromUtf8(argv[1]);
	qDebug() << path;
	ADDTOPATH(path);

	return app.exec();
}
