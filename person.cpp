//
//  person.cpp
//  Social Media Application
//
//  Created by annykyforu on 21.11.18.
//  Copyright © 2018 PRG2_ws18. All rights reserved.
//

#include <algorithm>
#include "person.h"
#include "social_media_account.h"

Person::Person() : name{"Example Examplerius"} {}
Person::Person(string n)
{
  if(n == "")
    throw runtime_error("Error! Empty name is not allowed.");
  name = n;
}
string Person::get_name() const { return name; }

int Person::add_account(string acc, int modus = 1)
{
  if(modus == 1){
    auto vip_acc = make_shared<VipAccount>(acc, shared_from_this());
    media_accounts.push_back(vip_acc);
    return vip_acc->get_accountnumber();
  } else {
    auto norm_acc = make_shared<NormalAccount>(acc, shared_from_this());
    media_accounts.emplace_back(norm_acc);
    return norm_acc->get_accountnumber();
  }
}

bool Person::remove_account(int numb)
{
  auto result = find_if(media_accounts.begin(), media_accounts.end(),
                       [&numb](const shared_ptr<SocialMediaAccount>& ptr)
                       { return numb == ptr->get_accountnumber(); }
                       );
  if(result != media_accounts.end()) {
    media_accounts.erase(result);
    return true;
  } else {
    return false;
  }
}

bool Person::share(shared_ptr<Person> _pers, shared_ptr<SocialMediaAccount> _sma)
{
  //check if this has an Account to share
  auto this_acc = find_if(media_accounts.begin(), media_accounts.end(),
                          [&_sma](const shared_ptr<SocialMediaAccount> ptr_acc)
                          { return _sma == ptr_acc; }
                          );
  if(this_acc == media_accounts.end())
  {
    throw runtime_error(get_name() + " doesn't have an Account to share!");
    return false;
  }

  //check if other Person doesn't already have the sharable Account
  auto _pers_acc = find_if(_pers->media_accounts.begin(), _pers->media_accounts.end(),
                           [&_sma](const shared_ptr<SocialMediaAccount> ptr_acc)
                           { return _sma == ptr_acc; }
                          );
  if (_pers_acc != _pers->media_accounts.end())
  {
    throw runtime_error(_pers->get_name() + " is already an Owner of this account!");
    return false;
  }
  _sma->add_person(_pers);
  _pers->media_accounts.push_back(_sma);
  return true;
}

ostream& Person::print(ostream& os) const
{
  os << "[Name: " << name << ", ";
  os << "Account: {";
  size_t count_accounts = media_accounts.size();
  for_each(media_accounts.begin(), media_accounts.end(),
           [&os, &count_accounts](const shared_ptr<SocialMediaAccount>& ptr)
           {
             --count_accounts;
             ptr->print_small(os);
             if(count_accounts > 0) os << ", ";
           }
           );
  os << "}]";
  return os;
}

ostream& Person::print_small(ostream& os) const
{
  os << name;
  return os;
}

const vector<shared_ptr<SocialMediaAccount>>& Person::get_accounts() const { return media_accounts; }

ostream& operator<<(ostream& o, const Person& pers) { return pers.print(o); }
