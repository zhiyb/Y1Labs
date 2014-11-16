#include <stdlib.h>
#include <qapplication.h>
#include "form.h"

#define CONSOLE "embeddedkonsole "

#define TASKNUM 5
static const QString task[TASKNUM][2] = {
	{"Program 1 - LEDTest", "Program1"},
	{"Program 2 - HelloWorld", "Program2"},
	{"Program 3 - UART Test", "Program3"},
	{"Program 4 - GPIO Test", "Program4"},
	{"USBasp", "USBasp"},
};
const QString fuseType[3] = {"Ext", "High", "Low"};

#define STDH 26
Form::Form(QWidget *parent, const char *name, WFlags f): QWidget(parent, name, f)
{
	list = new QComboBox(this);
	for (int i = 0; i < TASKNUM; i++)
		list->insertItem(task[i][0]);
	list->setCurrentItem(0);
	connect(list, SIGNAL(activated(int)), this, SLOT(read(int)));

	pbMake = new QPushButton("Make", this);
	connect(pbMake, SIGNAL(clicked()), this, SLOT(make()));
	pbUART = new QPushButton("UART", this);
	connect(pbUART, SIGNAL(clicked()), this, SLOT(uart()));
	pbJTAG = new QPushButton("JTAG", this);
	connect(pbJTAG, SIGNAL(clicked()), this, SLOT(jtag()));
	pbConsole = new QPushButton("Console", this);
	connect(pbConsole, SIGNAL(clicked()), this, SLOT(console()));
	pbFlash = new QPushButton("Flash", this);
	connect(pbFlash, SIGNAL(clicked()), this, SLOT(flash()));
	pbRFuse = new QPushButton("Read Fuse", this);
	connect(pbRFuse, SIGNAL(clicked()), this, SLOT(readFuse()));
	pbWFuse = new QPushButton("Write Fuse", this);
	connect(pbWFuse, SIGNAL(clicked()), this, SLOT(writeFuse()));
	pbREEPROM = new QPushButton("Read EEPROM", this);
	connect(pbREEPROM, SIGNAL(clicked()), this, SLOT(readEEPROM()));
	pbWEEPROM = new QPushButton("Write EEPROM", this);
	connect(pbWEEPROM, SIGNAL(clicked()), this, SLOT(writeEEPROM()));
	pbQuit = new QPushButton("Quit", this);
	connect(pbQuit, SIGNAL(clicked()), qApp, SLOT(quit()));

	for (int i = 0; i < 3; i++)
		fuse[i] = new HexByte(fuseType[i], 0, this);

	prog = new Program(task[0][0], task[0][1], 0);

	for (int i = 0; i < 3; i++)
		fuse[i]->setValue(prog->fuse(i));

	setMinimumSize(240, STDH * 7);
}

void Form::read(int i)
{
	delete prog;
	prog = new Program(task[i][0], task[i][1], this);

	for (int i = 0; i < 3; i++)
		fuse[i]->setValue(prog->fuse(i));
}

void Form::make(void)
{
	prog->make();
}

void Form::flash(void)
{
	prog->flash();
}

void Form::jtag(void)
{
	Program::run(CONSOLE "jtag");
}

void Form::uart(void)
{
	Program::run(CONSOLE "\"screen /dev/ttyUSB0 9600\"");
}

void Form::console(void)
{
	Program::run(CONSOLE);
}

void Form::readFuse(void)
{
	prog->readFuse();
	for (int i = 0; i < 3; i++)
		fuse[i]->setValue(prog->fuse(i));
}

void Form::writeFuse(void)
{
	int f[3];
	for (int i = 0; i < 3; i++)
		f[i] = fuse[i]->value();
	prog->setFuse(f);
	prog->writeFuse();
}

void Form::readEEPROM(void)
{
	prog->readEEPROM();
}

void Form::writeEEPROM(void)
{
	prog->writeEEPROM();
}

#define RSH (r->size().height())
#define RSW (r->size().width())
void Form::resizeEvent(QResizeEvent *r)
{
	list->setGeometry(0, 0, RSW, STDH);

	pbMake->setGeometry(0, STDH, RSW / 4, STDH);
	pbUART->setGeometry(RSW / 4, STDH, RSW / 4, STDH);
	pbJTAG->setGeometry(RSW / 2, STDH, RSW / 4, STDH);
	pbConsole->setGeometry(RSW * 3 / 4, STDH, RSW / 4, STDH);

	pbFlash->setGeometry(0, STDH * 2, RSW / 5, STDH);
	pbRFuse->setGeometry(RSW / 5, STDH * 2, RSW / 5, STDH);
	pbWFuse->setGeometry(RSW * 2 / 5, STDH * 2, RSW / 5, STDH);
	pbREEPROM->setGeometry(RSW * 3 / 5, STDH * 2, RSW / 5, STDH);
	pbWEEPROM->setGeometry(RSW * 4 / 5, STDH * 2, RSW / 5, STDH);

	for (int i = 0; i < 3; i++)
		fuse[i]->setGeometry(0, STDH * (3 + i), RSW, STDH);

	pbQuit->setGeometry(0, RSH - STDH, RSW, STDH);
}
