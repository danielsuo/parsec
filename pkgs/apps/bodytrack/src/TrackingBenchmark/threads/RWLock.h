// (C) Copyright Christian Bienia 2007
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0.
//
//  file : RWLock.h
//  author : Christian Bienia - cbienia@cs.princeton.edu
//  description : A read-write lock

#ifndef RWLOCK_H
#define RWLOCK_H

#if defined(HAVE_CONFIG_H)
# include "config.h"
#endif

#include <pthread.h>
#include <exception>

#include "LockTypes.h"


namespace threads {

//A standard rwlock
class RWLock: public RWLockType {
  public:
    RWLock();
    ~RWLock();

    //Enter a critical region for reading
    void ReadLock();
    //Try to acquire the lock for reading, return true if successful
    bool TryReadLock();
    //Enter a critical region for writing
    void WriteLock();
    //Try to acquire the lock for writing, return true if successful
    bool TryWriteLock();
    //Leave a critical region
    void Unlock();

  private:
    pthread_rwlock_t l;
};

} //namespace threads

#endif //RWLOCK_H
