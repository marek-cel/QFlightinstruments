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

#include <qfi/qfi_EHSI.h>

#ifdef WIN32
#   include <float.h>
#endif

#include <cmath>
#include <cstdio>

#include <qfi/qfi_Colors.h>
#include <qfi/qfi_Fonts.h>

////////////////////////////////////////////////////////////////////////////////

qfi_EHSI::qfi_EHSI( QWidget *parent ) :
    QGraphicsView ( parent ),

    _scene ( Q_NULLPTR ),

    _itemBack ( Q_NULLPTR ),
    _itemMask ( Q_NULLPTR ),
    _itemMark ( Q_NULLPTR ),

    _itemBrgArrow ( Q_NULLPTR ),
    _itemCrsArrow ( Q_NULLPTR ),
    _itemDevBar   ( Q_NULLPTR ),
    _itemDevScale ( Q_NULLPTR ),
    _itemHdgBug   ( Q_NULLPTR ),
    _itemHdgScale ( Q_NULLPTR ),
    _itemCdiTo    ( Q_NULLPTR ),
    _itemCdiFrom  ( Q_NULLPTR ),

    _itemCrsText ( Q_NULLPTR ),
    _itemHdgText ( Q_NULLPTR ),
    _itemDmeText ( Q_NULLPTR ),

    _heading   ( 0.0 ),
    _course    ( 0.0 ),
    _bearing   ( 0.0 ),
    _deviation ( 0.0 ),
    _distance  ( 0.0 ),

    _heading_sel ( 0.0 ),

    _cdi ( CDI::Off ),

    _bearingVisible   ( true ),
    _distanceVisible  ( true ),

    _devBarDeltaX_new ( 0.0 ),
    _devBarDeltaX_old ( 0.0 ),
    _devBarDeltaY_new ( 0.0 ),
    _devBarDeltaY_old ( 0.0 ),

    _scaleX ( 1.0 ),
    _scaleY ( 1.0 ),

    _originalPixPerDev ( 52.5 ),

    _originalNavCtr ( 150.0, 150.0 ),

    _originalCrsTextCtr ( 250.0,  25.0 ),
    _originalHdgTextCtr (  50.0,  25.0 ),
    _originalDmeTextCtr ( 250.0, 275.0 ),

    _originalHeight ( 300 ),
    _originalWidth  ( 300 ),

    _backZ (   0 ),
    _maskZ ( 100 ),
    _markZ ( 200 ),

    _brgArrowZ (  60 ),
    _crsArrowZ (  70 ),
    _crsTextZ  ( 130 ),
    _devBarZ   (  50 ),
    _devScaleZ (  10 ),
    _hdgBugZ   ( 120 ),
    _hdgScaleZ ( 110 ),
    _hdgTextZ  ( 130 ),
    _dmeTextZ  ( 130 )
{
    reset();

    _scene = new QGraphicsScene( this );
    setScene( _scene );

    _scene->clear();

    init();
}

////////////////////////////////////////////////////////////////////////////////

qfi_EHSI::~qfi_EHSI()
{
    if ( _scene )
    {
        _scene->clear();
        delete _scene;
        _scene = Q_NULLPTR;
    }

    reset();
}

////////////////////////////////////////////////////////////////////////////////

void qfi_EHSI::reinit()
{
    if ( _scene )
    {
        _scene->clear();

        init();
    }
}

////////////////////////////////////////////////////////////////////////////////

void qfi_EHSI::redraw()
{
    if ( isVisible() )
    {
        updateView();

        _devBarDeltaX_old = _devBarDeltaX_new;
        _devBarDeltaY_old = _devBarDeltaY_new;
    }
}

////////////////////////////////////////////////////////////////////////////////

void qfi_EHSI::setHeading( double heading )
{
    _heading = heading;

    while ( _heading <   0.0 ) _heading += 360.0;
    while ( _heading > 360.0 ) _heading -= 360.0;
}

////////////////////////////////////////////////////////////////////////////////

void qfi_EHSI::setCourse( double course )
{
    _course = course;

    while ( _course <   0.0 ) _course += 360.0;
    while ( _course > 360.0 ) _course -= 360.0;
}

////////////////////////////////////////////////////////////////////////////////

