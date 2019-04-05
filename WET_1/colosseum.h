#ifndef WET1_COLOSSEUM_H
#define WET1_COLOSSEUM_H

#include "splayTree.h"
#include "trainer.h"
#include "gladiator.h"

namespace colosseum {

    typedef enum {
        COLO_SUCCESS = 0,
        COLO_FAILURE = -1,
        COLO_ALLOCATION_ERROR = -2,
        COLO_INVALID_INPUT = -3
    } StatusColosseum;

    using namespace splayTree;
    using namespace gladiator;
    using namespace trainer;

    class Colosseum {
    private:
        SplayTree<GladiatorByID> *allGladByID;
        SplayTree<GladiatorByLevel> *allGladByLEVEL;
        SplayTree<Trainer> *allTrainersByID;


        StatusColosseum updateLevelsByID(SplayTree<GladiatorByID>
                                    *allGladByID, const int &stimulateCode,
                                    const int &stimulateFactor);

        StatusColosseum updateLevelsByLevel(SplayTree<GladiatorByLevel>
                                    *allGladByLEVEL, const int &stimulateCode,
                                    const int &stimulateFactor);

    public:

        /*constructor of the system
         *complexity: O(1)*/
        Colosseum();

        /*destructor of the system
         *complexity: O(n+k)*/
        ~Colosseum();

        /*add new trainer to the system, first check if it's already exist and if not insert it to the tree
         * return values as PDF
         * estimate complexity: O(log(ni)) ot in worst case O(k)*/
        StatusColosseum addTrainer(const int &trainerID);

        /*add new gladiator to the system, first check if it's already exist and if it's trainer exist,
         * if trainer exist AND the gladiator not insert it to the all three
         * trees byID, byLevel and of it's trainer
         * return values as PDF
         * estimate complexity: O(log(n) +k)*/
        StatusColosseum buyGladiator(const int &gladitorID, const int &trainerID, const int &level);

        /*removing a gladiator from the system, first check if it's already exist
         * return values as PDF
         * estimate complexity: O(log(n))*/
        StatusColosseum freeGladiator(const int &gladiatorID);

        /* Increase the level of a given gladiator by a given value.
        * if gladiator doesn't exist define as failure.
        * if gladiator exists and level increment value is positive remove
        * the gladiator from tree, create need with same ID and different level
        * insert the new gladiator into the tree. return success
        * complexity: O(log(n))*/
        StatusColosseum levelUp(const int &gladiatorID, const int &levelIncrease);


        /* exporting the gladiators' Id by their level to an array
         * if trainerID > 0 exporting ONLY trainer's gladiators' Id
         * complexity: O(ni + k)
         * if trainerID < 0 exporting ALL gladiators' Id
         * complexity: O(n)*/
        StatusColosseum getAllGladiatorsByLevel(const int& trainerID,int**
                gladiators, int* numOfGladiators);

        /* Find the gladiator with the highest level for a given trainer ID.
         * complexity: O(k)
         * If trainer id is 0 - failure.
         * If trainer id < 0 - return the highest gladiator ID in the whole
         * colosseum (into the pointer) and return success.
         *complexity: O(1)
         * If no gladiator for trainer or in system return -1 (into the pointer)
         * and return success.
         * If 2 gladiators are the same level, the best gladiator is with the
         * smallest ID */
        StatusColosseum getTopGladiator(const int &trainerID, int *gladiatorID);


        /* Change the level of a given gladiator to a new upgraded ID.
         * If current ID is the same as the upgraded ID, or if gladiator ID
         * doesn't exists, or if upgraded ID already exists - return FAILURE
         * Otherwise, change the gladiator ID in all trees using Free and Buy
         * gladiators functions (same implementation) - return SUCCESS
         * estimate complexity: O(log(n))*/
        StatusColosseum upgradeGladiator(const int &gladiatorID, const int &
        upgradedID);



        /* Multiply a gladiator level by a given factor if the ID of the
         * gladiator is equally divided by a given code (mod is 0).
         * Stimulate code must be greater than 1.
         * Logic: extract the all trees to arrays using inorder, updating all
         * effected gladiators, using 2 arrays and merging, inserting all
         * gladiators back into the trees using inorder.
         * Complexity: O(n+k) */
        StatusColosseum updateLevels(const int& stimulateCode, const int&
        stimulateFactor);

    };

}
#endif //WET1_COLOSSEUM_H

