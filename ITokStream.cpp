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
 @param rhs will take in a token object */
ITokStream& ITokStream::operator>>(Token& rhs)
{
   //For the token object,
   //set type_ (TokType)
   //set value_ (string)
   string number = "";
   number.push_back(is_.peek());
 
   if (is_.peek() == '.'){
      rhs.value_ = is_.get();
      rhs.type_ = TokType::end; //end  
   }else if (is_.peek() == '\n' ){
      rhs.value_ = is_.get();
      rhs.type_ = TokType::eol; //eol  
   }else if (is_.peek() == ':'){
      rhs.value_ += is_.get() + is_.get();
      rhs.type_ = TokType::assign; //assign
   }else if (is_.peek() == ')'){
      rhs.value_ = is_.get();
      rhs.type_ = TokType::rparen; //rparen
   }else if (is_.peek() == '(' ){
      rhs.value_ = is_.get();
      rhs.type_ = TokType::lparen; //lparen
   }else if (isdigit(number.back())){
      while (isdigit(number.back())){       // loop to get double digit numbers
         rhs.value_ += is_.get();
         number.push_back(is_.peek());
      }//end while
      rhs.type_ = TokType::number; //number
   }else if (tolower(number[0]) >= 'a' || tolower(number[0]) <= 'z'){
      rhs.value_ = is_.get();
      rhs.type_ = TokType::variable; //variable
   }else if (is_.peek() == '^' ){
      rhs.value_ = is_.get();
      rhs.type_ = TokType::powop; //powop
   }else if (is_.peek() == '*' ){
      rhs.value_ = is_.get();
      rhs.type_ = TokType::mulop; //mulop
   }else if (is_.peek() == '/' ){
      rhs.value_ = is_.get();
      rhs.type_ = TokType::mulop; //mulop
   }else if (is_.peek() == '+'){
      rhs.value_ = is_.get();
      rhs.type_ = TokType::addop; //addop
   }else if (is_.peek() == '-' ){
      rhs.value_ = is_.get();
      rhs.type_ = TokType::addop; //addop
   }else{
      //THROW AN ERROR - not an acceptable type - &
   }

   number = "";

}//end operator >>

/** Explicit type converter to a bool will
test if there is an error on the input stream.
 @return  True if there is a flag */
ITokStream::operator bool() const
{

}