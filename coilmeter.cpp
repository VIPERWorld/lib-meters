#include "coilmeter.h"

#include <QPainter>
#include <cmath>

CoilMeter::CoilMeter(QWidget *parent)
	: AbstractMeter(parent)
{
	init();
}

CoilMeter::CoilMeter(QWidget *parent, qreal min, qreal max)
	: AbstractMeter(parent, min, max)
{
	init();
}

CoilMeter::~CoilMeter()
{
}

void CoilMeter::init()
{
	QSizePolicy s(QSizePolicy::Preferred, QSizePolicy::Preferred);
	s.setHeightForWidth(true);
	setSizePolicy(s);

	_valueColor = QColor(0, 255, 0, 127);
	_warnColor  = QColor(255, 255, 0, 127);
	_alarmColor = QColor(255, 0, 0, 127);

	_overlayEnabled = true;

	_style = StyleBar;
}

QSize CoilMeter::sizeHint() const
{
	return QSize(320, 240);
}

QSize CoilMeter::minimumSizeHint() const
{
	return QSize(120, 90);
}

QSize CoilMeter::minimumSize() const
{
	return QSize(80, 6);
}

int CoilMeter::heightForWidth(int w) const
{
	return (w * 3) / 4;
}

void CoilMeter::setValueColor(QColor c)
{
	_valueColor = c;
}

QColor CoilMeter::valueColor() const
{
	return _valueColor;
}

void CoilMeter::setWarnColor(QColor c)
{
	_warnColor = c;
}

QColor CoilMeter::warnColor() const
{
	return _warnColor;
}

void CoilMeter::setAlarmColor(QColor c)
{
	_alarmColor = c;
}

QColor CoilMeter::alarmColor() const
{
	return _alarmColor;
}

void CoilMeter::setNeedleStyle(enum NeedleStyle style)
{
	_style = style;
	update();
}

enum CoilMeter::NeedleStyle CoilMeter::needleStyle() const
{
	return _style;
}

void CoilMeter::setOverlayEnabled(bool enable)
{
	_overlayEnabled = enable;
	update();
}

bool CoilMeter::overlayEnabled() const
{
	return _overlayEnabled;
}

void CoilMeter::setFlowingGradient(bool b)
{
	_flowingGradient = b;
	update();
}

QRect CoilMeter::findRect(const QRect& r)
{
	int w = r.width();
	int h = r.height();

	// scale the rect to 4:3 aspect ratio
	h = qMin(h, (3 * w) / 4);
	w = (4 * h) / 3;

	// center the rect and return it
	return(QRect((r.width() - w) / 2, (r.height() - h) / 2, w, h));
}

