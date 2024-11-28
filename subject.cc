#include "subject.h"
#include "observer.h"
#include <vector>
#include <iostream>

// attaches observer to subject
void Subject::attach( Observer* o ) {
    observers.emplace_back(o);
}

// detaches observer from subject
void Subject::detach( Observer* o ) {
    // loop through observers and remove the desired one
    for (auto it = observers.begin(); it != observers.end(); ++it) {
        if (*it == o) {
            observers.erase(it);
            break;
        }
    }
}

// notifies all observers attached to subject
void Subject::notifyObservers() {
    for (auto &ob: observers) {
        std::cerr << "[Subject] - notifying observer " << ob << std::endl; // DEBUG - MUST DELETE
        ob->notify(this);
    }
}
