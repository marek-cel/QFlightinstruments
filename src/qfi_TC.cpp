/***************************************************************************//**
 * @file qfi_TC.cpp
 * @author  Marek M. Cel <marekcel@marekcel.pl>
 *
 * @section LICENSE
 *
 * Copyright (C) 2013 Marek M. Cel
 *
 * This file is part of QFlightInstruments. You can redistribute and modify it
 * under the terms of GNU General Public License as published by the Free
 * Software Foundation; either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.
 * 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * Further information about the GNU General Public License can also be found
 * on the world wide web at http://www.gnu.org.
 *
 * ---
 *
 * Copyright (C) 2013 Marek M. Cel
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
#ifndef QFI_TC_CPP
#define QFI_TC_CPP
#endif

////////////////////////////////////////////////////////////////////////////////

#ifdef WIN32
#   include <float.h>
#endif

#include <math.h>

#include "qfi_TC.h"

////////////////////////////////////////////////////////////////////////////////

qfi_TC::qfi_TC( QWidget *parent ) :
    QGraphicsView ( parent ),

    m_scene ( nullptr ),

    m_itemBack   ( nullptr ),
    m_itemBall   ( nullptr ),
    m_itemFace_1 ( nullptr ),
    m_itemFace_2 ( nullptr ),
    m_itemMark   ( nullptr ),
    m_itemCase   ( nullptr ),

    m_turnRate ( 0.0f ),
    m_slipSkid ( 0.0f ),

    m_scaleX ( 1.0f ),
    m_scaleY ( 1.0f ),

    m_originalHeight ( 240 ),
    m_originalWidth  ( 240 ),

    m_originalMarkCtr ( 120.0f , 120.0f ),
    m_originalBallCtr ( 120.0f , -36.0f ),

    m_backZ  ( -70 ),
    m_ballZ  ( -60 ),
    m_face1Z ( -50 ),
    m_face2Z ( -40 ),
    m_markZ  ( -30 ),
    m_caseZ  (  10 )
{
    reset();

    m_scene = new QGraphicsScene( this );
    setScene( m_scene );

    m_scene->clear();

    init();
}

////////////////////////////////////////////////////////////////////////////////

qfi_TC::~qfi_TC()
{
    if ( m_scene != nullptr )
    {
        m_scene->clear();
        delete m_scene;
        m_scene = nullptr;
    }

    reset();
}

////////////////////////////////////////////////////////////////////////////////

void qfi_TC::reinit()
{
    if ( m_scene )
    {
        m_scene->clear();

        init();
    }
}

////////////////////////////////////////////////////////////////////////////////

void qfi_TC::update()
{
    updateView();
}

////////////////////////////////////////////////////////////////////////////////

void qfi_TC::setTurnRate( float turnRate )
{
    m_turnRate = turnRate;

    if ( m_turnRate < -6.0f ) m_turnRate = -6.0f;
    if ( m_turnRate >  6.0f ) m_turnRate =  6.0f;
}

////////////////////////////////////////////////////////////////////////////////

void qfi_TC::setSlipSkid( float slipSkid )
{
    m_slipSkid = slipSkid;

    if ( m_slipSkid < -15.0f ) m_slipSkid = -15.0f;
    if ( m_slipSkid >  15.0f ) m_slipSkid =  15.0f;
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
    m_scaleX = (float)width()  / (float)m_originalWidth;
    m_scaleY = (float)height() / (float)m_originalHeight;

    reset();

    m_itemBack = new QGraphicsSvgItem( ":/qfi/images/tc/tc_back.svg" );
    m_itemBack->setCacheMode( QGraphicsItem::NoCache );
    m_itemBack->setZValue( m_backZ );
    m_itemBack->setTransform( QTransform::fromScale( m_scaleX, m_scaleY ), true );
    m_scene->addItem( m_itemBack );

    m_itemBall = new QGraphicsSvgItem( ":/qfi/images/tc/tc_ball.svg" );
    m_itemBall->setCacheMode( QGraphicsItem::NoCache );
    m_itemBall->setZValue( m_ballZ );
    m_itemBall->setTransform( QTransform::fromScale( m_scaleX, m_scaleY ), true );
    m_itemBall->setTransformOriginPoint( m_originalBallCtr );
    m_scene->addItem( m_itemBall );

    m_itemFace_1 = new QGraphicsSvgItem( ":/qfi/images/tc/tc_face_1.svg" );
    m_itemFace_1->setCacheMode( QGraphicsItem::NoCache );
    m_itemFace_1->setZValue( m_face1Z );
    m_itemFace_1->setTransform( QTransform::fromScale( m_scaleX, m_scaleY ), true );
    m_scene->addItem( m_itemFace_1 );

    m_itemFace_2 = new QGraphicsSvgItem( ":/qfi/images/tc/tc_face_2.svg" );
    m_itemFace_2->setCacheMode( QGraphicsItem::NoCache );
    m_itemFace_2->setZValue( m_face2Z );
    m_itemFace_2->setTransform( QTransform::fromScale( m_scaleX, m_scaleY ), true );
    m_scene->addItem( m_itemFace_2 );

    m_itemMark = new QGraphicsSvgItem( ":/qfi/images/tc/tc_mark.svg" );
    m_itemMark->setCacheMode( QGraphicsItem::NoCache );
    m_itemMark->setZValue( m_markZ );
    m_itemMark->setTransform( QTransform::fromScale( m_scaleX, m_scaleY ), true );
    m_itemMark->setTransformOriginPoint( m_originalMarkCtr );
    m_scene->addItem( m_itemMark );

    m_itemCase = new QGraphicsSvgItem( ":/qfi/images/tc/tc_case.svg" );
    m_itemCase->setCacheMode( QGraphicsItem::NoCache );
    m_itemCase->setZValue( m_caseZ );
    m_itemCase->setTransform( QTransform::fromScale( m_scaleX, m_scaleY ), true );
    m_scene->addItem( m_itemCase );

    centerOn( width() / 2.0f , height() / 2.0f );

    updateView();
}

////////////////////////////////////////////////////////////////////////////////

void qfi_TC::reset()
{
    m_itemCase = nullptr;

    m_turnRate = 0.0f;
    m_slipSkid = 0.0f;
}

////////////////////////////////////////////////////////////////////////////////

void qfi_TC::updateView()
{
    m_scaleX = (float)width()  / (float)m_originalWidth;
    m_scaleY = (float)height() / (float)m_originalHeight;

    m_itemBall->setRotation( -m_slipSkid );

    float angle = ( m_turnRate / 3.0f ) * 20.0f;

    m_itemMark->setRotation( angle );

    m_scene->update();
}
