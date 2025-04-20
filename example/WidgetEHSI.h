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
#ifndef WIDGETEHSI_H
#define WIDGETEHSI_H

////////////////////////////////////////////////////////////////////////////////

#include <QWidget>

#include <qfi/qfi_EHSI.h>

#include "LayoutSquare.h"

////////////////////////////////////////////////////////////////////////////////

namespace Ui
{
    class WidgetEHSI;
}

////////////////////////////////////////////////////////////////////////////////

class WidgetEHSI : public QWidget
{
    Q_OBJECT

public:

    explicit WidgetEHSI( QWidget *parent = Q_NULLPTR );

    virtual ~WidgetEHSI();

    inline void redraw() { _ehsi->redraw(); }

    inline void setHeading( double heading )
    {
        _ehsi->setHeading( heading );
    }

    inline void setCourse( double course )
    {
        _ehsi->setCourse( course );
    }

    inline void setBearing( double bearing, bool visible = false )
    {
        _ehsi->setBearing( bearing, visible );
    }

    inline void setDeviation( double deviation, qfi_EHSI::CDI cdi )
    {
        _ehsi->setDeviation( deviation, cdi );
    }

    inline void setDistance( double distance, bool visible = false )
    {
        _ehsi->setDistance( distance, visible );
    }

    inline void setHeadingSel( double headingBug )
    {
        _ehsi->setHeadingSel( headingBug );
    }

private:

    Ui::WidgetEHSI *_ui;
    qfi_EHSI       *_ehsi;
    LayoutSquare   *_layoutSq;

    void setupUi();
};

////////////////////////////////////////////////////////////////////////////////

#endif // WIDGETEHSI_H
