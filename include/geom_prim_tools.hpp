#ifndef GEOM_PRIM_TOOLS_HPP
#define GEOM_PRIM_TOOLS_HPP

#include "pp/tool.hpp"
#include "pp/canvas.hpp"

#include "geom_prim.hpp"

namespace pp {

class RectangleTool : public pp::Tool {
    private:
        pp::Canvas* cvs_;

        bool is_drawing_;

        Rectangle* rect_;

        const std::string kIcon = "\ue88b";
        const std::string kName = "RectangleTool";

    public:
        RectangleTool(pp::Canvas* cvs)
            :cvs_(cvs), is_drawing_(false), rect_(NULL) {};

        virtual std::string_view Icon() const override {return kIcon;};
        virtual std::string_view Name() const override {return kName;};
        virtual bool IsCurrentlyDrawing() const override {return is_drawing_;};

        virtual void OnStart() override {
            is_drawing_ = false;
            rect_ = new Rectangle(cvs_->GetWindow()->CreateRectangle(), cvs_);
            rect_->SetTheme(cvs_->GetControlsTheme());
            cvs_->AddShape(rect_);
            cvs_->SetSelectedShape(rect_);
        };
        virtual void OnBreak() override {
            if (!is_drawing_) {
                return;
            }
            cvs_->DelShape(rect_);
            OnEnd();
        };
        virtual void OnEnd() override {
            rect_ = NULL;
            is_drawing_ = false;
            cvs_->SetSelectedShape(NULL);
        };

        virtual bool OnMouseDown(const dr4::Event::MouseButton &evt) override;
        virtual bool OnMouseUp(const dr4::Event::MouseButton &evt) override;
        virtual bool OnMouseMove(const dr4::Event::MouseMove &evt) override;
};

class CircleTool : public pp::Tool {
    private:
        pp::Canvas* cvs_;

        bool is_drawing_;

        Circle* circle_;

        const std::string kIcon = "\ueabc";
        const std::string kName = "CircleTool";

    public:
        CircleTool(pp::Canvas* cvs)
            :cvs_(cvs), is_drawing_(false), circle_(NULL) {};

        virtual std::string_view Icon() const override {return kIcon;};
        virtual std::string_view Name() const override {return kName;};
        virtual bool IsCurrentlyDrawing() const override {return is_drawing_;};

        virtual void OnStart() override {
            is_drawing_ = false;
            circle_ = new Circle(cvs_->GetWindow()->CreateCircle(), cvs_);
            circle_->SetTheme(cvs_->GetControlsTheme());
            cvs_->AddShape(circle_);
            cvs_->SetSelectedShape(circle_);
        };
        virtual void OnBreak() override {
            if (!is_drawing_) {
                return;
            }
            cvs_->DelShape(circle_);
            OnEnd();
        };
        virtual void OnEnd() override {
            circle_ = NULL;
            is_drawing_ = false;
            cvs_->SetSelectedShape(NULL);
        };

        virtual bool OnMouseDown(const dr4::Event::MouseButton &evt) override;
        virtual bool OnMouseUp(const dr4::Event::MouseButton &evt) override;
        virtual bool OnMouseMove(const dr4::Event::MouseMove &evt) override;
};

class ArrowTool : public pp::Tool {
    private:
        pp::Canvas* cvs_;

        bool is_drawing_;

        Arrow* arrow_;

        const std::string kIcon = "\uf46c";
        const std::string kName = "ArrowTool";

    public:
        ArrowTool(pp::Canvas* cvs)
            :cvs_(cvs), is_drawing_(false), arrow_(NULL) {};

        virtual std::string_view Icon() const override {return kIcon;};
        virtual std::string_view Name() const override {return kName;};
        virtual bool IsCurrentlyDrawing() const override {return is_drawing_;};

        virtual void OnStart() override {
            is_drawing_ = false;
            arrow_ = new Arrow(cvs_->GetWindow()->CreateLine(),
                               cvs_->GetWindow()->CreateLine(),
                               cvs_->GetWindow()->CreateLine(), cvs_);
            arrow_->SetTheme(cvs_->GetControlsTheme());
            cvs_->AddShape(arrow_);
            cvs_->SetSelectedShape(arrow_);
        };
        virtual void OnBreak() override {
            if (!is_drawing_) {
                return;
            }
            cvs_->DelShape(arrow_);
            OnEnd();
        };
        virtual void OnEnd() override {
            arrow_ = NULL;
            is_drawing_ = false;
            cvs_->SetSelectedShape(NULL);
        };

        virtual bool OnMouseDown(const dr4::Event::MouseButton &evt) override;
        virtual bool OnMouseUp(const dr4::Event::MouseButton &evt) override;
        virtual bool OnMouseMove(const dr4::Event::MouseMove &evt) override;
};

};

#endif // GEOM_PRIM_TOOLS_HPP
