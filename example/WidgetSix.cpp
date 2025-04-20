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

#include <example/WidgetSix.h>
#include <ui_WidgetSix.h>

////////////////////////////////////////////////////////////////////////////////

WidgetSix::WidgetSix( QWidget *parent ) :
    QWidget ( parent ),
    _ui ( new Ui::WidgetSix ),

    _widgetAI  ( Q_NULLPTR ),
    _widgetALT ( Q_NULLPTR ),
    _widgetASI ( Q_NULLPTR ),
    _widgetHI  ( Q_NULLPTR ),
    _widgetTC  ( Q_NULLPTR ),
    _widgetVSI ( Q_NULLPTR )
{
    _ui->setupUi( this );

    _widgetAI  = _ui->widgetAI;
    _widgetALT = _ui->widgetALT;
    _widgetASI = _ui->widgetASI;
    _widgetHI  = _ui->widgetHI;
    _widgetTC  = _ui->widgetTC;
    _widgetVSI = _ui->widgetVSI;
}

////////////////////////////////////////////////////////////////////////////////

WidgetSix::~WidgetSix()
{
    if ( _ui ) delete _ui;
    _ui = Q_NULLPTR;
}
