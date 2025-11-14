#include "geom_prim_back.hpp"
#include "geom_prim.hpp"

hui::GeomPrim* GeomPrimBack::CreateGeomPrim(__attribute_maybe_unused__ size_t geomPrimType, dr4::Window* dr4Window) {
    switch(geomPrimType) {
        case 0:
            return new Rectangle(dr4Window->CreateRectangle());
        case 1:
            return new Circle(dr4Window->CreateCircle());
        default:
            return NULL;
    }
}

extern "C" hui::GeomPrimBackend* GEOM_PRIM_BACKEND_FUNCTION () {
    return new GeomPrimBack();
}
