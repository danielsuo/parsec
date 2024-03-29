// (C) Copyright Christian Bienia 2007
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0.
//
//  file : Condition.cpp
//  author : Christian Bienia - cbienia@cs.princeton.edu
//  description : A condition variable

#if defined(HAVE_CONFIG_H)
# include "config.h"
#endif

#if defined(HAVE_LIBPTHREAD)
# include <pthread.h>
# include <errno.h>
#else //default: winthreads
# include <windows.h>
#endif //HAVE_LIBPTHREAD

#include <exception>

#include "Mutex.h"
#include "Condition.h"


namespace threads {

Condition::Condition(Mutex &_M) {
  int rv;

  M = &_M;

#if defined(HAVE_LIBPTHREAD)
  nWaiting = 0;
  nWakeupTickets = 0;

  rv = pthread_cond_init(&c, NULL);

  switch(rv) {
    case 0:
      //no error
      break;
    case EAGAIN:
    case ENOMEM:
    {
      break;
    }
    case EBUSY:
    case EINVAL:
    {
      break;
    }
    default:
    {
      break;
    }
  }
#else //default: winthreads
  nWaiting = 0;
  nWakeupTickets = 0;
  genCounter = 0;

  c = CreateEvent(NULL, true, false, NULL);
#endif //HAVE_LIBPTHREAD
}

Condition::~Condition() {
#if defined(HAVE_LIBPTHREAD)
  int rv;

  rv = pthread_cond_destroy(&c);

  switch(rv) {
    case 0:
      //no error
      break;
    case EBUSY:
    case EINVAL:
    {
      break;
    }
    default:
    {
      break;
    }
  }
#else //default: winthreads
  int rv;

  rv = CloseHandle(c);
#endif //HAVE_LIBPTHREAD
}

//Wake up exactly one thread, return number of threads currently waiting (before wakeup)
//If no more threads are waiting, the notification is lost
int Condition::NotifyOne() {
#if defined(HAVE_LIBPTHREAD)
  int slack;
  int rv;

  slack = nWaiting - nWakeupTickets;
  if(slack > 0) {
    nWakeupTickets++;
    rv = pthread_cond_signal(&c);

    switch(rv) {
      case 0:
        //no error
        break;
      case EINVAL:
      {
        break;
      }
      default:
      {
        break;
      }
    }
  }

  return slack;
#else //default: winthreads
  int slack;

  slack = nWaiting - nWakeupTickets;
  if(slack > 0) {
    nWakeupTickets++;
    genCounter++;
    SetEvent(c);
  }
  return slack;
#endif //HAVE_LIBPTHREAD
}

//Wake up all threads, return number of threads currently waiting (before wakeup)
int Condition::NotifyAll() {
#if defined(HAVE_LIBPTHREAD)
  int slack;
  int rv;

  slack = nWaiting - nWakeupTickets;
  if(slack > 0) {
    nWakeupTickets = nWaiting;
    rv = pthread_cond_broadcast(&c);

    switch(rv) {
      case 0:
        //no error
        break;
      case EINVAL:
      {
        break;
      }
      default:
      {
        break;
      }
    }
  }

  return slack;
#else //default: winthreads
  int slack;

  slack = nWaiting - nWakeupTickets;
  if(slack > 0) {
    nWakeupTickets = nWaiting;
    genCounter++;
    SetEvent(c);
  }
  return slack;
#endif //HAVE_LIBPTHREAD
}

//Wait until either NotifyOne() or NotifyAll() is executed
void Condition::Wait() {
#if defined(HAVE_LIBPTHREAD)
  int rv;

  nWaiting++;

  //nWakeupTickets protects against spurious wakeups
  while(nWakeupTickets == 0) {
    rv = pthread_cond_wait(&c, &(M->m));

    switch(rv) {
      case 0:
        //no error
        break;
      case EINVAL:
      {
        break;
      }
      case EPERM:
      {
        break;
      }
      default:
      {
        break;
      }
    }
  }

  nWakeupTickets--;
  nWaiting--;
#else //default: winthreads
  int myGeneration;
  bool doRelease;

  nWaiting++;
  myGeneration = genCounter;

  while(true) {
    //Wait until event has been signaled
    LeaveCriticalSection(&(M->m));
    WaitForSingleObject(c, INFINITE);
    EnterCriticalSection(&(M->m));

    //Exit when event is signaled and there are still threads from this generation waiting
    doRelease = nWakeupTickets > 0 && genCounter != myGeneration;
    if(doRelease)
      break;
  }

  nWaiting--;
  nWakeupTickets--;

  //if we're last waiter, reset event
  if(nWakeupTickets == 0) {
    ResetEvent(c);
  }
#endif //HAVE_LIBPTHREAD
}

} //namespace threads
