#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include "OrgChart.hpp"
using namespace std;

namespace ariel{
    OrgChart &OrgChart::add_root(string const & _role)
    {
        if( !isEmpty(_role)){
            this->root.role = _role;
            return *this; 
        }
        throw invalid_argument("Error:The role has no value.");
    }

    OrgChart &OrgChart::add_sub(string boss, string sub)
    {
        if(isEmpty(boss) || isEmpty(sub)){
        throw invalid_argument("Error:The requested OrgChart-Node has not exist");      
        }
        if (findNode(boss, sub ,this->root))
        {
            return *this;
        }  
        throw invalid_argument("Error:The requested OrgChart-Node has not exist");      
    }

/**
 * check if string is empty or have an invalid_argument.
 *
 *
 * @param _role  - string 
 * @return bool if the string is empty return true
 */
    bool OrgChart::isEmpty(string const & _role){
        int k = _role.compare("");
        int q = _role.compare("\n");
        int r = _role.compare("\r");
        int s = _role.compare(" ");
        return (!(!_role.empty() && k != 0 && q != 0 && r != 0 && s != 0));
    }

/**
 * find the requested OrgChart-Node and insert the "sub" to be
 * the subRole of the "boss".
 *
 * @param boss
 * @param sub
 * @param currentNode
 * @return bool - return true if the Node has found and the insert has done.
 */
    bool OrgChart::findNode(string &boss, string &sub,OrgNode &currentNode){
        if(isEmpty(currentNode.role)){
        throw invalid_argument("Error:The role has no value.");      
        }
        string currentRole = currentNode.role;
        int key = boss.compare(currentRole);
        if (key != 0 ){
            unsigned int i = 0;
            int subLength =  currentNode.subRole.size();
            while(i < subLength){
            bool f = findNode(boss, sub ,currentNode.subRole.at(i));
            i++;
            if(f){
                return true;
                 }
            }
        }
        else{
            insert(currentNode,sub);
            return true;
            }
        return false;
    }
/**
 * insert a sub to be "subRole" of some node.
 * @param boss
 * @param sub
 * @return bool - return true if the Node has found and the insert has done.
 */
    void OrgChart::insert(OrgNode &currentNode, string &sub){
        try{
            OrgNode temp;
            temp.role = sub;
            currentNode.subRole.push_back(temp);
        }
        catch(...){
            throw invalid_argument("Error:The role has no value.");      
        }
    }


// ---------------------------   begin - end : orders  ------------------------------------

    string *OrgChart::begin_level_order()
    {
        if(isEmpty(this->root.role)){
        throw invalid_argument("Error:The requested OrgChart-Node has not exist.");      
            }
        this->levelVector.clear();
        levelHelper(this->root);
        return &levelVector.at(0);       
    }
      string *OrgChart::begin_preorder()
    {
        if(isEmpty(this->root.role)){
        throw invalid_argument("Error:The requested OrgChart-Node has not exist.");      
        }
        this->preorderVector.clear();
        preorderHelper(this->root);
        return &preorderVector.at(0);

    }
    string *OrgChart::begin_reverse_order()
    {
        if(isEmpty(this->root.role)){
        throw invalid_argument("Error:The requested OrgChart-Node has not exist.");      
            }
        this->reverseVector.clear();
        reverseHelper(this->root);
        return &reverseVector.at(0);
    }
    string *OrgChart::reverse_order()
    {
        if(isEmpty(this->root.role)){
        throw invalid_argument("Error:The requested OrgChart-Node has not exist.");      
            }
        this->reverseVector.clear();
        reverseHelper(this->root);
        unsigned int vecSize = this->reverseVector.size();
        return &this->reverseVector[vecSize];

    }

      string *OrgChart::end_level_order()
    {
        if(isEmpty(this->root.role)){
        throw invalid_argument("Error:The requested OrgChart-Node has not exist.");      
            }
        this->levelVector.clear();    
        levelHelper(this->root);
        unsigned int vecSize = this->levelVector.size();
        return &this->levelVector[vecSize];
    }

    string *OrgChart::end_preorder()
    {
        if(isEmpty(this->root.role)){
        throw invalid_argument("Error:The requested OrgChart-Node has not exist.");      
            }
        this->preorderVector.clear();
        preorderHelper(this->root);
        unsigned int vecSize = this->preorderVector.size();
        return &this->preorderVector[vecSize];
    }

