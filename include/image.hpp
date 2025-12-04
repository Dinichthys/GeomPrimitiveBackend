#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <math.h>
#include <string>
#include <vector>
#include <string.h>

#include "pp/tool.hpp"
#include "pp/shape.hpp"
#include "pp/canvas.hpp"

#include "dr4/math/rect.hpp"

#include "geom_prim.hpp"

namespace pp {

static const std::string kEnterFileName = "image.png";
static const dr4::Vec2f kEnterFileNameSize = {300, 30};
static const size_t kRGBASizeEncoding = 4;
static const dr4::Color kDefaultColor = {0, 0, 0};
static const dr4::Color kBaseFillColorTextField = {150, 150, 150};

class EnterFileName : public pp::Shape {
    private:
        pp::Canvas* cvs_;

        dr4::Rect2f rect_info_;

        dr4::Text* text_;
        dr4::Rectangle* rect_;
        dr4::Texture* texture_;

        const float kBorderThickness = 2;

    public:
        EnterFileName(pp::Canvas* cvs) {
            cvs_ = cvs;

            text_ = cvs->GetWindow()->CreateText();
            text_->SetFontSize(kFontSize);
            text_->SetPos({});
            text_->SetColor(cvs->GetControlsTheme().textColor);
            dr4::Font* font = cvs->GetWindow()->CreateFont();
            if (font != NULL) {
                font->LoadFromFile(kFontFileName);
                text_->SetFont(font);
            }
            text_->SetText(kEnterFileName);

            texture_ = cvs->GetWindow()->CreateTexture();
            texture_->SetPos({});
            texture_->SetSize(kEnterFileNameSize);

            rect_ = cvs->GetWindow()->CreateRectangle();
            rect_->SetBorderThickness(kBorderThickness);
            rect_->SetBorderColor(cvs->GetControlsTheme().shapeBorderColor);
            rect_->SetFillColor(cvs->GetControlsTheme().shapeFillColor);
            rect_->SetPos({});
            rect_->SetSize(kEnterFileNameSize);
            rect_info_.pos = {};
            rect_info_.size = kEnterFileNameSize;
        };

        ~EnterFileName() {
            delete rect_;
            delete text_;
            delete texture_;
        };

        virtual void DrawOn(dr4::Texture& texture) const override {
            rect_->SetPos((texture.GetSize() - rect_info_.size) / 2);
            texture_->SetPos((texture.GetSize() - rect_info_.size) / 2);
            rect_->DrawOn(texture);
            text_->DrawOn(*texture_);
            texture_->DrawOn(texture);
        };

        virtual void SetPos(dr4::Vec2f pos) override {
            rect_info_.pos = pos;
            texture_->SetPos(pos);
            rect_->SetPos(pos);
        };

        virtual dr4::Vec2f GetPos() const override {
            return rect_info_.pos;
        };

        virtual bool OnKeyDown(const dr4::Event::KeyEvent &evt) override {
            auto str = text_->GetText();
            switch(evt.sym) {
                case dr4::KeyCode::KEYCODE_ENTER :
                    cvs_->SetSelectedShape(NULL);
                    return true;
                case dr4::KeyCode::KEYCODE_BACKSPACE :
                    text_->SetText(text_->GetText().substr(0, str.length() - 1));
                    texture_->Clear({0, 0, 0, 0});
                    return true;
                default :
                    return false;
            }
        }

        virtual bool OnText(const dr4::Event::TextEvent &evt) override {
            if ((strcmp(evt.unicode, "\b") == 0)
                || (strcmp(evt.unicode, "\n") == 0)) {
                return false;
            }

            auto str = text_->GetText();
            text_->SetText(str + evt.unicode);
            texture_->Clear({0, 0, 0, 0});

            return true;
        }

        const std::string& GetText() {return text_->GetText();};
};

class Image : public pp::Shape {
    private:
        pp::Canvas* cvs_;

        bool selected_;
        bool uploaded_;
        bool started_;

        const dr4::Color kBorderColor = {dr4::Color::ColorMaxValue, 0, 0};
        const float kBorderThickness = 5;

        dr4::Image* image_;
        dr4::Rect2f rect_info_;

        dr4::Rectangle* border_;

        std::vector<unsigned char> data_;
        dr4::Vec2f data_size_;

