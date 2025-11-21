#ifndef GEOM_PRIM_HPP
#define GEOM_PRIM_HPP

#include <math.h>

#include "pp/shape.hpp"
#include "pp/canvas.hpp"

#include "dr4/math/rect.hpp"

namespace pp {

static const float kEpsilon = 0.01;

class Rectangle : public pp::Shape {
    private:
        pp::Canvas* cvs_;

        bool selected_;

        const dr4::Color kBorderColor = {dr4::Color::ColorMaxValue, 0, 0};
        const float kBorderThickness = 5;

        dr4::Rectangle* rect_;
        dr4::Rect2f rect_info_;

    public:
        Rectangle(dr4::Rectangle* rect, pp::Canvas* cvs) {
            cvs_ = cvs;
            rect_ = rect; rect_info_ = {};
            rect_->SetBorderColor(kBorderColor);
            rect_->SetBorderThickness(kBorderThickness);
            rect_->SetFillColor({0, 0, 0, 0});
            selected_ = false;
        };

        ~Rectangle() {
            delete rect_;
        };

        virtual bool OnMouseDown(const dr4::Event::MouseButton &evt) override;
        virtual bool OnMouseUp(const dr4::Event::MouseButton &evt) override;
        virtual bool OnMouseMove(const dr4::Event::MouseMove &evt) override;

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

        virtual void OnSelect() override {selected_ = true;};
        virtual void OnDeselect() override {selected_ = false;};

        void SetTheme(const pp::ControlsTheme& theme) {
            rect_->SetFillColor(theme.shapeColor);
            rect_->SetBorderColor(theme.lineColor);
        };
};

class Circle : public pp::Shape {
    private:
        pp::Canvas* cvs_;

        bool selected_;

        const dr4::Color kBorderColor = {dr4::Color::ColorMaxValue, 0, 0};
        const float kBorderThickness = 5;

        dr4::Circle* circle_;
        dr4::Vec2f center_;

    public:
        Circle(dr4::Circle* circle, pp::Canvas* cvs) {
            cvs_ = cvs;
            circle_ = circle;
            circle_->SetBorderColor(kBorderColor);
            circle_->SetBorderThickness(kBorderThickness);
            circle_->SetFillColor({0, 0, 0, 0});
            selected_ = false;
        };

        ~Circle() {
            delete circle_;
        };

        virtual bool OnMouseDown(const dr4::Event::MouseButton &evt) override;
        virtual bool OnMouseUp(const dr4::Event::MouseButton &evt) override;
        virtual bool OnMouseMove(const dr4::Event::MouseMove &evt) override;

        virtual void DrawOn(dr4::Texture& texture) const override {
            circle_->DrawOn(texture);
        };

        virtual void SetPos(dr4::Vec2f pos) override {
            center_ = pos;
            circle_->SetCenter(pos);
        };

        virtual dr4::Vec2f GetPos() const override {
            return circle_->GetPos();
        };

        virtual void OnSelect() override {selected_ = true;};
        virtual void OnDeselect() override {selected_ = false;};

        void SetTheme(const pp::ControlsTheme& theme) {
            circle_->SetFillColor(theme.shapeColor);
            circle_->SetBorderColor(theme.lineColor);
        };
};

class Arrow : public pp::Shape {
    private:
        pp::Canvas* cvs_;

        bool selected_;

        const dr4::Color kFillColor = {dr4::Color::ColorMaxValue, 0, 0};
        const float kWidth = 3;
        const float kArrowLen = 20;
        const float kWidthDivSqrt2 = kWidth / sqrt(2);

        dr4::Line* line1_;
        dr4::Line* line2_;
        dr4::Line* line3_;

        dr4::Vec2f start_;
        dr4::Vec2f end_;

    public:
        Arrow(dr4::Line* line1, dr4::Line* line2, dr4::Line* line3, pp::Canvas* cvs) {
            cvs_ = cvs;
            line1_ = line1;
            line2_ = line2;
            line3_ = line3;
            line1_->SetColor(kFillColor);
            line1_->SetThickness(kWidth);
            line2_->SetColor(kFillColor);
            line2_->SetThickness(kWidth);
            line3_->SetColor(kFillColor);
            line3_->SetThickness(kWidth);
            selected_ = false;
        };

        ~Arrow() {
            delete line1_;
            delete line2_;
            delete line3_;
        }

        virtual bool OnMouseDown(const dr4::Event::MouseButton &evt) override;
        virtual bool OnMouseUp(const dr4::Event::MouseButton &evt) override;
        virtual bool OnMouseMove(const dr4::Event::MouseMove &evt) override;

        virtual void DrawOn(dr4::Texture& texture) const override {
            line1_->DrawOn(texture);
            line2_->DrawOn(texture);
            line3_->DrawOn(texture);
        };

        virtual void SetPos(dr4::Vec2f pos) override {
            line1_->SetStart(pos);
            dr4::Vec2f vec = end_ - start_;
            float len = sqrt(vec.x * vec.x + vec.y * vec.y);
            end_ = vec + pos;
            start_ = pos;
            line1_->SetEnd(end_);

            line2_->SetStart(end_);
            line2_->SetEnd(end_ + dr4::Vec2f(-(vec.y), vec.x) * kArrowLen / len);

            line3_->SetStart(end_);
            line3_->SetEnd(end_ + dr4::Vec2f(vec.y, -(vec.x)) * kArrowLen / len);
        };

        virtual dr4::Vec2f GetPos() const override {
            return start_;
        };

        virtual void OnSelect() override {selected_ = true;};
        virtual void OnDeselect() override {selected_ = false;};

        void SetTheme(const pp::ControlsTheme& theme) {
            line1_->SetColor(theme.lineColor);
            line2_->SetColor(theme.lineColor);
            line3_->SetColor(theme.lineColor);
        };

    private:
        bool IsLineContainPos(const dr4::Line* line, dr4::Vec2f pos) {
            dr4::Vec2f vec_line = line->GetEnd() - line->GetStart();
            float len_line = sqrt(vec_line.x * vec_line.x + vec_line.y * vec_line.y);
            float sin_line = vec_line.y / len_line;
            float cos_line = vec_line.x / len_line;

            dr4::Vec2f vec = pos - line->GetStart();
            float len = sqrt(vec.x * vec.x + vec.y * vec.y);
            float sin = vec.y / len;
            float cos = vec.x / len;

            return (len < len_line)
                    && (sin > sin_line - kEpsilon)
                    && (sin < sin_line + kEpsilon)
                    && (cos > cos_line - kEpsilon)
                    && (cos < cos_line + kEpsilon);
        };
};

};

#endif // GEOM_PRIM_HPP
