#include "splayTree.h"
#include "trainer.h"

#define NO_KEYS_IN_TREE -1

using namespace colosseum::trainer;

            Trainer::Trainer(const int &id):id(id),spt(NULL) {
            }

            Trainer::~Trainer(){
                delete (this->spt);
            }

            StatusTrainer Trainer::buyGladiator(const GladiatorByLevel &duplicateGladiator){
                assert((Trainer*)(duplicateGladiator.getTrainer()) == this);
                if(this->spt == NULL){
                    try {
                        this->spt = new SplayTree<GladiatorByLevel>;
                    }catch (const std::bad_alloc&) {
                        return TRAINER_ALLOCATION_ERROR;
                    }
                }
                return (StatusTrainer)this->spt->insertKey(duplicateGladiator);
            }

            StatusTrainer Trainer::freeGladiator(const GladiatorByLevel &duplicateGladiator) const {
                assert((Trainer*)(duplicateGladiator.getTrainer()) == this);
                return (StatusTrainer)this->spt->deleteKey(duplicateGladiator);
            }

            int Trainer::GetTopGladiator() const {
                if (spt == NULL || spt->isEmpty())
                    return NO_KEYS_IN_TREE;
                return spt->getMaxKey().getId();
            }

            bool Trainer::isEmpty() const {
                return spt == NULL || spt->isEmpty();
            }

            int Trainer::getId() const {
                return this->id;
            }

            StatusTrainer Trainer::levelUpGladiator(const GladiatorByLevel &duplicateKey, const int &levelInc) const {
                assert(levelInc > 0);
                assert((Trainer*)duplicateKey.getTrainer()==this);
                if (this->spt==NULL ||spt->find(duplicateKey) != TREE_SUCCESS) {
                    return TRAINER_FAILURE;
                }
                //find the requested gladiator remove it change it and reinsert it to the tree
                assert(spt->getRoot() == duplicateKey);
                GladiatorByLevel gladEvolve = spt->getRoot();
                spt->deleteKey(gladEvolve);
                assert(spt->find(gladEvolve) == TREE_FAILURE);
                gladEvolve.levelUp(levelInc);
                return (StatusTrainer)spt->insertKey(gladEvolve);
            }

            StatusTrainer Trainer::getAllGladiatorsByLevel(int **gladiators,
                                                        int *numOfGladiators) const {
                assert(gladiators != NULL && numOfGladiators != NULL);
                if (spt== NULL ||spt->isEmpty()) {
                    *gladiators = NULL;
                    *numOfGladiators = 0;
                    return TRAINER_SUCCESS;
                }
                *numOfGladiators = spt->getSize();
                try {
                    GladiatorByLevel *allGlad = new
                            GladiatorByLevel[*numOfGladiators];
                    spt->treeToArr(allGlad);
                    *gladiators = (int *) malloc(sizeof(int)*(*numOfGladiators));
                    //as requested in PDF allocating by malloc
                    if (*gladiators == NULL) {
                        delete[](allGlad);
                        return TRAINER_ALLOCATION_ERROR;
                    }
                    for (int i = 0; i < (*numOfGladiators); ++i) {
                        (*gladiators)[i] = allGlad[(*numOfGladiators) - i - 1].getId();// insert from end to start
                    }
                    delete[](allGlad);
                    return TRAINER_SUCCESS;
                } catch (const std::bad_alloc &) {
                    return TRAINER_ALLOCATION_ERROR;
                }
            }

            StatusTrainer Trainer::updateLevels(const int &stimulateCode, const
            int &stimulateFactor) const {
                assert(stimulateFactor >= 1 && stimulateCode >= 1);
                if (spt==NULL || spt->isEmpty()) return TRAINER_SUCCESS; //case
                // tree
                // is empty
                int numOfGladiators = spt->getSize();
                GladiatorByLevel *allGlad = NULL;
                GladiatorByLevel *effectedGlad = NULL;
                GladiatorByLevel *uneffectedGlad = NULL;

                try {
                    allGlad = new GladiatorByLevel[numOfGladiators];
                    effectedGlad = new GladiatorByLevel[numOfGladiators];
                    uneffectedGlad = new GladiatorByLevel[numOfGladiators];
                    spt->treeToArr(allGlad);

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

                        if (effectedGlad[effected_index] > uneffectedGlad[uneffected_index]) {
                            allGlad[i] = uneffectedGlad[uneffected_index];
                            uneffected_index++;
                        } else {
                            allGlad[i] = effectedGlad[effected_index];
                            effected_index++;
                        }
                    }

                    spt->arrToTree(allGlad,numOfGladiators);//reinsert the gladiators to the
                    // tree

                    delete[](allGlad);
                    delete[](effectedGlad);
                    delete[](uneffectedGlad);

                    return TRAINER_SUCCESS;

                } catch (const std::bad_alloc &) {
                    delete[](allGlad);
                    delete[](effectedGlad);
                    delete[](uneffectedGlad);
                    return TRAINER_ALLOCATION_ERROR;
                }
            }


            StatusTrainer Trainer::upgradeGladiator(const GladiatorByLevel &duplicateGladiator,
                                                 const int &upgradedID) const {
                assert(upgradedID > 0);
                assert((Trainer*)(duplicateGladiator.getTrainer()) == this);
                if (spt==NULL || spt->find(duplicateGladiator) !=TREE_SUCCESS) {
                    return TRAINER_SUCCESS;
                }
                assert(spt->getRoot() == duplicateGladiator);
                GladiatorByLevel gladUpgrade = spt->getRoot();
                spt->deleteKey(gladUpgrade);
                assert(spt->find(gladUpgrade) == TREE_FAILURE);
                gladUpgrade.upgradeGladiator(upgradedID);
                return (StatusTrainer)spt->insertKey(gladUpgrade);
            }

bool Trainer::operator==(const Trainer &trainer) const {
    return this->getId() == trainer.getId();
}

bool Trainer::operator!=(const Trainer &trainer) const {
    return !((*this) == trainer);
}

bool Trainer::operator<(const Trainer &trainer) const {
    return this->getId() < trainer.getId();
}

bool Trainer::operator>(const Trainer &trainer) const {
    return this->getId() > trainer.getId();
}


TrainerUpdateGladsLevel::TrainerUpdateGladsLevel
                    (const int& stimulateCode, const int& stimulateFactor) :
            stimulateCode(stimulateCode), stimulateFactor(stimulateFactor){}

            StatusTree TrainerUpdateGladsLevel::operator()(const Trainer &t1)
                        const {
                return (StatusTree)t1.updateLevels(this->stimulateCode,
                                       this->stimulateFactor);
            }
