#ifndef INCLUDED_CORE_NONCOPYABLE_H
#define INCLUDED_CORE_NONCOPYABLE_H

#define NONCOPYABLE(Type)\
	Type(const Type&) = delete;\
	Type& operator=(const Type&) = delete;

#define NOCOPY(Type)\
	Type(const Type&) = delete;

#define NOASSIGN(Type)\
	Type& operator=(const Type&) = delete;

#endif // #ifndef INCLUDED_CORE_NONCOPYABLE_H

