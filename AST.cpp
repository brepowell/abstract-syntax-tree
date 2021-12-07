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
#include "AST.h"
#include "ITokStream.h" //for Tokens
using namespace std;

/*When the expression was tokenized and converted to a postfix vector, 
   some tokens were not stored in the vector, such as 
   null, assign, lparen, rparen, eol, and end.
   Precedence was already considered in the conversion to postfix.
   This constructor just needs to build the AST from the vector provided.*/

/** AST Constructor 
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
         ||postfixExpr[i].type_ == TokType::powop
         ||postfixExpr[i].type_ == TokType::powop
      )
      {
         parent = new Node(postfixExpr[i]);
         childRight = operandNodes.top(); //top() returns reference
         operandNodes.pop(); //Removes the element from the stack
         childLeft = operandNodes.top(); //top() returns reference
         operandNodes.pop(); //Removes the element from the stack
      
         parent->right_ = childRight;
         parent->left_ = childLeft;

         //Add the parent to the top of the operandNodes stack
         operandNodes.push(parent);
      }//end if

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
   //root_ = copy(original.root_);
};

/** AST Destructor*/
AST::~AST()
{
//Write a clear or delete node function
};

/** Assignment operator overload
 @post  If successful, 
 @param rhs will contain the original tree to be copied
 @return the original AST */

AST AST::operator=(const AST& rhs)
{
   //Always check for self-assignment
   if (&rhs != this){
      //Before assigning a variable to an AST, the left hand side needs to be deallocated
      //clear();
      //copy the tree (the copy function takes in the root of original)
      //root_ = copy(rhs.root_);
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
/*
AST AST::simplify(map<string, AST>& v) const
{
   /*You need to retain the original form of the AST 
   if it is stored in the variable store.
   That's because variable values can change...
   Produce a new AST that is used for output. - Prof. Stiber */

/*
   AST simplified = v;

   //Create a copy the AST
   //AST expression = copy(this->root_);

   //perform variable substitution - may write a substitute method to help

   //If an operator has two numbers as operands,
   //replace the parent of that subtree with the result
   //delete the leaves

   //continue until no more substitutions are possible
   //return expression;
}
*/

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
   toInfixHelper(root_, infixExp);

   return infixExp;
}

/** Infix traversal of an AST
 @post  If successful, this will help the toInfix method
 @param root is the root node of the AST
 @return the pointer to current node in the AST */
void AST::toInfixHelper(Node* root, string& infixExp) const
{

   if (root != nullptr){
      //See if the token is an operator
      if (root->tok_.type_ != TokType::variable 
         && root->tok_.type_ != TokType::number){
         //if it is, add an open parentheses
         infixExp += "(";
      }//end if

      //Traverse the AST
      toInfixHelper (root->left_, infixExp);
      infixExp += root->tok_.value_ + " ";          //value_ is a string
      toInfixHelper (root->right_, infixExp);

      //See if the token is an operator again
      if (root->tok_.type_ != TokType::variable 
         && root->tok_.type_ != TokType::number){
         infixExp += ")";
      }//end if
   }else{
   return;
   }//end else

}//end toInfixHelper


/** Copy the tree recursively
 @post  If successful, the copy method will copy an entire tree.
 @param root is the root node of the original tree
 @return the root node of the new AST */
/*
Node* AST::copy(Node* root)
{
   //Return if tree is empty
   if(root == nullptr)
      return nullptr;
   
   //Copy the root node first
   Node* newNode = new Node(root->tok_);
   
   //Use recursion to copy the left and right subtrees
   newNode->left_ = copy(root->left_);
   newNode->right_ = copy(root->right_);

   //Return the pointer to the root node
   return newNode;
}
*/