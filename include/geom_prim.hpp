#ifndef GEOM_PRIM_HPP
#define GEOM_PRIM_HPP

#include "hui/geomprim.hpp"

#include "dr4/math/rect.hpp"

class Rectangle : public hui::GeomPrim {
    private:
        const dr4::Color kBorderColor = {dr4::Color::ColorMaxValue, 0, 0};
        const float kBorderThickness = 20;
        dr4::Rectangle* rect_;
        dr4::Rect2f rect_info_;

    public:
        Rectangle(dr4::Rectangle* rect) {
            rect_ = rect; rect_info_ = {};
            rect_->SetBorderColor(kBorderColor);
            rect_->SetBorderThickness(kBorderThickness);
            rect_->SetFillColor({0, 0, 0, 0});
        };

        virtual hui::EventResult OnMouseMove(const hui::MouseMoveEvent& evt)    override;
        virtual hui::EventResult OnMouseDown(const hui::MouseDownEvent& evt)    override;
        virtual hui::EventResult OnMouseRelease(const hui::MouseUpEvent& evt) override;

        virtual void DrawOn(dr4::Texture& texture) const override {
            rect_->DrawOn(texture);
        }

        virtual void SetPos(dr4::Vec2f pos) override {
            rect_info_.pos = pos;
            rect_->SetPos(pos);
        }

        virtual dr4::Vec2f GetPos() const override {
            return rect_info_.pos;
        }
};

#endif // GEOM_PRIM_HPP
