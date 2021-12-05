// Created by Breanna Powell
// 501 B / FALL
// SID: 0641962
// Due: 2021 12 08

/** Tokenizer Wrapper Class
    @file ITokStream.h*/
#ifndef ITOKSTREAM_H
#define ITOKSTREAM_H
#include <iostream>
#include <string>

class ITokStream
{
   public:
   /* Constructor*/
   ITokStream(istream& inputStream);

   //enum choices for TokType:
   enum class TokType { null, addop, mulop, powop, variable, number, lparen, rparen, assign, eol, end };

   /*TOKEN STRUCT*/
   struct Token 
   {
      Token(TokType t = TokType::null, string v = "")
      :  type_(t), value_(v) {};

      //The type of token the Token object holds
      TokType type_;

      //The String of the token that the object holds
      string value_;
   };//end Token class

   /** This input operator>> overload will take in
   a token object and then help to set the TokType
   for that object. In essence, this is a setter for
   the type_ variable in the TokType enum class
    @post The token will have a TokType set
      inside of the TokType type_ variable
    @param rhs will take in a token object */
   ITokStream& operator>>(Token& rhs);

   /** Explicit type converter to a bool will
   test if there is an error on the input stream.
    @return  True if there is a flag */
   explicit operator bool() const;

   private:
   //The istream input
   istream& is_;

};//end ITokStream class
#endif