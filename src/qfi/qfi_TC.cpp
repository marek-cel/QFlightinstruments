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

#include <qfi/qfi_TC.h>

#ifdef WIN32
#   include <float.h>
#endif

#include <cmath>

////////////////////////////////////////////////////////////////////////////////

qfi_TC::qfi_TC( QWidget *parent ) :
    QGraphicsView ( parent ),

    _scene ( Q_NULLPTR ),

    _itemBack   ( Q_NULLPTR ),
    _itemBall   ( Q_NULLPTR ),
    _itemFace_1 ( Q_NULLPTR ),
    _itemFace_2 ( Q_NULLPTR ),
    _itemMark   ( Q_NULLPTR ),
    _itemCase   ( Q_NULLPTR ),

    _turnRate ( 0.0 ),
    _slipSkid ( 0.0 ),

    _scaleX ( 1.0 ),
    _scaleY ( 1.0 ),

    _originalHeight ( 240 ),
    _originalWidth  ( 240 ),

    _originalMarkCtr ( 120.0 , 120.0 ),
    _originalBallCtr ( 120.0 , -36.0 ),

    _backZ  ( -70 ),
    _ballZ  ( -60 ),
    _face1Z ( -50 ),
    _face2Z ( -40 ),
    _markZ  ( -30 ),
    _caseZ  (  10 )
{
    reset();

    _scene = new QGraphicsScene( this );
    setScene( _scene );

    _scene->clear();

    init();
}

////////////////////////////////////////////////////////////////////////////////

qfi_TC::~qfi_TC()
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

void qfi_TC::reinit()
{
    if ( _scene )
    {
        _scene->clear();

        init();
    }
}

////////////////////////////////////////////////////////////////////////////////

void qfi_TC::redraw()
{
    if ( isVisible() )
    {
        updateView();
    }
}

////////////////////////////////////////////////////////////////////////////////

void qfi_TC::setTurnRate( double turnRate )
{
    _turnRate = turnRate;

    if ( _turnRate < -6.0 ) _turnRate = -6.0;
    if ( _turnRate >  6.0 ) _turnRate =  6.0;
}

////////////////////////////////////////////////////////////////////////////////

void qfi_TC::setSlipSkid( double slipSkid )
{
    _slipSkid = slipSkid;

    if ( _slipSkid < -15.0 ) _slipSkid = -15.0;
    if ( _slipSkid >  15.0 ) _slipSkid =  15.0;
}

////////////////////////////////////////////////////////////////////////////////

void qfi_TC::resizeEvent( QResizeEvent *event )
{
    ////////////////////////////////////
    QGraphicsView::resizeEvent( event );
    ////////////////////////////////////

    reinit();
}

////////////////////////////////////////////////////////////////////////////////

void qfi_TC::init()
{
    _scaleX = static_cast< double >( width()  ) / static_cast< double >( _originalWidth  );
    _scaleY = static_cast< double >( height() ) / static_cast< double >( _originalHeight );

    reset();

    _itemBack = new QGraphicsSvgItem( ":/qfi/images/tc/tc_back.svg" );
    _itemBack->setCacheMode( QGraphicsItem::NoCache );
    _itemBack->setZValue( _backZ );
    _itemBack->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _scene->addItem( _itemBack );

    _itemBall = new QGraphicsSvgItem( ":/qfi/images/tc/tc_ball.svg" );
    _itemBall->setCacheMode( QGraphicsItem::NoCache );
    _itemBall->setZValue( _ballZ );
    _itemBall->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _itemBall->setTransformOriginPoint( _originalBallCtr );
    _scene->addItem( _itemBall );

    _itemFace_1 = new QGraphicsSvgItem( ":/qfi/images/tc/tc_face_1.svg" );
    _itemFace_1->setCacheMode( QGraphicsItem::NoCache );
    _itemFace_1->setZValue( _face1Z );
    _itemFace_1->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _scene->addItem( _itemFace_1 );

    _itemFace_2 = new QGraphicsSvgItem( ":/qfi/images/tc/tc_face_2.svg" );
    _itemFace_2->setCacheMode( QGraphicsItem::NoCache );
    _itemFace_2->setZValue( _face2Z );
    _itemFace_2->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _scene->addItem( _itemFace_2 );

    _itemMark = new QGraphicsSvgItem( ":/qfi/images/tc/tc_mark.svg" );
    _itemMark->setCacheMode( QGraphicsItem::NoCache );
    _itemMark->setZValue( _markZ );
    _itemMark->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _itemMark->setTransformOriginPoint( _originalMarkCtr );
    _scene->addItem( _itemMark );

    _itemCase = new QGraphicsSvgItem( ":/qfi/images/tc/tc_case.svg" );
    _itemCase->setCacheMode( QGraphicsItem::NoCache );
    _itemCase->setZValue( _caseZ );
    _itemCase->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _scene->addItem( _itemCase );

    centerOn( width() / 2.0 , height() / 2.0 );

    updateView();
}

////////////////////////////////////////////////////////////////////////////////

void qfi_TC::reset()
{
    _itemBack   = Q_NULLPTR;
    _itemBall   = Q_NULLPTR;
    _itemFace_1 = Q_NULLPTR;
    _itemFace_2 = Q_NULLPTR;
    _itemMark   = Q_NULLPTR;
    _itemCase   = Q_NULLPTR;

    _turnRate = 0.0;
    _slipSkid = 0.0;
}

////////////////////////////////////////////////////////////////////////////////

void qfi_TC::updateView()
{
    _scaleX = static_cast< double >( width()  ) / static_cast< double >( _originalWidth  );
    _scaleY = static_cast< double >( height() ) / static_cast< double >( _originalHeight );

    _itemBall->setRotation( -_slipSkid );

    double angle = ( _turnRate / 3.0 ) * 20.0;

    _itemMark->setRotation( angle );

    _scene->update();
}