void CoilMeter::paintEvent(QPaintEvent *e)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	// findest the biggest possible centered rect with an aspect ratio of 4:3
	// that fits within current width and height
	QRect r = findRect(QRect(0, 0, width(), height()));
	painter.setViewport(r);
	painter.setWindow(-200, -150, 400, 300);

	int cornerRadius = 10;
	// draw housing
	painter.setBrush(palette().alternateBase());
	painter.drawRoundRect(-200, -150, 400, 300, cornerRadius, cornerRadius);

	// draw scale background
	painter.setBrush(palette().base());
	QRect scaleBackgroundRect(-180, -130, 360, 190);
	painter.drawRoundRect(scaleBackgroundRect, cornerRadius, cornerRadius);
	qreal vcenter = 55;

	// the rest (except the overlay) is draw a bit larger to match the proportions of an analog meter
	painter.save();
	painter.translate(0, 60);
	painter.scale(4.0/3.0, 4.0/3.0);

	// draw start and stop ticks
	painter.save();

	QFont font = painter.font();
	font.setPixelSize(14);
	painter.setFont(font);

	painter.setBrush(palette().windowText());
	painter.rotate(-60);
	painter.drawLine(0, -130, 0 , -110);
	painter.drawText(-10, -105, 20, 20, Qt::AlignHCenter | Qt::AlignTop, QString::number(minimum()));
	painter.rotate(120);
	painter.drawLine(0, -130, 0 , -110);
	painter.drawText(-10, -105, 20, 20, Qt::AlignHCenter | Qt::AlignTop, QString::number(maximum()));
	painter.restore();

	// draw minor ticks
	painter.save();
	painter.setBrush(palette().windowText());
	painter.rotate(-60);
	qreal x = minimum();
	qreal angle = (maximum() - minimum()) / minorTicks();
	angle = 120 / angle;
	while (x <= maximum()) {
		painter.drawLine(0, -130, 0 , -120);
		painter.rotate(angle);
		x += minorTicks();
	}
	painter.restore();

	// draw major ticks
	painter.save();
	painter.setBrush(palette().windowText());
	painter.rotate(-60);
	x = minimum();
	angle = (maximum() - minimum()) / majorTicks();
	angle = 120 / angle;
	while (x <= maximum()) {
		painter.drawLine(0, -130, 0 , -110);
		painter.rotate(angle);
		x += majorTicks();
	}
	painter.restore();

	// draw value
	if (_style == StyleNeedle) {
		painter.save();

		angle = ((120 * (value() - minimum())) / (maximum() - minimum())) - 60;
		painter.rotate(angle);

		painter.setClipRect(-200, -150, 400, 120);

		if (value() < warnValue())
			painter.setBrush(QBrush(_valueColor));
		else if (value() >= warnValue() && value() < alarmValue())
			painter.setBrush(QBrush(_warnColor));
		else
			painter.setBrush(QBrush(_alarmColor));

		painter.setPen(Qt::PenStyle());
		static const int needle[3][2] = {{-15, (int)vcenter}, {0, -130}, {15, (int)vcenter}};
		painter.drawPolygon(QPolygon(3, &needle[0][0]));
		painter.restore();
	} else {
		painter.save();

		angle = ((120 * (value() - minimum())) / (maximum() - minimum()));

		if (_style == StyleBar) {
			QPen pen;
			if (value() < warnValue())
				pen.setColor(_valueColor);
			else if (value() >= warnValue() && value() < alarmValue())
				pen.setColor(_warnColor);
			else
				pen.setColor(_alarmColor);

			pen.setWidth(15);
			pen.setCapStyle(Qt::FlatCap);
			painter.setPen(pen);
			painter.drawArc(QRectF(-sqrtf(-123 * -123), -123, 2 * sqrtf(-123 * -123), 246), 150 * 16, (int)(-angle * 16));

			QFont font = painter.font();
			font.setPixelSize(20);
			font.setBold(true);
			painter.setFont(font);
			painter.drawText(-50, -65, 100, 50, Qt::AlignCenter, QString::number(value(), 'f', 1));
			painter.restore();

		} else if (_style == StyleGradientBar) {
			QConicalGradient grad(0, 0, 30);
			// calculate the gradient stops for warn and alarm level
			qreal alarm = (alarmValue() - minimum()) / (maximum() - minimum());
			alarm = 0.333 - alarm * 0.333;
			qreal warn = (warnValue() - minimum()) / (maximum() - minimum());
			warn = 0.333 - warn * 0.333;

			if (_flowingGradient) {
				grad.setColorAt(0, _alarmColor);
				grad.setColorAt(alarm, _alarmColor);
				grad.setColorAt(warn, _warnColor);
				grad.setColorAt(0.333, _valueColor);
			} else {
				grad.setColorAt(0, _alarmColor);
				grad.setColorAt(alarm - 0.000000000001, _alarmColor);
				grad.setColorAt(alarm, _warnColor);
				grad.setColorAt(warn - 0.0000000000001, _warnColor);
				grad.setColorAt(warn, _valueColor);
				grad.setColorAt(0.333, _valueColor);
			}

			QPen pen;
			pen.setWidth(15);
			pen.setCapStyle(Qt::FlatCap);
			pen.setBrush(QBrush(grad));painter.setPen(pen);
			painter.drawArc(QRectF(-sqrtf(-123 * -123), -123, 2 * sqrtf(-123 * -123), 246), 150 * 16, (int)(-angle * 16));

			if (value() < warnValue())
				pen.setColor(_valueColor);
			else if (value() >= warnValue() && value() < alarmValue())
				pen.setColor(_warnColor);
			else
				pen.setColor(_alarmColor);
			painter.setPen(pen);

			QFont font = painter.font();
			font.setPixelSize(20);
			font.setBold(true);
			painter.setFont(font);
			painter.drawText(-50, -65, 100, 50, Qt::AlignCenter, QString::number(value(), 'f', 1));
			painter.restore();
		}
	}

	// draw needle origin
	if (_style == StyleNeedle) {
		painter.save();
		painter.setBrush(palette().alternateBase());
		painter.setClipRect(-60, -60, 120, 60);
		painter.drawEllipse(QRectF(-40, -40, 80, 80));
		painter.restore();
	}

	painter.restore();
	// draw overlay
	if (_overlayEnabled) {
		QRegion region = constructOverlayRegion(scaleBackgroundRect, cornerRadius);
		painter.setClipRegion(region);

		QLinearGradient g(0, 0, 1, 1);
		g.setCoordinateMode(QGradient::ObjectBoundingMode);
		g.setColorAt(0, QColor(255, 255, 255, 127));
		g.setColorAt(0.5, QColor(255, 255, 255, 0));
		QBrush b(g);
		painter.fillRect(scaleBackgroundRect, b);
	}
}

static QRegion roundedRectRegion(const QRect& rect, int r)
{
	QRegion region;
	// middle and borders
	region += rect.adjusted(r, 0, -r, 0);
	region += rect.adjusted(0, r, 0, -r);
	// top left
	QRect corner(rect.topLeft(), QSize(r*2, r*2));
	region += QRegion(corner, QRegion::Ellipse);
	// top right
	corner.moveTopRight(rect.topRight());
	region += QRegion(corner, QRegion::Ellipse);
	// bottom left
	corner.moveBottomLeft(rect.bottomLeft());
	region += QRegion(corner, QRegion::Ellipse);
	// bottom right
	corner.moveBottomRight(rect.bottomRight());
	region += QRegion(corner, QRegion::Ellipse);
	return region;
}

QRegion CoilMeter::constructOverlayRegion(const QRect& rect, int radius)
{
	QRegion region = roundedRectRegion(rect, radius);

	QRect ellipseRect = rect.adjusted(rect.width() / 20, rect.height() / 10, rect.width(), rect.height());
	QRegion ellipseRegion(ellipseRect,QRegion::Ellipse);
	return region.subtracted(ellipseRegion);
}
