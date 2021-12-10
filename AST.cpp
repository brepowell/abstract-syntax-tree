// Created by Breanna Powell
// 501 B / FALL
// SID: 0641962
// Due: 2021 12 08

/** Abstract Syntax Tree (AST) Class*/
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <queue>
#include <stack>
#include <sstream>
#include <cmath>
#include "AST.h"
#include "ITokStream.h" //for Tokens
using namespace std;

/* This class will create an Abstract Syntax Tree object.
   Notes:
   When the expression was tokenized and converted to a postfix vector, 
   some tokens were not stored in the vector, such as 
   null, assign, lparen, rparen, eol, and end.
   Precedence was already considered in the conversion to postfix.
   The constructor just needs to build the AST from the vector provided.
   There needs to be a substitute method and a simplify method to
   perform the act of combining nodes and solving the expression.
   There also needs to be an infix method that converts the final
   expression to infix again.
   */

/**
 * @brief Construct a new AST::AST object */
AST::AST()
   : root_(nullptr){}

/** AST Parameterized Constructor 
 @post This will construct an AST from the leaves up
 @param postfixExpr is a vector of tokens 
   ordered as a postfix expression */
AST::AST(vector<Token>& postfixExpr)
{
   //Initialize pointers for the tree structure
   Node* parent = nullptr;
   Node* childLeft = nullptr;
   Node* childRight = nullptr;

   //Create a queue to hold the values from the vector
   queue<Token> operandTokens; 

   //Create a stack to hold Node pointers
   stack<Node*> operandNodes;

   //Loop through the vector
   for (int i = 0; i < postfixExpr.size(); i++){

      //Grab operand tokens to add to the queue
      //of tokens. Stop at an operator.
      //This queue will hold only a subsection of the whole expression.
      while (i < postfixExpr.size() 
         && (postfixExpr[i].type_ == TokType::variable 
         || postfixExpr[i].type_ == TokType::number)){
         //Add numbers and variables to the operands queue
         operandTokens.push(postfixExpr[i]);
         i++; //Move index to the next position in the vector
      }

      //Loop through the queue, add the operands to the node stack
      while (!operandTokens.empty()){
         Node* nodePtr = new Node(operandTokens.front());
         operandTokens.pop();//removes from queue
         //Node constructor takes in a token object
         operandNodes.push(nodePtr);
      }
      
      //Operators will be internal nodes
      //Operands will be leaf nodes
      if(postfixExpr[i].type_ == TokType::addop
         ||postfixExpr[i].type_ == TokType::mulop
         ||postfixExpr[i].type_ == TokType::powop){
         parent = new Node(postfixExpr[i]);//make a parent node
         childRight = operandNodes.top(); //top() returns reference
         operandNodes.pop(); //Removes the element from the stack
         childLeft = operandNodes.top(); //top() returns reference
         operandNodes.pop(); //Removes the element from the stack
      
         parent->right_ = childRight;
         parent->left_ = childLeft;

         //Add the parent to the top of the operandNodes stack
         operandNodes.push(parent);
      
      //Account for cases where there is only 1 node that is a number
      }else if (postfixExpr[0].type_ == TokType::number
         && postfixExpr.size() == 1){
         //Add the parent to the top of the operandNodes stack
         parent = operandNodes.top();
         operandNodes.pop(); //Removes the element from the stack
      }//end if/else

   }//end outer for

   //The previous loops should build the tree from the leaves up.

   //The final parent node will be the root node for the whole tree object.
   root_ = parent;

   //Clear the vector
   postfixExpr.clear();
   
   //null the pointers
   parent = nullptr;
   childLeft = nullptr;
   childRight = nullptr;

};//end constructor

/** AST Copy Constructor*/
AST::AST(const AST& original)
{
   //copy returns a pointer to the new root
   root_ = copy(original.root_);
};

/** AST Destructor*/
AST::~AST()
{
   //Goes in postorder to delete all nodes
   clear(root_);
};

/** Assignment operator overload
 @post  If successful, 
 @param rhs will contain the original tree to be copied
 @return the original AST */
AST AST::operator=(const AST& rhs)
{
   //Always check for self-assignment
   if (&rhs != this){
      //Before assigning a variable to an AST, 
      //the left hand side needs to be deallocated
      clear(root_);
      //copy the tree (the copy function takes in the root of original)
      root_ = copy(rhs.root_);
   }//end if

   return *this;
}//end operator=

