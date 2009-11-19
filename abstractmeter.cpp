#include "abstractmeter.h"

AbstractMeter::AbstractMeter()
	: QWidget(), _min(0), _max(100), _minorTicks(2), _majorTicks(10), _value(50), _warnValue(75), _alarmValue(90), _offset(0)
{
}

AbstractMeter::AbstractMeter(QWidget *parent)
	: QWidget(parent), _min(0), _max(100), _minorTicks(2), _majorTicks(10), _value(50), _warnValue(75), _alarmValue(90), _offset(0)
{
}

AbstractMeter::AbstractMeter(QWidget *parent, qreal min, qreal max)
	: QWidget(parent)
{
	if (min > max)
		qSwap(min, max);

	_min = min;
	_max = max;

	qreal range = _max - _min;
	_minorTicks = range / 50;
	_majorTicks = range / 10;
	_value = 0.5 * range;
	_warnValue = 0.75 * range;
	_alarmValue = 0.9 * range;

	_offset = 0;
}

AbstractMeter::~AbstractMeter()
{
}

void AbstractMeter::setRange(qreal min, qreal max)
{
	if (min > max)
		qSwap(min, max);

	_min = min;
	_max = max;

	_value = qBound(_min, _value, _max);
	_warnValue = qBound(_min, _warnValue, _max);
	_alarmValue = qBound(_min, _warnValue, _max);

	update();
}

void AbstractMeter::setMinimum(qreal min)
{
	setRange(min, _max);
}

qreal AbstractMeter::minimum() const
{
	return _min;
}

void AbstractMeter::setMaximum(qreal max)
{
	setRange(_min, max);
}

qreal AbstractMeter::maximum() const
{
	return _max;
}

void AbstractMeter::setValue(qreal value)
{
	value += _offset;

	_value = qBound(_min, value, _max);
	update();
}

qreal AbstractMeter::value() const
{
	return _value;
}

void AbstractMeter::setValue(int value)
{
	setValue((qreal)value);
}

void AbstractMeter::setAlarmValue(qreal alarm)
{
	_alarmValue = qBound(_min, alarm, _max);
	_warnValue = qBound(_min, _warnValue, _alarmValue);
	update();
}

qreal AbstractMeter::alarmValue() const
{
	return _alarmValue;
}

void AbstractMeter::setWarnValue(qreal warn)
{
	_warnValue = qBound(_min, warn, _max);
	_alarmValue = qBound(_warnValue, _alarmValue, _max);
	update();
}

qreal AbstractMeter::warnValue() const
{
	return _warnValue;
}

void AbstractMeter::setMinorTicks(qreal ticks)
{
	_minorTicks = ticks;
}

qreal AbstractMeter::offset() const
{
	return _offset;
}

void AbstractMeter::setOffset(qreal offset)
{
	_offset = offset;
}

qreal AbstractMeter::minorTicks() const
{
	return _minorTicks;
}

void AbstractMeter::setMajorTicks(qreal ticks)
{
	_majorTicks = ticks;
}

qreal AbstractMeter::majorTicks() const
{
	return _majorTicks;
}
