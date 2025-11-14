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

        ~Rectangle() {
            delete rect_;
        };

        virtual hui::EventResult OnMouseMove(const hui::MouseMoveEvent& evt)  override;
        virtual hui::EventResult OnMouseDown(const hui::MouseDownEvent& evt)  override;
        virtual hui::EventResult OnMouseRelease(const hui::MouseUpEvent& evt) override;

        virtual void DrawOn(dr4::Texture& texture) const override {
            rect_->DrawOn(texture);
        };

        virtual void SetPos(dr4::Vec2f pos) override {
            rect_info_.pos = pos;
            rect_->SetPos(pos);
        };

        virtual dr4::Vec2f GetPos() const override {
            return rect_info_.pos;
        };
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

        ~Circle() {
            delete circle_;
        };

        virtual hui::EventResult OnMouseMove(const hui::MouseMoveEvent& evt)  override;
        virtual hui::EventResult OnMouseDown(const hui::MouseDownEvent& evt)  override;
        virtual hui::EventResult OnMouseRelease(const hui::MouseUpEvent& evt) override;

        virtual void DrawOn(dr4::Texture& texture) const override {
            circle_->DrawOn(texture);
        };

        virtual void SetPos(dr4::Vec2f pos) override {
            circle_->SetPos(pos);
        };

        virtual dr4::Vec2f GetPos() const override {
            return circle_->GetPos();
        };
};

class Arrow : public hui::GeomPrim {
    private:
        const dr4::Color kFillColor = {dr4::Color::ColorMaxValue, 0, 0};
        const float kWidth = 5;
        const float kArrowLenPercentage = 0.05;

        dr4::Line* line1_;
        dr4::Line* line2_;
        dr4::Line* line3_;

        dr4::Vec2f start_;
        dr4::Vec2f end_;

    public:
        Arrow(dr4::Line* line1, dr4::Line* line2, dr4::Line* line3) {
            line1_ = line1;
            line2_ = line2;
            line3_ = line3;
            line1_->SetColor(kFillColor);
            line1_->SetThickness(kWidth);
            line2_->SetColor(kFillColor);
            line2_->SetThickness(kWidth);
            line3_->SetColor(kFillColor);
            line3_->SetThickness(kWidth);
        };

        ~Arrow() {
            delete line1_;
            delete line2_;
            delete line3_;
        }

        virtual hui::EventResult OnMouseMove(const hui::MouseMoveEvent& evt)  override;
        virtual hui::EventResult OnMouseDown(const hui::MouseDownEvent& evt)  override;
        virtual hui::EventResult OnMouseRelease(const hui::MouseUpEvent& evt) override;

        virtual void DrawOn(dr4::Texture& texture) const override {
            line1_->DrawOn(texture);
            line2_->DrawOn(texture);
            line3_->DrawOn(texture);
        };

        virtual void SetPos(dr4::Vec2f pos) override {
            line1_->SetStart(pos);
            dr4::Vec2f vec = end_ - start_;
            end_ = vec + pos;
            start_ = pos;
            line1_->SetEnd(end_);

            line2_->SetStart(end_);
            line2_->SetEnd(end_ + dr4::Vec2f(-(vec.y), vec.x) * kArrowLenPercentage);

            line3_->SetStart(end_);
            line2_->SetEnd(end_ + dr4::Vec2f(vec.y, -(vec.x)) * kArrowLenPercentage);
        };

        virtual dr4::Vec2f GetPos() const override {
            return start_;
        };

};

#endif // GEOM_PRIM_HPP
