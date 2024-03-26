#pragma once

#include "Dataset.h"
#include "CrossSpeciesComparisonTreeMetaData.h"


#include "actions/StringAction.h"
#include "event/EventListener.h"

namespace mv {
    class CoreInterface;
}

using namespace mv;
using namespace mv::gui;
using namespace mv::util;


class InfoAction : public GroupAction
{
    Q_OBJECT

public:


    InfoAction(QObject* parent, CrossSpeciesComparisonTreeMeta& clusters);

public: // Action getters

    StringAction& getTreeMetaInfoAction() { return _TreeMetaInfoAction; }
    StringAction& getLeafInfoAction() { return _leafInfoAction; }

protected:
    Dataset<CrossSpeciesComparisonTreeMeta>       _clusters;                  /** Clusters dataset smart pointer */
    StringAction    _TreeMetaInfoAction;
    StringAction    _leafInfoAction;

    mv::EventListener     _eventListener;             /** Listen to HDPS events */
};