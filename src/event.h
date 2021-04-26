#ifndef EV_H
#define EV_H

const int SYS_BIT = 0b01; //system or user
const int ARR_BIT = 0b10; //arrival or departature
enum EventType: int {
  SYS_ARRIVAL = SYS_BIT | ARR_BIT,
  SYS_DEPARTURE = SYS_BIT,
  USER_ARRIVAL = ARR_BIT,
  USER_DEPARTURE = 0
};


struct Event {
  double time;            // Time at which Event takes place
  int type;               // Type of Event
  Event* next;            // Points to next event in list
  Event(double t, int i) {
    time = t;
    type = i;
    next = 0;
  }
  bool isArrival(){
    return (type & ARR_BIT) != 0;
  }

  bool isSystem(){
    return (type & SYS_BIT) != 0;
  }
};

class EventList {
  Event* head;           // Points to first Event in EventList
  int event_count;       // Total number of Events in EventList
public:
  ~EventList() { clear();}
  EventList() { event_count = 0; head = 0;}
  void insert(double time, int type);  // Insert new event into EventList
  Event* get();                        // Returns first Event in EventList
  void clear();                        // Removes all Events from EventList
  Event* remove(int type);             // Returns first Event of given type 
};

#endif
