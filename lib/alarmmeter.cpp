#include "alarmmeter.h"

AlarmMeter::AlarmMeter(QWidget *parent)
	: AbstractMeter(parent)
{
	init();
}

AlarmMeter::AlarmMeter(QWidget *parent, qreal min, qreal max)
	: AbstractMeter(parent, min, max)
{
	init();
}

AlarmMeter::~AlarmMeter()
{
}

void AlarmMeter::init()
{
	_valueColor = QColor(0, 255, 0, 127);
	_warnColor  = QColor(255, 255, 0, 127);
	_alarmColor = QColor(255, 0, 0, 127);
}

void AlarmMeter::setValueColor(QColor c)
{
	_valueColor = c;
}

QColor AlarmMeter::valueColor() const
{
	return _valueColor;
}

void AlarmMeter::setWarnColor(QColor c)
{
	_warnColor = c;
}

QColor AlarmMeter::warnColor() const
{
	return _warnColor;
}

void AlarmMeter::setAlarmColor(QColor c)
{
	_alarmColor = c;
}

QColor AlarmMeter::alarmColor() const
{
	return _alarmColor;
}

