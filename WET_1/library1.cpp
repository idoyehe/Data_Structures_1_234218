#include "library1.h"
#include "colosseum.h"

using namespace colosseum;

	void* Init() {
        try {
            Colosseum *DS = new Colosseum();
            return (void *) DS;
        } catch (const std::bad_alloc &) {
            return NULL;
        }
    }
	StatusType AddTrainer(void *DS, int trainerID) {
        if(DS == NULL) {
            return (StatusType)INVALID_INPUT;
        }
        return (StatusType)((Colosseum*)DS)->addTrainer(trainerID);
    }

	StatusType BuyGladiator(void *DS,int gladiatorID, int trainerID, int level) {
        if(DS == NULL) {
            return (StatusType) INVALID_INPUT;
        }
        return (StatusType)((Colosseum*)DS)->buyGladiator(gladiatorID,trainerID,level);
    }

	StatusType FreeGladiator(void *DS, int gladiatorID) {
        if (DS == NULL) {
            return (StatusType) INVALID_INPUT;
        }
        return (StatusType)((Colosseum *) DS)->freeGladiator(gladiatorID);
    }

	StatusType LevelUp(void *DS, int gladiatorID, int levelIncrease) {
        if(DS == NULL) {
            return (StatusType) INVALID_INPUT;
        }
        return (StatusType)((Colosseum*)DS)->levelUp(gladiatorID,levelIncrease);
    }

	StatusType UpgradeGladiator(void *DS, int gladiatorID, int upgradedID) {
        if (DS == NULL) {
            return (StatusType) INVALID_INPUT;
        }
        return (StatusType)((Colosseum *) DS)->upgradeGladiator(gladiatorID, upgradedID);
    }

	StatusType GetTopGladiator(void *DS, int trainerID, int *gladiatorID) {
        if(DS == NULL) {
            return (StatusType) INVALID_INPUT;
        }
        return (StatusType)((Colosseum*)DS)->getTopGladiator(trainerID,gladiatorID);
    }


StatusType GetAllGladiatorsByLevel(void *DS, int trainerID, int **gladiators,
                                   int *numOfGladiator) {
    if(DS == NULL) {
        return (StatusType) INVALID_INPUT;
    }
    return (StatusType)((Colosseum*)DS)->getAllGladiatorsByLevel(trainerID,gladiators,
                                                     numOfGladiator);
}

	StatusType UpdateLevels(void *DS, int stimulantCode, int stimulantFactor) {
        if(DS == NULL) {
            return (StatusType) INVALID_INPUT;
        }
        return(StatusType) ((Colosseum*)DS)->updateLevels(stimulantCode,stimulantFactor);
    }
	void Quit(void** DS) {
        if(DS == NULL){
            return;
        }
        delete((Colosseum*)*DS);
        *DS=NULL;
    }
