#include "trainingGroup.h"

colosseum::trainingGroup::TGroup::TGroup(const int &groupID) :
        groupID(groupID),conquered(false),rspt(NULL),ptrToHeap(NULL){
}

colosseum::trainingGroup::TGroup::TGroup(const int &groupID, void* ptrToHeap) :
        groupID(groupID), conquered(false) ,rspt(NULL),ptrToHeap(ptrToHeap){
}

colosseum::trainingGroup::TGroup::~TGroup() {
        delete (this->rspt);
}

const int &colosseum::trainingGroup::TGroup::getGroupID() const {
    return this->groupID;
}

void* colosseum::trainingGroup::TGroup::setConquered() {
    assert(this->conquered == false);
    this->conquered = true;
    void* ptrToHeap = this->ptrToHeap;
    this->ptrToHeap = NULL;
    return ptrToHeap;
}

colosseum::trainingGroup::StatusTGroup
colosseum::trainingGroup::TGroup::addGladiator(const int &gladiatorID,
                                               const int &gladiatorScore) {
    GladiatorByScore newGlad(gladiatorID,gladiatorScore);
    if(this->rspt == NULL) {//only for first gladiator that get in
        try {
            rspt = new RankSplayTree();
        } catch (const std::bad_alloc &) {
            return TG_ALLOCATION_ERROR;
        }
    }
    StatusTree res = this->rspt->insertKey(newGlad);
    assert(res != ST_FAILURE);
    return (StatusTGroup) res;
}

colosseum::trainingGroup::StatusTGroup
colosseum::trainingGroup::TGroup::getKScore(const int &k, int *score) {
    assert(k > 0);
    if(this->rspt == NULL || this->rspt->findKpivot(k) == ST_FAILURE){
        return TG_FAILURE;
    }
    (*score) = this->rspt->getRootScore();
    return TG_SUCCESS;
}

bool colosseum::trainingGroup::TGroup::operator==(
        const colosseum::trainingGroup::TGroup &tGroup) const {
    return this->getGroupID() == tGroup.getGroupID();
}

bool colosseum::trainingGroup::TGroup::isConquered() {
    return this->conquered;
}


int colosseum::trainingGroup::TGroup::operator()() const {
    return this->getGroupID();
}
