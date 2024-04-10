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


void CrossSpeciesComparisonTreeMetaData::fromVariantMap(const QVariantMap& variantMap)
{
    /*variantMapMustContain(variantMap, "CrossSpeciesComparisonTreeMetaInfo");
    variantMapMustContain(variantMap, "LeafInfo");
    variantMapMustContain(variantMap, "PropertyInfo");

    const auto data = variantMap["CrossSpeciesComparisonTreeMetaInfo"].toMap();
    const auto numberOfPoints = static_cast<size_t>(variantMap["LeafInfo"].toInt());
    const auto numberOfDimensions = variantMap["PropertyInfo"].toUInt();


    const auto elementTypeIndex = static_cast<CrossSpeciesComparisonTreeMetaData::ElementTypeSpecifier>(data["TypeIndex"].toInt());
    const auto rawData = data["Raw"].toMap();


    setElementTypeSpecifier(elementTypeIndex);
    resizeVector(numberOfElements);
    populateDataBufferFromVariantMap(rawData, (char*)getDataVoidPtr());
    _numDimensions = numberOfDimensions;
    */
}

QVariantMap CrossSpeciesComparisonTreeMetaData::toVariantMap() const
{
    QVariantMap rawData;
    /*
    const auto typeSpecifier = getElementTypeSpecifier();
    const auto typeSpecifierName = getElementTypeNames()[static_cast<std::int32_t>(typeSpecifier)];
    const auto typeIndex = static_cast<std::int32_t>(typeSpecifier);
    const auto numberOfElements = getNumberOfElements();

    QVariantMap rawData = rawDataToVariantMap((const char*)getDataConstVoidPtr(), getRawDataSize(), true);

    return {
        { "TypeIndex", QVariant::fromValue(typeIndex) },
        { "TypeName", QVariant(typeSpecifierName) },
        { "Raw", QVariant::fromValue(rawData) },
        { "NumberOfElements", QVariant::fromValue(numberOfElements) }
    };
    */
    return rawData;
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
    return Application::getIconFont("FontAwesome").getIcon("table", color);
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
    /*
    DatasetImpl::fromVariantMap(variantMap);

    variantMapMustContain(variantMap, "DimensionNames");
    variantMapMustContain(variantMap, "Selection");

    // For backwards compatibility, check PluginVersion
    if (variantMap["PluginVersion"] == "No Version" && !variantMap["Full"].toBool())
    {
        makeSubsetOf(getParent()->getFullDataset<mv::DatasetImpl>());

        qWarning() << "[ManiVault deprecation warning]: This project was saved with an older ManiVault version (<1.0). "
            "Please save the project again to ensure compatibility with newer ManiVault versions. "
            "Future releases may not be able to load this projects otherwise. ";
    }

    // Load raw point data
    if (isFull())
        getRawData<PointData>()->fromVariantMap(variantMap);
    else
    {
        variantMapMustContain(variantMap, "Indices");

        const auto& indicesMap = variantMap["Indices"].toMap();

        indices.resize(indicesMap["Count"].toInt());

        populateDataBufferFromVariantMap(indicesMap["Raw"].toMap(), (char*)indices.data());
    }

    // Load dimension names
    QStringList dimensionNameList;
    std::vector<QString> dimensionNames;

    // Fetch dimension names from map
    const auto fetchDimensionNames = [&variantMap]() -> QStringList {
        QStringList dimensionNames;

        // Dimension names in byte array format
        QByteArray dimensionsByteArray;

        // Copy the dimension names raw data into the byte array
        dimensionsByteArray.resize(variantMap["DimensionNames"].toMap()["Size"].value<std::uint64_t>());
        populateDataBufferFromVariantMap(variantMap["DimensionNames"].toMap(), (char*)dimensionsByteArray.data());

        // Open input data stream
        QDataStream dimensionsDataStream(&dimensionsByteArray, QIODevice::ReadOnly);

        // Stream the data to the dimension names
        dimensionsDataStream >> dimensionNames;

        return dimensionNames;
        };

    if (variantMap["NumberOfDimensions"].toInt() > 1000)
        dimensionNameList = fetchDimensionNames();
    else
        dimensionNameList = variantMap["DimensionNames"].toStringList();

    if (dimensionNameList.size() == getNumDimensions())
    {
        for (const auto& dimensionName : dimensionNameList)
            dimensionNames.push_back(dimensionName);
    }
    else
    {
        for (std::uint32_t dimensionIndex = 0; dimensionIndex < getNumDimensions(); dimensionIndex++)
            dimensionNames.emplace_back(QString("Dim %1").arg(QString::number(dimensionIndex)));
    }

    setDimensionNames(dimensionNames);

    if (variantMap.contains("Dimensions")) {
        _dimensionsPickerAction->fromParentVariantMap(variantMap);
    }

    events().notifyDatasetDataChanged(this);

    // Handle saved selection
    if (isFull()) {
        const auto& selectionMap = variantMap["Selection"].toMap();

        const auto count = selectionMap["Count"].toInt();

        if (count > 0) {
            auto selectionSet = getSelection<Points>();

            selectionSet->indices.resize(count);

            populateDataBufferFromVariantMap(selectionMap["Raw"].toMap(), (char*)selectionSet->indices.data());

            events().notifyDatasetDataSelectionChanged(this);
        }
    }
    */
}

QVariantMap CrossSpeciesComparisonTreeMeta::toVariantMap() const
{
    QVariantMap variantMap;
    /*
    auto variantMap = DatasetImpl::toVariantMap();

    QStringList dimensionNames;
    QByteArray dimensionsByteArray;
    QDataStream dimensionsDataStream(&dimensionsByteArray, QIODevice::WriteOnly);

    if (getDimensionNames().size() == getNumDimensions()) {
        for (const auto& dimensionName : getDimensionNames())
            dimensionNames << dimensionName;
    }
    else {
        for (std::uint32_t dimensionIndex = 0; dimensionIndex < getNumDimensions(); dimensionIndex++)
            dimensionNames << QString("Dim %1").arg(QString::number(dimensionIndex));
    }

    if (dimensionNames.size() > 1000)
        dimensionsDataStream << dimensionNames;

    QVariantMap indices;

    indices["Count"] = QVariant::fromValue(this->indices.size());
    indices["Raw"] = rawDataToVariantMap((char*)this->indices.data(), this->indices.size() * sizeof(std::uint32_t), true);

    QVariantMap selection;

    if (isFull()) {
        auto selectionSet = getSelection<Points>();

        selection["Count"] = QVariant::fromValue(selectionSet->indices.size());
        selection["Raw"] = rawDataToVariantMap((char*)selectionSet->indices.data(), selectionSet->indices.size() * sizeof(std::uint32_t), true);
    }

    variantMap["Data"] = isFull() ? getRawData<PointData>()->toVariantMap() : QVariantMap();
    variantMap["NumberOfPoints"] = getNumPoints();
    variantMap["Indices"] = indices;
    variantMap["Selection"] = selection;
    variantMap["DimensionNames"] = (dimensionNames.size() > 1000) ? rawDataToVariantMap((char*)dimensionsByteArray.data(), dimensionsByteArray.size(), true) : QVariant::fromValue(dimensionNames);
    variantMap["NumberOfDimensions"] = getNumDimensions();
    variantMap["Dimensions"] = _dimensionsPickerAction->toVariantMap();
    */
    return variantMap;
}
