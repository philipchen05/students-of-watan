#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>

class Observer; // forward declaration

class Subject {
  private:
    std::vector<Observer*> observers;

  protected:
    void attach( Observer* o );
    void detach( Observer* o );
    
  public:
    void notifyObservers();
    virtual ~Subject() = default;
};

#endif
