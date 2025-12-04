#include "print_screen.hpp"

extern "C" {
    #define STB_print_screen_WRITE_IMPLEMENTATION
    #include "stb/stb_image_write.h"
}

namespace pp {

bool PrintScreenTool::OnMouseDown(const dr4::Event::MouseButton &evt) {
    if ((!entered_ && !is_drawing_ && (cvs_->GetSelectedShape() == NULL))
        || ((cvs_->GetSelectedShape() != print_screen_) && (cvs_->GetSelectedShape() != file_name_shape_))) {
        OnStart();
        return true;
    }

    is_drawing_ = true;
    print_screen_->SetPos(evt.pos);
    print_screen_->OnSelect();
    print_screen_->OnMouseDown(evt);
    return true;
}

bool PrintScreenTool::OnMouseUp(const dr4::Event::MouseButton &evt) {
    if (!is_drawing_) {
        return false;
    }

    print_screen_->OnMouseUp(evt);
    print_screen_->OnDeselect();
    is_drawing_ = false;
    return true;
}

bool PrintScreenTool::OnMouseMove(const dr4::Event::MouseMove &evt) {
    if (!is_drawing_) {
        return false;
    }

    print_screen_->OnMouseMove(evt);
    return true;
}

bool PrintScreen::OnMouseDown(const dr4::Event::MouseButton &evt) {
    SetPos(evt.pos);
    is_drawing_ = true;
    return true;
}

bool PrintScreen::OnMouseUp(const dr4::Event::MouseButton &evt) {
    if (!is_drawing_) {
        return false;
    }

    rect_info_.size = evt.pos - rect_info_.pos;
    if (rect_info_.size.x < 0) {
        if (rect_info_.size.y < 0) {
            border_->SetPos(rect_info_.pos + rect_info_.size);
        } else {
            border_->SetPos({rect_info_.pos.x + rect_info_.size.x, rect_info_.pos.y});
        }
    } else {
        if (rect_info_.size.y < 0) {
            border_->SetPos({rect_info_.pos.x, rect_info_.pos.y + rect_info_.size.y});
        }
    }
    rect_info_.pos = border_->GetPos();
    rect_info_.size = {abs(rect_info_.size.x), abs(rect_info_.size.y)};
    border_->SetSize(rect_info_.size);

    tool_->SwitchToFileName();

    return true;
}

bool PrintScreen::OnMouseMove(const dr4::Event::MouseMove &evt) {
    if (!is_drawing) {
        return false;
    }

    rect_info_.size = evt.pos - rect_info_.pos;
    if (rect_info_.size.x < 0) {
        if (rect_info_.size.y < 0) {
            border_->SetPos(rect_info_.pos + rect_info_.size);
        } else {
            border_->SetPos({rect_info_.pos.x + rect_info_.size.x, rect_info_.pos.y});
        }
    } else {
        if (rect_info_.size.y < 0) {
            border_->SetPos({rect_info_.pos.x, rect_info_.pos.y + rect_info_.size.y});
        }
    }
    rect_info_.size = {abs(rect_info_.size.x), abs(rect_info_.size.y)};
    border_->SetSize(rect_info_.size);

    started_ = true;

    return true;
}

void PrintScreen::SavePicture(const std::string& file_name) {
    dr4::Image* image = background_->GetImage();

    unsigned char* data = (unsigned char*)calloc(rect_info_.size.x * rect_info_.size.y * kRGBASizeEncoding,
                                                 sizeof(unsigned char));

    size_t index = 0;
    for (size_t y = 0; y < rect_info_.size.y; y++) {
        for (size_t x = 0; x < rect_info_.size.x; x++) {
            dr4::Color color = image->GetPixel(x, y);

            data[index + 0] = color.r;
            data[index + 1] = color.g;
            data[index + 2] = color.b;
            data[index + 3] = color.a;

            index += kRGBASizeEncoding;
        }
    }

    stbi_write_png(file_name.c_str(), rect_info_.size.x, rect_info_.size.y, kRGBASizeEncoding,
                   data, rect_info_.size.x * kRGBASizeEncoding);

    free(data);

    delete image;
}

void PrintScreen::OnSelect() {
    cvs_->SetSelectedShape(this);
}
void PrintScreen::OnDeselect() {
    if (cvs_->GetSelectedShape() == this) {
        cvs_->SetSelectedShape(NULL);
    }
}

};
