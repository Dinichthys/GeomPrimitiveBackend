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

        size_t shape_idx;

        const std::string kIcon = "󰗆";
        const std::string kName = "RectangleTool";

    public:
        RectangleTool(pp::Canvas* cvs)
            :cvs_(cvs), is_drawing_(false), rect_(NULL) {};

        ~RectangleTool() = default;

        virtual std::string_view Icon() const override {return kIcon;};
        virtual std::string_view Name() const override {return kName;};
        virtual bool IsCurrentlyDrawing() const override {return is_drawing_;};

        virtual void OnStart() override {
            is_drawing_ = false;
            rect_ = new Rectangle(cvs_->GetWindow()->CreateRectangle(), cvs_);
            rect_->SetTheme(cvs_->GetControlsTheme());
            shape_idx = cvs_->AddShape(rect_);
            cvs_->GetState()->selectedShape = rect_;
            cvs_->GetState()->selectedTool = this;
        };
        virtual void OnBreak() override {
            if (!is_drawing_) {
                return;
            }
            cvs_->DelShape(shape_idx);
            OnEnd();
        };
        virtual void OnEnd() override {
            rect_ = NULL;
            is_drawing_ = false;
            cvs_->GetState()->selectedShape = NULL;
            cvs_->GetState()->selectedTool = NULL;
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

        size_t shape_idx;

        const std::string kIcon = "";
        const std::string kName = "CircleTool";

    public:
        CircleTool(pp::Canvas* cvs)
            :cvs_(cvs), is_drawing_(false), circle_(NULL) {};

        ~CircleTool() = default;

        virtual std::string_view Icon() const override {return kIcon;};
        virtual std::string_view Name() const override {return kName;};
        virtual bool IsCurrentlyDrawing() const override {return is_drawing_;};

        virtual void OnStart() override {
            is_drawing_ = false;
            circle_ = new Circle(cvs_->GetWindow()->CreateCircle(), cvs_);
            circle_->SetTheme(cvs_->GetControlsTheme());
            shape_idx = cvs_->AddShape(circle_);
            cvs_->GetState()->selectedShape = circle_;
            cvs_->GetState()->selectedTool = this;
        };
        virtual void OnBreak() override {
            if (!is_drawing_) {
                return;
            }
            cvs_->DelShape(shape_idx);
            OnEnd();
        };
        virtual void OnEnd() override {
            circle_ = NULL;
            is_drawing_ = false;
            cvs_->GetState()->selectedShape = NULL;
            cvs_->GetState()->selectedTool = NULL;
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

        size_t shape_idx;

        const std::string kIcon = "󰁜";
        const std::string kName = "ArrowTool";

    public:
        ArrowTool(pp::Canvas* cvs)
            :cvs_(cvs), is_drawing_(false), arrow_(NULL) {};

        ~ArrowTool() = default;

        virtual std::string_view Icon() const override {return kIcon;};
        virtual std::string_view Name() const override {return kName;};
        virtual bool IsCurrentlyDrawing() const override {return is_drawing_;};

        virtual void OnStart() override {
            is_drawing_ = false;
            arrow_ = new Arrow(cvs_->GetWindow()->CreateLine(),
                               cvs_->GetWindow()->CreateLine(),
                               cvs_->GetWindow()->CreateLine(), cvs_);
            arrow_->SetTheme(cvs_->GetControlsTheme());
            shape_idx = cvs_->AddShape(arrow_);
            cvs_->GetState()->selectedShape = arrow_;
            cvs_->GetState()->selectedTool = this;
        };
        virtual void OnBreak() override {
            if (!is_drawing_) {
                return;
            }
            cvs_->DelShape(shape_idx);
            OnEnd();
        };
        virtual void OnEnd() override {
            arrow_ = NULL;
            is_drawing_ = false;
            cvs_->GetState()->selectedShape = NULL;
            cvs_->GetState()->selectedTool = NULL;
        };

        virtual bool OnMouseDown(const dr4::Event::MouseButton &evt) override;
        virtual bool OnMouseUp(const dr4::Event::MouseButton &evt) override;
        virtual bool OnMouseMove(const dr4::Event::MouseMove &evt) override;
};

};

#endif // GEOM_PRIM_TOOLS_HPP