    string* OrgChart::begin()
    {
        return begin_level_order();
    }
    string* OrgChart::end()
    {
        return end_level_order();
    }

// ---------------------------  print & operator <<  ------------------------------------
/**
 * @brief 
 * insert all the orgChart into string it shape of diagram.
 * helped by those websites:
 *     https://www.techiedelight.com/c-program-print-binary-tree/
 *     https://en.wikipedia.org/wiki/Box-drawing_character
 */
 
    void OrgChart::print(OrgNode &currentRole, int end , string temp,int first)
    { 
    if(first==1){
        temp += "══════════";
    }
    else{
        temp += "   ";
    }
    printVector.push_back(temp);
    if (end == 1)
    {
        temp += " ";
        printVector.push_back(" ╚>");
        temp += "   ";
    }
    else
    {
        printVector.push_back(" ╠>");
        temp += " ║ ";
    }

    printVector.push_back( " " + currentRole.role + "\n");
    unsigned int subLength = currentRole.subRole.size();
    unsigned int i = 0;
    int key = 0;
    first = 0;
    while( i <subLength){
        unsigned int plus= i+1;
        if(plus == subLength) {
            key = 1;
        }
        print(currentRole.subRole.at(i), key , temp , first);
        i++;
        }

    }
/**
 * @brief 
 * return the start of the string for the iterator.
 * @return string* 
 */
    string *OrgChart::firstPrint()
    {
        if(isEmpty(this->root.role)){
        throw invalid_argument("Error:The requested OrgChart-Node has not exist.");      
        }
        this->printVector.clear();
        print(this->root,0,"",1);
        return &this->printVector.at(0);
    }
/**
 * @brief 
 * return the end of the string for the iterator.
 * @return string* 
 */
    string *OrgChart::lastPrint()
    {
        if(isEmpty(this->root.role)){
        throw invalid_argument("Error:The requested OrgChart-Node has not exist.");      
            }
        this->printVector.clear();
        print(this->root,0,"",1);
        unsigned int vectorLength = printVector.size();
        return &this->printVector[vectorLength];
    }

    ostream &operator<<(ostream &out, OrgChart &orgNode)
    {
        for (auto *i = orgNode.firstPrint(); i != orgNode.lastPrint(); i++){

            out << (*i);

        }
        return out;
    }

// ---------------------------   helpers of the orders  ------------------------------------
/**
 * @brief 
 *  insert all the orgChart into a vector in level order.
 
 * @param currentNode 
 */
    void OrgChart::levelHelper(OrgNode &currentNode)
    {
        vector<OrgNode> temp;
        temp.push_back(currentNode);   // adding the root first
        for(unsigned int i=0;i<temp.size();i++){
            OrgNode boss =  temp.at(i);
            this->levelVector.push_back(boss.role); 
            unsigned int j=0;
            while(j<boss.subRole.size()){
                OrgNode tempNode = boss.subRole[j];  
                temp.push_back(boss.subRole[j]);
                j++;
            }
        }  
    }
/**
 * @brief 
 *  insert all the orgChart into a vector in preorder. 
 *  recursive method. 
 * @param currentNode 
 */
    void OrgChart::preorderHelper(OrgNode &currentNode)
    {
        this->preorderVector.push_back(currentNode.role);
        unsigned int vecSize=currentNode.subRole.size();
        for(unsigned int i=0;i<vecSize;i++){
            OrgNode currentSub = currentNode.subRole[i];
            preorderHelper(currentSub);
        }
    }  
    
/**
 * @brief 
 *  Insert all the orgChart into a vector in reverse order.
 *  The method is like the level order but here we insert the subNodes from the right to the left.
 *  After that we doing the reverse on all the vector.
 * @param currentNode 
 */
    void OrgChart::reverseHelper(OrgNode &currentNode)
    {
         vector<OrgNode> temp;
        vector<string> _roleVector;
        temp.push_back(currentNode);   // adding the root first
        for(unsigned int i=0;i<temp.size();i++){
            OrgNode boss =  temp.at(i);
            _roleVector.push_back(boss.role); 
            unsigned int j=0;
            while(j<boss.subRole.size()){
                unsigned int length = boss.subRole.size();
                unsigned int lastIndex = length-j-1;  
                OrgNode tempNode =  boss.subRole[lastIndex];  
                temp.push_back(boss.subRole[lastIndex]);
                j++;
            }
        } 
        for(unsigned int i=0;i<_roleVector.size();i++){
            unsigned int vecSize = _roleVector.size();
            unsigned int reverseIndex = vecSize-i-1; 
            OrgNode boss =  temp[reverseIndex];
            this->reverseVector.push_back(boss.role); 
        }
    }
}