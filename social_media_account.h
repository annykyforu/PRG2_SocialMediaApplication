//
//  social_media_account.h
//  Social Media Application
//
//  Created by annykyforu on 21.11.18.
//  Copyright © 2018 PRG2_ws18. All rights reserved.
//

#ifndef social_media_account_h
#define social_media_account_h

#include <vector>
#include <string>
#include <memory>
#include <iostream>

using namespace std;
static int current_accnumb{0};

class Person;

class SocialMediaAccount{
private:
  constexpr static size_t message_limit{100};
  
  int score; //Starts at 0
  string name;  //Not empty
  int accountnumber; //Unique. Tip: consecutive number

  vector<weak_ptr<Person>> authorized_persons;  //Filled in Constructor
  vector<string> messages;  //Empty at start
  void add_msg(const string);
public:
  SocialMediaAccount(string, shared_ptr<Person>);
  ~SocialMediaAccount();
  bool add_person(shared_ptr<Person>);
  bool clear_weak_ptr();  //true if weak ptr removed, removes dangling weak ptr
  void clear_messages();
  virtual int calc_score(string) = 0;
  void write_msg(shared_ptr<SocialMediaAccount>, string);   //Error if limit has already been reached. write_msg increases score. Value yielded by calc score(string)
  size_t size() const;  //Number of messages
  int get_accountnumber() const;
  string get_name() const;
  size_t get_auth_persons() const;

  virtual ostream& print(ostream&) const;
  ostream& print_small(ostream&) const;
};

ostream& operator<<(ostream&, const SocialMediaAccount&);

/*
 The output of a SocialMediaAccount-Object should use the following format:
 Note: The printing of a SocialMediaAccount-Object is more verbose if it is printed directly and not by a Person-Object.
 [Name: name, id: accountnumber, Msgs: {msg1, msg2}, Owner: {person1.name, person2.name}, Score: {score}]
 z .B.
 [Name: Hogwarts , id: 1, Msgs: {Welcome to Wizardy , 10 points for Gryffindor}, Owner: {Albus Dumbledore , Dolores Umbridge}, Score : 5]
*/

class VipAccount : public SocialMediaAccount{
public:
  VipAccount(string, shared_ptr<Person>);
  int calc_score(string) override;  //Returns (10 + size of string) % 20
  ostream& print(ostream&) const override ; //Prints " (VIP)". Pay attention to spaces
};

class NormalAccount : public SocialMediaAccount{
public:
  NormalAccount(string, shared_ptr<Person>);
  int calc_score(string) override;  //Returns (5 + size of string) % 10
  ostream& print(ostream&) const override ; //Prints " (Normal)". Pay attention to spaces
};


#endif /* social_media_account_h */
