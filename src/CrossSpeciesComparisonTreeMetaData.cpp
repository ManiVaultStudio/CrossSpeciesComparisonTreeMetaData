#include "CrossSpeciesComparisonTreeMetaData.h"
#include "InfoAction.h"
#include <Application.h>
#include <util/Serialization.h>
#include <QtCore>
#include <QtDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QStringList>
#include <algorithm>
#include <iostream>
#include <iostream>
#include <QJsonDocument>
#include <QJsonValue>

Q_PLUGIN_METADATA(IID "nl.BioVault.CrossSpeciesComparisonTreeMetaData")

using namespace mv;



CrossSpeciesComparisonTreeMetaData::~CrossSpeciesComparisonTreeMetaData(void)
{

}

void CrossSpeciesComparisonTreeMetaData::init()
{


}



QString extractPropertyNames(QJsonObject _data) {
    QStringList finalStringList;

    // Get the keys of the main object
    QStringList mainKeys = _data.keys();

    if (!mainKeys.isEmpty()) {
        // Get the first inner object
        QJsonObject innerObject = _data.value(mainKeys.first()).toObject();

        // Iterate over the keys of the inner object
        for (const QString& innerKey : innerObject.keys()) {
            QJsonObject innerInnerObject = innerObject.value(innerKey).toObject();
            QStringList keys = innerInnerObject.keys();

            // Add the keys to the final string
            finalStringList.append(innerKey + ": " + keys.join(", "));
        }
    }

    // Join the final string list with newlines
    QString finalString = finalStringList.join("\n\n");

    return finalString;
}


QStringList extractLeafNames(const QJsonObject& jsonObj) {
    QStringList keys = jsonObj.keys();
    return keys;
}



Dataset<DatasetImpl> CrossSpeciesComparisonTreeMetaData::createDataSet(const QString& guid /*= ""*/) const
{
    auto dataset = Dataset<DatasetImpl>(new CrossSpeciesComparisonTreeMeta(getName(), true, guid));
    return dataset;
}


void CrossSpeciesComparisonTreeMetaData::setTreeMetaDataRaw(QJsonObject jsonString)
{
    //sortJsonObject(jsonString);

    
    //qDebug() << "**************************************************";
    _data = jsonString;
    _leafNames.clear();
    _leafNames = extractLeafNames(_data);
    _leafNames.sort();
    _propertyNames = "";
    _propertyNames = extractPropertyNames(_data);

    //std::cout<< "Species names: " << _speciesNames.join(", ").toStdString() << std::endl;
    //qDebug() << "**************************************************";
}

void CrossSpeciesComparisonTreeMetaData::setTreeMetaLeafNamesRaw(QStringList jsonString)
{
    _leafNames = jsonString;
}

QJsonObject& CrossSpeciesComparisonTreeMetaData::getTreeMetaDataRaw()
{
    return _data;
}

QStringList& CrossSpeciesComparisonTreeMetaData::getTreeMetaLeafNamesRaw()
{
    return _leafNames;
}

QString& CrossSpeciesComparisonTreeMetaData::getTreeMetaPropertyNamesRaw()
{
    return _propertyNames;
}

QIcon CrossSpeciesComparisonTreeMetaDataFactory::getIcon(const QColor& color /*= Qt::black*/) const
{
    return Application::getIconFont("FontAwesome").getIcon("table", color);
}

mv::plugin::RawData* CrossSpeciesComparisonTreeMetaDataFactory::produce()
{
    return new CrossSpeciesComparisonTreeMetaData(this);
}

void CrossSpeciesComparisonTreeMeta::init()
{
    _infoAction = QSharedPointer<InfoAction>::create(nullptr, *this);

    addAction(*_infoAction.get());

}

QIcon CrossSpeciesComparisonTreeMeta::getIcon(const QColor& color /*= Qt::black*/) const
{
    return Application::getIconFont("FontAwesome").getIcon("sitemap", color);
}

std::vector<std::uint32_t>& CrossSpeciesComparisonTreeMeta::getSelectionIndices()
{
    return getSelection<CrossSpeciesComparisonTreeMeta>()->indices;
}

void CrossSpeciesComparisonTreeMeta::setSelectionIndices(const std::vector<std::uint32_t>& indices)
{
}

bool CrossSpeciesComparisonTreeMeta::canSelect() const
{
    return false;
}

bool CrossSpeciesComparisonTreeMeta::canSelectAll() const
{
    return false;
}

bool CrossSpeciesComparisonTreeMeta::canSelectNone() const
{
    return false;
}

bool CrossSpeciesComparisonTreeMeta::canSelectInvert() const
{
    return false;
}

void CrossSpeciesComparisonTreeMeta::selectAll()
{
}

void CrossSpeciesComparisonTreeMeta::selectNone()
{
}

void CrossSpeciesComparisonTreeMeta::selectInvert()
{
}

void CrossSpeciesComparisonTreeMeta::setTreeMetaData(QJsonObject jsonString)
{
    //qDebug() << "%%3ItsSetting3%%";
    getRawData<CrossSpeciesComparisonTreeMetaData>()->setTreeMetaDataRaw(jsonString);
    //qDebug()<< "jsonString"<<jsonString;
    //qDebug() << "%%3ItsSetting3%%";
    //getRawData<CrossSpeciesComparisonTreeMetaData>()->changed();
}
void CrossSpeciesComparisonTreeMeta::setTreeMetaLeafNames(QStringList jsonString)
{
    getRawData<CrossSpeciesComparisonTreeMetaData>()->setTreeMetaLeafNamesRaw(jsonString);
}
QJsonObject& CrossSpeciesComparisonTreeMeta::getTreeMetaData()
{
    return  getRawData<CrossSpeciesComparisonTreeMetaData>()->getTreeMetaDataRaw();// TODO: insert return statement here
}

QStringList& CrossSpeciesComparisonTreeMeta::getTreeMetaLeafNames()
{
    return  getRawData<CrossSpeciesComparisonTreeMetaData>()->getTreeMetaLeafNamesRaw();// TODO: insert return statement here
}

QString& CrossSpeciesComparisonTreeMeta::getTreeMetaPropertyNames()
{
    return  getRawData<CrossSpeciesComparisonTreeMetaData>()->getTreeMetaPropertyNamesRaw();// TODO: insert return statement here
}

void CrossSpeciesComparisonTreeMeta::fromVariantMap(const QVariantMap& variantMap)
{


}

QVariantMap CrossSpeciesComparisonTreeMeta::toVariantMap() const
{
    return QVariantMap();
}
