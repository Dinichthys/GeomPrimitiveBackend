#ifndef PRINT_SCREEN_HPP
#define PRINT_SCREEN_HPP

#include <math.h>
#include <string>
#include <vector>
#include <string.h>

#include "pp/tool.hpp"
#include "pp/shape.hpp"
#include "pp/canvas.hpp"

#include "dr4/math/rect.hpp"

#include "geom_prim.hpp"
#include "image.hpp"

namespace pp {

class PrintScreenTool;

class PrintScreen : public pp::Shape {
    private:
        pp::Canvas* cvs_;

        PrintScreenTool* tool_;

        const dr4::Color kBorderColor = {dr4::Color::ColorMaxValue, 0, 0};
        const float kBorderThickness = 5;

        bool started_;
        bool is_drawing_;

        dr4::Rect2f rect_info_;

        dr4::Rectangle* border_;

        dr4::Texture* background_;

    public:
        PrintScreen(pp::Canvas* cvs, PrintScreenTool* tool) {
            cvs_ = cvs;

            tool_ = tool;

            border_ = cvs->GetWindow()->CreateRectangle();
            border_->SetBorderColor(cvs->GetControlsTheme().handleColor);
            border_->SetBorderThickness(kBorderThickness);
            border_->SetFillColor({0, 0, 0, 0});
            rect_info_ = {};

            background_ = cvs->GetWindow()->CreateTexture();
            background_->SetPos({});
            background_->SetZero(-rect_info_.pos);

            started_ = false;
            is_drawing_ = false;
        };

        ~PrintScreen() {
            delete border_;
        };

        virtual bool OnMouseDown(const dr4::Event::MouseButton &evt) override;
        virtual bool OnMouseUp(const dr4::Event::MouseButton &evt) override;
        virtual bool OnMouseMove(const dr4::Event::MouseMove &evt) override;

        virtual void DrawOn(dr4::Texture& texture) const override {
            if (!started_) {
                return;
            }

            border_->DrawOn(texture);
            dr4::Vec2f pos = texture.GetPos();
            texture.SetPos({});
            texture.DrawOn(*background_);
            texture.SetPos(pos);
        };

        virtual void SetPos(dr4::Vec2f pos) override {
            rect_info_.pos = pos;
            border_->SetPos(pos);
            background_->SetZero(-pos);
        };

        virtual dr4::Vec2f GetPos() const override {
            return rect_info_.pos;
        };

        void OnSelect() {};
        void OnDeselect() {};

        void SetTheme(const pp::ControlsTheme& theme) {
            border_->SetBorderColor(theme.handleColor);
        };

        void SavePicture(const std::string& file_name);
};

class PrintScreenTool : public pp::Tool {
    private:
        pp::Canvas* cvs_;

        bool is_drawing_;
        bool entered_;

        PrintScreen* print_screen_;

        EnterFileName* file_name_shape_;

        std::string file_name_ = kEnterFileName;

        const std::string kIcon = "PS";
        const std::string kName = "PrintScreenTool";

    public:
        PrintScreenTool(pp::Canvas* cvs)
            :cvs_(cvs), is_drawing_(false), entered_(false), print_screen_(NULL) {};

        virtual std::string_view Icon() const override {return kIcon;};
        virtual std::string_view Name() const override {return kName;};
        virtual bool IsCurrentlyDrawing() const override {return is_drawing_;};

        virtual void OnStart() override {
            if (entered_) {
                file_name_shape_ = new EnterFileName(cvs_);
                cvs_->AddShape(file_name_shape_);
                cvs_->SetSelectedShape(file_name_shape_);
            } else {
                is_drawing_ = true;
                print_screen_ = new PrintScreen(cvs_, this);
                print_screen_->SetTheme(cvs_->GetControlsTheme());
                cvs_->AddShape(print_screen_);
                cvs_->SetSelectedShape(print_screen_);
            }
        };
        virtual void OnBreak() override {
            if (!is_drawing_) {
                return;
            }
            cvs_->DelShape(print_screen_);
            cvs_->DelShape(file_name_shape_);
            OnEnd();
        };
        virtual void OnEnd() override {
            if (file_name_shape_ != NULL) {
                file_name_shape_->OnDeselect();
                cvs_->DelShape(file_name_shape_);
            }
            if (print_screen_ != NULL) {
                print_screen_->OnDeselect();
                cvs_->DelShape(print_screen_);
            }
            print_screen_ = NULL;
            file_name_shape_= NULL;

            is_drawing_ = false;
            cvs_->SetSelectedShape(NULL);
            entered_ = false;
        };

        void SwitchToFileName() {
            is_drawing_ = false;
            entered_ = true;
            OnStart();
        }

        virtual bool OnMouseDown(const dr4::Event::MouseButton &evt) override;
        virtual bool OnMouseUp(const dr4::Event::MouseButton &evt) override;
        virtual bool OnMouseMove(const dr4::Event::MouseMove &evt) override;

        virtual bool OnKeyDown(const dr4::Event::KeyEvent &evt) override {
            if (!entered_) {
                return false;
            }

            switch(evt.sym) {
                case dr4::KeyCode::KEYCODE_ENTER :
                    cvs_->SetSelectedShape(NULL);
                    file_name_ = file_name_shape_->GetText();
                    print_screen_->SavePicture(file_name_);
                    OnEnd();
                    return true;
                default :
                    return file_name_shape_->OnKeyDown(evt);
            }
        }

        virtual bool OnText(const dr4::Event::TextEvent &evt) override {
            if (entered_) {
                return file_name_shape_->OnText(evt);
            }

            return false;
        }
};

}; // pp

#endif // PRINT_SCREEN_HPP
