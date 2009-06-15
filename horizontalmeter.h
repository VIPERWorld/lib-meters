#ifndef HORIZONTALSCALE_H
#define HORIZONTALSCALE_H

#include <QtGui/QWidget>

#include "alarmmeter.h"

class LIBMETERSSHARED_EXPORT HorizontalMeter : public AlarmMeter
{
    Q_OBJECT

public:
	HorizontalMeter(QWidget *parent = 0);
	HorizontalMeter(QWidget *parent, qreal min, qreal max);
	~HorizontalMeter();

	enum Style{StyleNeedle, StyleBar, StyleGradientBar};

	void setMargin(int margin);
	void setMarginColor(const QColor &color);
	void setOverlayEnabled(bool enable);
	void setMarginEnabled(bool enable);
	void setFlowingGradient(bool);

	void setStyle(enum Style);

protected:
	virtual QSize sizeHint() const;
	virtual QSize minimumSizeHint() const;
	virtual QSize minimumSize() const;
	virtual void paintEvent(QPaintEvent *e);

private:
	int _margin;
	QColor _marginColor;

	enum Style _style;

	bool _overlayEnabled;
	bool _marginEnabled;

	bool _flowingGradient;

	void init();
};

#endif // HORIZONTALSCALE_H
