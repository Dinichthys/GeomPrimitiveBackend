#include "geom_prim_tools.hpp"

namespace pp {

//----------RECTANGLE-----------------------------------------------------------------------------------------

bool RectangleTool::OnMouseDown(const dr4::Event::MouseButton &evt) {
    if ((!is_drawing_ && (cvs_->GetSelectedShape() == NULL))
        || (cvs_->GetSelectedShape() != rect_)) {
        OnStart();
        return true;
    }

    is_drawing_ = true;
    rect_->SetPos(evt.pos);
    rect_->OnSelect();
    return true;
}

bool RectangleTool::OnMouseUp(const dr4::Event::MouseButton &evt) {
    if (!is_drawing_) {
        return false;
    }

    rect_->OnMouseUp(evt);
    rect_->OnDeselect();
    OnEnd();
    return true;
}

bool RectangleTool::OnMouseMove(const dr4::Event::MouseMove &evt) {
    if (!is_drawing_) {
        return false;
    }

    rect_->OnMouseMove(evt);
    return true;
}

//----------CIRCLE--------------------------------------------------------------------------------------------

bool CircleTool::OnMouseDown(const dr4::Event::MouseButton &evt) {
    if ((!is_drawing_ && (cvs_->GetSelectedShape() == NULL))
        || (cvs_->GetSelectedShape() != circle_)) {
        OnStart();
        return true;
    }

    is_drawing_ = true;
    circle_->SetPos(evt.pos);
    circle_->OnSelect();
    return true;
}

bool CircleTool::OnMouseUp(const dr4::Event::MouseButton &evt) {
    if (!is_drawing_) {
        return false;
    }

    circle_->OnMouseUp(evt);
    circle_->OnDeselect();
    OnEnd();
    return true;
}

bool CircleTool::OnMouseMove(const dr4::Event::MouseMove &evt) {
    if (!is_drawing_) {
        return false;
    }

    circle_->OnMouseMove(evt);
    return true;
}
//----------ARROW---------------------------------------------------------------------------------------------

bool ArrowTool::OnMouseDown(const dr4::Event::MouseButton &evt) {
    if ((!is_drawing_ && (cvs_->GetSelectedShape() == NULL))
        || (cvs_->GetSelectedShape() != arrow_)) {
        OnStart();
        return true;
    }

    is_drawing_ = true;
    arrow_->SetPos(evt.pos);
    arrow_->OnSelect();
    return true;
}

bool ArrowTool::OnMouseUp(const dr4::Event::MouseButton &evt) {
    if (!is_drawing_) {
        return false;
    }

    arrow_->OnMouseUp(evt);
    arrow_->OnDeselect();
    OnEnd();
    return true;
}

bool ArrowTool::OnMouseMove(const dr4::Event::MouseMove &evt) {
    if (!is_drawing_) {
        return false;
    }

    arrow_->OnMouseMove(evt);
    return true;
}

//------------------------------------------------------------------------------------------------------------

};