/** Simplify the expression
 @post  If successful, the simplify method 
  will look for any variables that have already 
  been assigned and stored as ASTs inside of the 
  variable store. Then it will plug those values 
  into the tree. It will need to delete nodes. 
  The original tree is passed by constant reference
  because this function makes a copy to simplify. 
  No harm comes to the original.
 @param v is a variable store (a map of key, value pairs)
 @return a simplified AST */
AST AST::simplify(map<char, AST>& v) //const
{
   Node* root = root_;
   /*You need to retain the original form of the AST 
   if it is stored in the variable store.
   That's because variable values can change...
   Produce a new AST that is used for output. - Prof. Stiber */

   //Make a vector - postfix vector (pass it to substitute)
   vector<Token> postFixForSimplifying;

   //Call substitute to make sure each variable is replaced
   //This will recursively call itself until
   //no more substitutions are possible.
   substitute(root, v, postFixForSimplifying);

   //Create an AST from that postfix vector
   AST expression(postFixForSimplifying);
   
   //cerr << "Before simplest: " << root_->tok_.value_ << endl;

   //Call simplestForm to do the math
   //and simplify the whole AST to the simplest form.
   simplestForm(expression.root_);

   //cerr << "After simplest: " << root_->tok_.value_ << endl;
   
   //Deallocate the space for the vector
   postFixForSimplifying.clear();
   //The AST has been simplified as much as possible.
   return expression;
}


/**
 * @brief Substitute will find all of the variables
 * in variable store that have already been assigned
 * by the user. These variables need to be replaced by
 * the AST that is in the variable store.
 * (This could be a single node, like x := 1, or
 * it could be another subexpression, like a := z + y)
 * @param root passes the root of the AST to simplify
 * @param v the variable storage (stored the ASTs)
 * @param postfixTokens will store the nodes for the
 * simplification in postfix order
 */
void AST::substitute(Node* root, map<char, AST>& v,
   vector<Token>& postfixTokens)
{
   //Convert the AST back into postfix for ease of substitution
   //Traverse in postorder and add to postfix vector.
   if(root != nullptr)
      substituteHelper(root_, postfixTokens);

   //For each token in the vector, check if it needs to be subsituted
   for(int i = 0; i < postfixTokens.size(); i++){
      //Look for variables, skip numbers and operators
      if(postfixTokens[i].type_ == TokType::variable){
         //The search key for the variable store is
         //the value of the token i.
         char key = postfixTokens[i].value_[0];
         map<char,AST>::iterator it;
         it = v.find(key);
      
         //If the node's value exists as a variable in storage
         if (it != v.end()){
            //Call the substitute helper again for whatever
            //AST might be stored using this key
            vector<Token> innerTokens;
            substituteHelper(it->second.root_, innerTokens);

            //Combine the postfixTokens and the innerTokens
            vector<Token>::iterator t = postfixTokens.begin() + i;
            postfixTokens.insert(t, innerTokens.begin(), innerTokens.end());
         }//end inner if
      }//end if
   }//end for
}//end substitute

/** Substitute Helper
 * @brief Helps substitute by traversing in postorder
 * and adding the tokens in postfix order
 * @param root the root node of the AST
 * @param postfixTokens the vector to store the tokens
 */
void AST::substituteHelper(Node* root, vector<Token> &postfixTokens)
{
   if(root->left_ != nullptr)
      substituteHelper(root->left_, postfixTokens);
   if(root->right_ != nullptr)
      substituteHelper(root->right_, postfixTokens);
   postfixTokens.push_back(root->tok_); //add tokens to the vector
}

/** Simplest Form - simplifies as much as possible
 * @brief This will take an AST and simplify
 * all subexpressions until the final expression is
 * in its simplest form
 * @param root the current node of the AST
 */
