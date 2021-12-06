// Created by Breanna Powell
// 501 B / FALL
// SID: 0641962
// Due: 2021 12 08

/** Abstract Syntax Tree (AST) Class*/
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "AST.h"
#include "ITokStream.h"
using namespace std;

/** AST Constructor 
 @post This will construct an AST from the leaves up
 @param postfixExpr is a vector of tokens 
   ordered as a postfix expression */
AST::AST(vector<Token>& postfixExpr)
{

};

/** AST Copy Constructor*/
AST::AST(const AST& original)
{

};

/** AST Destructor*/
AST::~AST()
{

};

/** Assignment operator overload
 @post  If successful, 
 @param rhs will contain the original tree to be copied
 @return the original AST */
AST AST::operator=(const AST& rhs)
{

}

/** Simplify the expression
 @post  If successful, the simplify method will look for any
  variables that have already been assigned and stored as ASTs 
  inside of the variable store. Then it will plug those values into the tree. 
  It will need to delete nodes. The original tree is passed by constant reference
  because this function makes a copy to simplify. No harm comes to the original.
 @param v is a variable store (a map of key, value pairs)
 @return a simplified AST */
AST AST::simplify(map<string, AST>& v) const
{

}

/** Convert the expression back to infix and save it as a string
 @post  If successful, this will add parentheses to show order of operations
 @return a string representation of the infix expression */
string AST::toInfix() const
{

}

/** Infix traversal of an AST
 @post  If successful, the simplify method will copy an entire tree.
 @param root is the root node of the AST
 @return the pointer to current node in the AST */
void AST::toInfixHelper(Node* root, string& infixExp)
{

}

/** Copy the tree recursively
 @post  If successful, the simplify method will copy an entire tree.
 @param root is the root node of the original tree
 @return the root node of the new AST */
Node* AST::copy(Node* root)
{

}