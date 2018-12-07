//
//  administration.hpp
//  Social Media Application
//
//  Created by annykyforu on 21.11.18.
//  Copyright © 2018 PRG2_ws18. All rights reserved.
//

#ifndef administration_h
#define administration_h

#include <string>
#include <unordered_map>
#include <memory>
#include <iostream>
#include "person.h"
using namespace std;

struct Administration
{
  unordered_map<string, shared_ptr<Person>> map; // Instance variable
  string create_person(string); //Creates Person in the map. If name already exists => overwrite
  void del_person(string); //If no person can be found −> Runtime Error
  ostream& print(ostream&) const; //Output
};
ostream& operator<<(ostream&, const Administration&);


/*
 Output for Administration:
 Map: [
 value
 value
 ]
 z.B.: Map: [
 [Name: Albus Dumbledore, Accounts: {[Name: Hogwarts, Owner: {Albus Dumbledore, Dolores Umbridge}, #Msgs: 1}]
 [Name: Dolores Umbridge, Accounts: {[Name: Hogwarts, Owner: {Albus Dumbledore, Dolores Umbridge}, #Msgs: 1}]
 ]
 */
#endif /* administration_h */
