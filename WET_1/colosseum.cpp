#include "colosseum.h"

#define NO_GLAD_IN_TREE -1

using namespace colosseum;

        Colosseum::Colosseum() : allGladByID(NULL), allGladByLEVEL(NULL), allTrainersByID(NULL){
                try {
                        allGladByID = new SplayTree<GladiatorByID>();
                        allGladByLEVEL = new SplayTree<GladiatorByLevel>();
                        allTrainersByID = new SplayTree<Trainer> ();
                }catch (const std::bad_alloc&) {
                        delete (allGladByID);
                        delete (allGladByLEVEL);
                        delete (allTrainersByID);
                        throw std::bad_alloc();
                }
        }


        Colosseum::~Colosseum(){
                delete (allGladByID);
                delete (allGladByLEVEL);
                delete (allTrainersByID);
        }

        StatusColosseum Colosseum::addTrainer(const int& trainerID) {
                if (trainerID <= 0) return  COLO_INVALID_INPUT;
                try {
                        Trainer newTrainer(trainerID);
                        StatusTree result=this->allTrainersByID->insertKey
                                (newTrainer);
                    return (StatusColosseum)result;
                } catch (const std::bad_alloc &) {
                        return COLO_ALLOCATION_ERROR;
                }
        }

        StatusColosseum Colosseum::buyGladiator(const int & gladiatorID,const int & trainerID, const int & level){
                if(gladiatorID <= 0 || level <= 0 || trainerID <= 0){
                        return COLO_INVALID_INPUT;
                }
                GladiatorByID duplicateGladiator(gladiatorID);
                if(allGladByID->find(duplicateGladiator) == TREE_SUCCESS){//gladiator already exist on the system
                        return COLO_FAILURE;
                }
                Trainer duplicateTrainer(trainerID);
                if(allTrainersByID->find(duplicateTrainer) == TREE_FAILURE){//trainer does NOT  exist on the system
                        return COLO_FAILURE;
                }

                Trainer* trainerOfGladiator=allTrainersByID->getRootRef();//get
                // the requested trainer
                assert(trainerOfGladiator->getId() == trainerID);

                GladiatorByLevel gladToAdd(gladiatorID,level,trainerOfGladiator);
                //create requested gladiator
                if(allGladByID->insertKey(gladToAdd) == TREE_ALLOCATION_ERROR){
                        return COLO_ALLOCATION_ERROR;
                }
                if(allGladByLEVEL->insertKey(gladToAdd) == TREE_ALLOCATION_ERROR){
                        allGladByID->deleteKey(gladToAdd);
                        return COLO_ALLOCATION_ERROR;
                }
                if(trainerOfGladiator->buyGladiator(gladToAdd) ==
                        TRAINER_ALLOCATION_ERROR){
                        allGladByID->deleteKey(gladToAdd);
                        allGladByLEVEL->deleteKey(gladToAdd);
                        return COLO_ALLOCATION_ERROR;
                }
                return COLO_SUCCESS;
        }


    StatusColosseum Colosseum::freeGladiator(const int &gladiatorID) {
        if(gladiatorID <= 0){
            return COLO_INVALID_INPUT;;
        }
        GladiatorByID duplicateKey(gladiatorID);
        if(this->allGladByID->find(duplicateKey)==TREE_FAILURE){
            return COLO_FAILURE;
        }
        GladiatorByID toRemove1(this->allGladByID->getRoot());
        GladiatorByLevel toRemove2(toRemove1);
        assert(toRemove1.getId()==gladiatorID);
#ifndef NDEBUG
        StatusTree  res1 =
#endif
                this->allGladByID->deleteKey(toRemove1);
        assert(res1 == TREE_SUCCESS);
#ifndef NDEBUG
          res1 =
#endif
                this->allGladByLEVEL->deleteKey(toRemove2);
        assert(res1 == TREE_SUCCESS);
        Trainer* gladTrainer=(Trainer*)toRemove2.getTrainer();
#ifndef NDEBUG
        StatusTrainer res2 =
#endif
                gladTrainer->freeGladiator(toRemove2);
        assert(res2 == TRAINER_SUCCESS);
        return COLO_SUCCESS;
    }




StatusColosseum Colosseum::levelUp(const int &gladiatorID,
                              const int &levelIncrease) {
    if (gladiatorID <= 0 || levelIncrease <= 0)
        return COLO_INVALID_INPUT;;

    GladiatorByID duplicateKey(gladiatorID);
    if (this->allGladByID->find(duplicateKey)==TREE_FAILURE)
        return COLO_FAILURE;

    GladiatorByID newGladiator(this->allGladByID->getRoot());
    assert(newGladiator.getId() == gladiatorID);
    newGladiator.levelUp(levelIncrease);
    Trainer* trainer = ((Trainer*)newGladiator.getTrainer());

#ifndef  NDEBUG
    StatusColosseum res =
#endif
            this->freeGladiator(gladiatorID);
    assert(res == COLO_SUCCESS);

    if(this->allGladByID->insertKey(newGladiator) == TREE_ALLOCATION_ERROR){
        return COLO_ALLOCATION_ERROR;
    }

    if(this->allGladByLEVEL->insertKey(newGladiator) == TREE_ALLOCATION_ERROR){
        return COLO_ALLOCATION_ERROR;
    }

    if(trainer->buyGladiator(newGladiator) == TRAINER_ALLOCATION_ERROR){
        return COLO_ALLOCATION_ERROR;
    }
    return COLO_SUCCESS;
}

