#ifndef COILMETER_H
#define COILMETER_H

#include "abstractmeter.h"

class LIBMETERSSHARED_EXPORT CoilMeter : public AbstractMeter
{
		Q_OBJECT

public:
	CoilMeter(QWidget *);
	CoilMeter(QWidget *parent, qreal min, qreal max);
	~CoilMeter();

	enum Style{StyleNeedle, StyleBar, StyleGradientBar};

	void setOverlayEnabled(bool enable);
	void setNeedleColors(const QColor& normal, const QColor& warn, const QColor& alarm);
	void setFlowingGradient(bool);
	void setStyle(enum Style);

protected:
	virtual QSize sizeHint() const;
	virtual QSize minimumSizeHint() const;
	virtual QSize minimumSize() const;
	virtual void paintEvent(QPaintEvent *e);
	virtual int heightForWidth(int w) const;

private:
	QColor d_needleColors[3];
	bool d_flowingGradient;

	enum Style d_style;

	bool d_overlayEnabled;

	void init();
	QRect findRect(const QRect& r);
	QRegion constructOverlayRegion(const QRect& rect, int radius);
};

#endif // COILMETER_H
