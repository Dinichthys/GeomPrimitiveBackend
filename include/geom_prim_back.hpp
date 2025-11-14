#ifndef GEOM_PRIM_BACK_HPP
#define GEOM_PRIM_BACK_HPP

#include "cum/geomprim_ifc.hpp"
#include "cum/plugin.hpp"
#include "cum/version.hpp"

class GeomPrimBack : public hui::GeomPrimBackend {
    public:
        virtual hui::GeomPrim* CreateGeomPrim(size_t geomPrimType, dr4::Window* dr4Window) override;

        virtual const std::string &GetName() const override {return kName;};
        virtual const std::string &GetDescription() const override {return kDescription;};
        virtual const cum::PluginVersion &GetVersion() const override {return kVersion;};

        virtual std::vector<std::string> GetDependencies() const override {return {};};
        virtual bool IsCompatibleWith(__attribute_maybe_unused__ const Plugin& other) const override {return true;};

        const cum::PluginVersion kVersion = {1, 4, 88};
        const std::string kName = "DenGeomPrimBackend";
        const std::string kDescription =
            "This plugin provides opportunity for creating and drawing geometric primitives\n";
};

#endif // GEOM_PRIM_BACK_HPP
