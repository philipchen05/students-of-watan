#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include "subject.h"

class Observer {
  public:
    virtual void notify(Subject *sbj) = 0;
    virtual ~Observer() = default;
};

#endif
