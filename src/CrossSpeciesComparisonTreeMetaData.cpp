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
    /*WidgetAction::fromVariantMap(variantMap);

    const auto dataMap = variantMap["Data"].toMap();

    variantMapMustContain(dataMap, "IndicesRawData");
    variantMapMustContain(dataMap, "NumberOfIndices");

    // Packed indices for all clusters
    QVector<std::uint32_t> packedIndices;

    packedIndices.resize(dataMap["NumberOfIndices"].toInt());

    // Convert raw data to indices
    populateDataBufferFromVariantMap(dataMap["IndicesRawData"].toMap(), (char*)packedIndices.data());

    if (dataMap.contains("ClustersRawData")) {
        QByteArray clustersByteArray;

        QDataStream clustersDataStream(&clustersByteArray, QIODevice::ReadOnly);

        const auto clustersRawDataSize = dataMap["ClustersRawDataSize"].toInt();

        clustersByteArray.resize(clustersRawDataSize);

        populateDataBufferFromVariantMap(dataMap["ClustersRawData"].toMap(), (char*)clustersByteArray.data());
        
        QVariantList clusters;

        clustersDataStream >> clusters;

        _clusters.resize(clusters.count());

        long clusterIndex = 0;

        for (const auto& clusterVariant : clusters) {
            const auto clusterMap = clusterVariant.toMap();

            auto& cluster = _clusters[clusterIndex];

            cluster.setName(clusterMap["Name"].toString());
            cluster.setId(clusterMap["ID"].toString());
            cluster.setColor(clusterMap["Color"].toString());

            const auto globalIndicesOffset = clusterMap["GlobalIndicesOffset"].toInt();
            const auto numberOfIndices = clusterMap["NumberOfIndices"].toInt();

            cluster.getIndices() = std::vector<std::uint32_t>(packedIndices.begin() + globalIndicesOffset, packedIndices.begin() + globalIndicesOffset + numberOfIndices);

            ++clusterIndex;
        }
    }

    // For backwards compatibility
    if (dataMap.contains("Clusters")) {
        const auto clustersList = dataMap["Clusters"].toList();

        _clusters.resize(clustersList.count());

        for (const auto& clusterVariant : clustersList) {
            const auto clusterMap = clusterVariant.toMap();
            const auto clusterIndex = clustersList.indexOf(clusterMap);

            auto& cluster = _clusters[clusterIndex];

            cluster.setName(clusterMap["Name"].toString());
            cluster.setId(clusterMap["ID"].toString());
            cluster.setColor(clusterMap["Color"].toString());

            const auto globalIndicesOffset = clusterMap["GlobalIndicesOffset"].toInt();
            const auto numberOfIndices = clusterMap["NumberOfIndices"].toInt();

            cluster.getIndices() = std::vector<std::uint32_t>(packedIndices.begin() + globalIndicesOffset, packedIndices.begin() + globalIndicesOffset + numberOfIndices);
        }
    }
    */
}

QVariantMap CrossSpeciesComparisonTreeMetaData::toVariantMap() const
{
    auto variantMap = WidgetAction::toVariantMap();
   /*
    std::vector<std::uint32_t> indices;

    for (const auto& cluster : _clusters)
        indices.insert(indices.end(), cluster.getIndices().begin(), cluster.getIndices().end());

    QVariantMap indicesRawData = rawDataToVariantMap((char*)indices.data(), indices.size() * sizeof(std::uint32_t), true);

    std::size_t globalIndicesOffset = 0;

    QVariantList clusters;

    clusters.reserve(_clusters.count());

    for (const auto& cluster : _clusters) {
        const auto numberOfIndicesInCluster = cluster.getIndices().size();

        clusters.push_back(QVariantMap({
            { "Name", cluster.getName() },
            { "ID", cluster.getId() },
            { "Color", cluster.getColor() },
            { "GlobalIndicesOffset", QVariant::fromValue(globalIndicesOffset) },
            { "NumberOfIndices", QVariant::fromValue(numberOfIndicesInCluster) }
            }));

        globalIndicesOffset += numberOfIndicesInCluster;
    }

    // https://stackoverflow.com/questions/19537186/serializing-qvariant-through-qdatastream

    QByteArray clustersByteArray;
    QDataStream clustersDataStream(&clustersByteArray, QIODevice::WriteOnly);

    clustersDataStream << clusters;

    QVariantMap clustersRawData = rawDataToVariantMap((char*)clustersByteArray.data(), clustersByteArray.size(), true);

    variantMap.insert({
        { "ClustersRawData", clustersRawData },
        { "ClustersRawDataSize", clustersByteArray.size() },
        { "IndicesRawData", indicesRawData },
        { "NumberOfIndices", QVariant::fromValue(indices.size()) }
        });
        */
    return variantMap;
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
    /*DatasetImpl::fromVariantMap(variantMap);

    getRawData<CrossSpeciesComparisonTreeMetaData>()->fromVariantMap(variantMap);

    events().notifyDatasetDataChanged(this);*/

}

QVariantMap CrossSpeciesComparisonTreeMeta::toVariantMap() const
{
    auto variantMap = DatasetImpl::toVariantMap();
    /*
    variantMap["Data"] = getRawData<CrossSpeciesComparisonTreeMetaData>()->toVariantMap();
    */
    return variantMap;
}
