#ifndef HORIZONTALSCALE_H
#define HORIZONTALSCALE_H

#include <QtGui/QWidget>

#include "alarmmeter.h"

class LIBMETERSSHARED_EXPORT HorizontalMeter : public AlarmMeter
{
    Q_OBJECT
	Q_PROPERTY(NeedleStyle needleStyle READ needleStyle WRITE setNeedleStyle)
	Q_ENUMS(NeedleStyle)

	Q_PROPERTY(bool overlayEnabled READ overlayEnabled WRITE setOverlayEnabled)
	Q_PROPERTY(bool marginEnabled READ marginEnabled WRITE setMarginEnabled)
	Q_PROPERTY(QColor marginColor READ marginColor WRITE setMarginColor)

public:
	HorizontalMeter(QWidget *parent = 0);
	HorizontalMeter(QWidget *parent, qreal min, qreal max);
	~HorizontalMeter();

	enum NeedleStyle{StyleNeedle, StyleBar, StyleFixedGradient, StyleFlowGradient};

	void setMargin(int margin);
	void setMarginColor(const QColor &color);
	QColor marginColor() const;
	void setMarginEnabled(bool enable);
	bool marginEnabled() const;

	void setOverlayEnabled(bool enable);
	bool overlayEnabled() const;

	void setFlowingGradient(bool);

	void setNeedleStyle(enum NeedleStyle);
	enum NeedleStyle needleStyle() const;

protected:
	virtual QSize sizeHint() const;
	virtual QSize minimumSizeHint() const;
	virtual QSize minimumSize() const;
	virtual void paintEvent(QPaintEvent *e);

private:
	int _margin;
	QColor _marginColor;

	enum NeedleStyle _style;

	bool _overlayEnabled;
	bool _marginEnabled;

	void init();
};

#endif // HORIZONTALSCALE_H
