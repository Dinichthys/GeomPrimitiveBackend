#ifndef GEOM_PRIM_BACK_HPP
#define GEOM_PRIM_BACK_HPP

#include "cum/ifc/pp.hpp"
#include "cum/plugin.hpp"

class GeomPrimBack : public cum::PPToolPlugin {
    public:
        virtual std::vector<std::unique_ptr<::pp::Tool>> CreateTools(pp::Canvas *cvs) override;

        virtual std::string_view GetIdentifier() const override {return kName;};
        virtual std::string_view GetName() const override {return kName;};
        virtual std::string_view GetDescription() const override {return kDescription;};

        virtual std::vector<std::string_view> GetDependencies() const override {return {};};
        virtual std::vector<std::string_view> GetConflicts() const override {return {};};

        virtual void AfterLoad() override {};

        const std::string kName = "DenGeomPrimBackend";
        const std::string kDescription =
            "This plugin provides opportunity for creating and drawing geometric primitives\n";
};

#endif // GEOM_PRIM_BACK_HPP
