#ifndef WET1_GLADIATOR_H
#define WET1_GLADIATOR_H

#include <cassert>
#include <cstdlib>

namespace colosseum {
    namespace gladiator {

        class GladiatorByID {
        private:
            int id;
            int level;
            const void* trainer;
        public:
            /*constructor with all three parameters
             * complexity: O(1)*/
            GladiatorByID(const int &id, const int &level,const void *trainer);

            /*constructor with only id parameter
             * complexity: O(1)*/
            GladiatorByID(const int &id);

            /*constructor with NO parameters, USE ONLY FOR ALLOCATE ARRAY OF GLADIATORS
            * complexity: O(1)*/
            GladiatorByID();

            /*return the Id of the Gladiator
             *complexity: O(1)*/
            const int &getId() const;

            /*return the level of the Gladiator
             *complexity: O(1)*/
            const int &getLevel() const;

            /*return the pointer to the trainer of the Gladiator
             * ASSERTION: need to be cast
             * complexity: O(1)*/
            const void *getTrainer() const;

            /*increase the gladiator's level by levelIncrease
             * ASSERTION: levelIncrease > 0
             *complexity: O(1)*/
            void levelUp(const int &levelIncrease);

            /*change the gladiator's id th upgradeId
            * ASSERTION: upgradeId > 0
            * complexity: O(1)*/

            void upgradeGladiator(const int &upgradeId);


            /*check if the stimulateCode is working on the gladiator's id
             *ASSERTION: stimulateCode >= 1
             * return True for stimulateCode that work otherwise False
             * complexity: O(1)*/
            bool stimulateCode(const int &stimulateCode) const;

            /*multiply the gladiator's level by stimulate factor
             *ASSERTION: stimulateFactor >= 1
             *return SUCCESS
             *complexity: O(1)*/
            void stimulateFactor(const int &stimulateFactor);

            /* Comparison operators for Gladiator the default is
            * comparing by gladiator's ID
            * complexity: O(1)*/
            bool operator==(const GladiatorByID& gladiator) const;
            bool operator!=(const GladiatorByID& gladiator) const;
            virtual bool operator<(const GladiatorByID& gladiator) const;
            virtual bool operator>(const GladiatorByID& gladiator) const;

            virtual ~GladiatorByID();
        };

        class GladiatorByLevel : public GladiatorByID {
        public:
            GladiatorByLevel(const int &id, const int &level,const void *trainer);
            explicit GladiatorByLevel(const int &gladiatorId);
            GladiatorByLevel();
            GladiatorByLevel(const GladiatorByID& gladiator);
            bool operator<(const GladiatorByLevel& gladiator) const;
            bool operator>(const GladiatorByLevel& gladiator) const;
            ~GladiatorByLevel();
        };
    }
}
#endif //WET1_GLADIATOR_H
