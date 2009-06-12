#ifndef COILMETER_H
#define COILMETER_H

#include "abstractmeter.h"

class LIBMETERSSHARED_EXPORT CoilMeter : public AbstractMeter
{
	Q_OBJECT

	Q_PROPERTY(QColor valueColor READ valueColor WRITE setValueColor)
	Q_PROPERTY(QColor warnColor READ warnColor WRITE setWarnColor)
	Q_PROPERTY(QColor alarmColor READ alarmColor WRITE setAlarmColor)

	Q_PROPERTY(NeedleStyle needleStyle READ needleStyle WRITE setNeedleStyle)
	Q_ENUMS(NeedleStyle)

	Q_PROPERTY(bool overlayEnabled READ overlayEnabled WRITE setOverlayEnabled)

public:
	CoilMeter(QWidget *);
	CoilMeter(QWidget *parent, qreal min, qreal max);
	~CoilMeter();

	enum NeedleStyle{StyleNeedle, StyleBar, StyleGradientBar};

	void setOverlayEnabled(bool enable);
	void setFlowingGradient(bool);
	void setNeedleStyle(enum NeedleStyle);

	QColor valueColor() const;
	QColor warnColor() const;
	QColor alarmColor() const;

	bool overlayEnabled() const;

	enum NeedleStyle needleStyle() const;

public slots:
	void setValueColor(QColor);
	void setWarnColor(QColor);
	void setAlarmColor(QColor);

protected:
	virtual QSize sizeHint() const;
	virtual QSize minimumSizeHint() const;
	virtual QSize minimumSize() const;
	virtual void paintEvent(QPaintEvent *e);
	virtual int heightForWidth(int w) const;

private:
	QColor _valueColor;
	QColor _warnColor;
	QColor _alarmColor;

	bool _flowingGradient;

	enum NeedleStyle _style;

	bool _overlayEnabled;

	void init();
	QRect findRect(const QRect& r);
	QRegion constructOverlayRegion(const QRect& rect, int radius);
};

#endif // COILMETER_H
