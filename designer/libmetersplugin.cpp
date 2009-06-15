
#include <coilmeter.h>
#include <horizontalmeter.h>
#include "libmetersplugin.h"

#include <QtPlugin>

CoilMeterPlugin::CoilMeterPlugin(QObject *parent)
        : QObject(parent)
{
    initialized = false;
}

void CoilMeterPlugin::initialize(QDesignerFormEditorInterface *)
{
    if (initialized)
        return;

    initialized = true;
}

bool CoilMeterPlugin::isInitialized() const
{
    return initialized;
}

QWidget *CoilMeterPlugin::createWidget(QWidget *parent)
{
	return new CoilMeter(parent);
}

QString CoilMeterPlugin::name() const
{
	return "CoilMeterPlugin";
}

QString CoilMeterPlugin::group() const
{
    return "bitwigglers.org";
}

QIcon CoilMeterPlugin::icon() const
{
    return QIcon(":battmeter.png");
}

QString CoilMeterPlugin::toolTip() const
{
    return "";
}

QString CoilMeterPlugin::whatsThis() const
{
    return "";
}

bool CoilMeterPlugin::isContainer() const
{
    return false;
}

QString CoilMeterPlugin::domXml() const
{
	return "<widget class=\"CoilMeter\" name=\"coilmeter\">\n"
           " <property name=\"geometry\">\n"
           "  <rect>\n"
           "   <x>0</x>\n"
           "   <y>0</y>\n"
           "   <width>200</width>\n"
           "   <height>30</height>\n"
           "  </rect>\n"
           " </property>\n"
           " <property name=\"toolTip\" >\n"
		   "  <string>Coil Meter</string>\n"
           " </property>\n"
           " <property name=\"whatsThis\" >\n"
		   "  <string>Coil Meter</string>\n"
           " </property>\n"
           " </widget>\n";
}

QString CoilMeterPlugin::includeFile() const
{
	return "coilmeter.h";
}

Q_EXPORT_PLUGIN2(customwidgetplugin, CoilMeterPlugin)

/**************************************************************************/

HorizontalMeterPlugin::HorizontalMeterPlugin(QObject *parent)
		: QObject(parent)
{
	initialized = false;
}

void HorizontalMeterPlugin::initialize(QDesignerFormEditorInterface *)
{
	if (initialized)
		return;

	initialized = true;
}

bool HorizontalMeterPlugin::isInitialized() const
{
	return initialized;
}

QWidget* HorizontalMeterPlugin::createWidget(QWidget *parent)
{
	return new HorizontalMeter(parent);
}

QString HorizontalMeterPlugin::name() const
{
	return "HorizontalMeterPlugin";
}

QString HorizontalMeterPlugin::group() const
{
	return "bitwigglers.org";
}

QIcon HorizontalMeterPlugin::icon() const
{
	return QIcon(":battmeter.png");
}

QString HorizontalMeterPlugin::toolTip() const
{
	return "";
}

QString HorizontalMeterPlugin::whatsThis() const
{
	return "";
}

bool HorizontalMeterPlugin::isContainer() const
{
	return false;
}

QString HorizontalMeterPlugin::domXml() const
{
	return "<widget class=\"CoilMeter\" name=\"coilmeter\">\n"
		   " <property name=\"geometry\">\n"
		   "  <rect>\n"
		   "   <x>0</x>\n"
		   "   <y>0</y>\n"
		   "   <width>200</width>\n"
		   "   <height>30</height>\n"
		   "  </rect>\n"
		   " </property>\n"
		   " <property name=\"toolTip\" >\n"
		   "  <string>Coil Meter</string>\n"
		   " </property>\n"
		   " <property name=\"whatsThis\" >\n"
		   "  <string>Coil Meter</string>\n"
		   " </property>\n"
		   " </widget>\n";
}

QString HorizontalMeterPlugin::includeFile() const
{
	return "coilmeter.h";
}

//Q_EXPORT_PLUGIN2(customwidgetplugin, HorizontalMeterPlugin)

