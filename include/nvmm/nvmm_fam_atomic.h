/*
 *  (c) Copyright 2016-2017 Hewlett Packard Enterprise Development Company LP.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  As an exception, the copyright holders of this Library grant you permission
 *  to (i) compile an Application with the Library, and (ii) distribute the
 *  Application containing code generated by the Library and added to the
 *  Application during this compilation process under terms of your choice,
 *  provided you also meet the terms and conditions of the Application license.
 *
 */

#ifndef _NVMM_FAM_ATOMIC_H_
#define _NVMM_FAM_ATOMIC_H_

#include <fam_atomic.h>

namespace nvmm {

// wrapper for unsigned integers
inline uint32_t fam_atomic_u32_read(uint32_t* addr) {
  return (uint32_t) fam_atomic_32_read((int32_t*) addr);
}

inline uint64_t fam_atomic_u64_read(uint64_t* addr) {
  return (uint64_t) fam_atomic_64_read((int64_t*) addr);
}

inline void fam_atomic_u128_read(uint64_t *address, uint64_t result[2]) {
  fam_atomic_128_read((int64_t*) address, (int64_t*) result);
}


inline void fam_atomic_u32_write(uint32_t* addr, uint32_t value) {
  fam_atomic_32_write((int32_t*) addr, (int32_t) value);
}

inline void fam_atomic_u64_write(uint64_t* addr, uint64_t value) {
  fam_atomic_64_write((int64_t*) addr, (int64_t) value);
}

inline void fam_atomic_u128_write(uint64_t* addr, uint64_t value[2]) {
  fam_atomic_128_write((int64_t*) addr, (int64_t*) value);
}


inline uint32_t fam_atomic_u32_fetch_and_add(uint32_t* addr, uint32_t increment) {
  return (uint32_t) fam_atomic_32_fetch_add((int32_t*) addr, (int32_t) increment);
}

inline uint64_t fam_atomic_u64_fetch_and_add(uint64_t* addr, uint64_t increment) {
  return (uint64_t) fam_atomic_64_fetch_add((int64_t*) addr, (int64_t) increment);
}


inline uint32_t fam_atomic_u32_compare_and_store(uint32_t* addr, uint32_t oldval, uint32_t newval) {
  return (uint32_t) fam_atomic_32_compare_store((int32_t*) addr, (int32_t) oldval, (int32_t) newval);
}

inline uint64_t fam_atomic_u64_compare_and_store(uint64_t* addr, uint64_t oldval, uint64_t newval) {
  return (uint64_t) fam_atomic_64_compare_store((int64_t*) addr, (int64_t) oldval, (int64_t) newval);
}

inline void fam_atomic_u128_compare_and_store(uint64_t* addr, uint64_t oldval[2], uint64_t newval[2], uint64_t result[2]) {
    fam_atomic_128_compare_store((int64_t*) addr, (int64_t*) oldval, (int64_t*) newval, (int64_t*)result);
}

inline int32_t fam_atomic_32_fetch_and_add(int32_t* addr, int32_t increment) {
  return (int32_t) fam_atomic_32_fetch_add((int32_t*) addr, (int32_t) increment);
}

inline int64_t fam_atomic_64_fetch_and_add(int64_t* addr, int64_t increment) {
  return (int64_t) fam_atomic_64_fetch_add((int64_t*) addr, (int64_t) increment);
}


inline int32_t fam_atomic_32_compare_and_store(int32_t* addr, int32_t oldval, int32_t newval) {
  return (int32_t) fam_atomic_32_compare_store((int32_t*) addr, (int32_t) oldval, (int32_t) newval);
}

inline int64_t fam_atomic_64_compare_and_store(int64_t* addr, int64_t oldval, int64_t newval) {
  return (int64_t) fam_atomic_64_compare_store((int64_t*) addr, (int64_t) oldval, (int64_t) newval);
}

inline void fam_atomic_128_compare_and_store(int64_t* addr, int64_t oldval[2], int64_t newval[2], int64_t result[2]) {
    fam_atomic_128_compare_store((int64_t*) addr, (int64_t*) oldval, (int64_t*) newval, (int64_t*)result);
}

inline void explicit_memory_barrier() {
    asm volatile("" ::: "memory");
}

// wrapper for cacheline-aligned fam_spinlock
struct nvmm_fam_spinlock
{
    void init()
    {
        lock_ = FAM_SPINLOCK_INITIALIZER;
    }
    void lock()
    {
        fam_spin_lock(&lock_);
    }

    bool trylock()
    {
        return fam_spin_trylock(&lock_);
    }

    void unlock()
    {
        fam_spin_unlock(&lock_);
    }

private:
    struct fam_spinlock lock_;
}  __attribute__((__aligned__(64)));

} // namespace nvmm
#endif
