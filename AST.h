// Created by Breanna Powell
// 501 B / FALL
// SID: 0641962
// Due: 2021 12 08

/** Abstract Syntax Tree (AST) Class
    @file AST.h*/
#ifndef AST_H
#define AST_H
#include <iostream>
#include <string>
#include "ITokStream.h" //for Tokens
using namespace std;

class AST
{
   public:

   /**
    @brief Construct a new AST::AST object */
   AST();

   /**
    * @brief This will construct an AST from the leaves up
      @param postfixExpr is a vector of tokens 
      ordered as a postfix expression */
   explicit AST(vector<Token>& postfixExpr);

   /** AST Copy Constructor*/
   AST(const AST& original); 

   /** AST Destructor*/
   ~AST();

   /** Assignment operator overload
    @post  If successful, 
    @param rhs will contain the original tree to be copied
    @return the original AST */
   AST operator=(const AST& rhs);

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
   AST simplify(map<char, AST>& v) const;

   /** Convert the expression back to infix and save it as a string
    @post  If successful, this will add parentheses 
    to show order of operations
    @return a string representation of the infix expression */
   string toInfix() const;

   protected:

   /** Node struct */
   struct Node
   {
      explicit Node(Token t)
         :  tok_(t), left_(nullptr), right_(nullptr) {};

      //stores a token object that has a type
      Token tok_;
      Node* left_;
      Node* right_;
   };//end Node struct

   private:

   /** Infix traversal of an AST
    @post  If successful, this will help the toInfix method
    @param root is the root node of the AST
    @return the pointer to current node in the AST */
   void toInfixHelper(Node* root, string& infixExp) const;

   /** Copy the tree recursively
    @post  If successful, the copy method will copy an entire tree.
    @param root is the root node of the original tree
    @return the root node of the new AST */
   AST::Node* copy(Node* root);

   /**
   * @brief Substitute will find all of the variables
   * in variable store that have already been assigned
   * by the user. These variables need to be replaced by
   * the AST that is in the variable store.
   * (This could be a single node, like x := 1, or
   * it could be another subexpression, like a := z + y)
   * @param root passes the root of the AST to simplify
   * @param v the variable storage (stored the ASTs)
   */
   void substitute(Node* root, map<char, AST>& v,
   vector<Token>& postfixTokens);

   /**
   * @brief Helps substitute by traversing in postorder
   * and adding the tokens in postfix order
   * @param root the root node of the AST
   * @param postfixTokens the vector to store the tokens
   */
   void substituteHelper(Node* root, vector<Token> &postfixTokens);

   /**
   * @brief This will take an AST and simplify
   * all subexpressions until the final expression is
   * in its simplest form
   * @param root the current node of the AST
   */
   void simplestForm(Node* root);

   /**
   * @brief Empties an AST by deleting all nodes
   * and nulling all pointers
   * @param root the pointer to the root node for the tree*/
   void clear(Node* root);

   //Pointer to the root node of the AST, which points to its children
   Node* root_;

};//end AST class
#endif