void qfi_EHSI::setBearing( double bearing, bool visible )
{
    _bearing        = bearing;
    _bearingVisible = visible;

    while ( _bearing <   0.0 ) _bearing += 360.0;
    while ( _bearing > 360.0 ) _bearing -= 360.0;
}

////////////////////////////////////////////////////////////////////////////////

void qfi_EHSI::setDeviation( double deviation, CDI cdi )
{
    _deviation = deviation;
    _cdi = cdi;

    if ( _deviation < -1.0 ) _deviation = -1.0;
    if ( _deviation >  1.0 ) _deviation =  1.0;
}

////////////////////////////////////////////////////////////////////////////////

void qfi_EHSI::setDistance( double distance, bool visible )
{
    _distance        = fabs( distance );
    _distanceVisible = visible;
}

////////////////////////////////////////////////////////////////////////////////

void qfi_EHSI::setHeadingSel( double heading )
{
    _heading_sel = heading;

    while ( _heading_sel <   0.0 ) _heading_sel += 360.0;
    while ( _heading_sel > 360.0 ) _heading_sel -= 360.0;
}

////////////////////////////////////////////////////////////////////////////////

void qfi_EHSI::resizeEvent( QResizeEvent *event )
{
    ////////////////////////////////////
    QGraphicsView::resizeEvent( event );
    ////////////////////////////////////

    reinit();
}

////////////////////////////////////////////////////////////////////////////////

