#ifndef COILMETER_H
#define COILMETER_H

#include "abstractmeter.h"

class LIBMETERSSHARED_EXPORT CoilMeter : public AbstractMeter
{
public:
	CoilMeter(QWidget *);
};

#endif // COILMETER_H
