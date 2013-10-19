#ifdef DEADLOCK_HUNTER
    DH::MutexGuard dh_##GUARD(MUTEX);
    APP::MutexGuard GUARD(MUTEX);
#else
    APP::MutexGuard GUARD(MUTEX);
#endif
