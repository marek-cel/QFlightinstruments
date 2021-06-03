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

#include <example/WidgetALT.h>
#include <ui_WidgetALT.h>

////////////////////////////////////////////////////////////////////////////////

WidgetALT::WidgetALT( QWidget *parent ) :
    QWidget( parent ),
    _ui( new Ui::WidgetALT ),
    _alt ( Q_NULLPTR ),
    _layoutSq ( Q_NULLPTR )
{
    _ui->setupUi( this );

    setupUi();

    _alt = _ui->graphicsALT;
}

////////////////////////////////////////////////////////////////////////////////

WidgetALT::~WidgetALT()
{
    if ( _layoutSq ) delete _layoutSq;
    _layoutSq = Q_NULLPTR;

    if ( _ui ) delete _ui;
    _ui = Q_NULLPTR;
}

////////////////////////////////////////////////////////////////////////////////

void WidgetALT::setupUi()
{
    _layoutSq = new LayoutSquare( this );

    _layoutSq->setContentsMargins( 0, 0, 0, 0 );
    _layoutSq->addWidget( _ui->graphicsALT );

    setLayout( _layoutSq );
}
