#ifndef WET1_GLADIATOR_H
#define WET1_GLADIATOR_H

#include <cassert>


namespace colosseum {
    namespace gladiator {

        class GladiatorByID {
        private:
            int gladiatorID;
            int score;
        public:
            /*constructor with all parameters
             * complexity: O(1)*/
            GladiatorByID(const int &gladiatorId, const int &score);

            /*constructor with only id parameter
             * complexity: O(1)*/
            explicit GladiatorByID(const int &gladiatorId);

            /*return the Id of the Gladiator
             *complexity: O(1)*/
            const int &getGladiatorID() const;

            /*return the score of the Gladiator
             *complexity: O(1)*/
            const int &getGladiatorScore() const;

            /* Comparison operators for Gladiator the default is
             * comparing by gladiator's ID
             * complexity: O(1)*/
            bool operator==(const GladiatorByID& gladiator) const;
            bool operator!=(const GladiatorByID& gladiator) const;
            virtual bool operator<(const GladiatorByID& gladiator) const;
            virtual bool operator>(const GladiatorByID& gladiator) const;

            virtual ~GladiatorByID();


        };

        class GladiatorByScore : public GladiatorByID {
        public:
            GladiatorByScore(const int &gladiatorId, const int &score);
            explicit GladiatorByScore(const int &gladiatorId);
            bool operator<(const GladiatorByScore& gladiator) const;
            bool operator>(const GladiatorByScore& gladiator) const;
            ~GladiatorByScore();
        };
    }
}
#endif //WET1_GLADIATOR_H
