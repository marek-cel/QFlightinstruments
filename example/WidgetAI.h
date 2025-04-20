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
#ifndef WIDGETAI_H
#define WIDGETAI_H

////////////////////////////////////////////////////////////////////////////////

#include <QWidget>

#include <qfi/qfi_AI.h>

#include "LayoutSquare.h"

////////////////////////////////////////////////////////////////////////////////

namespace Ui
{
    class WidgetAI;
}

////////////////////////////////////////////////////////////////////////////////

class WidgetAI : public QWidget
{
    Q_OBJECT
    
public:

    explicit WidgetAI( QWidget *parent = Q_NULLPTR );

    ~WidgetAI();

    inline void redraw() { _ai->redraw(); }

    inline void setRoll( double roll )
    {
        _ai->setRoll( roll );
    }

    inline void setPitch( double pitch )
    {
        _ai->setPitch( pitch );
    }
    
private:

    Ui::WidgetAI  *_ui;
    qfi_AI        *_ai;
    LayoutSquare  *_layoutSq;

    void setupUi();
};

////////////////////////////////////////////////////////////////////////////////

#endif // WIDGETAI_H
