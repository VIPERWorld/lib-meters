#include "abstractmeter.h"


AbstractMeter::AbstractMeter()
	: QWidget(), m_min(0), m_max(100), m_minorTicks(2), m_majorTicks(10), m_value(50), m_warnValue(75), m_alarmValue(90)
{
}

AbstractMeter::AbstractMeter(QWidget *parent)
	: QWidget(parent), m_min(0), m_max(100), m_minorTicks(2), m_majorTicks(10), m_value(50), m_warnValue(75), m_alarmValue(90)
{
}

AbstractMeter::AbstractMeter(QWidget *parent, qreal min, qreal max)
	: QWidget(parent)
{
	if (min > max)
		qSwap(min, max);

	m_min = min;
	m_max = max;

	qreal range = max - min;
	m_minorTicks = range / 50;
	m_majorTicks = range / 10;
	m_value = 0.5 * range;
	m_warnValue = 0.75 * range;
	m_alarmValue = 0.9 * range;
}

AbstractMeter::~AbstractMeter()
{
}

void AbstractMeter::setRange(qreal min, qreal max)
{
	if (min > max)
		qSwap(min, max);

	m_min = min;
	m_max = max;

	m_value = qBound(min, m_value, max);
	m_warnValue = qBound(min, m_value, max);
	m_alarmValue = qBound(min, m_value, max);

	update();
}

void AbstractMeter::setValue(qreal value)
{
	m_value = qBound(m_min, value, m_max);
	update();
}

void AbstractMeter::setValue(int value)
{
	setValue((qreal)value);
}

void AbstractMeter::setAlarmValue(qreal alarm)
{
	m_alarmValue = qBound(m_min, alarm, m_max);
	update();
}

void AbstractMeter::setWarnValue(qreal warn)
{
	m_warnValue = qBound(m_min, warn, m_max);
	update();
}

void AbstractMeter::setMinorTicks(qreal ticks)
{
	m_minorTicks = ticks;
}

void AbstractMeter::setMajorTicks(qreal ticks)
{
	m_majorTicks = ticks;
}
