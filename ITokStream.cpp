// Created by Breanna Powell
// 501 B / FALL
// SID: 0641962
// Due: 2021 12 08

/** Tokenizer Wrapper Class*/  
#include <iostream>
#include <string>
#include "ITokStream.h"
using namespace std;
  
/* Constructor*/
ITokStream::ITokStream(istream& inputStream)
   :  is_(inputStream){};

/** This input operator>> overload will take in
a token object and then help to set the TokType
for that object. In essence, this is a setter for
the type_ variable in the TokType enum class
 @post The token will have a TokType set
   inside of the TokType type_ variable
 @param rhs will take in a token object
 @return will return an ITokStream reference */
ITokStream& ITokStream::operator>>(Token& rhs)
{
   //For the token object,
   //set type_ (TokType)
   //set value_ (string)
   rhs.value_ = "";

   //End signals
   if (is_.peek() == '.'){
      rhs.value_ += is_.get(); //get is a char, adds to string
      rhs.type_ = TokType::end; //end
      //cerr << "Got a end" << endl;  //test
   }else if (is_.peek() == '\n' ){
      rhs.value_ += is_.get();
      rhs.type_ = TokType::eol; //eol 
      //cerr << "Got a eol" << endl; //test

   //Spaces
   }else if (is_.peek() == ' '){
      rhs.value_ += is_.get();
      rhs.type_ = TokType::null; //null
      //cerr << "Got a space" << endl; //test

   //Operators 
   }else if (is_.peek() == ':'){
      rhs.value_ += is_.get();
      if(is_.peek() == '='){
         rhs.value_ += is_.get();
         rhs.type_ = TokType::assign; //assign :=
      }else{
         //ERROR - not an assignment operator
      }//end if/else
   }else if (is_.peek() == '^' ){
      rhs.value_ += is_.get();
      rhs.type_ = TokType::powop; //powop
   }else if (is_.peek() == '*' ){
      rhs.value_ += is_.get();
      rhs.type_ = TokType::mulop; //mulop
   }else if (is_.peek() == '/' ){
      rhs.value_ += is_.get();
      rhs.type_ = TokType::mulop; //mulop
   }else if (is_.peek() == '+'){
      rhs.value_ += is_.get();
      rhs.type_ = TokType::addop; //addop
      //cerr << "Got a +" << endl; //test
   }else if (is_.peek() == '-' ){
      rhs.value_ += is_.get();
      rhs.type_ = TokType::addop; //addop

   //Parentheses
   }else if (is_.peek() == ')'){
      rhs.value_ += is_.get();
      rhs.type_ = TokType::rparen; //rparen
   }else if (is_.peek() == '(' ){
      rhs.value_ += is_.get();
      rhs.type_ = TokType::lparen; //lparen

   //Operands
   }else if (isdigit(is_.peek())){
      //get the first number in the istream
      rhs.value_ += is_.get();
      rhs.type_ = TokType::number; //number
      //loop to get double digit (or longer) numbers 
      while (isdigit(is_.peek())){
         rhs.value_ += is_.get(); //continue to add digits onto value_
         //THROW AN ERROR - if the string is longer than an int can hold
      }//end while
      //cerr << "Got a number" << endl; //test
      //cerr << "number is " << rhs.value_ << endl;
   }else if (isalpha(is_.peek())){
      rhs.value_ += is_.get();
      rhs.type_ = TokType::variable; //variable
      //cerr << "Got a letter" << endl; //test
   }else{
      //THROW AN ERROR - not an acceptable type - &
      //Currently, these are NULL type, as are whitespaces
   }

   return *this;

}//end operator>>

/** Explicit type converter to a bool will
test if there is an error on the input stream.
 @return  True if there is a flag */
/*ITokStream::operator bool() const
{

}
*/
