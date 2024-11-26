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
    void notifyObservers();
    virtual char getState( int row, int col ) const = 0;

  public:
    virtual ~Subject() = default;
};

#endif
