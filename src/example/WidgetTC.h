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
#ifndef WIDGETTC_H
#define WIDGETTC_H

////////////////////////////////////////////////////////////////////////////////

#include <QWidget>

#include <qfi/qfi_TC.h>

#include "LayoutSquare.h"

////////////////////////////////////////////////////////////////////////////////

namespace Ui
{
    class WidgetTC;
}

////////////////////////////////////////////////////////////////////////////////

class WidgetTC : public QWidget
{
    Q_OBJECT

public:

    explicit WidgetTC( QWidget *parent = Q_NULLPTR );

    ~WidgetTC();

    inline void redraw() { _tc->redraw(); }

    inline void setTurnRate( double turnRate )
    {
        _tc->setTurnRate( turnRate );
    }

    inline void setSlipSkid( double slipSkid )
    {
        _tc->setSlipSkid( slipSkid );
    }

private:

    Ui::WidgetTC *_ui;
    qfi_TC       *_tc;
    LayoutSquare *_layoutSq;

    void setupUi();
};

////////////////////////////////////////////////////////////////////////////////

#endif // WIDGETTC_H