void qfi_EHSI::init()
{
    _scaleX = static_cast< double >( width()  ) / static_cast< double >( _originalWidth  );
    _scaleY = static_cast< double >( height() ) / static_cast< double >( _originalHeight );

    reset();

    _itemBack = new QGraphicsSvgItem( ":/qfi/images/ehsi/ehsi_back.svg" );
    _itemBack->setCacheMode( QGraphicsItem::NoCache );
    _itemBack->setZValue( _backZ );
    _itemBack->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _scene->addItem( _itemBack );

    _itemMask = new QGraphicsSvgItem( ":/qfi/images/ehsi/ehsi_mask.svg" );
    _itemMask->setCacheMode( QGraphicsItem::NoCache );
    _itemMask->setZValue( _maskZ );
    _itemMask->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _scene->addItem( _itemMask );

    _itemMark = new QGraphicsSvgItem( ":/qfi/images/ehsi/ehsi_mark.svg" );
    _itemMark->setCacheMode( QGraphicsItem::NoCache );
    _itemMark->setZValue( _markZ );
    _itemMark->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _scene->addItem( _itemMark );

    _itemBrgArrow = new QGraphicsSvgItem( ":/qfi/images/ehsi/ehsi_brg_arrow.svg" );
    _itemBrgArrow->setCacheMode( QGraphicsItem::NoCache );
    _itemBrgArrow->setZValue( _brgArrowZ );
    _itemBrgArrow->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _itemBrgArrow->setTransformOriginPoint( _originalNavCtr );
    _scene->addItem( _itemBrgArrow );

    _itemCrsArrow = new QGraphicsSvgItem( ":/qfi/images/ehsi/ehsi_crs_arrow.svg" );
    _itemCrsArrow->setCacheMode( QGraphicsItem::NoCache );
    _itemCrsArrow->setZValue( _crsArrowZ );
    _itemCrsArrow->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _itemCrsArrow->setTransformOriginPoint( _originalNavCtr );
    _scene->addItem( _itemCrsArrow );

    _itemDevBar = new QGraphicsSvgItem( ":/qfi/images/ehsi/ehsi_dev_bar.svg" );
    _itemDevBar->setCacheMode( QGraphicsItem::NoCache );
    _itemDevBar->setZValue( _devBarZ );
    _itemDevBar->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _itemDevBar->setTransformOriginPoint( _originalNavCtr );
    _scene->addItem( _itemDevBar );

    _itemDevScale = new QGraphicsSvgItem( ":/qfi/images/ehsi/ehsi_dev_scale.svg" );
    _itemDevScale->setCacheMode( QGraphicsItem::NoCache );
    _itemDevScale->setZValue( _devScaleZ );
    _itemDevScale->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _itemDevScale->setTransformOriginPoint( _originalNavCtr );
    _scene->addItem( _itemDevScale );

    _itemHdgBug = new QGraphicsSvgItem( ":/qfi/images/ehsi/ehsi_hdg_bug.svg" );
    _itemHdgBug->setCacheMode( QGraphicsItem::NoCache );
    _itemHdgBug->setZValue( _hdgBugZ );
    _itemHdgBug->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _itemHdgBug->setTransformOriginPoint( _originalNavCtr );
    _scene->addItem( _itemHdgBug );

    _itemHdgScale = new QGraphicsSvgItem( ":/qfi/images/ehsi/ehsi_hdg_scale.svg" );
    _itemHdgScale->setCacheMode( QGraphicsItem::NoCache );
    _itemHdgScale->setZValue( _hdgScaleZ );
    _itemHdgScale->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _itemHdgScale->setTransformOriginPoint( _originalNavCtr );
    _scene->addItem( _itemHdgScale );

    _itemCdiTo = new QGraphicsSvgItem( ":/qfi/images/ehsi/ehsi_cdi_to.svg" );
    _itemCdiTo->setCacheMode( QGraphicsItem::NoCache );
    _itemCdiTo->setZValue( _crsArrowZ );
    _itemCdiTo->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _itemCdiTo->setTransformOriginPoint( _originalNavCtr );
    _scene->addItem( _itemCdiTo );

    _itemCdiFrom = new QGraphicsSvgItem( ":/qfi/images/ehsi/ehsi_cdi_from.svg" );
    _itemCdiFrom->setCacheMode( QGraphicsItem::NoCache );
    _itemCdiFrom->setZValue( _crsArrowZ );
    _itemCdiFrom->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _itemCdiFrom->setTransformOriginPoint( _originalNavCtr );
    _scene->addItem( _itemCdiFrom );

    _itemCrsText = 0;

    _itemCrsText = new QGraphicsTextItem( QString( "CRS 999" ) );
    _itemCrsText->setCacheMode( QGraphicsItem::NoCache );
    _itemCrsText->setZValue( _crsTextZ );
    _itemCrsText->setDefaultTextColor( qfi_Colors::_lime );
    _itemCrsText->setFont( qfi_Fonts::medium() );
    _itemCrsText->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _itemCrsText->moveBy( _scaleX * ( _originalCrsTextCtr.x() - _itemCrsText->boundingRect().width()  / 2.0 ),
                          _scaleY * ( _originalCrsTextCtr.y() - _itemCrsText->boundingRect().height() / 2.0 ) );
    _scene->addItem( _itemCrsText );

    _itemHdgText = new QGraphicsTextItem( QString( "HDG 999" ) );
    _itemHdgText->setCacheMode( QGraphicsItem::NoCache );
    _itemHdgText->setZValue( _hdgTextZ );
    _itemHdgText->setDefaultTextColor( qfi_Colors::_magenta );
    _itemHdgText->setFont( qfi_Fonts::medium() );
    _itemHdgText->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _itemHdgText->moveBy( _scaleX * ( _originalHdgTextCtr.x() - _itemHdgText->boundingRect().width()  / 2.0 ),
                          _scaleY * ( _originalHdgTextCtr.y() - _itemHdgText->boundingRect().height() / 2.0 ) );
    _scene->addItem( _itemHdgText );

    _itemDmeText = new QGraphicsTextItem( QString( "99.9 NM" ) );
    _itemDmeText->setCacheMode( QGraphicsItem::NoCache );
    _itemDmeText->setZValue( _dmeTextZ );
    _itemDmeText->setDefaultTextColor( qfi_Colors::_white );
    _itemDmeText->setFont( qfi_Fonts::medium() );
    _itemDmeText->setTransform( QTransform::fromScale( _scaleX, _scaleY ), true );
    _itemDmeText->moveBy( _scaleX * ( _originalDmeTextCtr.x() - _itemDmeText->boundingRect().width()  / 2.0 ),
                          _scaleY * ( _originalDmeTextCtr.y() - _itemDmeText->boundingRect().height() / 2.0 ) );
    _scene->addItem( _itemDmeText );

    updateView();
}

////////////////////////////////////////////////////////////////////////////////

