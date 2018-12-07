//
//  administration.cpp
//  Social Media Application
//
//  Created by annykyforu on 21.11.18.
//  Copyright © 2018 PRG2_ws18. All rights reserved.
//

#include <algorithm>
#include "administration.h"

string Administration::create_person(string name)
{
  shared_ptr<Person> person_shared{new Person(name)};
  auto exists = map.find(name);
  if(exists != map.end()){
    exists->second.swap(person_shared);
    return exists->first;
  } else {
    auto new_pair = make_pair(name, person_shared);
    map.insert(new_pair);
    return new_pair.first;
  }
}

void Administration::del_person(string name)
{
  auto delete_ptr = map.find(name);
  if(delete_ptr != map.end())
  {
    map.erase(delete_ptr);
  } else {
    throw runtime_error("Error delete! Person not found.");
  }
}

ostream& Administration::print(ostream& o) const
{
  o << "Map: [" << endl;
  for_each(map.begin(), map.end(),
           [&o](const pair<string, shared_ptr<Person>>& p)
           { o << *p.second << endl; }
           );
  o << "]";
  return o;
}

ostream& operator<<(ostream& o, const Administration& admin) { return admin.print(o); }
