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

#include <qfi/qfi_AI.h>

#ifdef WIN32
#   include <float.h>
#endif

#include <cmath>

////////////////////////////////////////////////////////////////////////////////

qfi_AI::qfi_AI( QWidget *parent ) :
    QGraphicsView ( parent ),

    _scene ( Q_NULLPTR ),

    _itemBack ( Q_NULLPTR ),
    _itemFace ( Q_NULLPTR ),
    _itemRing ( Q_NULLPTR ),
    _itemCase ( Q_NULLPTR ),

    _roll  ( 0.0 ),
    _pitch ( 0.0 ),

    _faceDeltaX_new ( 0.0 ),
    _faceDeltaX_old ( 0.0 ),
    _faceDeltaY_new ( 0.0 ),
    _faceDeltaY_old ( 0.0 ),

    _scaleX ( 1.0 ),
    _scaleY ( 1.0 ),

    _originalHeight ( 240 ),
    _originalWidth  ( 240 ),

    _originalPixPerDeg ( 1.7 ),

    _originalAdiCtr ( 120.0 , 120.0 ),

    _backZ ( -30 ),
    _faceZ ( -20 ),
    _ringZ ( -10 ),
    _caseZ (  10 )
{
    reset();

    _scene = new QGraphicsScene( this );
    setScene( _scene );

    _scene->clear();

    init();
}

////////////////////////////////////////////////////////////////////////////////

qfi_AI::~qfi_AI()
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

void qfi_AI::reinit()
{
    if ( _scene )
    {
        _scene->clear();

        init();
    }
}

////////////////////////////////////////////////////////////////////////////////

void qfi_AI::redraw()
{
    if ( isVisible() )
    {
        updateView();

        _faceDeltaX_old  = _faceDeltaX_new;
        _faceDeltaY_old  = _faceDeltaY_new;
    }
}

////////////////////////////////////////////////////////////////////////////////

void qfi_AI::setRoll( double roll )
{
    _roll = roll;

    if ( _roll < -180.0 ) _roll = -180.0;
    if ( _roll >  180.0 ) _roll =  180.0;
}

////////////////////////////////////////////////////////////////////////////////

void qfi_AI::setPitch( double pitch )
{
    _pitch = pitch;

    if ( _pitch < -25.0 ) _pitch = -25.0;
    if ( _pitch >  25.0 ) _pitch =  25.0;
}

////////////////////////////////////////////////////////////////////////////////

void qfi_AI::resizeEvent( QResizeEvent *event )
{
    ////////////////////////////////////
    QGraphicsView::resizeEvent( event );
    ////////////////////////////////////

    reinit();
}

////////////////////////////////////////////////////////////////////////////////

void qfi_AI::init()
{
    _scaleX = static_cast< double >( width()  ) / static_cast< double >( _originalWidth  );
    _scaleY = static_cast< double >( height() ) / static_cast< double >( _originalHeight );

    reset();

    _itemBack = new QGraphicsSvgItem( ":/qfi/images/ai/ai_back.svg" );
    _itemBack->setCacheMode( QGraphicsItem::NoCache );
    _itemBack->setZValue( _backZ );
    _itemBack->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _itemBack->setTransformOriginPoint( _originalAdiCtr );
    _scene->addItem( _itemBack );

    _itemFace = new QGraphicsSvgItem( ":/qfi/images/ai/ai_face.svg" );
    _itemFace->setCacheMode( QGraphicsItem::NoCache );
    _itemFace->setZValue( _faceZ );
    _itemFace->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _itemFace->setTransformOriginPoint( _originalAdiCtr );
    _scene->addItem( _itemFace );

    _itemRing = new QGraphicsSvgItem( ":/qfi/images/ai/ai_ring.svg" );
    _itemRing->setCacheMode( QGraphicsItem::NoCache );
    _itemRing->setZValue( _ringZ );
    _itemRing->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _itemRing->setTransformOriginPoint( _originalAdiCtr );
    _scene->addItem( _itemRing );

    _itemCase = new QGraphicsSvgItem( ":/qfi/images/ai/ai_case.svg" );
    _itemCase->setCacheMode( QGraphicsItem::NoCache );
    _itemCase->setZValue( _caseZ );
    _itemCase->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _scene->addItem( _itemCase );

    centerOn( width() / 2.0 , height() / 2.0 );

    updateView();
}

////////////////////////////////////////////////////////////////////////////////

void qfi_AI::reset()
{
    _itemBack = Q_NULLPTR;
    _itemFace = Q_NULLPTR;
    _itemRing = Q_NULLPTR;
    _itemCase = Q_NULLPTR;

    _roll  = 0.0;
    _pitch = 0.0;

    _faceDeltaX_new = 0.0;
    _faceDeltaX_old = 0.0;
    _faceDeltaY_new = 0.0;
    _faceDeltaY_old = 0.0;
}

////////////////////////////////////////////////////////////////////////////////

void qfi_AI::updateView()
{
    _scaleX = static_cast< double >( width()  ) / static_cast< double >( _originalWidth  );
    _scaleY = static_cast< double >( height() ) / static_cast< double >( _originalHeight );

    _itemBack->setRotation( - _roll );
    _itemFace->setRotation( - _roll );
    _itemRing->setRotation( - _roll );

    double roll_rad = M_PI * _roll / 180.0;

    double delta  = _originalPixPerDeg * _pitch;

    _faceDeltaX_new = _scaleX * delta * sin( roll_rad );
    _faceDeltaY_new = _scaleY * delta * cos( roll_rad );

    _itemFace->moveBy( _faceDeltaX_new - _faceDeltaX_old, _faceDeltaY_new - _faceDeltaY_old );

    _scene->update();
}
