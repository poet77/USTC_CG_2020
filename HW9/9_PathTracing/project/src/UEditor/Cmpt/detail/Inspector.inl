/*
    Generated by Ubpa::UScene_parser
    Any changes to this file will be overwritten by the next CMake run
    ----
    Usage:
        #include "this-file" // in cpp
*/

#include <UDP/Reflection/Reflection.h>

#include <UScene/core/SObj.h>

namespace Ubpa::Cmpt::detail::dynamic_reflection {
    void ReflRegister_Inspector() {
        Reflection<Inspector>::Instance() // name : class Ubpa::Cmpt::Inspector
            .Register("description", "SObj's components Viewer")
            ;
        if constexpr (std::is_base_of_v<Component, Inspector>) {
            Reflection<Inspector>::Instance().RegisterConstructor([](SObj* sobj) {
                if constexpr (std::is_base_of_v<Component, Inspector>) {
                    if constexpr (Ubpa::detail::SObj_::IsNecessaryCmpt<Inspector>)
                        return sobj->Get<Inspector>();
                    else
                        return sobj->GetOrAttach<Inspector>();
                };
            });
        }
    }
}
