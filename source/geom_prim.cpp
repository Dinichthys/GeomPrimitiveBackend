#include "geom_prim.hpp"

#include <math.h>

//----------RECTANGLE-----------------------------------------------------------------------------------------

hui::EventResult Rectangle::OnMouseDown(const hui::MouseDownEvent& evt) {
    rect_info_.pos = evt.relPos;
    rect_->SetPos(rect_info_.pos);
    return hui::EventResult::HANDLED;
}

hui::EventResult Rectangle::OnMouseRelease(const hui::MouseUpEvent& evt) {
    rect_info_.size = evt.relPos - rect_info_.pos;
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
    return hui::EventResult::HANDLED;
}

hui::EventResult Rectangle::OnMouseMove(const hui::MouseMoveEvent& evt) {
    rect_info_.size = evt.rel - rect_info_.pos;
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
    return hui::EventResult::HANDLED;
}

//----------CIRCLE--------------------------------------------------------------------------------------------

hui::EventResult Circle::OnMouseDown(const hui::MouseDownEvent& evt) {
    center_ = evt.relPos;
    circle_->SetCenter(evt.relPos);
    return hui::EventResult::HANDLED;
}

hui::EventResult Circle::OnMouseRelease(const hui::MouseUpEvent& evt) {
    dr4::Vec2f vec = evt.relPos - center_;
    float radius = sqrt(vec.x * vec.x + vec.y * vec.y);
    circle_->SetRadius(radius);
    return hui::EventResult::HANDLED;
}

hui::EventResult Circle::OnMouseMove(const hui::MouseMoveEvent& evt) {
    dr4::Vec2f vec = evt.rel - center_;
    float radius = sqrt(vec.x * vec.x + vec.y * vec.y);
    circle_->SetRadius(radius);
    return hui::EventResult::HANDLED;
}

//----------ARROW---------------------------------------------------------------------------------------------

hui::EventResult Arrow::OnMouseDown(const hui::MouseDownEvent& evt) {
    start_ = evt.relPos;
    line1_->SetStart(evt.relPos);
    return hui::EventResult::HANDLED;
}

hui::EventResult Arrow::OnMouseRelease(const hui::MouseUpEvent& evt) {
    end_ = evt.relPos;
    dr4::Vec2f vec = end_ - start_;
    float len = sqrt(vec.x * vec.x + vec.y * vec.y);
    line1_->SetEnd(end_);

    line2_->SetStart(end_);
    line2_->SetEnd(end_ + dr4::Vec2f(-(vec.y), vec.x) * kArrowLen / len);

    line3_->SetStart(end_);
    line3_->SetEnd(end_ + dr4::Vec2f(vec.y, -(vec.x)) * kArrowLen / len);
    return hui::EventResult::HANDLED;
}

hui::EventResult Arrow::OnMouseMove(const hui::MouseMoveEvent& evt) {
    end_ = evt.rel;
    dr4::Vec2f vec = end_ - start_;
    dr4::Vec2f ortho(-(vec.y), vec.x);
    float len = sqrt(vec.x * vec.x + vec.y * vec.y);
    line1_->SetEnd(end_);

    line2_->SetStart(end_);
    line2_->SetEnd(end_ - (vec + ortho) * kArrowLen / len);

    line3_->SetStart(end_);
    line3_->SetEnd(end_ - (vec - ortho) * kArrowLen / len);
    return hui::EventResult::HANDLED;
}
