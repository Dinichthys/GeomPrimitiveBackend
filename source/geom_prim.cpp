#include "geom_prim.hpp"

#include <math.h>

//----------RECTANGLE-----------------------------------------------------------------------------------------

bool Rectangle::OnMouseDown(const dr4::Event& evt) {
    rect_info_.pos = evt.mouseButton.pos;
    rect_->SetPos(rect_info_.pos);
    return true;
}

bool Rectangle::OnMouseRelease(const dr4::Event& evt) {
    rect_info_.size = evt.mouseButton.pos - rect_info_.pos;
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
    return true;
}

bool Rectangle::OnMouseMove(const dr4::Event& evt) {
    rect_info_.size = evt.mouseMove.pos - rect_info_.pos;
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
    return true;
}

//----------CIRCLE--------------------------------------------------------------------------------------------

bool Circle::OnMouseDown(const dr4::Event& evt) {
    center_ = evt.mouseButton.pos;
    circle_->SetCenter(evt.mouseButton.pos);
    return true;
}

bool Circle::OnMouseRelease(const dr4::Event& evt) {
    dr4::Vec2f vec = evt.mouseButton.pos - center_;
    float radius = sqrt(vec.x * vec.x + vec.y * vec.y);
    circle_->SetRadius(radius);
    return true;
}

bool Circle::OnMouseMove(const dr4::Event& evt) {
    dr4::Vec2f vec = evt.mouseMove.pos - center_;
    float radius = sqrt(vec.x * vec.x + vec.y * vec.y);
    circle_->SetRadius(radius);
    return true;
}

//----------ARROW---------------------------------------------------------------------------------------------

bool Arrow::OnMouseDown(const dr4::Event& evt) {
    start_ = evt.mouseButton.pos;
    line1_->SetStart(evt.mouseButton.pos);
    return true;
}

bool Arrow::OnMouseRelease(const dr4::Event& evt) {
    end_ = evt.mouseButton.pos;
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

bool Arrow::OnMouseMove(const dr4::Event& evt) {
    end_ = evt.mouseMove.pos;
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
