#pragma once

#include <utility.valuegraph/Value.h>

namespace nspace{
class ChangeTracker{
private:
    const Value & _value;
    ValueVersionId _lastAccessedVersion;
public:
    ChangeTracker(const Value & value):_value(value),_lastAccessedVersion(value.version()){}

    inline bool hasChanged()const{
        return _lastAccessedVersion != _value.version();
    }
    void access(){
        _lastAccessedVersion = _value.version();
    }

};
}
