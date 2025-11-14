#include "geom_prim.hpp"

#include <math.h>

hui::EventResult Rectangle::OnMouseDown(const hui::MouseDownEvent& evt) {
    rect_info_.pos = evt.relPos;
    rect_->SetPos(rect_info_.pos);
    return hui::EventResult::HANDLED;
}

hui::EventResult Rectangle::OnMouseRelease(const hui::MouseUpEvent& evt) {
    rect_info_.size = evt.relPos - rect_info_.pos;
    rect_info_.size = {abs(rect_info_.size.x), abs(rect_info_.size.y)};
    rect_->SetSize(rect_info_.size);
    return hui::EventResult::HANDLED;
}

hui::EventResult Rectangle::OnMouseMove(const hui::MouseMoveEvent& evt) {
    rect_info_.size = evt.rel - rect_info_.pos;
    rect_info_.size = {abs(rect_info_.size.x), abs(rect_info_.size.y)};
    rect_->SetSize(rect_info_.size);
    return hui::EventResult::HANDLED;
}

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
