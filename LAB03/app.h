//
// Created by grzegorz on 19.03.19.
//

#pragma once

#include <wx-3.0/wx/wx.h>

#include "frame.h"

class App : public wxApp {
public:
    bool OnInit() override {
        _frame = new Frame();
        _frame->Show(true);
        return true;
    }

private:
    Frame* _frame;
};


//LAB03_APP_H
