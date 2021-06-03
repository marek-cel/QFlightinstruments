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

#include <qfi/qfi_ASI.h>

#ifdef WIN32
#   include <float.h>
#endif

#include <cmath>

////////////////////////////////////////////////////////////////////////////////

qfi_ASI::qfi_ASI( QWidget *parent ) :
    QGraphicsView ( parent ),

    _scene ( Q_NULLPTR ),

    _itemFace ( Q_NULLPTR ),
    _itemHand ( Q_NULLPTR ),
    _itemCase ( Q_NULLPTR ),

    _airspeed ( 0.0 ),

    _scaleX ( 1.0 ),
    _scaleY ( 1.0 ),

    _originalHeight ( 240 ),
    _originalWidth  ( 240 ),

    _originalAsiCtr ( 120.0 , 120.0 ),

    _faceZ ( -20 ),
    _handZ ( -10 ),
    _caseZ (  10 )
{
    reset();

    _scene = new QGraphicsScene( this );
    setScene( _scene );

    _scene->clear();

    init();
}

////////////////////////////////////////////////////////////////////////////////

qfi_ASI::~qfi_ASI()
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

void qfi_ASI::reinit()
{
    if ( _scene )
    {
        _scene->clear();

        init();
    }
}

////////////////////////////////////////////////////////////////////////////////

void qfi_ASI::redraw()
{
    if ( isVisible() )
    {
        updateView();
    }
}

////////////////////////////////////////////////////////////////////////////////

void qfi_ASI::setAirspeed( double airspeed )
{
    _airspeed = airspeed;

    if ( _airspeed <   0.0 ) _airspeed =   0.0;
    if ( _airspeed > 235.0 ) _airspeed = 235.0;
}

////////////////////////////////////////////////////////////////////////////////

void qfi_ASI::resizeEvent( QResizeEvent *event )
{
    ////////////////////////////////////
    QGraphicsView::resizeEvent( event );
    ////////////////////////////////////

    reinit();
}

////////////////////////////////////////////////////////////////////////////////

void qfi_ASI::init()
{
    _scaleX = static_cast< double >( width()  ) / static_cast< double >( _originalWidth  );
    _scaleY = static_cast< double >( height() ) / static_cast< double >( _originalHeight );

    reset();

    _itemFace = new QGraphicsSvgItem( ":/qfi/images/asi/asi_face.svg" );
    _itemFace->setCacheMode( QGraphicsItem::NoCache );
    _itemFace->setZValue( _faceZ );
    _itemFace->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _scene->addItem( _itemFace );

    _itemHand = new QGraphicsSvgItem( ":/qfi/images/asi/asi_hand.svg" );
    _itemHand->setCacheMode( QGraphicsItem::NoCache );
    _itemHand->setZValue( _handZ );
    _itemHand->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _itemHand->setTransformOriginPoint( _originalAsiCtr );
    _scene->addItem( _itemHand );

    _itemCase = new QGraphicsSvgItem( ":/qfi/images/asi/asi_case.svg" );
    _itemCase->setCacheMode( QGraphicsItem::NoCache );
    _itemCase->setZValue( _caseZ );
    _itemCase->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _scene->addItem( _itemCase );

    centerOn( width() / 2.0 , height() / 2.0 );

    updateView();
}

////////////////////////////////////////////////////////////////////////////////

void qfi_ASI::reset()
{
    _itemFace = Q_NULLPTR;
    _itemHand = Q_NULLPTR;
    _itemCase = Q_NULLPTR;

    _airspeed = 0.0;
}

////////////////////////////////////////////////////////////////////////////////

void qfi_ASI::updateView()
{
    double angle = 0.0;

    if ( _airspeed < 40.0 )
    {
        angle = 0.9 * _airspeed;
    }
    else if ( _airspeed < 70.0 )
    {
        angle = 36.0 + 1.8 * ( _airspeed - 40.0 );
    }
    else if ( _airspeed < 130.0 )
    {
        angle = 90.0 + 2.0 * ( _airspeed - 70.0 );
    }
    else if ( _airspeed < 160.0 )
    {
        angle = 210.0 + 1.8 * ( _airspeed - 130.0 );
    }
    else
    {
        angle = 264.0 + 1.2 * ( _airspeed - 160.0 );
    }

    _itemHand->setRotation( angle );

    _scene->update();
}
