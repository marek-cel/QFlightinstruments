/****************************************************************************//*
 * Copyright (C) 2021 Marek M. Cel
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 ******************************************************************************/
#ifndef WIDGETSIX_H
#define WIDGETSIX_H

////////////////////////////////////////////////////////////////////////////////

#include <QWidget>

#include "WidgetAI.h"
#include "WidgetALT.h"
#include "WidgetASI.h"
#include "WidgetHI.h"
#include "WidgetTC.h"
#include "WidgetVSI.h"

////////////////////////////////////////////////////////////////////////////////

namespace Ui
{
    class WidgetSix;
}

////////////////////////////////////////////////////////////////////////////////

class WidgetSix : public QWidget
{
    Q_OBJECT

public:

    explicit WidgetSix( QWidget *parent = Q_NULLPTR );

    ~WidgetSix();

    WidgetAI  * getAI  () { return _widgetAI;  }
    WidgetALT * getALT () { return _widgetALT; }
    WidgetASI * getASI () { return _widgetASI; }
    WidgetHI  * getHI  () { return _widgetHI;  }
    WidgetTC  * getTC  () { return _widgetTC ; }
    WidgetVSI * getVSI () { return _widgetVSI; }

private:

    Ui::WidgetSix *_ui;

    WidgetAI  *_widgetAI;
    WidgetALT *_widgetALT;
    WidgetASI *_widgetASI;
    WidgetHI  *_widgetHI;
    WidgetTC  *_widgetTC;
    WidgetVSI *_widgetVSI;
};

////////////////////////////////////////////////////////////////////////////////

#endif // WIDGETSIX_H
