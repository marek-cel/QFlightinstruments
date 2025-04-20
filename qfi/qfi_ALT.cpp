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

#include <qfi/qfi_ALT.h>

#ifdef WIN32
#   include <float.h>
#endif

#include <cmath>

////////////////////////////////////////////////////////////////////////////////

qfi_ALT::qfi_ALT( QWidget *parent ) :
    QGraphicsView ( parent ),

    _scene ( Q_NULLPTR ),

    _itemFace_1 ( Q_NULLPTR ),
    _itemFace_2 ( Q_NULLPTR ),
    _itemFace_3 ( Q_NULLPTR ),
    _itemHand_1 ( Q_NULLPTR ),
    _itemHand_2 ( Q_NULLPTR ),
    _itemCase   ( Q_NULLPTR ),

    _altitude (  0.0 ),
    _pressure ( 28.0 ),

    _scaleX ( 1.0 ),
    _scaleY ( 1.0 ),

    _originalHeight ( 240 ),
    _originalWidth  ( 240 ),

    _originalAltCtr ( 120.0 , 120.0 ),

    _face1Z ( -50 ),
    _face2Z ( -40 ),
    _face3Z ( -30 ),
    _hand1Z ( -20 ),
    _hand2Z ( -10 ),
    _caseZ  (  10 )
{
    reset();

    _scene = new QGraphicsScene( this );
    setScene( _scene );

    _scene->clear();

    init();
}

////////////////////////////////////////////////////////////////////////////////

qfi_ALT::~qfi_ALT()
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

void qfi_ALT::reinit()
{
    if ( _scene )
    {
        _scene->clear();

        init();
    }
}

////////////////////////////////////////////////////////////////////////////////

void qfi_ALT::redraw()
{
    if ( isVisible() )
    {
        updateView();
    }
}

////////////////////////////////////////////////////////////////////////////////

void qfi_ALT::setAltitude( double altitude )
{
    _altitude = altitude;
}

////////////////////////////////////////////////////////////////////////////////

void qfi_ALT::setPressure( double pressure )
{
    _pressure = pressure;

    if ( _pressure < 28.0 ) _pressure = 28.0;
    if ( _pressure > 31.5 ) _pressure = 31.5;
}

////////////////////////////////////////////////////////////////////////////////

void qfi_ALT::resizeEvent( QResizeEvent *event )
{
    ////////////////////////////////////
    QGraphicsView::resizeEvent( event );
    ////////////////////////////////////

    reinit();
}

////////////////////////////////////////////////////////////////////////////////

void qfi_ALT::init()
{
    _scaleX = static_cast< double >( width()  ) / static_cast< double >( _originalWidth  );
    _scaleY = static_cast< double >( height() ) / static_cast< double >( _originalHeight );

    reset();

    _itemFace_1 = new QGraphicsSvgItem( ":/qfi/images/alt/alt_face_1.svg" );
    _itemFace_1->setCacheMode( QGraphicsItem::NoCache );
    _itemFace_1->setZValue( _face1Z );
    _itemFace_1->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _itemFace_1->setTransformOriginPoint( _originalAltCtr );
    _scene->addItem( _itemFace_1 );

    _itemFace_2 = new QGraphicsSvgItem( ":/qfi/images/alt/alt_face_2.svg" );
    _itemFace_2->setCacheMode( QGraphicsItem::NoCache );
    _itemFace_2->setZValue( _face2Z );
    _itemFace_2->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _scene->addItem( _itemFace_2 );

    _itemFace_3 = new QGraphicsSvgItem( ":/qfi/images/alt/alt_face_3.svg" );
    _itemFace_3->setCacheMode( QGraphicsItem::NoCache );
    _itemFace_3->setZValue( _face3Z );
    _itemFace_3->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _itemFace_3->setTransformOriginPoint( _originalAltCtr );
    _scene->addItem( _itemFace_3 );

    _itemHand_1 = new QGraphicsSvgItem( ":/qfi/images/alt/alt_hand_1.svg" );
    _itemHand_1->setCacheMode( QGraphicsItem::NoCache );
    _itemHand_1->setZValue( _hand1Z );
    _itemHand_1->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _itemHand_1->setTransformOriginPoint( _originalAltCtr );
    _scene->addItem( _itemHand_1 );

    _itemHand_2 = new QGraphicsSvgItem( ":/qfi/images/alt/alt_hand_2.svg" );
    _itemHand_2->setCacheMode( QGraphicsItem::NoCache );
    _itemHand_2->setZValue( _hand2Z );
    _itemHand_2->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _itemHand_2->setTransformOriginPoint( _originalAltCtr );
    _scene->addItem( _itemHand_2 );

    _itemCase = new QGraphicsSvgItem( ":/qfi/images/alt/alt_case.svg" );
    _itemCase->setCacheMode( QGraphicsItem::NoCache );
    _itemCase->setZValue( _caseZ );
    _itemCase->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _scene->addItem( _itemCase );

    centerOn( width() / 2.0 , height() / 2.0 );

    updateView();
}

////////////////////////////////////////////////////////////////////////////////

void qfi_ALT::reset()
{
    _itemFace_1 = Q_NULLPTR;
    _itemFace_2 = Q_NULLPTR;
    _itemFace_3 = Q_NULLPTR;
    _itemHand_1 = Q_NULLPTR;
    _itemHand_2 = Q_NULLPTR;
    _itemCase   = Q_NULLPTR;

    _altitude =  0.0;
    _pressure = 28.0;
}

////////////////////////////////////////////////////////////////////////////////

void qfi_ALT::updateView()
{
    int altitude = ceil( _altitude + 0.5 );

    double angleH1 = _altitude * 0.036;
    double angleH2 = ( altitude % 1000 ) * 0.36;
    double angleF1 = ( _pressure - 28.0 ) * 100.0;
    double angleF3 = _altitude * 0.0036;

    _itemHand_1->setRotation(   angleH1 );
    _itemHand_2->setRotation(   angleH2 );
    _itemFace_1->setRotation( - angleF1 );
    _itemFace_3->setRotation(   angleF3 );

    _scene->update();
}
