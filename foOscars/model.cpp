#include "model.h"

Model::Model() {
    std::cout <<"getting into model constructor " <<std::endl;
    //
    CardFunction funcTuple(1,1,1,addPointsFromActionCard);
    actionMap.insert(std::pair<int, CardFunction>(0,funcTuple));
}

void Model::addPointsFromActionCard(int scoreModification, int unused1, int unused2)
{
    std::cout << "modifying score by : " << scoreModification << std::endl;
}

void Model::addPointsForColor(int color, int scoreModification, int unused1)
{
    std::cout << "adding : " << scoreModification << " to all cards at color index: " << color << std::endl;
}

void Model::decreaseOtherPlayerPoints(int victimPlayerIndex, int scoreModification, int unused1)
{
    std::cout << "removing: " << scoreModification << " points from player at index: " << victimPlayerIndex << std::endl;
}

void Model::modelTestMethod()
{
    std::cout << "getting into modelTest MEthod " << std::endl;
    int* params = actionMap.at(0).parameters;
    std::cout << " getting past parameter cast " << std::endl;
    auto func = actionMap.at(0).function;

    func(params[0], params[1], params[2]);
}


