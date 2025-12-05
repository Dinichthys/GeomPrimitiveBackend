#include "image.hpp"

extern "C" {
    #define STB_IMAGE_IMPLEMENTATION
    #include "stb/stb_image.h"
}

namespace pp {

bool ImageTool::OnMouseDown(const dr4::Event::MouseButton &evt) {
    if (!entered_) {
        return false;
    }

    if ((!is_drawing_ && (cvs_->GetSelectedShape() == NULL))
        || (cvs_->GetSelectedShape() != image_)) {
        is_drawing_ = true;
        image_->OnMouseDown(evt);
        return true;
    }

    is_drawing_ = true;
    image_->OnMouseDown(evt);
    return true;
}

bool ImageTool::OnMouseUp(const dr4::Event::MouseButton &evt) {
    if (!is_drawing_) {
        return false;
    }

    image_->OnMouseUp(evt);
    image_->OnDeselect();
    OnEnd();
    return true;
}

bool ImageTool::OnMouseMove(const dr4::Event::MouseMove &evt) {
    if (!is_drawing_) {
        return false;
    }

    image_->OnMouseMove(evt);
    return true;
}

bool Image::OnMouseDown(const dr4::Event::MouseButton &evt) {
    if (selected_) {
        SetPos(evt.pos);
        is_drawing_ = true;
        return true;
    }

    dr4::Rect2f external_rect = rect_info_;
    external_rect.size = {external_rect.size.x + kBorderThickness, external_rect.size.y + kBorderThickness};

    dr4::Rect2f internal_rect = rect_info_;
    internal_rect.size = {internal_rect.size.x - kBorderThickness, internal_rect.size.y - kBorderThickness};

    if ((external_rect.Contains(evt.pos)) && (!internal_rect.Contains(evt.pos))) {
        cvs_->SetSelectedShape(this);
        selected_ = true;

        return true;
    }

    return false;
}

bool Image::OnMouseUp(const dr4::Event::MouseButton &evt) {
    if (!selected_ || !is_drawing_) {
        return false;
    }

    rect_info_.size = evt.pos - rect_info_.pos;
    if (rect_info_.size.x < 0) {
        if (rect_info_.size.y < 0) {
            image_->SetPos(rect_info_.pos + rect_info_.size);
            border_->SetPos(rect_info_.pos + rect_info_.size);
        } else {
            image_->SetPos({rect_info_.pos.x + rect_info_.size.x, rect_info_.pos.y});
            border_->SetPos({rect_info_.pos.x + rect_info_.size.x, rect_info_.pos.y});
        }
    } else {
        if (rect_info_.size.y < 0) {
            image_->SetPos({rect_info_.pos.x, rect_info_.pos.y + rect_info_.size.y});
            border_->SetPos({rect_info_.pos.x, rect_info_.pos.y + rect_info_.size.y});
        }
    }
    rect_info_.pos = image_->GetPos();
    rect_info_.size = {abs(rect_info_.size.x), abs(rect_info_.size.y)};
    image_->SetSize(rect_info_.size);
    border_->SetSize(rect_info_.size);

    cvs_->SetSelectedShape(NULL);
    selected_ = false;

    return true;
}

bool Image::OnMouseMove(const dr4::Event::MouseMove &evt) {
    if (!selected_ || !is_drawing_) {
        return false;
    }

    started_ = true;

    rect_info_.size = evt.pos - rect_info_.pos;
    if (rect_info_.size.x < 0) {
        if (rect_info_.size.y < 0) {
            image_->SetPos(rect_info_.pos + rect_info_.size);
            border_->SetPos(rect_info_.pos + rect_info_.size);
        } else {
            image_->SetPos({rect_info_.pos.x + rect_info_.size.x, rect_info_.pos.y});
            border_->SetPos({rect_info_.pos.x + rect_info_.size.x, rect_info_.pos.y});
        }
    } else {
        if (rect_info_.size.y < 0) {
            image_->SetPos({rect_info_.pos.x, rect_info_.pos.y + rect_info_.size.y});
            border_->SetPos({rect_info_.pos.x, rect_info_.pos.y + rect_info_.size.y});
        }
    }
    rect_info_.size = {abs(rect_info_.size.x), abs(rect_info_.size.y)};
    image_->SetSize(rect_info_.size);
    border_->SetSize(rect_info_.size);

    return true;
}

void Image::SetPicture(const std::string& file_name) {
    int n = 0, width = 0, height = 0;
    unsigned char* data = stbi_load(file_name.c_str(), &width, &height, &n, kRGBASizeEncoding);
    if (data == nullptr) {
        uploaded_ = false;
        return;
    }

    data_ = std::vector<unsigned char>(data, data + width * height * kRGBASizeEncoding);
    data_size_ = {float(width), float(height)};
    uploaded_ = true;

    stbi_image_free(data);
}

void Image::ImageDataRedraw() const {
    if (!uploaded_) {
        for (size_t x = 0; x < rect_info_.size.x; x++) {
            for (size_t y = 0; y < rect_info_.size.y; y++) {
                image_->SetPixel(x, y, kDefaultColor);
            }
        }
        return;
    }

    for (size_t x = 0; x < rect_info_.size.x; x++) {
        for (size_t y = 0; y < rect_info_.size.y; y++) {
            size_t cur_x = x * data_size_.x / rect_info_.size.x;
            size_t cur_y = y * data_size_.y / rect_info_.size.y;

            size_t index = kRGBASizeEncoding * (cur_y * data_size_.x + cur_x);
            image_->SetPixel(x, y, {
                data_[index + 0],
                data_[index + 1],
                data_[index + 2],
                data_[index + 3]
            });
        }
    }

}

};
