#ifndef GEOM_PRIM_HPP
#define GEOM_PRIM_HPP

#include <math.h>

#include "pp/shape.hpp"
#include "pp/canvas.hpp"

#include "dr4/math/rect.hpp"

static const char* const kFontFileName = "/usr/share/fonts/TTF/CaskaydiaCoveNerdFontMono-Regular.ttf";
static const float kFontSize = 20;

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
        dr4::Circle* resize_dot_;

    public:
        Rectangle(dr4::Rectangle* rect, pp::Canvas* cvs) {
            cvs_ = cvs;
            rect_ = rect; rect_info_ = {};
            rect_->SetBorderColor(kBorderColor);
            rect_->SetBorderThickness(kBorderThickness);
            rect_->SetFillColor({0, 0, 0, 0});
            selected_ = false;
            resize_dot_ = cvs->GetWindow()->CreateCircle();
            resize_dot_->SetRadius(kBorderThickness);
        };

        ~Rectangle() {
            delete rect_;
            delete resize_dot_;
        };

        virtual bool OnMouseDown(const dr4::Event::MouseButton &evt) override;
        virtual bool OnMouseUp(const dr4::Event::MouseButton &evt) override;
        virtual bool OnMouseMove(const dr4::Event::MouseMove &evt) override;

        virtual void DrawOn(dr4::Texture& texture) const override {
            if (selected_) {
                rect_->SetBorderColor(cvs_->GetControlsTheme().handleColor);
            } else {
                rect_->SetBorderColor(cvs_->GetControlsTheme().shapeBorderColor);
            }

            rect_->DrawOn(texture);

            if (selected_) {
                resize_dot_->DrawOn(texture);
            }
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
            rect_->SetFillColor(theme.shapeFillColor);
            rect_->SetBorderColor(theme.shapeBorderColor);
            resize_dot_->SetFillColor(theme.handleHoverColor);
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
        dr4::Rectangle* border_;

    public:
        Circle(dr4::Circle* circle, pp::Canvas* cvs) {
            cvs_ = cvs;
            circle_ = circle;
            circle_->SetBorderColor(kBorderColor);
            circle_->SetBorderThickness(kBorderThickness);
            circle_->SetFillColor({0, 0, 0, 0});
            border_ = cvs->GetWindow()->CreateRectangle();
            border_->SetFillColor({0, 0, 0, 0});
            border_->SetBorderThickness(kBorderThickness);
            selected_ = false;
        };

        ~Circle() {
            delete circle_;
            delete border_;
        };

        virtual bool OnMouseDown(const dr4::Event::MouseButton &evt) override;
        virtual bool OnMouseUp(const dr4::Event::MouseButton &evt) override;
        virtual bool OnMouseMove(const dr4::Event::MouseMove &evt) override;

        virtual void DrawOn(dr4::Texture& texture) const override {
            if (selected_) {
                circle_->SetBorderColor(cvs_->GetControlsTheme().handleActiveColor);
            } else {
                circle_->SetBorderColor(cvs_->GetControlsTheme().shapeBorderColor);
            }

            circle_->DrawOn(texture);

            if (selected_) {
                float radius = circle_->GetRadius().x;
                border_->SetPos(center_ - dr4::Vec2f(radius, radius));
                border_->SetSize({2 * radius, 2 * radius});
                border_->DrawOn(texture);
            }
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
            circle_->SetFillColor(theme.shapeFillColor);
            circle_->SetBorderColor(theme.shapeBorderColor);
            border_->SetBorderColor(theme.handleColor);
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

        dr4::Rectangle* border_;

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

            border_ = cvs->GetWindow()->CreateRectangle();
            border_->SetFillColor({0, 0, 0, 0});
            border_->SetBorderThickness(kWidth);

            selected_ = false;
        };

        ~Arrow() {
            delete line1_;
            delete line2_;
            delete line3_;

            delete border_;
        }

        virtual bool OnMouseDown(const dr4::Event::MouseButton &evt) override;
        virtual bool OnMouseUp(const dr4::Event::MouseButton &evt) override;
        virtual bool OnMouseMove(const dr4::Event::MouseMove &evt) override;

        virtual void DrawOn(dr4::Texture& texture) const override {
            if (selected_) {
                line1_->SetColor(cvs_->GetControlsTheme().handleActiveColor);
                line2_->SetColor(cvs_->GetControlsTheme().handleActiveColor);
                line3_->SetColor(cvs_->GetControlsTheme().handleActiveColor);
            } else {
                line1_->SetColor(cvs_->GetControlsTheme().shapeBorderColor);
                line2_->SetColor(cvs_->GetControlsTheme().shapeBorderColor);
                line3_->SetColor(cvs_->GetControlsTheme().shapeBorderColor);
            }

            line1_->DrawOn(texture);
            line2_->DrawOn(texture);
            line3_->DrawOn(texture);

            if (selected_) {
                float min_x = std::min(line1_->GetStart().x,
                              std::min(line1_->GetEnd().x,
                              std::min(line2_->GetStart().x,
                              std::min(line2_->GetEnd().x,
                              std::min(line3_->GetStart().x, line3_->GetEnd().x)))));
                float min_y = std::min(line1_->GetStart().y,
                              std::min(line1_->GetEnd().y,
                              std::min(line2_->GetStart().y,
                              std::min(line2_->GetEnd().y,
                              std::min(line3_->GetStart().y, line3_->GetEnd().y)))));
                float max_x = std::max(line1_->GetStart().x,
                              std::max(line1_->GetEnd().x,
                              std::max(line2_->GetStart().x,
                              std::max(line2_->GetEnd().x,
                              std::max(line3_->GetStart().x, line3_->GetEnd().x)))));
                float max_y = std::max(line1_->GetStart().y,
                              std::max(line1_->GetEnd().y,
                              std::max(line2_->GetStart().y,
                              std::max(line2_->GetEnd().y,
                              std::max(line3_->GetStart().y, line3_->GetEnd().y)))));
                border_->SetPos({min_x, min_y});
                border_->SetSize({max_x - min_x, max_y - min_y});
                border_->DrawOn(texture);
            }
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
            line1_->SetColor(theme.shapeBorderColor);
            line2_->SetColor(theme.shapeBorderColor);
            line3_->SetColor(theme.shapeBorderColor);

            border_->SetBorderColor(theme.handleColor);
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

class Penis : public pp::Shape {
    private:
        pp::Canvas* cvs_;

        bool selected_;

        const dr4::Color kFillColor = {dr4::Color::ColorMaxValue, 0, 0};
        const float kWidth = 3;
        const float kBallsRadius = 10;
        const float kWidthDivSqrt2 = kWidth / sqrt(2);

        dr4::Line* line1_;
        dr4::Line* line2_;

        dr4::Circle* ball1_;
        dr4::Circle* ball2_;
        dr4::Circle* ending_;

        dr4::Rectangle* border_;

        dr4::Vec2f start_;
        dr4::Vec2f end_;

    public:
        Penis(pp::Canvas* cvs) {
            cvs_ = cvs;
            line1_ = cvs->GetWindow()->CreateLine();
            line2_ = cvs->GetWindow()->CreateLine();
            ball1_ = cvs->GetWindow()->CreateCircle();
            ball2_ = cvs->GetWindow()->CreateCircle();
            ending_ = cvs->GetWindow()->CreateCircle();

            line1_->SetColor(kFillColor);
            line1_->SetThickness(kWidth);
            line2_->SetColor(kFillColor);
            line2_->SetThickness(kWidth);

            ball1_->SetFillColor({0, 0, 0, 0});
            ball1_->SetRadius(kBallsRadius);
            ball1_->SetBorderThickness(kWidth);
            ball1_->SetBorderColor(kFillColor);


            ball2_->SetFillColor({0, 0, 0, 0});
            ball2_->SetRadius(kBallsRadius);
            ball2_->SetBorderThickness(kWidth);
            ball2_->SetBorderColor(kFillColor);

            ending_->SetFillColor({0, 0, 0, 0});
            ending_->SetRadius(kBallsRadius);
            ending_->SetBorderThickness(kWidth);
            ending_->SetBorderColor(kFillColor);

            border_ = cvs->GetWindow()->CreateRectangle();
            border_->SetFillColor({0, 0, 0, 0});
            border_->SetBorderThickness(kWidth);

            selected_ = false;
        };

        ~Penis() {
            delete line1_;
            delete line2_;

            delete ball1_;
            delete ball2_;
            delete ending_;

            delete border_;
        }

        virtual bool OnMouseDown(const dr4::Event::MouseButton &evt) override;
        virtual bool OnMouseUp(const dr4::Event::MouseButton &evt) override;
        virtual bool OnMouseMove(const dr4::Event::MouseMove &evt) override;

        virtual void DrawOn(dr4::Texture& texture) const override {
            if (selected_) {
                line1_->SetColor(cvs_->GetControlsTheme().handleActiveColor);
                line2_->SetColor(cvs_->GetControlsTheme().handleActiveColor);
                ball1_->SetBorderColor(cvs_->GetControlsTheme().handleActiveColor);
                ball2_->SetBorderColor(cvs_->GetControlsTheme().handleActiveColor);
                ending_->SetBorderColor(cvs_->GetControlsTheme().handleActiveColor);
            } else {
                line1_->SetColor(cvs_->GetControlsTheme().shapeBorderColor);
                line2_->SetColor(cvs_->GetControlsTheme().shapeBorderColor);
                ball1_->SetBorderColor(cvs_->GetControlsTheme().shapeBorderColor);
                ball2_->SetBorderColor(cvs_->GetControlsTheme().shapeBorderColor);
                ending_->SetBorderColor(cvs_->GetControlsTheme().shapeBorderColor);
            }

            line1_->DrawOn(texture);
            line2_->DrawOn(texture);
            ball1_->DrawOn(texture);
            ball2_->DrawOn(texture);
            ending_->DrawOn(texture);

            if (selected_) {
                float min_x = std::min(ball1_->GetCenter().x,
                              std::min(ball2_->GetCenter().x, ending_->GetCenter().x));
                float min_y = std::min(ball1_->GetCenter().y,
                              std::min(ball2_->GetCenter().y, ending_->GetCenter().y));
                float max_x = std::max(ball1_->GetCenter().x,
                              std::max(ball2_->GetCenter().x, ending_->GetCenter().x));
                float max_y = std::max(ball1_->GetCenter().y,
                              std::max(ball2_->GetCenter().y, ending_->GetCenter().y));
                border_->SetPos({min_x - kBallsRadius, min_y - kBallsRadius});
                border_->SetSize({max_x - min_x + 2 * kBallsRadius, max_y - min_y + 2 * kBallsRadius});
                border_->DrawOn(texture);
            }
        };

        virtual void SetPos(dr4::Vec2f pos) override {
            dr4::Vec2f vec = end_ - start_;
            float len = sqrt(vec.x * vec.x + vec.y * vec.y);

            dr4::Vec2f center1 = pos - dr4::Vec2f(vec.y, vec.x) / len * kBallsRadius;
            dr4::Vec2f center2 = pos + dr4::Vec2f(vec.y, vec.x) / len * kBallsRadius;

            ball1_->SetCenter(center1);
            ball2_->SetCenter(center2);

            line1_->SetStart(center1 + vec / len * kBallsRadius);
            line1_->SetEnd(center1 + vec / len * (len - kBallsRadius));

            line2_->SetStart(center2 + vec / len * kBallsRadius);
            line2_->SetEnd(center2 + vec / len * (len - kBallsRadius) + dr4::Vec2f(vec.y, -vec.x) / len * kWidth);

            ending_->SetCenter(pos + vec / len * (len - kBallsRadius));
            end_ = vec + pos;
            start_ = pos;
        };

        virtual dr4::Vec2f GetPos() const override {
            return start_;
        };

        virtual void OnSelect() override {selected_ = true;};
        virtual void OnDeselect() override {selected_ = false;};

        void SetTheme(const pp::ControlsTheme& theme) {
            line1_->SetColor(theme.shapeBorderColor);
            line2_->SetColor(theme.shapeBorderColor);
            ball1_->SetBorderColor(theme.shapeBorderColor);
            ball2_->SetBorderColor(theme.shapeBorderColor);
            ending_->SetBorderColor(theme.shapeBorderColor);

            border_->SetBorderColor(theme.handleColor);
        };
};

static const float kCaretWidth = 3;

class Text : public pp::Shape {
    private:
        pp::Canvas* cvs_;

        bool selected_;
        bool printing_;
        bool blink_;

        const float kThickness = 5;

        size_t caret_pos_;

        dr4::Texture* texture_;
        dr4::Text* text_;

        dr4::Rectangle* border_;

        dr4::Rectangle* caret_;

        dr4::Rect2f rect_info_;

    public:
        Text(pp::Canvas* cvs) {
            cvs_ = cvs;

            texture_ = cvs->GetWindow()->CreateTexture();

            text_ = cvs->GetWindow()->CreateText();

            const dr4::Font* font = cvs->GetWindow()->GetDefaultFont();
            if (font != NULL) {
                text_->SetFont(font);
            } else {
                dr4::Font* font = cvs->GetWindow()->CreateFont();
                if (font != NULL) {
                    font->LoadFromFile(kFontFileName);
                    text_->SetFont(font);
                }
            }
            text_->SetText("");
            text_->SetPos({0, 0});
            text_->SetFontSize(kFontSize);

            caret_ = cvs->GetWindow()->CreateRectangle();
            caret_->SetFillColor(cvs->GetControlsTheme().handleActiveColor);
            caret_->SetSize({kCaretWidth, kFontSize});
            caret_->SetPos({});
            caret_pos_ = 0;

            border_ = cvs->GetWindow()->CreateRectangle();
            border_->SetFillColor({0, 0, 0, 0});
            border_->SetBorderThickness(kThickness);

            selected_ = false;
            printing_ = false;
            blink_ = false;
        };

        ~Text() {
            delete texture_;
            delete text_;

            if (printing_) {
                cvs_->GetWindow()->StopTextInput();
            }

            delete border_;
        }

        virtual bool OnMouseDown(const dr4::Event::MouseButton &evt) override;
        virtual bool OnMouseUp(const dr4::Event::MouseButton &evt) override;
        virtual bool OnMouseMove(const dr4::Event::MouseMove &evt) override;
        virtual bool OnKeyDown(const dr4::Event::KeyEvent &) override;
        virtual bool OnText(const dr4::Event::TextEvent &) override;
        virtual bool OnIdle(const IdleEvent &) override {
            blink_ = !blink_;
        };

        virtual void DrawOn(dr4::Texture& texture) const override {
            if (selected_) {
                text_->SetColor(cvs_->GetControlsTheme().handleActiveColor);
            } else {
                text_->SetColor(cvs_->GetControlsTheme().textColor);
            }

            text_->DrawOn(*texture_);
            texture_->DrawOn(texture);

            if (selected_ || printing_) {
                border_->DrawOn(texture);
                if (blink_) {
                    caret_->DrawOn(texture);
                }
            }
        };

        virtual void SetPos(dr4::Vec2f pos) override {
            texture_->SetPos(pos);
            rect_info_.pos = pos;
            border_->SetPos(pos);
        };

        virtual dr4::Vec2f GetPos() const override {
            return texture_->GetPos();
        };

        virtual void OnSelect() override {selected_ = true;};
        virtual void OnDeselect() override {selected_ = false;};

        void SetTheme(const pp::ControlsTheme& theme) {
            text_->SetColor(theme.textColor);

            border_->SetBorderColor(theme.handleColor);
        };
};

};

#endif // GEOM_PRIM_HPP
