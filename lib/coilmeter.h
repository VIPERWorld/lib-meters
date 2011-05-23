#ifndef COILMETER_H
#define COILMETER_H

#include "alarmmeter.h"

#include <QTimer>

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

    void setPrecision(int);
    int precision();

    void setUnit(const QString&);

    bool overlayEnabled() const;

    enum NeedleStyle needleStyle() const;

    virtual int heightForWidth(int w) const;

    void setHousingFont(QFont& f) {_housingFont = f;}
    void setHousingText(const QString& s) {_housingText = s;}

protected:
    virtual QSize sizeHint() const;
    virtual QSize minimumSizeHint() const;
    virtual QSize minimumSize() const;
    virtual void paintEvent(QPaintEvent *e);

private:
    enum NeedleStyle _style;

    bool _overlayEnabled;

    int _precision;
    QString _unit;

    QFont _housingFont;
    QString _housingText;

    void init();
    QRect findRect(const QRect& r);
    QRegion constructOverlayRegion(const QRect& rect, int radius);

    QTimer offsetFontTimer;
    QColor _offsetColor;
    bool _offsetOdd;

private slots:
    void setOffsetFontColor();
};

#endif // COILMETER_H
