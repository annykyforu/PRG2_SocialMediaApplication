//
//  main.cpp
//  Social Media Application
//
//  Created by annykyforu on 21.11.18.
//  Copyright © 2018 PRG2_ws18. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <unordered_map>
#include "person.h"
#include "social_media_account.h"
#include "administration.h"
#include <iostream>

using namespace std;

int main() {
 shared_ptr<Person> pers_lebron {new Person("LeBron")};
 shared_ptr<Person> pers_kobe {new Person("Kobe")};

 int vip_acc_numb = pers_lebron->add_account("Cavaliers", 1);
 int norm_acc_numb = pers_kobe->add_account("Lakers", 0);

 auto vip_ptr = find_if(pers_lebron->get_accounts().begin(), pers_lebron->get_accounts().end(),
                        [&vip_acc_numb](const shared_ptr<SocialMediaAccount> ptr)
                        { return vip_acc_numb == ptr->get_accountnumber(); }
                        );
 pers_lebron->share(pers_kobe, *vip_ptr);

 auto norm_ptr = find_if(pers_kobe->get_accounts().begin(), pers_kobe->get_accounts().end(),
                         [&norm_acc_numb](const shared_ptr<SocialMediaAccount> ptr)
                         { return norm_acc_numb == ptr->get_accountnumber(); }
                         );
 (*vip_ptr)->write_msg(*norm_ptr, "LeBron's back home");
 (*norm_ptr)->write_msg(*vip_ptr, "Look again");

 cout << *pers_lebron << endl;
 cout << *pers_kobe << endl;

 (*vip_ptr)->print(cout); cout << endl;
 (*norm_ptr)->print(cout); cout << endl;

 // pers_lebron.reset();  //There is an error here
 // (*vip_ptr)->clear_weak_ptr();   //There is an error here
 // (*vip_ptr)->print(cout); cout << endl;  //There is an error here
 (*norm_ptr)->print(cout); cout << endl;

  return 0;
}
