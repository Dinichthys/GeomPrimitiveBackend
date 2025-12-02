#include "geom_prim.hpp"

#include <math.h>
#include <string.h>

namespace pp {

//----------RECTANGLE-----------------------------------------------------------------------------------------

bool Rectangle::OnMouseDown(const dr4::Event::MouseButton &evt) {
    if (selected_) {
        rect_info_.pos = evt.pos;
        rect_->SetPos(rect_info_.pos);

        resize_dot_->SetCenter(evt.pos);

        return true;
    }

    dr4::Rect2f external_rect = rect_info_;
    external_rect.size = {external_rect.size.x + kBorderThickness, external_rect.size.y + kBorderThickness};

    dr4::Rect2f internal_rect = rect_info_;
    internal_rect.size = {internal_rect.size.x - kBorderThickness, internal_rect.size.y - kBorderThickness};

    if ((external_rect.Contains(evt.pos)) && (!internal_rect.Contains(evt.pos))) {
        cvs_->SetSelectedShape(this);
        selected_ = true;

        resize_dot_->SetCenter(evt.pos);

        return true;
    }

    return false;
}

bool Rectangle::OnMouseUp(const dr4::Event::MouseButton &evt) {
    if (!selected_) {
        return false;
    }

    rect_info_.size = evt.pos - rect_info_.pos;
    if (rect_info_.size.x < 0) {
        if (rect_info_.size.y < 0) {
            rect_info_.pos = rect_info_.pos + rect_info_.size;
        } else {
            rect_info_.pos = {rect_info_.pos.x + rect_info_.size.x, rect_info_.pos.y};
        }
        rect_->SetPos(rect_info_.pos);
    } else {
        if (rect_info_.size.y < 0) {
            rect_info_.pos = {rect_info_.pos.x, rect_info_.pos.y + rect_info_.size.y};
            rect_->SetPos(rect_info_.pos);
        }
    }
    rect_info_.size = {abs(rect_info_.size.x), abs(rect_info_.size.y)};
    rect_->SetSize(rect_info_.size);

    cvs_->SetSelectedShape(NULL);
    selected_ = false;

    return true;
}

bool Rectangle::OnMouseMove(const dr4::Event::MouseMove &evt) {
    if (!selected_) {
        return false;
    }

    rect_info_.size = evt.pos - rect_info_.pos;
    if (rect_info_.size.x < 0) {
        if (rect_info_.size.y < 0) {
            rect_->SetPos(rect_info_.pos + rect_info_.size);
        } else {
            rect_->SetPos({rect_info_.pos.x + rect_info_.size.x, rect_info_.pos.y});
        }
    } else {
        if (rect_info_.size.y < 0) {
            rect_->SetPos({rect_info_.pos.x, rect_info_.pos.y + rect_info_.size.y});
        }
    }
    rect_info_.size = {abs(rect_info_.size.x), abs(rect_info_.size.y)};
    rect_->SetSize(rect_info_.size);

    resize_dot_->SetCenter(evt.pos);

    return true;
}

//----------CIRCLE--------------------------------------------------------------------------------------------

bool Circle::OnMouseDown(const dr4::Event::MouseButton &evt) {
    if (selected_) {
        center_ = evt.pos;
        circle_->SetCenter(evt.pos);
        return true;
    }

    float radius_circle = circle_->GetRadius().x;
    dr4::Vec2f vec = evt.pos - center_;
    float cur_radius = sqrt(vec.x * vec.x + vec.y * vec.y);
    if ((cur_radius > radius_circle - kBorderThickness)
        && (cur_radius < radius_circle + kBorderThickness)) {
        cvs_->SetSelectedShape(this);
        selected_ = true;
        return true;
    }

    return false;
}

bool Circle::OnMouseUp(const dr4::Event::MouseButton &evt) {
    if (!selected_) {
        return false;
    }

    dr4::Vec2f vec = evt.pos - center_;
    float radius = sqrt(vec.x * vec.x + vec.y * vec.y);
    circle_->SetRadius(radius);
    circle_->SetCenter(center_);
    cvs_->SetSelectedShape(NULL);
    selected_ = false;
    return true;
}

bool Circle::OnMouseMove(const dr4::Event::MouseMove &evt) {
    if (!selected_) {
        return false;
    }

    dr4::Vec2f vec = evt.pos - center_;
    float radius = sqrt(vec.x * vec.x + vec.y * vec.y);
    circle_->SetRadius(radius);
    circle_->SetCenter(center_);
    return true;
}

//----------ARROW---------------------------------------------------------------------------------------------

bool Arrow::OnMouseDown(const dr4::Event::MouseButton &evt) {
    if (selected_) {
        start_ = evt.pos;
        line1_->SetStart(evt.pos);
        return true;
    }

    if (IsLineContainPos(line1_, evt.pos)
        || IsLineContainPos(line2_, evt.pos)
        || IsLineContainPos(line3_, evt.pos)) {
        cvs_->SetSelectedShape(this);
        selected_ = true;
        return true;
    }

    return false;
}

bool Arrow::OnMouseUp(const dr4::Event::MouseButton &evt) {
    if (!selected_) {
        return false;
    }

    end_ = evt.pos;
    dr4::Vec2f vec = end_ - start_;
    dr4::Vec2f ortho(-(vec.y), vec.x);
    float len = sqrt(vec.x * vec.x + vec.y * vec.y);
    line1_->SetEnd(end_);

    line2_->SetStart(end_ + (ortho - vec) * kWidthDivSqrt2 / len);
    line2_->SetEnd(end_ - (vec + ortho) * kArrowLen / len);

    line3_->SetStart(end_ + ortho * kWidth / len);
    line3_->SetEnd(end_ - (vec - ortho) * kArrowLen / len);
    cvs_->SetSelectedShape(NULL);
    selected_ = false;
    return true;
}

bool Arrow::OnMouseMove(const dr4::Event::MouseMove &evt) {
    if (!selected_) {
        return false;
    }

    end_ = evt.pos;
    dr4::Vec2f vec = end_ - start_;
    dr4::Vec2f ortho(-(vec.y), vec.x);
    float len = sqrt(vec.x * vec.x + vec.y * vec.y);
    line1_->SetEnd(end_);

    line2_->SetStart(end_ + (ortho - vec) * kWidthDivSqrt2 / len);
    line2_->SetEnd(end_ - (vec + ortho) * kArrowLen / len);

    line3_->SetStart(end_ + ortho * kWidth / len);
    line3_->SetEnd(end_ - (vec - ortho) * kArrowLen / len);
    return true;
}

//----------PENIS---------------------------------------------------------------------------------------------

bool Penis::OnMouseDown(const dr4::Event::MouseButton &evt) {
    if (selected_) {
        SetPos(evt.pos);
        return true;
    }

    float radius_circle = kWidth;
    dr4::Vec2f vec = evt.pos - end_;
    float cur_radius = sqrt(vec.x * vec.x + vec.y * vec.y);
    if ((cur_radius < radius_circle)) {
        cvs_->SetSelectedShape(this);
        selected_ = true;
        return true;
    }

    return false;
}

bool Penis::OnMouseUp(const dr4::Event::MouseButton &evt) {
    if (!selected_) {
        return false;
    }

    end_ = evt.pos;
    dr4::Vec2f vec = end_ - start_;
    float len = sqrt(vec.x * vec.x + vec.y * vec.y);

    dr4::Vec2f center1 = start_ - dr4::Vec2f(vec.y, -vec.x) / len * kBallsRadius;
    dr4::Vec2f center2 = start_ + dr4::Vec2f(vec.y, -vec.x) / len * kBallsRadius;

    ball1_->SetCenter(center1);
    ball2_->SetCenter(center2);

    line1_->SetStart(center1 + vec / len * kBallsRadius);
    line1_->SetEnd(center1 + vec / len * (len - kBallsRadius));

    line2_->SetStart(center2 + vec / len * kBallsRadius);
    line2_->SetEnd(center2 + vec / len * (len - kBallsRadius) + dr4::Vec2f(vec.y, -vec.x) / len * kWidth);

    ending_->SetCenter(start_ + vec / len * (len - kBallsRadius));

    cvs_->SetSelectedShape(NULL);
    selected_ = false;
    return true;
}

bool Penis::OnMouseMove(const dr4::Event::MouseMove &evt) {
    if (!selected_) {
        return false;
    }

    end_ = evt.pos;
    dr4::Vec2f vec = end_ - start_;
    float len = sqrt(vec.x * vec.x + vec.y * vec.y);

    dr4::Vec2f center1 = start_ - dr4::Vec2f(vec.y, -vec.x) / len * kBallsRadius;
    dr4::Vec2f center2 = start_ + dr4::Vec2f(vec.y, -vec.x) / len * kBallsRadius;

    ball1_->SetCenter(center1);
    ball2_->SetCenter(center2);

    line1_->SetStart(center1 + vec / len * kBallsRadius);
    line1_->SetEnd(center1 + vec / len * (len - kBallsRadius));

    line2_->SetStart(center2 + vec / len * kBallsRadius);
    line2_->SetEnd(center2 + vec / len * (len - kBallsRadius) + dr4::Vec2f(vec.y, -vec.x) / len * kWidth);

    ending_->SetCenter(start_ + vec / len * (len - kBallsRadius));

    return true;
}

//----------TEXT----------------------------------------------------------------------------------------------

bool Text::OnMouseDown(const dr4::Event::MouseButton &evt) {
    if (selected_) {
        SetPos(evt.pos);
        return true;
    }

    if (rect_info_.Contains(evt.pos)) {
        cvs_->SetSelectedShape(this);
        selected_ = true;
        return true;
    }

    return false;
}

bool Text::OnMouseUp(const dr4::Event::MouseButton &evt) {
    if (!selected_) {
        return false;
    }

    rect_info_.size = evt.pos - rect_info_.pos;
    if (rect_info_.size.x < 0) {
        if (rect_info_.size.y < 0) {
            rect_info_.pos = rect_info_.pos + rect_info_.size;
        } else {
            rect_info_.pos = {rect_info_.pos.x + rect_info_.size.x, rect_info_.pos.y};
        }
        SetPos(rect_info_.pos);
    } else {
        if (rect_info_.size.y < 0) {
            rect_info_.pos = {rect_info_.pos.x, rect_info_.pos.y + rect_info_.size.y};
            SetPos(rect_info_.pos);
        }
    }
    rect_info_.size = {abs(rect_info_.size.x), abs(rect_info_.size.y)};
    texture_->SetSize(rect_info_.size);
    border_->SetSize(rect_info_.size);
    text_->SetFontSize(rect_info_.size.y);

    selected_ = false;
    printing_ = true;

    return true;
}

bool Text::OnMouseMove(const dr4::Event::MouseMove &evt) {
    if (!selected_) {
        return false;
    }

    rect_info_.size = evt.pos - rect_info_.pos;
    if (rect_info_.size.x < 0) {
        if (rect_info_.size.y < 0) {
            rect_info_.pos = rect_info_.pos + rect_info_.size;
        } else {
            rect_info_.pos = {rect_info_.pos.x + rect_info_.size.x, rect_info_.pos.y};
        }
        SetPos(rect_info_.pos);
    } else {
        if (rect_info_.size.y < 0) {
            rect_info_.pos = {rect_info_.pos.x, rect_info_.pos.y + rect_info_.size.y};
            SetPos(rect_info_.pos);
        }
    }
    rect_info_.size = {abs(rect_info_.size.x), abs(rect_info_.size.y)};
    texture_->SetSize(rect_info_.size);
    border_->SetSize(rect_info_.size);
    text_->SetFontSize(rect_info_.size.y);

    return true;
}

bool Text::OnKeyDown(const dr4::Event::KeyEvent &evt) {
    if (!printing_) {
        return false;
    }

    auto str = text_->GetText();
    size_t shift = 0;
    switch(evt.sym) {
        case dr4::KeyCode::KEYCODE_ENTER :
            printing_ = false;
            cvs_->SetSelectedShape(NULL);
            return true;
        case dr4::KeyCode::KEYCODE_BACKSPACE :
            shift = ((str.length() > 2) && (str[str.length() - 2] == '\n')) ? 2 : 1;
            text_->SetText(str.substr(0, str.length() - shift));
            return true;
        default :
            return false;
    }
}

bool Text::OnText(const dr4::Event::TextEvent &evt) {
    if (!printing_) {
        return false;
    }

    auto str = text_->GetText();
    text_->SetText(str + evt.unicode);

    if (text_->GetBounds().x > rect_info_.pos.x) {
        text_->SetText(str.substr(0, str.length() - strlen(evt.unicode)) + '\n' + evt.unicode);
    }

    return true;
}

};
