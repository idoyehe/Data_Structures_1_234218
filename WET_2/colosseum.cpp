#include "colosseum.h"
#define INVALID_ID (-1)


colosseum::Colosseum::Colosseum(const int &n, int *trainingGroupsIDs):
        allGladiators(NULL), groupTable(NULL),activeGroups(NULL) {
    assert(n > 1);
        this->allGladiators = new SplayTree<GladiatorByID>();
        this->groupTable = new HashTable<TGroup>(n);
        this->activeGroups = new Heap<int>();
        void **addressing = new void *[n]();
        StatusHeap res1 = this->activeGroups->makeHeap(trainingGroupsIDs,
                                                       addressing, n);
        assert(res1 != HP_FAILURE);
        if (res1 == HP_ALLOCATION_ERROR) {
            delete[](addressing);
            throw std::bad_alloc();
        }
        for (int i = 0; i < n; ++i) {
            TGroup toInsert(trainingGroupsIDs[i], addressing[i]);
            StatusHashTable res2 = this->groupTable->insertData(toInsert);
            assert(res2 != HT_FAILURE);
            if (res2 == HT_ALLOCATION_ERROR) {
                delete[](addressing);
                throw std::bad_alloc();
            }
        }
        delete[](addressing);
}

colosseum::Colosseum::~Colosseum() {
    delete this->allGladiators;
    delete this->groupTable;
    delete this->activeGroups;
}

colosseum::StatusColosseum
colosseum::Colosseum::addTrainingGroup(const int &trainingGroupID) {
    if(trainingGroupID < 0){
        return COLO_INVALID_INPUT;
    }
    if(this->groupTable->isExist(trainingGroupID)){
        return COLO_FAILURE;
    }

    void* newAddressing = NULL;
    StatusHeap res1 = this->activeGroups->insert(trainingGroupID,&newAddressing);
    if (res1 == HP_ALLOCATION_ERROR){
        return COLO_ALLOCATION_ERROR;
    }
    assert(res1 == HP_SUCCESS);
    TGroup toInsert(trainingGroupID,newAddressing);
    StatusHashTable res2 = this->groupTable->insertData(toInsert);
    assert( res2 != HT_FAILURE);
    if( res2 == HT_ALLOCATION_ERROR){
        this->activeGroups->decK(newAddressing,INVALID_ID);
        this->activeGroups->deleteMin();
        return COLO_ALLOCATION_ERROR;
    }
    assert(res2 == HT_SUCCESS);
    return COLO_SUCCESS;
}

colosseum::StatusColosseum
colosseum::Colosseum::addGladiator(const int &gladiatorID, const int &score, const
int &trainingGroupID) {
    if(gladiatorID < 0 || score < 0 || trainingGroupID < 0){
        return COLO_INVALID_INPUT;
    }
    GladiatorByID gladToinsert(gladiatorID,score);
    if(this->allGladiators->find(gladToinsert) == ST_SUCCESS){
        return COLO_FAILURE;
    }
    TGroup* requestedGroup = NULL;
    if(this->groupTable->findData(trainingGroupID,&requestedGroup) == HT_FAILURE){
        assert(requestedGroup == NULL);
        return COLO_FAILURE;
    }
    StatusTree res1 = this->allGladiators->insertKey(gladToinsert);
    assert(res1 != ST_FAILURE);
    if(res1 == ST_ALLOCATION_ERROR){
        return COLO_ALLOCATION_ERROR;
    }
    assert(res1 == ST_SUCCESS);
    StatusTGroup res2 = requestedGroup->addGladiator(gladiatorID,score);
    assert(res2 != TG_FAILURE);
    if(res2 == TG_ALLOCATION_ERROR){
#ifndef NDEBUG
        StatusTree res3 =
#endif
        this->allGladiators->deleteKey(gladToinsert);
        assert(res3 == ST_SUCCESS);
        return COLO_ALLOCATION_ERROR;
    }
    return COLO_SUCCESS;
}

colosseum::StatusColosseum
colosseum::Colosseum::getMinTrainingGroup(int *trainingGroupID) {
    if(trainingGroupID == NULL){
        return COLO_INVALID_INPUT;
    }
    (*trainingGroupID) = this->activeGroups->getMin();
    return COLO_SUCCESS;
}

colosseum::StatusColosseum
colosseum::Colosseum::trainingGroupFight(const int &trainingGroupID1,
                                         const int &trainingGroupID2, const int &k1,
                                         const int &k2) {
    if(k1 <= 0 || k2 <= 0 || trainingGroupID1 < 0 || trainingGroupID2 < 0){
        return COLO_INVALID_INPUT;
    }
    if(trainingGroupID1 == trainingGroupID2){
        return COLO_FAILURE;
    }

    TGroup* group1 = NULL;
    if(this->groupTable->findData(trainingGroupID1,&group1) == HT_FAILURE){
        assert(group1 == NULL);
        return COLO_FAILURE;
    }
    TGroup* group2 = NULL;
    if(this->groupTable->findData(trainingGroupID2,&group2) == HT_FAILURE){
        assert(group2 == NULL);
        return COLO_FAILURE;
    }
    assert(group1 != NULL && group2 !=NULL);
    if(group1->isConquered() || group2->isConquered()){
        return COLO_FAILURE;
    }
    int score1,score2;
    if(group1->getKScore(k1,&score1) == TG_FAILURE || group2->getKScore(k2,&score2) ==
                                                              TG_FAILURE){
        return COLO_FAILURE;
    }
    TGroup* losingGroup = group1;//default
    if(score1 > score2){
        losingGroup = group2;
    }
    else{
        if(score1 == score2 && group1->getGroupID() < group2->getGroupID()){
            losingGroup = group2;
        }
        else {
            assert(score1 < score2 ||
                   (score1 == score2 &&
                    group1->getGroupID() > group2->getGroupID()));
        }
    }
    void* pointerToHeap = losingGroup->setConquered();
#ifndef NDEBUG
    StatusHeap res1 =
#endif
    this->activeGroups->decK(pointerToHeap,INVALID_ID);
    assert(res1 == HP_SUCCESS);
#ifndef NDEBUG
    StatusHeap res2 =
#endif
    this->activeGroups->deleteMin();
    assert(res2 == HP_SUCCESS);
    return COLO_SUCCESS;
}
