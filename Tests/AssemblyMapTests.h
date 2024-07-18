#include "../AssemblyMap.h"
#include "../Error.h"
bool TestAssemblyMapInitailization () {
    try {
        AssemblyMap asmMap ("Data/");
        return true;
    } catch (Error&) {
        return false;
    }
}
