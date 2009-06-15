#ifndef ALARMMETER_H
#define ALARMMETER_H

#include "abstractmeter.h"

class LIBMETERSSHARED_EXPORT AlarmMeter : public AbstractMeter
{
	Q_OBJECT
	Q_PROPERTY(QColor valueColor READ valueColor WRITE setValueColor)
	Q_PROPERTY(QColor warnColor READ warnColor WRITE setWarnColor)
	Q_PROPERTY(QColor alarmColor READ alarmColor WRITE setAlarmColor)

public:
	AlarmMeter(QWidget *);
	AlarmMeter(QWidget *parent, qreal min, qreal max);
	~AlarmMeter();

	QColor valueColor() const;
	QColor warnColor() const;
	QColor alarmColor() const;

public slots:
	void setValueColor(QColor);
	void setWarnColor(QColor);
	void setAlarmColor(QColor);

private:
	QColor _valueColor;
	QColor _warnColor;
	QColor _alarmColor;

	void init();
};

#endif // ALARMMETER_H
