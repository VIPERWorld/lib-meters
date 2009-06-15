#include "horizontalmeter.h"

#include <QPainter>

HorizontalMeter::HorizontalMeter(QWidget *parent)
	: AbstractMeter(parent)
{
	init();
}

HorizontalMeter::HorizontalMeter(QWidget *parent, qreal min, qreal max)
	: AbstractMeter(parent, min, max)
{
	init();
}

HorizontalMeter::~HorizontalMeter()
{
}

void HorizontalMeter::init()
{
	QSizePolicy sp(QSizePolicy::Preferred, QSizePolicy::Fixed);
	sp.setHeightForWidth(true);
	setSizePolicy(sp);

	_margin = 10;
	_marginColor = Qt::black;

	_needleColors[0] = QColor(0, 255, 0, 127);
	_needleColors[1] = QColor(255, 255, 0, 127);
	_needleColors[2] = QColor(255, 0, 0, 127);

	_overlayEnabled = true;
	_marginEnabled = true;

	_style = StyleBar;
}

QSize HorizontalMeter::sizeHint() const
{
	return QSize(400, 80);
}

QSize HorizontalMeter::minimumSizeHint() const
{
	return QSize(200, 40);
}

QSize HorizontalMeter::minimumSize() const
{
	return QSize(120, 40);
}

void HorizontalMeter::setNeedleColors(const QColor& normal, const QColor& warn, const QColor& alarm)
{
	_needleColors[0] = normal;
	_needleColors[1] = warn;
	_needleColors[2] = alarm;
}

void HorizontalMeter::setStyle(enum Style style)
{
	_style = style;
	update();
}

void HorizontalMeter::setMargin(int margin)
{
	_margin = margin < 0 ? 0 : margin;
	update();
}

void HorizontalMeter::setMarginColor(const QColor &color)
{
	_marginColor = color;
	update();
}

void HorizontalMeter::setOverlayEnabled(bool enable)
{
	_overlayEnabled = enable;
}

void HorizontalMeter::setFlowingGradient(bool b)
{
	_flowingGradient = b;
}

void HorizontalMeter::setMarginEnabled(bool enable)
{
	_marginEnabled = enable;
}

void HorizontalMeter::paintEvent(QPaintEvent *e)
{
	// map the range to the geometry of the widget
	QMatrix matrix;
	matrix.scale((qreal)width() / (qreal)(maximum() - minimum()), 1);
	matrix.translate(-minimum(), 0);

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setViewport(2 * _margin, _margin, width() - 4 * _margin, height() - 2 * _margin);
	QPen pen;
	pen.setColor(palette().color(foregroundRole()));
	pen.setCosmetic(true);
	pen.setWidth(1);
	painter.setPen(pen);

	QFont f = font();
	f.setPointSize(12);
	painter.setFont(f);

	// draw minor ticks
	QLineF line;
	qreal x = minimum();
	while (x <= maximum()) {
		line.setLine(x, 0, x, 0.33 * height());
		line = matrix.map(line);
		painter.drawLine(line);
		x += minorTicks();
	}

	// draw major ticks and labels
	pen.setWidth(3);
	painter.setPen(pen);
	x = minimum();
	while (x <= maximum()) {
		line.setLine(x, 0, x, 0.70 * height());
		line = matrix.map(line);
		painter.drawLine(line);

		QRectF r(x - majorTicks() /2, 0.80 * height(), majorTicks(), 0.30 * height());
		r.setTopLeft(matrix.map(r.topLeft()));
		r.setBottomRight(matrix.map(r.bottomRight()));

		QFont f	= font();
		f.setPointSize(15);
		painter.setFont(f);

		painter.drawText(r, Qt::AlignCenter, QString::number(x));

		x += majorTicks();
	}

	// draw value
	if (_style == StyleBar) {
		QPointF p1(minimum(), 0);
		QPointF p2(value(), 0.6 * height());
		p1 = matrix.map(p1);
		p2 = matrix.map(p2);
		QRectF r(p1, p2);
		QColor color;
		if (value() < warnValue())
			color = _needleColors[0];
		else if (value() >= warnValue() && value() < alarmValue())
			color = _needleColors[1];
		else
			color = _needleColors[2];

		painter.fillRect(r, color);

	} else if (_style == StyleNeedle) {
		if (value() < warnValue())
			pen.setColor(_needleColors[0]);
		else if (value() >= warnValue() && value() < alarmValue())
			pen.setColor(_needleColors[1]);
		else
			pen.setColor(_needleColors[2]);
		pen.setWidth(5);
		painter.setPen(pen);
		line.setLine(value(), 0, value(), 0.6 * height());
		line = matrix.map(line);
		painter.drawLine(line);
	} else if (_style == StyleGradientBar) {
		painter.save();
		QPointF p1(minimum(), 0);
		QPointF p2(value(), 0.6 * height());
		QPointF p3(maximum(), 0.6 * height());

		p1 = matrix.map(p1);
		p2 = matrix.map(p2);
		p3 = matrix.map(p3);

		QRectF rVal(p1, p2);
		QRectF r(p1, p3);

		QLinearGradient g(0, 0.5, 1, 0.5);
		g.setCoordinateMode(QGradient::ObjectBoundingMode);
		qreal warn = (warnValue() - minimum()) / (maximum() - minimum());
		qreal alarm = (alarmValue() - minimum()) / (maximum() - minimum());

		if (_flowingGradient) {
			g.setColorAt(0, _needleColors[0]);
			g.setColorAt(warn, _needleColors[1]);
			g.setColorAt(alarm, _needleColors[2]);
			g.setColorAt(1, _needleColors[2]);
		}
		else {
			g.setColorAt(0, _needleColors[0]);
			g.setColorAt(warn - 0.00001, _needleColors[0]);
			g.setColorAt(warn, _needleColors[1]);
			g.setColorAt(alarm - 0.0001, _needleColors[1]);
			g.setColorAt(alarm, _needleColors[2]);
			g.setColorAt(1, _needleColors[2]);
		}

		painter.setClipRect(rVal);
		painter.fillRect(r, QBrush(g));
		painter.restore();
	}

	// draw frame
	if (_marginEnabled) {
		painter.setViewport(QRect(0, 0, width(), height()));
		pen.setColor(_marginColor);
		pen.setWidth(_margin);
		painter.setPen(pen);
		painter.drawRect(painter.viewport());
	}

	// draw overlay
	if (_overlayEnabled) {
		painter.setViewport(QRect(0, 0, width(), height()));
		QLinearGradient g(width() / 2, 0, width() / 2, 1);
		g.setCoordinateMode(QGradient::ObjectBoundingMode);
		g.setColorAt(0, QColor(255, 255, 255, 64));
		g.setColorAt(0.25, QColor(255, 255, 255, 127));
		g.setColorAt(0.5, QColor(255, 255, 255, 0));
		QBrush b(g);
		painter.fillRect(painter.viewport(), b);
	}
}

