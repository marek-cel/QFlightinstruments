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

#include <qfi/qfi_HI.h>

#ifdef WIN32
#   include <float.h>
#endif

#include <cmath>

////////////////////////////////////////////////////////////////////////////////

qfi_HI::qfi_HI( QWidget *parent ) :
    QGraphicsView ( parent ),

    _scene ( Q_NULLPTR ),

    _itemFace ( Q_NULLPTR ),
    _itemCase ( Q_NULLPTR ),

    _heading ( 0.0 ),

    _scaleX ( 1.0 ),
    _scaleY ( 1.0 ),

    _originalHeight ( 240 ),
    _originalWidth  ( 240 ),

    _originalHsiCtr ( 120.0 , 120.0 ),

    _faceZ ( -20 ),
    _caseZ (  10 )
{
    reset();

    _scene = new QGraphicsScene( this );
    setScene( _scene );

    _scene->clear();

    init();
}

////////////////////////////////////////////////////////////////////////////////

qfi_HI::~qfi_HI()
{
    if ( _scene != Q_NULLPTR )
    {
        _scene->clear();
        delete _scene;
        _scene = Q_NULLPTR;
    }

    reset();
}

////////////////////////////////////////////////////////////////////////////////

void qfi_HI::reinit()
{
    if ( _scene )
    {
        _scene->clear();

        init();
    }
}

////////////////////////////////////////////////////////////////////////////////

void qfi_HI::redraw()
{
    if ( isVisible() )
    {
        updateView();
    }
}

////////////////////////////////////////////////////////////////////////////////

void qfi_HI::setHeading( double heading )
{
    _heading = heading;
}

////////////////////////////////////////////////////////////////////////////////

void qfi_HI::resizeEvent( QResizeEvent *event )
{
    ////////////////////////////////////
    QGraphicsView::resizeEvent( event );
    ////////////////////////////////////

    reinit();
}

////////////////////////////////////////////////////////////////////////////////

void qfi_HI::init()
{
    _scaleX = static_cast< double >( width()  ) / static_cast< double >( _originalWidth  );
    _scaleY = static_cast< double >( height() ) / static_cast< double >( _originalHeight );

    reset();

    _itemFace = new QGraphicsSvgItem( ":/qfi/images/hi/hi_face.svg" );
    _itemFace->setCacheMode( QGraphicsItem::NoCache );
    _itemFace->setZValue( _faceZ );
    _itemFace->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _itemFace->setTransformOriginPoint( _originalHsiCtr );
    _scene->addItem( _itemFace );

    _itemCase = new QGraphicsSvgItem( ":/qfi/images/hi/hi_case.svg" );
    _itemCase->setCacheMode( QGraphicsItem::NoCache );
    _itemCase->setZValue( _caseZ );
    _itemCase->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _scene->addItem( _itemCase );

    centerOn( width() / 2.0 , height() / 2.0 );

    updateView();
}

////////////////////////////////////////////////////////////////////////////////

void qfi_HI::reset()
{
    _itemFace = Q_NULLPTR;
    _itemCase = Q_NULLPTR;

    _heading = 0.0;
}

////////////////////////////////////////////////////////////////////////////////

void qfi_HI::updateView()
{
    _itemFace->setRotation( - _heading );

    _scene->update();
}
