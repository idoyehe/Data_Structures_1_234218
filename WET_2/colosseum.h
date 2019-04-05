#ifndef WET2_COLOSSEUM_H
#define WET2_COLOSSEUM_H

#include "splayTree.h"
#include "trainingGroup.h"
#include "heap.h"
#include "hashTable.h"

namespace colosseum {

    typedef enum {
        COLO_SUCCESS = 0,
        COLO_FAILURE = -1,
        COLO_ALLOCATION_ERROR = -2,
        COLO_INVALID_INPUT = -3
    } StatusColosseum;

    using namespace splayTree;
    using namespace gladiator;
    using namespace trainingGroup;
    using namespace heap;
    using namespace hashTable;

    class Colosseum {
    private:
        SplayTree <GladiatorByID> *allGladiators;
        HashTable<TGroup> *groupTable;
        Heap<int> *activeGroups;
    public:
        /*get number of group and their ID and build new minimum heap with all the id
         * and build new hash table and insert all the Groups to it
         * complexity: O(n)*/
        Colosseum(const int& n, int* trainingGroupsIDs);

        /*destructor deallocate all the saves data in the colosseum:
         * deallocate the hash table is complexity O(n + m), because each group has
         * gladiators tree
         * deallocate the heap of group id is complexity O(n),
         * deallocate the splay tree of all gladiators is complexity O(m),
         * complexity: O(n + m)*/
        ~Colosseum();

        /*adding new group with given group id, first check for valid input next
         * check if group is exist in the hash table average complexity O(1),
         * add the group to the heap of group ID complexity O(log(n)),
         * add the group to the hash table estimate complexity O(1),
         * average estimate complexity O(log(n)))*/
        StatusColosseum addTrainingGroup(const int &trainingGroupID);


        /*adding new gladiator to given group id, first check for valid input next
         * check if gladiator is exist estimate complexity O(log(m)),
         * search the group in the hash table average complexity O(1),
         * add the gladiator to the group's splay tree estimate complexity O(log(m)),
         * average estimate complexity O(log(m))*/
        StatusColosseum addGladiator(const int& gladiatorID, const int& score,const
        int& trainingGroupID);

        /*preform fight between two given group's ID first check for valid input
         * search the groups in the hash table average complexity O(1),
         * get the score of the best k gladiators in the groups estimate complexity O(log(m))
         * remark the losing group in the heap complexity O(log(n))
         * average estimate complexity O(log(m) + log(n))*/
        StatusColosseum trainingGroupFight(const int& trainingGroupID1,const int&
        trainingGroupID2,const int& k1,const int& k2);


        /*return the root in the heap
         * complexity O(1)*/
        StatusColosseum getMinTrainingGroup(int* trainingGroupID);
    };

}
#endif //WET1_COLOSSEUM_H
