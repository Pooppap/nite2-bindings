#ifndef WRAPPER_UTILS_H
#define WRAPPER_UTILS_H

#include "boost_python.h"
#include <vector>

//-------------------------------------------------------------------------------------------------

class ScopedGILRelease
{
public:
    inline ScopedGILRelease()
        : m_thread_state(PyEval_SaveThread())
    {
    }

    inline ~ScopedGILRelease()
    {
        PyEval_RestoreThread(m_thread_state);
    }
private:
    PyThreadState * m_thread_state;
};

//-------------------------------------------------------------------------------------------------

class GILStateScopedEnsure
{
public:
    inline GILStateScopedEnsure()
        : m_state(PyGILState_Ensure())
    {
    }

    inline ~GILStateScopedEnsure()
    {
        PyGILState_Release(m_state);
    }
private:
    PyGILState_STATE m_state;
};

//-------------------------------------------------------------------------------------------------

template<class T>
class VersionWrapper : private T
{
public:
    inline VersionWrapper(const T & v)
    {
        major = v.major;
        minor = v.minor;
        maintenance = v.maintenance;
        build = v.build;
    }
    inline int getMajor() const { return major; }
    inline int getMinor() const { return minor; }
    inline int getMaintenance() const { return maintenance; }
    inline int getBuild() const { return build; }
private:
    VersionWrapper() {}
};

template<class T>
inline std::ostream & operator << (std::ostream & output, const VersionWrapper<T> & v)
{
    return output << v.getMajor() << '.' << v.getMinor() << '.' << v.getMaintenance() << '.' << v.getBuild();
}

//-------------------------------------------------------------------------------------------------

static inline bool addListener(std::vector<bp::object> & listeners, const bp::object & callback)
{
    for(const auto & cb : listeners)
        if(cb == callback)
            return false;
    const auto last_size = listeners.size();
    listeners.push_back(callback);
    if(last_size == 0 && listeners.size() > 0)
        return true;
    else
        return false;
}

static inline bool removeListener(std::vector<bp::object> & listeners, const bp::object & callback)
{
    const auto last_size = listeners.size();
    listeners.erase(std::remove(listeners.begin(), listeners.end(), callback), listeners.end());
    if(last_size != 0 && listeners.size() == 0)
        return true;
    else
        return false;
}

//-------------------------------------------------------------------------------------------------

#endif // WRAPPER_UTILS_H
