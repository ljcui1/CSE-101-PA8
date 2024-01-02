//-----------------------------------------------------------------------------
// Name: Lia Cui
// CRUZID: ljcui
// Assignment Name: PA8
//
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"
#if defined(_MSC_VER)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

using namespace std;

int main(){


    //Dictionary A;
    //A.setValue("d", 1);
    //A.setValue("b", 5);
    //A.setValue("a", 10);
    //A.setValue("c", 15);
    //A.setValue("f", 20);
    //A.setValue("e", 25);
    //A.setValue("g", 30);
    //A.begin();
    //A.remove("a");
    //for (A.begin(); A.hasCurrent(); A.next()) {
    //    cout << "(" + A.currentKey() + ", " << A.currentVal() << ") ";
    //    A.currentVal()++;  // change value
    //    cout << "(" + A.currentKey() + ", " << A.currentVal() << ")\n";
    //}
    //cout << endl;

    //string X = "abc";
    //X.~basic_string();

    //string K[] = { // words to insert
    //                 "a",
    //                 "b"
    //};

    //K[0].clear();
    //K[1].clear();

   string S[] =   { // words to insert
                     "plaices",
                     "ambusher",
                     "crosby",
                     "wattles",
                     "pardoner",
                     "pythons",
                     "second",
                     "forms",
                     "impales",
                     "pic",
                     "verticals",
                     "recriminator",
                     "depressants",
                     "cul",
                     "potables",
                     "norm",
                     "reinsurer",
                     "deschooler",
                     "recoining",
                     "dissocialised",
                     "cohabit",
                     "hemiolia",
                     "cantling",
                     "glamorized",
                     "millesimal",
                     "glagolitic"
                  };
   string T[] =   { // words to delete
                     "second",
                     "forms",
                     "impales",
                     "pic",
                     "verticals",
                     "recriminator",
                     "depressants",
                     "cul",
                     "potables",
                     "norm",
                     "reinsurer",
                     "deschooler",
                     "recoining",      
                  };

   Dictionary A;
   Dictionary B;

   cout << endl;
   //A.setValue("plaices", 1);
   //A.setValue("ambusher", 2);
   //A.setValue("crosby", 3);
   //A.setValue("wattles", 4);
   //A.setValue("a", 1);
   //A.setValue("b", 2);
   //A.setValue("c", 3);
   //A.setValue("d", 4);
   //int x = 1;
   // insert some pairs into A
   for(int i=0; i<26; i++){
      A.setValue(S[i], i+1);
   }

   // call operator=()
    B = A;


  //  //cout << "forward iteration on B, changing values:" << endl;
  //  //for (A.begin(); A.hasCurrent(); A.next()) {
  //  //    cout << "(" + A.currentKey() + ", " << A.currentVal() << ") ";
  //  //    A.currentVal()++;  // change value
  //  //    cout << "(" + A.currentKey() + ", " << A.currentVal() << ")\n";
  //  //}
  //  //cout << endl;
  //  //cout << "forward iteration on B, changing values:" << endl;
  //  //for (B.begin(); B.hasCurrent(); B.next()) {
  //  //    cout << "(" + B.currentKey() + ", " << B.currentVal() << ") ";
  //  //    B.currentVal()++;  // change value
  //  //    cout << "(" + B.currentKey() + ", " << B.currentVal() << ")\n";
  //  //}
  //  //cout << endl;

   B.setValue("deschooler", 101);
   B.setValue("reinsurer", 102);
   B.setValue("glagolitic", 103);
   B.setValue("cul", 104);
   B.setValue("ambusher", 105);

  // // call copy constructor
   Dictionary C = B;

  cout << "A.size() = " << A.size() << endl  << A << endl;
  cout << "B.size() = " << B.size() << endl  << B << endl;
  cout << "C.size() = " << C.size() << endl  << C << endl;

   // check copy constructor
   cout << "copy constructor creates identical trees: " << endl;
   //cout << C.pre_string() << endl;
   //cout << B.pre_string() << endl;
   cout << ((C.pre_string()==B.pre_string())?"true":"false") << endl;
   cout << endl;

   // check operator==()
   cout << "A==B is " << (A==B?"true":"false") << endl;
   cout << "B==C is " << (B==C?"true":"false") << endl;
   cout << "C==A is " << (C==A?"true":"false") << endl << endl;

   // perform alterations on A
   cout << "A.getValue(\"hemiolia\") = " << A.getValue("hemiolia") << endl;
   A.getValue("hemiolia") *= 10; // change the value associated with "hemiolia"
   cout << "A.getValue(\"hemiolia\") = " << A.getValue("hemiolia") << endl << endl;

   // check state of A
   cout << "A.size() = " << A.size() << endl  << A << endl;
   cout << "A pre-order: " << endl << A.pre_string() << endl;

   // remove some pairs from A
   for(int i=0; i<13; i++){ 
      A.remove(T[i]);
   }

   // check state of A
   cout << "A.size() = " << A.size() << endl  << A << endl;
   cout << "A pre-order: " << endl << A.pre_string() << endl;

   // do forward iteration on B
   //cout << "forward iteration on B, changing values:" << endl;
   //for (A.begin(); A.hasCurrent(); A.next()) {
   //    cout << "(" + A.currentKey() + ", " << A.currentVal() << ") ";
   //    A.currentVal()++;  // change value
   //    cout << "(" + A.currentKey() + ", " << A.currentVal() << ")\n";
   //}
   //cout << endl;
   cout << "forward iteration on B, changing values:" << endl;
   for(B.begin(); B.hasCurrent(); B.next()){
      cout << "("+B.currentKey()+", " << B.currentVal() << ") ";
      B.currentVal()++;  // change value
      cout << "("+B.currentKey()+", " << B.currentVal() << ")\n";
   }
   cout << endl;

   // do reverse iteration on C
   cout << "reverse iteration on C, changing values" << endl;
   for(C.end(); C.hasCurrent(); C.prev()){
      cout << "("+C.currentKey()+", " << C.currentVal() << ") ";
      C.currentVal()++;  // change value
      cout << "("+C.currentKey()+", " << C.currentVal() << ")\n";
   }
   cout << endl;
   
   // check exceptions
   cout << "test pre-condition errors:" << endl;
   try{
      A.getValue("blah");
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.remove("blah");
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.currentKey();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.currentVal();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }  
   try{
      A.next();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.prev();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   cout << endl;  

   A.~Dictionary();
   B.~Dictionary();
   C.~Dictionary();
   for(int i=0; i<26; i++){
       S[i].~basic_string();
   }
   for (int i = 0; i < 13; i++) {
       T[i].~basic_string();
   }


#if defined(_MSC_VER)
   _CrtDumpMemoryLeaks();
#endif
   return( EXIT_SUCCESS );
}
