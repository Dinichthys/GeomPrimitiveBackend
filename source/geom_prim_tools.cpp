#include "geom_prim_tools.hpp"

namespace pp {

//----------RECTANGLE-----------------------------------------------------------------------------------------

bool RectangleTool::OnMouseDown(const dr4::Event::MouseButton &evt) {
    if ((!is_drawing_ && (cvs_->GetSelectedShape() == NULL))
        || (cvs_->GetSelectedShape() != rect_)) {
        OnStart();
        rect_->SetPos(evt.pos);
        rect_->OnSelect();
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
        circle_->SetPos(evt.pos);
        circle_->OnSelect();
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
        arrow_->SetPos(evt.pos);
        arrow_->OnSelect();
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

//----------PENIS---------------------------------------------------------------------------------------------

bool PenisTool::OnMouseDown(const dr4::Event::MouseButton &evt) {
    if ((!is_drawing_ && (cvs_->GetSelectedShape() == NULL))
        || (cvs_->GetSelectedShape() != penis_)) {
        OnStart();
        penis_->SetPos(evt.pos);
        penis_->OnSelect();
        return true;
    }

    is_drawing_ = true;
    penis_->SetPos(evt.pos);
    penis_->OnSelect();
    return true;
}

bool PenisTool::OnMouseUp(const dr4::Event::MouseButton &evt) {
    if (!is_drawing_) {
        return false;
    }

    penis_->OnMouseUp(evt);
    penis_->OnDeselect();
    OnEnd();
    return true;
}

bool PenisTool::OnMouseMove(const dr4::Event::MouseMove &evt) {
    if (!is_drawing_) {
        return false;
    }

    penis_->OnMouseMove(evt);
    return true;
}

//----------TEXT----------------------------------------------------------------------------------------------

bool TextTool::OnMouseDown(const dr4::Event::MouseButton &evt) {
    if ((!is_drawing_ && (cvs_->GetSelectedShape() == NULL))
        || (cvs_->GetSelectedShape() != text_)) {
        OnStart();
        text_->SetPos(evt.pos);
        text_->OnSelect();
        return true;
    }

    is_drawing_ = true;
    text_->SetPos(evt.pos);
    text_->OnSelect();
    return true;
}

bool TextTool::OnMouseUp(const dr4::Event::MouseButton &evt) {
    if (!is_drawing_) {
        return false;
    }

    text_->OnMouseUp(evt);
    is_drawing_ = false;
    is_printing_ = true;
    cvs_->GetWindow()->StartTextInput();
    return true;
}

bool TextTool::OnMouseMove(const dr4::Event::MouseMove &evt) {
    if (!is_drawing_) {
        return false;
    }

    text_->OnMouseMove(evt);
    return true;
}

bool TextTool::OnKeyDown(const dr4::Event::KeyEvent &evt) {
    if (!is_printing_) {
        return false;
    }

    text_->OnKeyDown(evt);

    if (evt.sym == dr4::KeyCode::KEYCODE_ENTER) {
        text_->OnDeselect();
        OnEnd();
        cvs_->GetWindow()->StopTextInput();
        is_printing_ = false;
        return true;
    }

    return text_->OnKeyDown(evt);
}

bool TextTool::OnText(const dr4::Event::TextEvent &evt) {
    if (!is_printing_) {
        return false;
    }

    text_->OnText(evt);
    return true;
}

bool TextTool::OnIdle(const IdleEvent &evt) {
    if (!is_printing_) {
        return false;
    }

    text_->OnIdle(evt);
    return true;
}

//------------------------------------------------------------------------------------------------------------

};