void qfi_EHSI::reset()
{
    _itemBrgArrow = Q_NULLPTR;
    _itemCrsArrow = Q_NULLPTR;
    _itemDevBar   = Q_NULLPTR;
    _itemDevScale = Q_NULLPTR;
    _itemHdgBug   = Q_NULLPTR;
    _itemHdgScale = Q_NULLPTR;
    _itemCdiTo    = Q_NULLPTR;
    _itemCdiFrom  = Q_NULLPTR;

    _itemCrsText = 0;
    _itemHdgText = 0;
    _itemDmeText = 0;

    _heading   = 0.0;
    _course    = 0.0;
    _bearing   = 0.0;
    _deviation = 0.0;
    _distance  = 0.0;

    _heading_sel = 0.0;

    _cdi = CDI::Off;

    _bearingVisible  = true;
    _distanceVisible = true;

    _devBarDeltaX_new = 0.0;
    _devBarDeltaX_old = 0.0;
    _devBarDeltaY_new = 0.0;
    _devBarDeltaY_old = 0.0;
}

////////////////////////////////////////////////////////////////////////////////

void qfi_EHSI::updateView()
{
    _scaleX = static_cast< double >( width()  ) / static_cast< double >( _originalWidth  );
    _scaleY = static_cast< double >( height() ) / static_cast< double >( _originalHeight );

    _itemCrsArrow->setRotation( -_heading + _course );
    _itemHdgBug->setRotation( -_heading + _heading_sel );
    _itemHdgScale->setRotation( -_heading );

    if ( _bearingVisible )
    {
        _itemBrgArrow->setVisible( true );
        _itemBrgArrow->setRotation( -_heading + _bearing );
    }
    else
    {
        _itemBrgArrow->setVisible( false );
    }

    if ( _cdi != CDI::Off )
    {
        _itemDevBar->setVisible( true );
        _itemDevScale->setVisible( true );

        double angle_deg = -_heading + _course;
#       ifndef M_PI
        double angle_rad = 3.14159265358979323846 * angle_deg / 180.0;
#       else
        double angle_rad = M_PI * angle_deg / 180.0;
#       endif


        double sinAngle = sin( angle_rad );
        double cosAngle = cos( angle_rad );

        _itemDevBar   ->setRotation( angle_deg );
        _itemDevScale ->setRotation( angle_deg );
        _itemCdiTo    ->setRotation( angle_deg );
        _itemCdiFrom  ->setRotation( angle_deg );

        if ( _cdi == CDI::TO )
        {
            _itemCdiTo   ->setVisible( true  );
            _itemCdiFrom ->setVisible( false );
        }
        else if ( _cdi == CDI::FROM )
        {
            _itemCdiTo   ->setVisible( false );
            _itemCdiFrom ->setVisible( true  );
        }
        else
        {
            _itemCdiTo   ->setVisible( false );
            _itemCdiFrom ->setVisible( false );
        }

        double delta  = _originalPixPerDev * _deviation;

        _devBarDeltaX_new = _scaleX * delta * cosAngle;
        _devBarDeltaY_new = _scaleY * delta * sinAngle;

        double x = _devBarDeltaX_new - _devBarDeltaX_old;
        double y = _devBarDeltaY_new - _devBarDeltaY_old;

        _itemDevBar  ->moveBy( x, y );
        _itemCdiTo   ->moveBy( x, y );
        _itemCdiFrom ->moveBy( x, y );
    }
    else
    {
        _itemDevBar   ->setVisible( false );
        _itemDevScale ->setVisible( false );
        _itemCdiTo    ->setVisible( false );
        _itemCdiFrom  ->setVisible( false );

        _devBarDeltaX_new = _devBarDeltaX_old;
        _devBarDeltaY_new = _devBarDeltaY_old;
    }

    _itemCrsText->setPlainText( QString("CRS %1").arg( _course      , 3, 'f', 0, QChar('0') ) );
    _itemHdgText->setPlainText( QString("HDG %1").arg( _heading_sel , 3, 'f', 0, QChar('0') ) );

    if ( _distanceVisible )
    {
        _itemDmeText->setVisible( true );
        _itemDmeText->setPlainText( QString("%1 NM").arg( _distance, 5, 'f', 1, QChar(' ') ) );
    }
    else
    {
        _itemDmeText->setVisible( false );
    }

    _scene->update();

    centerOn( width() / 2.0 , height() / 2.0 );
}
