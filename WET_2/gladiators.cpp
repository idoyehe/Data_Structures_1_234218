#include "gladiators.h"

using namespace colosseum::gladiator;

GladiatorByID::GladiatorByID(const int &gladiatorId, const int &score) :
        gladiatorID(gladiatorId) ,score(score){
}

GladiatorByID::GladiatorByID(const int &gladiatorId) : gladiatorID(gladiatorId){
}

const int &GladiatorByID::getGladiatorID() const {
    return this->gladiatorID;
}

const int &GladiatorByID::getGladiatorScore() const {
    return this->score;
}

bool GladiatorByID::operator==(const GladiatorByID &gladiator) const {
    return this->gladiatorID == gladiator.gladiatorID;
}

bool GladiatorByID::operator!=(const GladiatorByID &gladiator) const {
    return !((*this) == gladiator);
}

bool GladiatorByID::operator<(const GladiatorByID &gladiator) const {
    return this->gladiatorID < gladiator.gladiatorID;
}

bool GladiatorByID::operator>(const GladiatorByID &gladiator) const {
    return this->gladiatorID > gladiator.gladiatorID;
}

GladiatorByID::~GladiatorByID() {
}


GladiatorByScore::GladiatorByScore(const int &gladiatorId, const int &score)
        : GladiatorByID(gladiatorId, score) {
}

GladiatorByScore::GladiatorByScore(const int &gladiatorId) :
        GladiatorByID(gladiatorId) {
}

bool GladiatorByScore::operator<(const GladiatorByScore &gladiator) const {
    if (this->getGladiatorScore() != gladiator.getGladiatorScore()) {
        return this->getGladiatorScore() < gladiator.getGladiatorScore();
    }

    assert (this->getGladiatorScore() == gladiator.getGladiatorScore());
    return this->getGladiatorID() > gladiator.getGladiatorID();
    /*case same level this will be smaller
     * if it's id will be greater than gladiator's Id*/
}

bool GladiatorByScore::operator>(const GladiatorByScore &gladiator) const {
    if (this->getGladiatorScore() != gladiator.getGladiatorScore()) {
        return this->getGladiatorScore() > gladiator.getGladiatorScore();
    }

    assert (this->getGladiatorScore() == gladiator.getGladiatorScore());
    return this->getGladiatorID() < gladiator.getGladiatorID();
    /*case same level this will be greater
     * if it's id will be smaller than gladiator's Id*/
}

GladiatorByScore::~GladiatorByScore() {
}
