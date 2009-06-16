#ifndef COILMETER_H
#define COILMETER_H

#include "alarmmeter.h"

class LIBMETERSSHARED_EXPORT CoilMeter : public AlarmMeter
{
	Q_OBJECT

	Q_PROPERTY(NeedleStyle needleStyle READ needleStyle WRITE setNeedleStyle)
	Q_ENUMS(NeedleStyle)
	Q_PROPERTY(bool overlayEnabled READ overlayEnabled WRITE setOverlayEnabled)

public:
	CoilMeter(QWidget *);
	CoilMeter(QWidget *parent, qreal min, qreal max);
	~CoilMeter();

	enum NeedleStyle{StyleNeedle, StyleBar, StyleFixedGradient, StyleFlowGradient};

	void setOverlayEnabled(bool enable);
	void setNeedleStyle(enum NeedleStyle);

	bool overlayEnabled() const;

	enum NeedleStyle needleStyle() const;

protected:
	virtual QSize sizeHint() const;
	virtual QSize minimumSizeHint() const;
	virtual QSize minimumSize() const;
	virtual void paintEvent(QPaintEvent *e);
	virtual int heightForWidth(int w) const;

private:
	enum NeedleStyle _style;

	bool _overlayEnabled;

	void init();
	QRect findRect(const QRect& r);
	QRegion constructOverlayRegion(const QRect& rect, int radius);
};

#endif // COILMETER_H
