#include "geom_prim_tools.hpp"

//----------RECTANGLE-----------------------------------------------------------------------------------------

bool RectangleTool::OnMouseDown(const dr4::Event::MouseButton &evt) {
    if ((!is_drawing_ && (cvs_->GetState()->selectedShape == NULL))
        || (cvs_->GetState()->selectedShape != rect_)) {
        OnStart();
        return true;
    }

    is_drawing_ = true;
    rect_->SetPos(evt.pos);
    return true;
}

bool RectangleTool::OnMouseUp(const dr4::Event::MouseButton &evt) {
    rect_->OnMouseUp(evt);
    OnEnd();
    return true;
}

bool RectangleTool::OnMouseMove(const dr4::Event::MouseMove &evt) {
    rect_->OnMouseMove(evt);
    return true;
}

//----------CIRCLE--------------------------------------------------------------------------------------------

bool CircleTool::OnMouseDown(const dr4::Event::MouseButton &evt) {
    if ((!is_drawing_ && (cvs_->GetState()->selectedShape == NULL))
        || (cvs_->GetState()->selectedShape != circle_)) {
        OnStart();
        return true;
    }

    is_drawing_ = true;
    circle_->SetPos(evt.pos);
    return true;
}

bool CircleTool::OnMouseUp(const dr4::Event::MouseButton &evt) {
    circle_->OnMouseUp(evt);
    OnEnd();
    return true;
}

bool CircleTool::OnMouseMove(const dr4::Event::MouseMove &evt) {
    circle_->OnMouseMove(evt);
    return true;
}
//----------ARROW---------------------------------------------------------------------------------------------

bool ArrowTool::OnMouseDown(const dr4::Event::MouseButton &evt) {
    if ((!is_drawing_ && (cvs_->GetState()->selectedShape == NULL))
        || (cvs_->GetState()->selectedShape != arrow_)) {
        OnStart();
        return true;
    }

    is_drawing_ = true;
    arrow_->SetPos(evt.pos);
    return true;
}

bool ArrowTool::OnMouseUp(const dr4::Event::MouseButton &evt) {
    arrow_->OnMouseUp(evt);
    OnEnd();
    return true;
}

bool ArrowTool::OnMouseMove(const dr4::Event::MouseMove &evt) {
    arrow_->OnMouseMove(evt);
    return true;
}

//------------------------------------------------------------------------------------------------------------
