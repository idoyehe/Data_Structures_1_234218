#include "library2.h"
#include "colosseum.h"

using namespace colosseum;
void* init(int n, int *trainingGroupsIDs){
    if(trainingGroupsIDs == nullptr || n < 2){
        return nullptr;
    }
    for(int i=0; i< n;++i){
        if(trainingGroupsIDs[i] < 0){
            return nullptr;
        }
    }
    try {
        Colosseum *DS = new Colosseum(n,trainingGroupsIDs);
        return (void *) DS;
    } catch (const std::bad_alloc &) {
        return nullptr;
    }
}

StatusType addTrainingGroup(void *DS, int trainingGroupID){
    if (DS == nullptr){
        return INVALID_INPUT;
    }
    return  (StatusType) ((Colosseum *) DS)->addTrainingGroup(trainingGroupID);

}

StatusType addGladiator(void *DS, int gladiatorID, int score, int trainingGroup){
    if (DS == nullptr){
        return INVALID_INPUT;
    }
    return  (StatusType)((Colosseum*)DS)->addGladiator(gladiatorID,score,trainingGroup);

}

StatusType trainingGroupFight(void *DS, int trainingGroup1, int trainingGroup2, int k1, int k2){
    if (DS == nullptr){
        return INVALID_INPUT;
    }
    return  (StatusType)((Colosseum*)DS)->trainingGroupFight(trainingGroup1,
                                                             trainingGroup2,k1,k2);

}

StatusType getMinTrainingGroup(void *DS, int *trainingGroup) {
    if (DS == nullptr) {
        return INVALID_INPUT;
    }
    return (StatusType) ((Colosseum *) DS)->getMinTrainingGroup(trainingGroup);
}

void quit(void** DS) {
    if(DS == nullptr){
        return;
    }
    delete((Colosseum*)*DS);
    *DS=nullptr;
}
