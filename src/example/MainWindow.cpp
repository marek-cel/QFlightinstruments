/***************************************************************************//**
 * @file example/MainWindow.cpp
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
#ifndef MAINWINDOW_CPP
#define MAINWINDOW_CPP
#endif

////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <math.h>

#include "MainWindow.h"
#include "ui_MainWindow.h"

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow( parent ),
    m_ui( new Ui::MainWindow ),

    m_timerId ( 0 ),
    m_steps   ( 0 ),

    m_realTime ( 0.0 )
{
    m_ui->setupUi( this );

    m_timerId  = startTimer( 0 );

    m_time.start();
}

////////////////////////////////////////////////////////////////////////////////

MainWindow::~MainWindow()
{
    cout << "Average time step: " << ( (double)m_realTime ) / ( (double)m_steps ) << " s" << endl;

    if ( m_timerId ) killTimer( m_timerId );

    if ( m_ui ) delete m_ui; m_ui = 0;
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::timerEvent( QTimerEvent *event )
{
    /////////////////////////////////
    QMainWindow::timerEvent( event );
    /////////////////////////////////

    float timeStep = m_time.restart();

    m_realTime = m_realTime + timeStep / 1000.0f;

    float alpha     =  0.0f;
    float beta      =  0.0f;
    float roll      =  0.0f;
    float pitch     =  0.0f;
    float heading   =  0.0f;
    float slipSkid  =  0.0f;
    float turnRate  =  0.0f;
    float devH      =  0.0f;
    float devV      =  0.0f;
    float airspeed  =  0.0f;
    float altitude  =  0.0f;
    float pressure  = 28.0f;
    float climbRate =  0.0f;
    float machNo    =  0.0f;
    float adf       =  0.0f;
    float dme       =  0.0f;

    if ( m_ui->pushButtonAuto->isChecked() )
    {
        alpha     =   20.0f * sin( m_realTime /  10.0f );
        beta      =   15.0f * sin( m_realTime /  10.0f );
        roll      =  180.0f * sin( m_realTime /  10.0f );
        pitch     =   90.0f * sin( m_realTime /  20.0f );
        heading   =  360.0f * sin( m_realTime /  40.0f );
        slipSkid  =    1.0f * sin( m_realTime /  10.0f );
        turnRate  =    7.0f * sin( m_realTime /  10.0f );
        devH      =    1.0f * sin( m_realTime /  20.0f );
        devV      =    1.0f * sin( m_realTime /  20.0f );
        airspeed  =  125.0f * sin( m_realTime /  40.0f ) +  125.0f;
        altitude  = 9000.0f * sin( m_realTime /  40.0f ) + 9000.0f;
        pressure  =    2.0f * sin( m_realTime /  20.0f ) +   30.0f;
        climbRate =  650.0f * sin( m_realTime /  20.0f );
        machNo    = airspeed / 650.0f;
        adf       = -360.0f * sin( m_realTime /  50.0f );
        dme       =   99.0f * sin( m_realTime / 100.0f );

        m_ui->spinBoxAlpha ->setValue( alpha     );
        m_ui->spinBoxBeta  ->setValue( beta      );
        m_ui->spinBoxRoll  ->setValue( roll      );
        m_ui->spinBoxPitch ->setValue( pitch     );
        m_ui->spinBoxSlip  ->setValue( slipSkid  );
        m_ui->spinBoxTurn  ->setValue( turnRate  );
        m_ui->spinBoxDevH  ->setValue( devH      );
        m_ui->spinBoxDevV  ->setValue( devV      );
        m_ui->spinBoxHead  ->setValue( heading   );
        m_ui->spinBoxSpeed ->setValue( airspeed  );
        m_ui->spinBoxMach  ->setValue( machNo    );
        m_ui->spinBoxAlt   ->setValue( altitude  );
        m_ui->spinBoxPress ->setValue( pressure  );
        m_ui->spinBoxClimb ->setValue( climbRate );
        m_ui->spinBoxADF   ->setValue( adf       );
        m_ui->spinBoxDME   ->setValue( dme       );
    }
    else
    {
        alpha     = (float)m_ui->spinBoxAlpha ->value();
        beta      = (float)m_ui->spinBoxBeta  ->value();
        roll      = (float)m_ui->spinBoxRoll  ->value();
        pitch     = (float)m_ui->spinBoxPitch ->value();
        heading   = (float)m_ui->spinBoxHead  ->value();
        slipSkid  = (float)m_ui->spinBoxSlip  ->value();
        turnRate  = (float)m_ui->spinBoxTurn  ->value();
        devH      = (float)m_ui->spinBoxDevH  ->value();
        devV      = (float)m_ui->spinBoxDevV  ->value();
        airspeed  = (float)m_ui->spinBoxSpeed ->value();
        pressure  = (float)m_ui->spinBoxPress ->value();
        altitude  = (float)m_ui->spinBoxAlt   ->value();
        climbRate = (float)m_ui->spinBoxClimb ->value();
        machNo    = (float)m_ui->spinBoxMach  ->value();
        adf       = (float)m_ui->spinBoxADF   ->value();
        dme       = (float)m_ui->spinBoxDME   ->value();
    }

    m_ui->widgetPFD->setFlightPathMarker ( alpha, beta );
    m_ui->widgetPFD->setRoll          ( roll     );
    m_ui->widgetPFD->setPitch         ( pitch     );
    m_ui->widgetPFD->setSlipSkid      ( slipSkid  );
    m_ui->widgetPFD->setTurnRate      ( turnRate / 6.0f );
    m_ui->widgetPFD->setDevH          ( devH      );
    m_ui->widgetPFD->setDevV          ( devV      );
    m_ui->widgetPFD->setHeading       ( heading   );
    m_ui->widgetPFD->setAirspeed      ( airspeed  );
    m_ui->widgetPFD->setMachNo        ( machNo    );
    m_ui->widgetPFD->setAltitude      ( altitude  );
    m_ui->widgetPFD->setPressure      ( pressure  );
    m_ui->widgetPFD->setClimbRate     ( climbRate / 100.0f );
    m_ui->widgetPFD->setIdentifier    ( "ILAX" , true );
    m_ui->widgetPFD->setDistance      ( dme    , true );

    m_ui->widgetNAV->setHeading    ( heading   );
    m_ui->widgetNAV->setHeadingBug ( 0.0f );
    m_ui->widgetNAV->setCourse     ( 0.0f );
    m_ui->widgetNAV->setBearing    ( adf  , true );
    m_ui->widgetNAV->setDeviation  ( devH , true );
    m_ui->widgetNAV->setDistance   ( dme  , true );

    m_ui->widgetSix->setRoll      ( roll      );
    m_ui->widgetSix->setPitch     ( pitch     );
    m_ui->widgetSix->setAltitude  ( altitude  );
    m_ui->widgetSix->setPressure  ( pressure  );
    m_ui->widgetSix->setAirspeed  ( airspeed  );
    m_ui->widgetSix->setHeading   ( heading   );
    m_ui->widgetSix->setSlipSkid  ( slipSkid * 15.0f );
    m_ui->widgetSix->setTurnRate  ( turnRate  );
    m_ui->widgetSix->setClimbRate ( climbRate );

    m_ui->widgetPFD->update();
    m_ui->widgetNAV->update();
    m_ui->widgetSix->update();

    m_steps++;
}