AST::Node* AST::simplestForm(Node* root)
{
   if(root->left_ != nullptr)
      simplestForm(root->left_);
   if(root->right_ != nullptr)
      simplestForm(root->right_);

   //addop, mulop, powop, variable, number
   //Look for nodes where there is an operator
   //as the parent node and 2 numbers for children
   if (root->tok_.type_ != TokType::number &&
      root->left_ != nullptr &&
      root->right_ != nullptr && 
      root->left_->tok_.type_ == TokType::number &&
      root->right_->tok_.type_ == TokType::number){
      
      //Store the values from the nodes in a subtree
      //always put the left value into the result first
      int result = stoi(root->left_->tok_.value_);
      int operand2 = stoi(root->right_->tok_.value_);

      if (root->tok_.type_ == TokType::addop){
         //Add numbers
         if(root->tok_.value_ == "+"){
            result += operand2;
         }else if(root->tok_.value_ == "-"){
            result -= operand2;
         }//end inner if/else  
      }else if (root->tok_.type_ == TokType::mulop){
         if(root->tok_.value_ == "*"){
            result *= operand2;
         }else if(root->tok_.value_ == "/"){
            result /= operand2;
         }  
      }else if (root->tok_.type_ == TokType::powop){
         result = pow(result,operand2);
      }//end else-if statements
      
      //Replace the parent node with the result
      //Change the parent node's value
      root->tok_.value_ = to_string(result);
      
      //Change the parent node's type
      root->tok_.type_ = TokType::number;
      
      //Delete the child nodes
      delete root->left_;
      delete root->right_;
      root->left_ = nullptr;
      root->right_ = nullptr;      
   }//end if - the parent node has been replaced with a number

   //cerr << "Root is: " << root->tok_.value_ << endl; //TEST

   return root;
}//end simplestForm

/** Convert the expression back to infix and save it as a string
 @post  If successful, this will add parentheses 
 to show order of operations
 @return a string representation of the infix expression */
string AST::toInfix() const
{
   //Create a string
   string infixExp = "";

   //Pass the root of the AST to the infixHelper
   //Pass the infixExp string too
   if (root_ != nullptr){
      toInfixHelper(root_, infixExp);
   }

   return infixExp;
}

/** Infix traversal of an AST
 @post  If successful, this will help the toInfix method
 @param root is the root node of the AST
 @return the pointer to current node in the AST */
void AST::toInfixHelper(Node* root, string& infixExp) const
{   
   //See if the token is an operator
   if (root->tok_.type_ != TokType::variable 
      && root->tok_.type_ != TokType::number){
      //if it is, add an open parentheses to the string
      infixExp += "(";
   }//end if

   //Traverse the AST
   if(root->left_ != nullptr)
      toInfixHelper (root->left_, infixExp);
   infixExp += root->tok_.value_ + " ";          //value_ is a string
   if(root->right_ != nullptr)
      toInfixHelper (root->right_, infixExp);

   //See if the token is an operator again
   if (root->tok_.type_ != TokType::variable 
      && root->tok_.type_ != TokType::number){
      infixExp += ")";
   }//end if

   //Get rid of any extra spaces in the infixExp
   for(int i = 0; i <infixExp.size(); i++){
      if(i < infixExp.size() - 1 && 
      infixExp[i] == ' ' &&
      infixExp[i+1] == ')'){
         infixExp.erase(i,1);
      }
   }
}//end toInfixHelper

/** Copy the tree recursively
 @post  If successful, the copy method will copy an entire tree.
 @param root is the root node of the original tree
 @return the root node of the new AST */
AST::Node* AST::copy(Node* root)
{
   //Return if tree is empty
   if(root == nullptr)
      return nullptr;
   
   //Copy the root node first - preorder traversal
   Node* newNode = new Node(root->tok_);
   
   //Use recursion to copy the left and right subtrees
   if(root->left_ != nullptr)
      newNode->left_ = copy(root->left_);
   if(root->right_ != nullptr)
      newNode->right_ = copy(root->right_);

   //Return the pointer to the root node
   return newNode;
}

/** Clear
 * @brief Empties an AST by deleting all nodes
 * and nulling all pointers
 * @param root the pointer to the root node for the tree*/
void AST::clear(Node* root){
   if(root != nullptr){
      if(root->left_ != nullptr)
         clear(root->left_);
      if(root->right_ != nullptr)
         clear(root->right_);

      root->left_ = nullptr;
      root->right_ = nullptr;
      delete root;
      root = nullptr;
   }//end if - root node was null already
}//end clear