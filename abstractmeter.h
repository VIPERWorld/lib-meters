#ifndef ABSTRACTMETER_H
#define ABSTRACTMETER_H

#include "libmeters_global.h"

#include <QWidget>

class LIBMETERSSHARED_EXPORT AbstractMeter : public QWidget
{
	Q_OBJECT

public:
	AbstractMeter();
	AbstractMeter(QWidget *parent = 0);
	AbstractMeter(QWidget *parent, qreal min, qreal max);
	~AbstractMeter();

public slots:
	void setValue(qreal value);
	void setValue(int value);
	void setAlarmValue(qreal alarm);
	void setWarnValue(qreal alarm);

	void setRange(qreal min, qreal max);
	void setMinorTicks(qreal ticks);
	void setMajorTicks(qreal ticks);

protected:
	qreal m_min;
	qreal m_max;
	qreal m_minorTicks;
	qreal m_majorTicks;

	qreal m_value;
	qreal m_warnValue;
	qreal m_alarmValue;
};

#endif // ABSTRACTMETER_H
