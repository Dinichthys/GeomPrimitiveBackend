#include "geom_prim_back.hpp"
#include "geom_prim_tools.hpp"

#include "cum/manager.hpp"

std::vector<std::unique_ptr<::pp::Tool>> GeomPrimBack::CreateTools(pp::Canvas *cvs) {
    std::vector<std::unique_ptr<::pp::Tool>> res;

    res.push_back(std::unique_ptr<::pp::Tool>(new RectangleTool(cvs)));
    res.push_back(std::unique_ptr<::pp::Tool>(new CircleTool(cvs)));
    res.push_back(std::unique_ptr<::pp::Tool>(new ArrowTool(cvs)));

    return res;
}

extern "C" cum::Plugin* CREATE_PLUGIN_FUNC_NAME() {
    return new GeomPrimBack();
}
