#ifndef WET1_TRAINER_H
#define WET1_TRAINER_H

#include "splayTree.h"
#include "gladiator.h"

#define NO_KEYS_IN_TREE -1

namespace colosseum {

    namespace trainer {

        typedef enum {
            TRAINER_SUCCESS = 0,
            TRAINER_FAILURE = -1,
            TRAINER_ALLOCATION_ERROR = -2
        } StatusTrainer;

        using namespace gladiator;
        using namespace splayTree;

        class Trainer {
        private:
            int id;
            SplayTree<GladiatorByLevel>* spt;

        public:

            /*constructor of the trainer and initialize id and the gladiators splay tree
            * complexity: O(1)*/
            Trainer(const int &id);

            /*destructor of the trainer call only to splay tree destructor
             *complexity: O(ni)*/
            ~Trainer();

            /* add a new gladiator to the splay tree
             * estimate complexity: O(log(ni)) */
            StatusTrainer buyGladiator(const GladiatorByLevel &duplicateGladiator);

            /* remove a given gladiator from the splay tree
             * estimate complexity: O(log(ni)) */
            StatusTrainer freeGladiator(const GladiatorByLevel &duplicateGladiator) const;

            /* find the highest gladiator ID in the splay tree, if doesn't exist
             * return NO_KEYS_IN_TREE (-1)
             * complexity: O(1)*/
            int GetTopGladiator() const;

            /*return true if the trainer has no gladiators is otherwise false
             *complexity: O(1)*/
            bool isEmpty() const;

            /*return the ID of the trainer
             *complexity: O(1)*/
            int getId() const;

            /*gets duplicate gladiator and search it in the tree if founded update it's level
             * return SUCCESS if the gladiator founded and updated otherwise FAILURE
             * estimate complexity: O(log(ni)) */
            StatusTrainer levelUpGladiator(const GladiatorByLevel &duplicateKey,
                                        const int &levelInc) const;

            /*get all the gladiators' of this trainer sorted from stronger to wicker
             * return ALLOCATION_ERRor if allocation fails otherwise SUCCESS
             *complexity: O(ni)*/
            StatusTrainer
            getAllGladiatorsByLevel(int **gladiators, int *numOfGladiators)const;

            /*gets duplicate gladiator and search it in the tree if founded update it's ID
            * return SUCCESS if the gladiator founded and updated otherwise FAILURE
            * estimate complexity: O(log(ni)) */
            StatusTrainer upgradeGladiator(const GladiatorByLevel &duplicateKey,
                                        const int &upgradedID) const;


            /*update the level of all trainer's gladiators by removing all of them from the tree and
             *reinsert them sorted with new order
             *return ALLOCATION_ERRor if allocation fails otherwise SUCCESS
             *complexity: O(ni) */
            StatusTrainer updateLevels(const int &stimulateCode, const int
            &stimulateFactor) const;

            /* Comparison operators for trainer the default is
             * comparing by trainer's ID
             * complexity: O(1)*/
            bool operator==(const Trainer& trainer) const;
            bool operator!=(const Trainer& trainer) const;
            virtual bool operator<(const Trainer& trainer) const;
            virtual bool operator>(const Trainer& trainer) const;

        };
        class TrainerUpdateGladsLevel {
        private:
            int stimulateCode;
            int stimulateFactor;
        public:
            /*constructor*/
            TrainerUpdateGladsLevel(const int& stimulateCode,
                                    const int& stimulateFactor);

            /*calling updateLevels with t1*/
            StatusTree operator()(const Trainer &t1) const;
        };
    }
}
#endif //WET1_TRAINER_H