StatusColosseum Colosseum::getAllGladiatorsByLevel(const int& trainerID,
                                 int**gladiators, int*numOfGladiators) {
    if (gladiators == NULL || numOfGladiators == NULL || trainerID == 0) {
        return COLO_INVALID_INPUT;;
    }
    if (trainerID > 0) {
        Trainer duplicateTrainer(trainerID);
        if (this->allTrainersByID->find(duplicateTrainer) == TREE_FAILURE) {
            return COLO_FAILURE;//case no exist trainerId in the system
        }
        const Trainer* requestedTrainer(allTrainersByID->getRootRef());
        assert(requestedTrainer->getId() == trainerID);
        return (StatusColosseum)requestedTrainer->getAllGladiatorsByLevel
                (gladiators,numOfGladiators);
    }
    assert(trainerID < 0);
    *numOfGladiators = this->allGladByLEVEL->getSize();
    if (this->allGladByLEVEL->isEmpty()) {
        *gladiators = NULL;
        return COLO_SUCCESS;
    }

    try {
        GladiatorByLevel *allGlad = new GladiatorByLevel[*numOfGladiators];
        this->allGladByLEVEL->treeToArr(allGlad);
        *gladiators = (int *) malloc(
                sizeof(int)*(*numOfGladiators));//as requested in PDF allocating by malloc
        if (*gladiators == NULL) {
            delete[](allGlad);
            return COLO_ALLOCATION_ERROR;
        }
        for (int i = 0; i < (*numOfGladiators); ++i) {
            (*gladiators)[i] = allGlad[(*numOfGladiators) - i - 1].getId();
            //insert backwards
        }
        delete[](allGlad);
        return COLO_SUCCESS;
    }   catch (const std::bad_alloc &) {
        return COLO_ALLOCATION_ERROR;
    }
}

    StatusColosseum Colosseum::getTopGladiator(const int &trainerID,int *gladiatorID){
        if (trainerID == 0 || gladiatorID == NULL)
            return COLO_INVALID_INPUT;;

        if (trainerID < 0) {
            if (this->allGladByLEVEL->isEmpty()) {
                *gladiatorID = NO_GLAD_IN_TREE;
                return COLO_SUCCESS;
            }

            *gladiatorID = this->allGladByLEVEL->getMaxKey().getId();
            return COLO_SUCCESS;
        }

        assert(trainerID >0);
        Trainer dupTrainer = Trainer(trainerID);
        if (this->allTrainersByID->find(dupTrainer) == TREE_FAILURE)
            return COLO_FAILURE;

        Trainer *trainer = this->allTrainersByID->getRootRef();
        assert(trainer->getId() == trainerID);

        *gladiatorID = trainer->GetTopGladiator();
        return COLO_SUCCESS;
    }

StatusColosseum Colosseum::upgradeGladiator(const int &gladiatorID,
                                       const int &upgradedID) {
        if (gladiatorID <= 0 || upgradedID <= 0)
                return COLO_INVALID_INPUT;;

        if (gladiatorID == upgradedID)
                return COLO_FAILURE;

        // check if upgradedID doesn't exist
        GladiatorByID upgradedDup(upgradedID);
        if (this->allGladByID->find(upgradedDup) == TREE_SUCCESS)
                return COLO_FAILURE;

        // check if gladiator ID exist
        GladiatorByID gladDup(gladiatorID);
        if (this->allGladByID->find(gladDup) == TREE_FAILURE)
                return COLO_FAILURE;

        GladiatorByLevel newGladiator(this->allGladByID->getRoot());
        assert(newGladiator.getId() == gladiatorID);

        //remove the gladiator from all trees
#ifndef  NDEBUG
        StatusColosseum res =
#endif
        this->freeGladiator(gladiatorID);
        assert(res == COLO_SUCCESS);

        // upgrade local gladiator ID
        newGladiator.upgradeGladiator(upgradedID);
        Trainer* trainer = (Trainer*)newGladiator.getTrainer();

        // create a new gladiator in all trees
    if(this->allGladByID->insertKey(newGladiator) == TREE_ALLOCATION_ERROR){
        return COLO_ALLOCATION_ERROR;
    }

    if(this->allGladByLEVEL->insertKey(newGladiator) == TREE_ALLOCATION_ERROR){
        return COLO_ALLOCATION_ERROR;
    }

    if(trainer->buyGladiator(newGladiator) == TRAINER_ALLOCATION_ERROR){
        return COLO_ALLOCATION_ERROR;
    }
    return COLO_SUCCESS;
}





