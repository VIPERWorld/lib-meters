#ifndef QWT_DESIGNER_PLUGIN_H
#define QWT_DESIGNER_PLUGIN_H

#include <qglobal.h>

#include <QDesignerCustomWidgetInterface>
#include <QDesignerTaskMenuExtension>
#include <QExtensionFactory>

namespace DesignerPlugin
{

class CustomWidgetInterface: public QObject, 
        public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    CustomWidgetInterface(QObject *parent);

    virtual bool isContainer() const;
    virtual bool isInitialized() const;
    virtual QIcon icon() const;
    virtual QString codeTemplate() const;
    virtual QString domXml() const;
    virtual QString group() const;
    virtual QString includeFile() const;
    virtual QString name() const;
    virtual QString toolTip() const;
    virtual QString whatsThis() const;
    virtual void initialize(QDesignerFormEditorInterface *);

protected:
    QString d_name; 
    QString d_include; 
    QString d_toolTip; 
    QString d_whatsThis; 
    QString d_domXml; 
    QString d_codeTemplate;
    QIcon d_icon;

private:
    bool d_isInitialized;
};

class CustomWidgetCollectionInterface: public QObject,
        public QDesignerCustomWidgetCollectionInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)

public:
    CustomWidgetCollectionInterface(QObject *parent = NULL);

    virtual QList<QDesignerCustomWidgetInterface*> customWidgets() const;

private:
    QList<QDesignerCustomWidgetInterface*> d_plugins;
};


class CoilMeterInterface: public CustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    CoilMeterInterface(QObject *parent);
    virtual QWidget *createWidget(QWidget *parent);
};

class HorizontalMeterInterface: public CustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    HorizontalMeterInterface(QObject *parent);
    virtual QWidget *createWidget(QWidget *parent);
};

};



#endif

