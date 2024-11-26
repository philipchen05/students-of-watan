#ifndef OBSERVER_H
#define OBSERVER_H

#include "subject.h"

class Observer {
  public:
    virtual void notify(const Subject *sbj) = 0;
    virtual ~Observer() = default;
};

#endif
