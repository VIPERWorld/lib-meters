#ifndef ABSTRACTMETER_H
#define ABSTRACTMETER_H

#include "libmeters_global.h"

#include <QWidget>

class LIBMETERSSHARED_EXPORT AbstractMeter : public QWidget
{
	Q_OBJECT
	Q_PROPERTY(qreal minimum READ minimum WRITE setMinimum)
	Q_PROPERTY(qreal maximum READ maximum WRITE setMaximum)
	Q_PROPERTY(qreal value READ value  WRITE setValue)
	Q_PROPERTY(qreal warnValue READ warnValue WRITE setWarnValue)
	Q_PROPERTY(qreal alarmValue READ alarmValue WRITE setAlarmValue)
	Q_PROPERTY(qreal minorTicks READ minorTicks WRITE setMinorTicks)
	Q_PROPERTY(qreal majorTicks READ majorTicks WRITE setMajorTicks)

public:
	AbstractMeter();
	AbstractMeter(QWidget *parent = 0);
	AbstractMeter(QWidget *parent, qreal min, qreal max);
	~AbstractMeter();

	qreal value() const;
	qreal warnValue() const;
	qreal alarmValue() const;
	qreal minorTicks() const;
	qreal majorTicks() const;
	qreal minimum() const;
	qreal maximum() const;

public slots:
	void setValue(qreal value);
	void setValue(int value);
	void setAlarmValue(qreal alarm);
	void setWarnValue(qreal alarm);

	void setRange(qreal min, qreal max);
	void setMinorTicks(qreal ticks);
	void setMajorTicks(qreal ticks);

	void setMinimum(qreal min);
	void setMaximum(qreal max);

private:
	qreal _min;
	qreal _max;
	qreal _minorTicks;
	qreal _majorTicks;

	qreal _value;
	qreal _warnValue;
	qreal _alarmValue;
};

#endif // ABSTRACTMETER_H
