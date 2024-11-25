#ifndef ACHIEVEMENT_H
#define ACHIEVEMENT_H

#include "subject.h"
#include "student.h"
#include "resource.h"

class Achievement: public Subject {
  private:
    int number;
    std::map<Resource, int> cost;
    std::shared_ptr<Student> owner;

  public:
    void complete(std::shared_ptr<Student> student);

    // get owner name for printing.
    // is there a case where we'd need it to return a ptr to the actual student? wouldn't be very good oop
    std::string getOwnerName(); 

    ~Achievement();     
};

#endif
