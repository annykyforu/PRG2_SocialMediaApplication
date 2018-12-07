//
//  person.h
//  Social Media Application
//
//  Created by annykyforu on 21.11.18.
//  Copyright © 2018 PRG2_ws18. All rights reserved.
//

#ifndef person_h
#define person_h

#include <vector>
#include <string>
#include <memory>
#include <iostream>

using namespace std;

class SocialMediaAccount;
class VipAccount;
class NormalAccount;

class Person : public enable_shared_from_this<Person>{
private:
  string name;  //Not empty
  vector<shared_ptr<SocialMediaAccount>> media_accounts;  //Empty at start
public:
  Person();
  Person(string);
  string get_name() const;
  int add_account(string, int); //int Variable determines mode. 1 = VipAccount, 0 = NormalAccount. Returns accountnumber
  bool remove_account(int); //Can remove Account with id int
  bool share(shared_ptr<Person>, shared_ptr<SocialMediaAccount>); //this teilt mit der Person den Account. Zuvor muss noch geprüft werden, ob a) this den Account überhaupt besitzt und b) ob die andere Person den Account nicht bereits besitzt den this teilen will.
  ostream& print(ostream&) const;
  ostream& print_small(ostream&) const;
  const vector<shared_ptr<SocialMediaAccount>>& get_accounts() const;
};
ostream& operator<<(ostream&, const Person&);


#endif /* person_h */

/*
 The output of a Person-Object should use the following format:
 [Name: name, Account: {[Name: Acc1.name, Owner: {Acc1.owner, Acc1.owner2}, #Msgs : len(Acc1.msg)], [Name: Acc2.name ...}]
 z .B.
 [Name: Albus Dumbledore, Accounts:{[Name: Hogwarts, Owner: {Albus Dumbledore, Dolores Umbridge}, #Msgs: 1]}]
 */
