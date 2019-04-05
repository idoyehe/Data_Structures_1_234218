#ifndef DATASRUCTURES_RANKSPLAYTREE_H
#define DATASRUCTURES_RANKSPLAYTREE_H

#include "gladiators.h"
#include "splayTree.h"

using namespace colosseum::gladiator;

namespace splayTree {
    class RankSplayTree {
    private:
        class Vertex {
        private:
            GladiatorByScore data;
            Vertex *leftV;
            Vertex *rightV;
            int vertex_score;
            int leftTreeScore;
            int leftTreeSize;
            int rightTreeScore;
            int rightTreeSize;
            /*
             * rotating the vertex to the left and update the save data in tree
             */
            Vertex *LL_Rotate();
            /*
             * rotating the vertex to the right
             */
            Vertex *RR_Rotate();
        public:
            /*constructor*/
            Vertex(const GladiatorByScore& data) ;

            /*
            * destructor of the vertex removing all sub vertices recursively
            */
            ~Vertex();

            /*return const reference to the data in the vertex*/
            const GladiatorByScore& getData() const ;

            /*get reference of a key and splay it's vertex to the root,
             * if not found splay the last vertex reached*/
            Vertex* find(const GladiatorByScore& key);

            /* finding the vertex with K score*/
            Vertex* findKPivot(const int& k, int& refLocation);

            /*find the min key vertex and splay it all the way to the root*/
            Vertex *findMin();

            /*find the max key vertex and splay it all the way to the root*/
            Vertex *findMax();

            /*join 2 splay trees to one big tree
             * ASSERTION: key(x)<key(y) for all x in this and all y in root
             */
            Vertex* join(Vertex *root2);

            /*split this tree to 2 trees by the pivot and export them into 2 pointers
             * key(x) <= pivot for all x in t1
             * key(y)> pivot for all y in t2
             */
            void split(Vertex **t1, Vertex **t2, const GladiatorByScore& pivot);

            /*insert new allocated vertex into the root
             * of the tree by using split*/
            Vertex *insertV(Vertex *vertexToInsert);

            /*removing the root of the tree, by using join,
             * BUT does NOT deallocate it, export it by pointer*/
            Vertex *removeRoot(Vertex **oldRoot) ;

            /*get the score of the root */
            int getScore();
        };

        Vertex* root;
        int size;
    public:
        /*constructor of the splay tree*/
        explicit RankSplayTree();

        /*get a reference to key and try to find it in the tree using vertex find function*/
        StatusTree find(const GladiatorByScore& key);

        /* finding the vertex with K score*/
        StatusTree findKpivot(const int & k);

        /*insert a key to the tree, it does NOT check if the key already inside!! update max and size as well
        * ALLOCATION_ERROR-> when allocating new vertex fails
        * SUCCESS -> when the key inserted to the tree*/
        StatusTree insertKey(const GladiatorByScore& key);

        /*gets a reference to key and splay it to the root and remove it using vertex remove root function
         * FAILURE-> when key does NOT found
         * SUCCESS-> remove successfully from the tree*/
        StatusTree deleteKey(const GladiatorByScore& duplicateKey);

        /*return the size of the tree*/
        int getSize() const ;

        /*return the score of the root*/
        int getRootScore() const;

        /*return a const reference to the root key in the tree
        * ASSERTION: the tree is NOT empty*/
        const GladiatorByScore& getRoot() const ;

        /*return true if the tree is empty otherwise false*/
        bool isEmpty()const ;

        /*recursive destructor using vertex destructor*/
        ~RankSplayTree() ;
    };
}
#endif //DATASRUCTURES_RANKSPLAYTREE_H
