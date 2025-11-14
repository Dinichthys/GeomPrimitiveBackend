#include "geom_prim_back.hpp"
#include "geom_prim.hpp"

hui::GeomPrim* GeomPrimBack::CreateGeomPrim(__attribute_maybe_unused__ size_t geomPrimType, dr4::Window* dr4Window) {
    return new Rectangle(dr4Window->CreateRectangle());
}

extern "C" hui::GeomPrimBackend* GEOM_PRIM_BACKEND_FUNCTION () {
    return new GeomPrimBack();
}