StatusColosseum Colosseum::updateLevelsByID(SplayTree<GladiatorByID>*allGladByID,
                      const int &stimulateCode, const int &stimulateFactor) {
    assert(stimulateFactor >= 1 && stimulateCode >= 1);
    int numOfGladiators = allGladByID->getSize();

    if (allGladByID->isEmpty()) return COLO_SUCCESS; //case tree is empty

    try {
        GladiatorByID *allGlad = new GladiatorByID[numOfGladiators];
        allGladByID->treeToArr(allGlad);

        /*stimulate the factor on the right gladiators
        * here no need 2 arrays because the tree sorted by ID and we dont
        * change it*/
        for (int i = 0; i < numOfGladiators; i++) {
            if (allGlad[i].stimulateCode(stimulateCode)) {
                allGlad[i].stimulateFactor(stimulateFactor);
            }
        }
        //reinsert the gladiators to the tree
        allGladByID->arrToTree(allGlad, numOfGladiators);

        delete[](allGlad);
        return COLO_SUCCESS;

    } catch (const std::bad_alloc &) {
        return COLO_ALLOCATION_ERROR;
    }
}


StatusColosseum Colosseum::updateLevelsByLevel(SplayTree
                      <GladiatorByLevel> *allGladByLEVEL,
                      const int &stimulateCode, const int &stimulateFactor) {
    assert(stimulateFactor >= 1 && stimulateCode >= 1);
    int numOfGladiators = allGladByLEVEL->getSize();

    if (allGladByLEVEL->isEmpty()) return COLO_SUCCESS; //case tree is empty

    GladiatorByLevel *allGlad = NULL;
    GladiatorByLevel *effectedGlad = NULL;
    GladiatorByLevel *uneffectedGlad = NULL;

    try {
        allGlad = new GladiatorByLevel[numOfGladiators];
        effectedGlad = new GladiatorByLevel[numOfGladiators];
        uneffectedGlad = new GladiatorByLevel[numOfGladiators];
        allGladByLEVEL->treeToArr(allGlad);

        int effectedGladSize = 0, uneffectedGladSize = 0;
        // split the gladiator array to 2 different arrays
        for (int i = 0; i < (numOfGladiators); ++i) {
            if (allGlad[i].stimulateCode(stimulateCode)) {
                effectedGlad[effectedGladSize] = allGlad[i];
                effectedGladSize++;
            } else {
                uneffectedGlad[uneffectedGladSize] = allGlad[i];
                uneffectedGladSize++;
            }
        }

        //stimulate the factor on the right gladiators
        for (int i = 0; i < effectedGladSize; i++) {
            assert(effectedGlad[i].stimulateCode(stimulateCode));
            effectedGlad[i].stimulateFactor(stimulateFactor);
        }

        //merge the 2 arrays into 1 sorted array
        int effected_index = 0, uneffected_index = 0;
        for (int i = 0; i < numOfGladiators; i++) {
            if (effected_index == effectedGladSize) {
                allGlad[i] = uneffectedGlad[uneffected_index];
                uneffected_index++;
                continue;
            }
            if (uneffected_index == uneffectedGladSize) {
                allGlad[i] = effectedGlad[effected_index];
                effected_index++;
                continue;
            }

            if (effectedGlad[effected_index] >
                    uneffectedGlad[uneffected_index]){
                allGlad[i] = uneffectedGlad[uneffected_index];
                uneffected_index++;
            } else {
                allGlad[i] = effectedGlad[effected_index];
                effected_index++;
            }
        }

        allGladByLEVEL->arrToTree(allGlad,
                                  numOfGladiators);//reinsert the gladiators to the
        // tree

        delete[](allGlad);
        delete[](effectedGlad);
        delete[](uneffectedGlad);

        return COLO_SUCCESS;

    } catch (const std::bad_alloc &) {
        delete[](allGlad);
        delete[](effectedGlad);
        delete[](uneffectedGlad);
        return COLO_ALLOCATION_ERROR;
    }
}


StatusColosseum Colosseum::updateLevels(const int& stimulateCode, const int&
                                                        stimulateFactor) {
    if (stimulateCode < 1 || stimulateFactor < 1) {
        return COLO_INVALID_INPUT;;
    }

    if(this->updateLevelsByID(this->allGladByID,stimulateCode,
                              stimulateFactor) == COLO_ALLOCATION_ERROR){
        return COLO_ALLOCATION_ERROR;
    }

    if(this->updateLevelsByLevel(this->allGladByLEVEL,stimulateCode,
                              stimulateFactor) == COLO_ALLOCATION_ERROR){
        return COLO_ALLOCATION_ERROR;
    }

    if (this->allTrainersByID->keysManipulation
            (TrainerUpdateGladsLevel(stimulateCode, stimulateFactor))
        == TREE_ALLOCATION_ERROR) {
        return COLO_ALLOCATION_ERROR;
    }
    return COLO_SUCCESS;
}
