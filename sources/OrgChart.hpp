#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>

using namespace std;

namespace ariel
{
    struct OrgNode{
        vector<OrgNode> subRole;
        string role;
        // OrgNode dad;
        unsigned int tag = 0;
    };

    class OrgChart
    {
    private:
        OrgNode root;
    // vectors for the oreders:
        vector<string> printVector;
        vector<string> levelVector;
        vector<string> reverseVector;
        vector<string> preorderVector;

    public: 
//  help functions:  
        void levelHelper(OrgNode &currentNode);
        void reverseHelper(OrgNode &currentNode);
        void preorderHelper(OrgNode &currentNode);
  

//  OrgChart buliding functions:
        OrgChart &add_root(string const & _role);
        OrgChart &add_sub(string boss, string sub);
        ~OrgChart() = default;
        OrgChart() = default;
        OrgChart (OrgChart & o) = default;
        OrgChart (OrgChart && o) = default;
        OrgChart & operator= (OrgChart &&) =  default;
        
// orperators & printing:  
        friend ostream &operator<<(ostream &out,OrgChart & orgNode);
        void print(OrgNode &currentRole, int end, string temp,int first);
        string* firstPrint();
        string* lastPrint(); 
        
//iterators:
        string* begin_level_order();
        string* begin_reverse_order();
        string* end_preorder();
        string* end_level_order();
        string* begin_preorder();
        string* reverse_order();
        string* begin();
        string* end();

// Auxiliary functions:
    bool static isEmpty(string const & _role);
    void static insert(OrgNode &currentNode, string &sub);
    bool findNode(string &boss, string &sub,OrgNode &currentNode);
        };

}