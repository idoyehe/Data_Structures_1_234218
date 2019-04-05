#ifndef DATASRUCTURES_TRAININGGROUP_H
#define DATASRUCTURES_TRAININGGROUP_H

#include <cassert>
#include "gladiators.h"
#include "rankSplayTree.h"

namespace colosseum {
    namespace trainingGroup {
        using namespace gladiator;
        using namespace splayTree;

        typedef enum {
            TG_SUCCESS = 0,
            TG_FAILURE = -1,
            TG_ALLOCATION_ERROR = -2
        } StatusTGroup;

        class TGroup {
        private:
            int groupID;
            bool conquered;
            RankSplayTree *rspt;
            void * ptrToHeap;

        public:
            /*constructor new group with given group ID
             * complexity: O(1)*/
            explicit TGroup(const int &groupID);

            /*constructor new group with given group ID and ptr to Heap
            * complexity: O(1)*/
            TGroup(const int &groupID,void*ptrToHeap);

            /*destructor the group and all it's gladiators
            * complexity: O(mi); mi is number of gladiators in group*/
            ~TGroup();

            /*get the group ID
            * complexity: O(1)*/
            const int &getGroupID() const;

            /*sign the group to be Conquered
            * complexity: O(1)*/
            void* setConquered();

            /*return true if and only if the team is conquered
             * complexity: O(1)*/
            bool isConquered();

            /* add a new gladiator to the group splay tree
             * estimate complexity: O(log(mi)) mi is number of gladiators in group*/
            StatusTGroup addGladiator(const int &gladiatorID, const int &gladiatorScore);

            /* get the score if the K best gladiators in the group
             * estimate complexity: O(log(mi)) mi is number of gladiators in group*/
            StatusTGroup getKScore(const int &k, int *score);

            /*return true if the groups' id are equal
            * complexity: O(1)*/
            bool operator==(const TGroup& tGroup) const;

            /*return the group ID
            * complexity: O(1)*/
            int operator()() const;
        };
    }
}
#endif //DATASRUCTURES_TRAININGGROUP_H
