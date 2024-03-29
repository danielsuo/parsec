// (C) Copyright Christian Bienia 2007
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0.
//
//  file : Condition.h
//  author : Christian Bienia - cbienia@cs.princeton.edu
//  description : A condition variable

#ifndef CONDITION_H
#define CONDITION_H

#if defined(HAVE_CONFIG_H)
# include "config.h"
#endif

#pragma warning( disable : 4290)		//disable Microsoft compiler exception warning

#if defined(HAVE_LIBPTHREAD)
# include <pthread.h>
#else //default: winthreads
# include <windows.h>
#endif //HAVE_LIBPTHREAD

#include <exception>

#include "Mutex.h"


namespace threads {

//A standard condition variable
class Condition {
  public:
    Condition(Mutex &);
    ~Condition();

    //Wake up exactly one thread, return number of threads currently waiting (before wakeup)
    //If no more threads are waiting, the notification is lost
    int NotifyOne();
    //Wake up all threads, return number of threads currently waiting (before wakeup)
    int NotifyAll();

    //Wait until either NotifyOne() or NotifyAll() is executed
    void Wait();
  private:
    //the mutex associated with the condition variable
    Mutex *M;
    //number of waiting threads (with either no wakeup permission or pending wakeup)
    int nWaiting;
    //threads allowed to wake up (i.e. pending wakeups), nWakeupTickets <= nWaiting
    //notifications increase the number of tickets, successful wakeups decrease them
    int nWakeupTickets;
#if defined(HAVE_LIBPTHREAD)
    pthread_cond_t c;
#else //default: winthreads
    //generation counter to improve fairness
    unsigned int genCounter;
    HANDLE c;
#endif //HAVE_LIBPTHREAD

};

} //namespace threads

#endif //CONDITION_H
