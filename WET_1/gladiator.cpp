#include <cassert>
#include "gladiator.h"

#define UNSET -1

using namespace colosseum::gladiator;

            GladiatorByID::GladiatorByID(const int &id, const int &level,const void *trainer) :
                    id(id), level(level), trainer(trainer) {}

            GladiatorByID::GladiatorByID(const int &id) : id(id), level(UNSET), trainer(NULL) {}

            GladiatorByID::GladiatorByID() : id(UNSET), level(UNSET), trainer(NULL) {}

            const int & GladiatorByID::getId() const {
                return this->id;
            }

            const int &GladiatorByID::getLevel() const {
                return this->level;
            }

            const void *GladiatorByID::getTrainer()const {
                return this->trainer;
            }

            void GladiatorByID::levelUp(const int &levelIncrease) {
                assert(levelIncrease > 0);
                this->level += levelIncrease;
                return ;
            }

            void GladiatorByID::upgradeGladiator(const int &upgradeId) {
                assert(upgradeId > 0);
                this->id = upgradeId;
                return ;
            }

            bool GladiatorByID::stimulateCode(const int &stimulateCode) const {
                assert(stimulateCode >= 1);
                return this->getId() % stimulateCode == 0;
            }

            void GladiatorByID::stimulateFactor(const int &stimulateFactor) {
                assert(stimulateFactor >= 1);
                this->level *= stimulateFactor;
                return;
            }

GladiatorByID::~GladiatorByID() {
}

bool GladiatorByID::operator==(const GladiatorByID &gladiator) const {
    return this->getId() == gladiator.getId();
}

bool GladiatorByID::operator!=(const GladiatorByID &gladiator) const {
    return !((*this) == gladiator);
}

bool GladiatorByID::operator<(const GladiatorByID &gladiator) const {
    return this->getId() < gladiator.getId();
}

bool GladiatorByID::operator>(const GladiatorByID &gladiator) const {
    return this->getId() > gladiator.getId();
}

GladiatorByLevel::GladiatorByLevel(const int &id, const int &level,const void *trainer)
        : GladiatorByID(id, level,trainer) {
}

GladiatorByLevel::GladiatorByLevel(const int &gladiatorId) :
        GladiatorByID(gladiatorId) {
}
GladiatorByLevel::GladiatorByLevel() : GladiatorByID(){}


bool GladiatorByLevel::operator<(const GladiatorByLevel &gladiator) const {
    if (this->getLevel() != gladiator.getLevel()) {
        return this->getLevel() < gladiator.getLevel();
    }

    assert (this->getLevel() == gladiator.getLevel());
    return this->getId() > gladiator.getId();
    /*case same level this will be smaller
     * if it's id will be greater than gladiator's Id*/
}

bool GladiatorByLevel::operator>(const GladiatorByLevel &gladiator) const {
    if (this->getLevel() != gladiator.getLevel()) {
        return this->getLevel() > gladiator.getLevel();
    }

    assert (this->getLevel() == gladiator.getLevel());
    return this->getId() < gladiator.getId();
    /*case same level this will be greater
     * if it's id will be smaller than gladiator's Id*/
}

GladiatorByLevel::~GladiatorByLevel() {
}

GladiatorByLevel::GladiatorByLevel(const GladiatorByID &gladiator) :
        GladiatorByID(gladiator){}
