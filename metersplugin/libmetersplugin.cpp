#include <qglobal.h>
#include <qaction.h>
#include <QtPlugin>
#include <QDesignerFormEditorInterface>
#include <QDesignerFormWindowInterface>
#include <QDesignerFormWindowCursorInterface>
#include <QExtensionManager>
#include <QErrorMessage>

#include "libmetersplugin.h"
#include <coilmeter.h>
#include <horizontalmeter.h>

using namespace DesignerPlugin;

CustomWidgetInterface::CustomWidgetInterface(QObject *parent): 
    QObject(parent),
    d_isInitialized(false)
{
}

bool CustomWidgetInterface::isContainer() const
{
    return false;
}

bool CustomWidgetInterface::isInitialized() const
{
    return d_isInitialized;
}

QIcon CustomWidgetInterface::icon() const
{
    return d_icon;
}

QString CustomWidgetInterface::codeTemplate() const
{
    return d_codeTemplate;
}

QString CustomWidgetInterface::domXml() const
{
    return d_domXml;
}

QString CustomWidgetInterface::group() const
{
    return "LibMeter Widgets";
}

QString CustomWidgetInterface::includeFile() const
{
    return d_include;
}

QString CustomWidgetInterface::name() const
{
    return d_name;
}

QString CustomWidgetInterface::toolTip() const
{
    return d_toolTip;
}

QString CustomWidgetInterface::whatsThis() const
{
    return d_whatsThis;
}

void CustomWidgetInterface::initialize(
    QDesignerFormEditorInterface *formEditor)
{
    if ( d_isInitialized )
        return;

    d_isInitialized = true;
}

/***********************************************************************/

CoilMeterInterface::CoilMeterInterface(QObject *parent):
    CustomWidgetInterface(parent)
{
    d_name = "CoilMeter";
    d_include = "coilmeter.h";
    d_icon = QPixmap(":/images/coilmeter.png");
    d_domXml = 
            "<widget class=\"CoilMeter\" name=\"coilMeter\">\n"
            "</widget>\n";
}

QWidget *CoilMeterInterface::createWidget(QWidget *parent)
{
    return new CoilMeter(parent);
}

/************************************************************************/

HorizontalMeterInterface::HorizontalMeterInterface(QObject *parent):
    CustomWidgetInterface(parent)
{
    d_name = "HorizontalMeter";
    d_include = "horizontalmeter.h";
    d_icon = QPixmap(":/images/horizontalmeter.png");
    d_domXml =
            "<widget class=\"HorizontalMeter\" name=\"horizontalMeter\">\n"
            "</widget>\n";
}

QWidget *HorizontalMeterInterface::createWidget(QWidget *parent)
{
    return new HorizontalMeter(parent);
}

/***************************************************************/

CustomWidgetCollectionInterface::CustomWidgetCollectionInterface(   
    QObject *parent):
    QObject(parent)
{
    d_plugins.append(new CoilMeterInterface(this));
    d_plugins.append(new HorizontalMeterInterface(this));
}

QList<QDesignerCustomWidgetInterface*> 
CustomWidgetCollectionInterface::customWidgets(void) const
{
    return d_plugins;
}

/***************************************************************/

Q_EXPORT_PLUGIN2(DesignerPlugin, CustomWidgetCollectionInterface)

