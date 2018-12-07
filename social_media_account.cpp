//
//  social_media_account.cpp
//  Social Media Application
//
//  Created by annykyforu on 21.11.18.
//  Copyright © 2018 PRG2_ws18. All rights reserved.
//

#include <algorithm>
#include "social_media_account.h"
#include "person.h"

SocialMediaAccount::SocialMediaAccount(string _name, shared_ptr<Person> _auth) : score{0}, name{_name}, accountnumber{current_accnumb++}
{
  weak_ptr<Person> pers_ptr = _auth;
  authorized_persons.push_back(pers_ptr);
}
SocialMediaAccount::~SocialMediaAccount() {}

void SocialMediaAccount::add_msg(const string msg)
{
  if(messages.size() >= message_limit){
    throw runtime_error("Error! Message limit has been reached.\n");
  } else {
    messages.push_back(msg);
  }
}

bool SocialMediaAccount::add_person(shared_ptr<Person> pers)
{
  auto find_p = count_if(authorized_persons.begin(), authorized_persons.end(),
                        [&pers](const weak_ptr<Person>& wp){ return pers == wp.lock(); }
                        );
  if(find_p != 0) {
    return false;
  } else {
    authorized_persons.push_back(pers);
    return true;
  }
}

bool SocialMediaAccount::clear_weak_ptr()
{
  bool status{false};
  auto temp = authorized_persons.begin();
  while (temp != authorized_persons.end()) {
    if((*temp).expired()) {
      authorized_persons.erase(temp);
      status = true;
    } else {
      ++temp;
    }
  }
  return status;
}

void SocialMediaAccount::clear_messages() { messages.clear(); }

void SocialMediaAccount::write_msg(shared_ptr<SocialMediaAccount> acc, string msg)
{
  try {
    acc->add_msg(msg);
  } catch (const runtime_error& error) {
    cout << error.what();
    return;
  }
  this->score += calc_score(msg);
}

size_t SocialMediaAccount::size() const { return messages.size(); }
int SocialMediaAccount::get_accountnumber() const { return accountnumber; }
string SocialMediaAccount::get_name() const { return name; }
size_t SocialMediaAccount::get_auth_persons() const { return authorized_persons.size(); }

ostream& SocialMediaAccount::print(ostream& o) const
{
  o << "[Name: " << name << ", id: " << accountnumber << ", ";
  o << "Msgs: {";
  size_t count_msgs = this->size();
  for(auto& msg : this->messages)
  {
     --count_msgs;
     o << msg;
     if (count_msgs > 0 ) { o << ", "; }
  }
  o << "}, Owner: {";
  size_t count_persons = authorized_persons.size();
  for_each(authorized_persons.begin(), authorized_persons.end(),
           [&o, &count_persons](const weak_ptr<Person>& wp)
           {
             --count_persons;
             try {
               auto temp_ptr = wp.lock();
               temp_ptr->print_small(o);
             } catch (bad_weak_ptr bwp) {
               throw runtime_error("Error! Person does not exist.");
             }
             if(count_persons > 0) { o << ", "; }
           });
  o << "}, Score: " << score << "]";
  return o;
}

ostream& SocialMediaAccount::print_small(ostream& o) const
{
  o << "[Name: " << name << ", Owner: {";
  size_t count_owners = authorized_persons.size();
  for_each(authorized_persons.begin(), authorized_persons.end(),
           [&o, &count_owners](const weak_ptr<Person>& wp)
           {
             --count_owners;
             try {
               auto temp_ptr = wp.lock();
               temp_ptr->print_small(o);
             } catch (bad_weak_ptr bwp) {
               throw runtime_error("Error! Person does not exist.");
             }
             if(count_owners > 0) { o << ", "; }
           });
  o << "}, #Msgs: " << this->size() << "]";
  return o;
}

ostream& operator<<(ostream& o, const SocialMediaAccount& sma) { return sma.print(o); }


VipAccount::VipAccount(string _name, shared_ptr<Person> _person) : SocialMediaAccount(_name, _person) {}
int VipAccount::calc_score(string text) { return (10 + text.size()) % 20; }
ostream& VipAccount::print(ostream& o) const
{
  SocialMediaAccount::print(o);
  o << " (VIP)";
  return o;
}

NormalAccount::NormalAccount(string _name, shared_ptr<Person> _person) : SocialMediaAccount(_name, _person) {}
int NormalAccount::calc_score(string text) { return (5 + text.size()) % 10; }
ostream& NormalAccount::print(ostream& o) const
{
  SocialMediaAccount::print(o);
  o << " (Normal)";
  return o;
}
