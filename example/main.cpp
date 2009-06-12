#include <QtGui/QApplication>
#include <QWidget>
#include <coilmeter.h>
#include "main.h"
#include <cmath>

Widget::Widget(QWidget * parent) : QWidget(parent)
{
	needle = new CoilMeter(this, -50, 20);
	bar = new CoilMeter(this, -50, 20);
	gradBar = new CoilMeter(this, -50, 20);
	flowBar = new CoilMeter(this, -50, 20);
#if 0
	hneedle = new HorizontalScale(this, -50, 20);
	hbar = new HorizontalScale(this, -50, 20);
	hgradBar = new HorizontalScale(this, -50, 20);
	hflowBar = new HorizontalScale(this, -50, 20);

	hneedle->setMargin(20);
	hneedle->setStyle(HorizontalScale::StyleNeedle);
	hneedle->setAlarmValue(15);
	hneedle->setWarnValue(-20);

	hbar->setMargin(20);
	hbar->setStyle(HorizontalScale::StyleBar);
	hbar->setAlarmValue(15);
	hbar->setWarnValue(-20);

	hgradBar->setMargin(20);
	hgradBar->setStyle(HorizontalScale::StyleGradientBar);
	hgradBar->setAlarmValue(15);
	hgradBar->setWarnValue(-20);

	hflowBar->setMargin(20);
	hflowBar->setStyle(HorizontalScale::StyleGradientBar);
	hflowBar->setAlarmValue(15);
	hflowBar->setWarnValue(-20);

	QPalette p = hneedle->palette();
	QLinearGradient g1(0, 0, 1, 1);
	g1.setCoordinateMode(QGradient::ObjectBoundingMode);
	g1.setColorAt(0, Qt::lightGray);
	g1.setColorAt(1, Qt::darkGray);
	QBrush b1(g1);
	p.setBrush(hneedle->backgroundRole(), b1);

	hneedle->setPalette(p);
	hbar->setPalette(p);
	hgradBar->setPalette(p);
	hflowBar->setPalette(p);
	hneedle->setAutoFillBackground(true);
	hbar->setAutoFillBackground(true);
	hgradBar->setAutoFillBackground(true);
	hflowBar->setAutoFillBackground(true);
	hgradBar->setFlowingGradient(false);
	hflowBar->setFlowingGradient(true);

	vlayout = new QVBoxLayout();
	vlayout->addWidget(hneedle);
	vlayout->addWidget(hbar);
	vlayout->addWidget(hgradBar);
	vlayout->addWidget(hflowBar);
#endif
	layout = new QGridLayout();
	layout->addWidget(needle, 0, 0);
	layout->addWidget(bar, 0, 1);
	layout->addWidget(gradBar, 1, 0);
	layout->addWidget(flowBar, 1, 1);

	hlayout = new QHBoxLayout(this);
	hlayout->addLayout(layout);
//	hlayout->addLayout(vlayout);

	needle->setValue(-5);
	bar->setValue(-5);
	gradBar->setValue(-5);
	flowBar->setValue(-5);

	timer = new QTimer(this);

	QPalette p2 = palette();
	QLinearGradient g2(0, 0, 1, 1);
	g2.setCoordinateMode(QGradient::ObjectBoundingMode);
	g2.setColorAt(0, Qt::lightGray);
	g2.setColorAt(1, QColor(Qt::darkGray).darker());
	QBrush b2(g2);
	p2.setBrush(QPalette::AlternateBase, b2);

	QLinearGradient g3(0, 0, 1, 1);
	g3.setCoordinateMode(QGradient::ObjectBoundingMode);
	g3.setColorAt(0, QColor(255, 255, 0).lighter());
	g3.setColorAt(1, QColor(255, 0, 0).lighter());
	QBrush b3(g3);
	p2.setBrush(QPalette::Base, b2);
	p2.setColor(QPalette::Base, Qt::black);

	p2.setColor(QPalette::WindowText, QColor(Qt::white).darker());

	needle->setPalette(p2);
	bar->setPalette(p2);
	gradBar->setPalette(p2);
	flowBar->setPalette(p2);

	QObject::connect(timer, SIGNAL(timeout()), this, SLOT(updateScales()));

	needle->setNeedleStyle(CoilMeter::StyleNeedle);
	needle->setWarnValue(0);
	needle->setAlarmValue(15);
	needle->setMajorTicks(10);
	needle->setMinorTicks(2);
	needle->setValue(0);

	bar->setNeedleStyle(CoilMeter::StyleBar);
	bar->setWarnValue(-20);
	bar->setAlarmValue(15);
	bar->setMajorTicks(10);
	bar->setMinorTicks(2);
	bar->setValue(0);

	gradBar->setNeedleStyle(CoilMeter::StyleGradientBar);
	gradBar->setWarnValue(-20);
	gradBar->setAlarmValue(15);
	gradBar->setMajorTicks(10);
	gradBar->setMinorTicks(2);
	gradBar->setValue(0);
	gradBar->setFlowingGradient(false);

	flowBar->setNeedleStyle(CoilMeter::StyleGradientBar);
	flowBar->setWarnValue(-20);
	flowBar->setAlarmValue(15);
	flowBar->setMajorTicks(10);
	flowBar->setMinorTicks(2);
	flowBar->setValue(0);
	flowBar->setFlowingGradient(true);

	timer->start(10);
}

#include <QDebug>
void Widget::updateScales()
{
	static int degree = 0;
	qreal value = 70 * sinf(degree * (3.14159 / 180));
	value /= 2;
	value -= 15;

	needle->setValue(value);
	bar->setValue(value);
	gradBar->setValue(value);
	flowBar->setValue(value);
	//hneedle->setValue(value);
	//hbar->setValue(value);
	//hgradBar->setValue(value);
	//hflowBar->setValue(value);

	degree += 5;
	degree %= 360;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	Widget w(NULL);
	w.show();
	return a.exec();
}


