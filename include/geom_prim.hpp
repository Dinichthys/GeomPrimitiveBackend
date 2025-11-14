#ifndef GEOM_PRIM_HPP
#define GEOM_PRIM_HPP

#include "hui/geomprim.hpp"

#include "dr4/math/rect.hpp"

class Rectangle : public hui::GeomPrim {
    private:
        const dr4::Color kBorderColor = {dr4::Color::ColorMaxValue, 0, 0};
        const float kBorderThickness = 5;
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

class Circle : public hui::GeomPrim {
    private:
        const dr4::Color kBorderColor = {dr4::Color::ColorMaxValue, 0, 0};
        const float kBorderThickness = 5;
        dr4::Circle* circle_;
        dr4::Vec2f center_;

    public:
        Circle(dr4::Circle* circle) {
            circle_ = circle;
            circle_->SetBorderColor(kBorderColor);
            circle_->SetBorderThickness(kBorderThickness);
            circle_->SetFillColor({0, 0, 0, 0});
        };

        virtual hui::EventResult OnMouseMove(const hui::MouseMoveEvent& evt)    override;
        virtual hui::EventResult OnMouseDown(const hui::MouseDownEvent& evt)    override;
        virtual hui::EventResult OnMouseRelease(const hui::MouseUpEvent& evt) override;

        virtual void DrawOn(dr4::Texture& texture) const override {
            circle_->DrawOn(texture);
        }

        virtual void SetPos(dr4::Vec2f pos) override {
            circle_->SetPos(pos);
        }

        virtual dr4::Vec2f GetPos() const override {
            return circle_->GetPos();
        }
};

// class Arrow : public hui::GeomPrim {
//     private:
//         const dr4::Color kFillColor = {dr4::Color::ColorMaxValue, 0, 0};
//         const float kWidth = 5;
//         dr4::Line* rect1_;
//         dr4::Line* rect2_;
//         dr4::Line* rect3_;
//
//         dr4::Vec2f start_;
//         dr4::Vec2f end_;
//
//     public:
//         Arrow(dr4::Rectangle* rect1, dr4::Rectangle* rect2, dr4::Rectangle* rect3) {
//             rect1_ = rect1;
//             rect2_ = rect2;
//             rect3_ = rect3;
//             rect1_->SetFillColor(kFillColor);
//             rect2_->SetFillColor(kFillColor);
//             rect3_->SetFillColor(kFillColor);
//         };
//
//         virtual hui::EventResult OnMouseMove(const hui::MouseMoveEvent& evt)    override;
//         virtual hui::EventResult OnMouseDown(const hui::MouseDownEvent& evt)    override;
//         virtual hui::EventResult OnMouseRelease(const hui::MouseUpEvent& evt) override;
//
//         virtual void DrawOn(dr4::Texture& texture) const override {
//             rect1_->DrawOn(texture);
//             rect2_->DrawOn(texture);
//             rect3_->DrawOn(texture);
//         }
//
//         virtual void SetPos(dr4::Vec2f pos) override {
//             rect_info_.pos = pos;
//             rect_->SetPos(pos);
//         }
//
//         virtual dr4::Vec2f GetPos() const override {
//             return rect_info_.pos;
//         }
//
// };

#endif // GEOM_PRIM_HPP
