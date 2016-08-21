#include <QApplication>
#include "mainwindow.h"
#include "bcm2835.h"

int main(int argc, char *argv[])
{
	bcm2835_init();
	bcm2835_spi_begin();
	bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_256);	// Approx. 2MHz
	bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
	bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
	bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);

	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	int ret = a.exec();
	bcm2835_spi_end();
	bcm2835_close();
	return ret;
}
