#include "geom_prim_back.hpp"
#include "geom_prim_tools.hpp"
#include "image.hpp"

#include "cum/manager.hpp"

std::vector<std::unique_ptr<::pp::Tool>> GeomPrimBack::CreateTools(pp::Canvas *cvs) {
    std::vector<std::unique_ptr<::pp::Tool>> res;

    res.emplace_back(std::make_unique<pp::RectangleTool>(cvs));
    res.emplace_back(std::make_unique<pp::CircleTool>(cvs));
    res.emplace_back(std::make_unique<pp::ArrowTool>(cvs));
    res.emplace_back(std::make_unique<pp::PenisTool>(cvs));
    res.emplace_back(std::make_unique<pp::TextTool>(cvs));
    res.emplace_back(std::make_unique<pp::ImageTool>(cvs));

    return res;
}

extern "C" cum::Plugin* CREATE_PLUGIN_FUNC_NAME() {
    return new GeomPrimBack();
}
