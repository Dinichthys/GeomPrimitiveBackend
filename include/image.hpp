#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <math.h>
#include <string>
#include <vector>

#include "pp/tool.hpp"
#include "pp/shape.hpp"
#include "pp/canvas.hpp"

#include "dr4/math/rect.hpp"

namespace pp {

static const std::string kImageFileName = "image.png";
static const size_t kRGBASizeEncoding = 4;
static const dr4::Color kDefaultColor = {0, 0, 0};

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
        Image(pp::Canvas* cvs) {
            cvs_ = cvs;
            image_ = cvs->GetWindow()->CreateImage();
            image_->SetPos({});

            border_ = cvs->GetWindow()->CreateRectangle();
            border_->SetBorderColor(kBorderColor);
            border_->SetBorderThickness(kBorderThickness);
            border_->SetFillColor({0, 0, 0, 0});
            rect_info_ = {};
            selected_ = false;

            uploaded_ = false;
            data_size_ = {};

            SetPicture();
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

            if (selected_) {
                border_->SetBorderColor(cvs_->GetControlsTheme().handleColor);
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
            border_->SetBorderColor(theme.lineColor);
        };

    private:
        void SetPicture();

        void ImageDataRedraw() const;
};

class ImageTool : public pp::Tool {
    private:
        pp::Canvas* cvs_;

        bool is_drawing_;

        Image* image_;

        const std::string kIcon = "I";
        const std::string kName = "ImageTool";

    public:
        ImageTool(pp::Canvas* cvs)
            :cvs_(cvs), is_drawing_(false), image_(NULL) {};

        virtual std::string_view Icon() const override {return kIcon;};
        virtual std::string_view Name() const override {return kName;};
        virtual bool IsCurrentlyDrawing() const override {return is_drawing_;};

        virtual void OnStart() override {
            is_drawing_ = false;
            image_ = new Image(cvs_);
            image_->SetTheme(cvs_->GetControlsTheme());
            cvs_->AddShape(image_);
            cvs_->SetSelectedShape(image_);
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
        };

        virtual bool OnMouseDown(const dr4::Event::MouseButton &evt) override;
        virtual bool OnMouseUp(const dr4::Event::MouseButton &evt) override;
        virtual bool OnMouseMove(const dr4::Event::MouseMove &evt) override;
};

}; // pp

#endif // IMAGE_HPP