    public:
        Image(pp::Canvas* cvs, const std::string& file_name) {
            cvs_ = cvs;
            image_ = cvs->GetWindow()->CreateImage();
            image_->SetPos({});

            border_ = cvs->GetWindow()->CreateRectangle();
            border_->SetBorderColor(cvs->GetControlsTheme().handleColor);
            border_->SetBorderThickness(kBorderThickness);
            border_->SetFillColor({0, 0, 0, 0});
            rect_info_ = {};
            selected_ = false;

            uploaded_ = false;
            data_size_ = {};

            SetPicture(file_name);
            image_->SetSize(data_size_);

            started_ = false;
        };

        ~Image() {
            delete border_;
            delete image_;
        };

        virtual bool OnMouseDown(const dr4::Event::MouseButton &evt) override;
        virtual bool OnMouseUp(const dr4::Event::MouseButton &evt) override;
        virtual bool OnMouseMove(const dr4::Event::MouseMove &evt) override;

        virtual void DrawOn(dr4::Texture& texture) const override {
            if (!started_) {
                return;
            }

            ImageDataRedraw();
            image_->DrawOn(texture);

            if (selected_) {
                border_->DrawOn(texture);
            }
        };

        virtual void SetPos(dr4::Vec2f pos) override {
            rect_info_.pos = pos;
            border_->SetPos(pos);
            image_->SetPos(pos);
        };

        virtual dr4::Vec2f GetPos() const override {
            return rect_info_.pos;
        };

        virtual void OnSelect() override {
            cvs_->SetSelectedShape(this);
            selected_ = true;
        };
        virtual void OnDeselect() override {
            if (cvs_->GetSelectedShape() == this) {
                cvs_->SetSelectedShape(NULL);
            }
            selected_ = false;
        };

        void SetTheme(const pp::ControlsTheme& theme) {
            border_->SetBorderColor(theme.handleColor);
        };

    private:
        void SetPicture(const std::string& file_name);

        void ImageDataRedraw() const;
};

class ImageTool : public pp::Tool {
    private:
        pp::Canvas* cvs_;

        bool is_drawing_;
        bool entered_;

        Image* image_;

        EnterFileName* file_name_shape_;

        std::string file_name_ = kEnterFileName;

        const std::string kIcon = "I";
        const std::string kName = "ImageTool";

    public:
        ImageTool(pp::Canvas* cvs)
            :cvs_(cvs), is_drawing_(false), entered_(false), image_(NULL) {};

        virtual std::string_view Icon() const override {return kIcon;};
        virtual std::string_view Name() const override {return kName;};
        virtual bool IsCurrentlyDrawing() const override {return is_drawing_;};

        virtual void OnStart() override {
            if (entered_) {
                is_drawing_ = true;
                image_ = new Image(cvs_, file_name_);
                image_->SetTheme(cvs_->GetControlsTheme());
                cvs_->AddShape(image_);
                cvs_->SetSelectedShape(image_);
            } else {
                file_name_shape_ = new EnterFileName(cvs_);
                cvs_->AddShape(file_name_shape_);
                cvs_->SetSelectedShape(file_name_shape_);
            }
        };
        virtual void OnBreak() override {
            if (!is_drawing_) {
                return;
            }
            cvs_->DelShape(image_);
            OnEnd();
        };
        virtual void OnEnd() override {
            image_ = NULL;
            is_drawing_ = false;
            cvs_->SetSelectedShape(NULL);
            entered_ = false;
        };

        virtual bool OnMouseDown(const dr4::Event::MouseButton &evt) override;
        virtual bool OnMouseUp(const dr4::Event::MouseButton &evt) override;
        virtual bool OnMouseMove(const dr4::Event::MouseMove &evt) override;

        virtual bool OnKeyDown(const dr4::Event::KeyEvent &evt) override {
            if (entered_) {
                return false;
            }

            switch(evt.sym) {
                case dr4::KeyCode::KEYCODE_ENTER :
                    cvs_->SetSelectedShape(NULL);
                    file_name_ = file_name_shape_->GetText();
                    cvs_->DelShape(file_name_shape_);
                    entered_ = true;
                    file_name_shape_ = NULL;
                    OnStart();
                    return true;
                default :
                    return file_name_shape_->OnKeyDown(evt);
            }
        }

        virtual bool OnText(const dr4::Event::TextEvent &evt) override {
            if (entered_) {
                return false;
            }

            return file_name_shape_->OnText(evt);
        }
};

}; // pp

#endif // IMAGE_HPP
