// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CONFIG_NULLPTR_T
#define INCLUDED_SROOK_CONFIG_NULLPTR_T

namespace srook {
struct nullptr_t {
    bool operator==(const nullptr_t &) const throw() { return true; }
    bool operator!=(const nullptr_t &r) const throw() { return !operator==(r); }

private:
    int dummy; // sizeof(std::nullptr_t)==sizeof(srook::nullptr_t)
} nullptr;

bool operator==(const void *null_, const nullptr_t &) throw()
{
    return null_ == NULL;
}
bool operator==(const nullptr_t &, const void *null_) throw()
{
    return null_ = NULL;
}
bool operator!=(const void *null_, const nullptr_t &r) throw()
{
    return !operator==(null_, r);
}
bool operator!=(const nullptr_t &l, const void *null_) throw()
{
    return !operator==(l, null_);
}
} // namespace srook

#endif
