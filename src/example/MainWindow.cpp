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

#include <example/MainWindow.h>
#include <ui_MainWindow.h>

#include <iostream>
#include <cmath>

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow( parent ),
    _ui( new Ui::MainWindow ),

    _timerId ( 0 ),
    _steps   ( 0 ),

    _realTime ( 0.0 ),
    _playTime ( 0.0 )
{
    _ui->setupUi( this );

    _timerId = startTimer( 0 );

    _time.start();
}

////////////////////////////////////////////////////////////////////////////////

MainWindow::~MainWindow()
{
    cout << "Average time step: " << _realTime / ( static_cast< double >( _steps ) ) << " s" << endl;

    if ( _timerId ) killTimer( _timerId );

    if ( _ui ) delete _ui;
    _ui = Q_NULLPTR;
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::timerEvent( QTimerEvent *event )
{
    /////////////////////////////////
    QMainWindow::timerEvent( event );
    /////////////////////////////////

    // getting time step
    double timeStep = _time.restart();

    _realTime = _realTime + timeStep / 1000.0;

    // flight and navigation parameters to be shown on instruments
    double alpha     =  0.0;
    double beta      =  0.0;
    double roll      =  0.0;
    double pitch     =  0.0;
    double heading   =  0.0;
    double slipSkid  =  0.0;
    double turnRate  =  0.0;
    double devLC     =  0.0;
    double devGS     =  0.0;
    double fd_r      =  0.0;
    double fd_p      =  0.0;
    double airspeed  =  0.0;
    double altitude  =  0.0;
    double pressure  = 28.0;
    double climbRate =  0.0;
    double machNo    =  0.0;
    double hdg       =  0.0;
    double crs       =  0.0;
    double vor       =  0.0;
    double adf       =  0.0;
    double dme       =  0.0;
    double sel_alt   =  0.0;
    double sel_ias   =  0.0;

    qfi_EADI::FltMode fltMode = qfi_EADI::FltMode::Off;
    qfi_EADI::SpdMode spdMode = qfi_EADI::SpdMode::Off;

    qfi_EADI::LNAV lnav = qfi_EADI::LNAV::Off;
    qfi_EADI::VNAV vnav = qfi_EADI::VNAV::Off;

    qfi_EHSI::CDI cdi = qfi_EHSI::CDI::Off;

    qfi_EADI::PressureMode press_mode = qfi_EADI::PressureMode::STD;

    if ( _ui->pushButtonPlay->isChecked() )
    {
        // automatic parametes setting

        _playTime = _playTime + timeStep / 1000.0;

        alpha     =     20.0 * sin( _playTime /  10.0 );
        beta      =     15.0 * sin( _playTime /  10.0 );
        roll      =    180.0 * sin( _playTime /  10.0 );
        pitch     =     90.0 * sin( _playTime /  20.0 );
        heading   =    360.0 * sin( _playTime /  40.0 );
        slipSkid  =      1.0 * sin( _playTime /  10.0 );
        turnRate  =      7.0 * sin( _playTime /  10.0 );
        devLC     =      1.0 * sin( _playTime /  20.0 );
        devGS     =      1.0 * sin( _playTime /  20.0 );
        fd_r      =     30.0 * sin( _playTime /  20.0 );
        fd_p      =     10.0 * sin( _playTime /  20.0 );
        airspeed  = -  100.0 * cos( _playTime /  10.0 ) +  100.0;
        altitude  = - 5000.0 * cos( _playTime /  40.0 ) + 5000.0;
        pressure  =      2.0 * sin( _playTime /  20.0 ) +   30.0;
        climbRate =   2000.0 * sin( _playTime /  20.0 );
        machNo    = airspeed / 650.0;
        hdg       =   -360.0 * sin( _playTime /  40.0 );
        crs       =    360.0 * sin( _playTime /  20.0 );
        vor       =      1.0 * sin( _playTime /  20.0 );
        adf       =   -360.0 * sin( _playTime /  50.0 );
        dme       =     99.0 * sin( _playTime / 100.0 );
        sel_ias   = -   50.0 * cos( _playTime /  40.0 ) +   50.0;
        sel_alt   = - 1000.0 * cos( _playTime /  40.0 ) + 1000.0;

        _ui->spinBoxAlpha  ->setValue( alpha     );
        _ui->spinBoxBeta   ->setValue( beta      );
        _ui->spinBoxRoll   ->setValue( roll      );
        _ui->spinBoxPitch  ->setValue( pitch     );
        _ui->spinBoxSlip   ->setValue( slipSkid  );
        _ui->spinBoxTurn   ->setValue( turnRate  );
        _ui->spinBoxLC     ->setValue( devLC     );
        _ui->spinBoxGS     ->setValue( devGS     );
        _ui->spinBoxFDR    ->setValue( fd_r      );
        _ui->spinBoxFDP    ->setValue( fd_p      );
        _ui->spinBoxHead   ->setValue( heading   );
        _ui->spinBoxSpeed  ->setValue( airspeed  );
        _ui->spinBoxMach   ->setValue( machNo    );
        _ui->spinBoxAlt    ->setValue( altitude  );
        _ui->spinBoxPress  ->setValue( pressure  );
        _ui->spinBoxClimb  ->setValue( climbRate );
        _ui->spinBoxHDG    ->setValue( hdg       );
        _ui->spinBoxCRS    ->setValue( crs       );
        _ui->spinBoxVOR    ->setValue( vor       );
        _ui->spinBoxADF    ->setValue( adf       );
        _ui->spinBoxDME    ->setValue( dme       );
        _ui->spinBoxSelIAS ->setValue( sel_ias   );
        _ui->spinBoxSelALT ->setValue( sel_alt   );
    }
    else
    {
        // manual parametes setting

        alpha     = _ui->spinBoxAlpha ->value();
        beta      = _ui->spinBoxBeta  ->value();
        roll      = _ui->spinBoxRoll  ->value();
        pitch     = _ui->spinBoxPitch ->value();
        heading   = _ui->spinBoxHead  ->value();
        slipSkid  = _ui->spinBoxSlip  ->value();
        turnRate  = _ui->spinBoxTurn  ->value();
        devLC     = _ui->spinBoxLC    ->value();
        devGS     = _ui->spinBoxGS    ->value();
        fd_r      = _ui->spinBoxFDR   ->value();
        fd_p      = _ui->spinBoxFDP   ->value();
        airspeed  = _ui->spinBoxSpeed ->value();
        pressure  = _ui->spinBoxPress ->value();
        altitude  = _ui->spinBoxAlt   ->value();
        climbRate = _ui->spinBoxClimb ->value();
        machNo    = _ui->spinBoxMach  ->value();
        crs       = _ui->spinBoxCRS   ->value();
        hdg       = _ui->spinBoxHDG   ->value();
        vor       = _ui->spinBoxVOR   ->value();
        adf       = _ui->spinBoxADF   ->value();
        dme       = _ui->spinBoxDME   ->value();
        sel_ias   = _ui->spinBoxSelIAS ->value();
        sel_alt   = _ui->spinBoxSelALT ->value();
    }

    switch ( _ui->comboBoxFltMode->currentIndex() )
    {
        case (int)qfi_EADI::FltMode::Off : fltMode = qfi_EADI::FltMode::Off ; break;
        case (int)qfi_EADI::FltMode::FD  : fltMode = qfi_EADI::FltMode::FD  ; break;
        case (int)qfi_EADI::FltMode::CMD : fltMode = qfi_EADI::FltMode::CMD ; break;
    }

    switch ( _ui->comboBoxSpdMode->currentIndex() )
    {
        case (int)qfi_EADI::SpdMode::Off     : spdMode = qfi_EADI::SpdMode::Off     ; break;
        case (int)qfi_EADI::SpdMode::FMC_SPD : spdMode = qfi_EADI::SpdMode::FMC_SPD ; break;
    }

    switch ( _ui->comboBoxLNAV->currentIndex() )
    {
        case (int)qfi_EADI::LNAV::Off     : lnav = qfi_EADI::LNAV::Off     ; break;
        case (int)qfi_EADI::LNAV::HDG     : lnav = qfi_EADI::LNAV::HDG     ; break;
        case (int)qfi_EADI::LNAV::NAV     : lnav = qfi_EADI::LNAV::NAV     ; break;
        case (int)qfi_EADI::LNAV::NAV_ARM : lnav = qfi_EADI::LNAV::NAV_ARM ; break;
        case (int)qfi_EADI::LNAV::APR     : lnav = qfi_EADI::LNAV::APR     ; break;
        case (int)qfi_EADI::LNAV::APR_ARM : lnav = qfi_EADI::LNAV::APR_ARM ; break;
        case (int)qfi_EADI::LNAV::BC      : lnav = qfi_EADI::LNAV::BC      ; break;
        case (int)qfi_EADI::LNAV::BC_ARM  : lnav = qfi_EADI::LNAV::BC_ARM  ; break;
    }

    switch ( _ui->comboBoxVNAV->currentIndex() )
    {
        case (int)qfi_EADI::VNAV::Off     : vnav = qfi_EADI::VNAV::Off     ; break;
        case (int)qfi_EADI::VNAV::ALT     : vnav = qfi_EADI::VNAV::ALT     ; break;
        case (int)qfi_EADI::VNAV::IAS     : vnav = qfi_EADI::VNAV::IAS     ; break;
        case (int)qfi_EADI::VNAV::VS      : vnav = qfi_EADI::VNAV::VS      ; break;
        case (int)qfi_EADI::VNAV::ALT_SEL : vnav = qfi_EADI::VNAV::ALT_SEL ; break;
        case (int)qfi_EADI::VNAV::GS      : vnav = qfi_EADI::VNAV::GS      ; break;
        case (int)qfi_EADI::VNAV::GS_ARM  : vnav = qfi_EADI::VNAV::GS_ARM  ; break;
    }

    switch ( _ui->comboBoxCDI->currentIndex() )
    {
        case (int)qfi_EHSI::CDI::Off  : cdi = qfi_EHSI::CDI::Off  ; break;
        case (int)qfi_EHSI::CDI::TO   : cdi = qfi_EHSI::CDI::TO   ; break;
        case (int)qfi_EHSI::CDI::FROM : cdi = qfi_EHSI::CDI::FROM ; break;
    }

    double press_coef = 1.0;

    switch ( _ui->comboBoxPress->currentIndex() )
    {
        case (int)qfi_EADI::PressureMode::STD : press_mode = qfi_EADI::PressureMode::STD ; break;
        case (int)qfi_EADI::PressureMode::IN  : press_mode = qfi_EADI::PressureMode::IN  ; break;
        case (int)qfi_EADI::PressureMode::MB  : press_mode = qfi_EADI::PressureMode::MB  ; press_coef = 33.86; break;
    }

    double fd_roll  = roll  + fd_r;
    double fd_pitch = pitch + fd_p;

    if ( fd_roll >  180.0 ) fd_roll =  180.0;
    if ( fd_roll < -180.0 ) fd_roll = -180.0;

    if ( fd_pitch >  90.0 ) fd_pitch =  90.0;
    if ( fd_pitch < -90.0 ) fd_pitch = -90.0;

    // setting widgets data

    // EADI
    _ui->widgetEADI->setFltMode     ( fltMode );
    _ui->widgetEADI->setSpdMode     ( spdMode );
    _ui->widgetEADI->setLNAV        ( lnav    );
    _ui->widgetEADI->setVNAV        ( vnav    );
    _ui->widgetEADI->setRoll        ( roll    );
    _ui->widgetEADI->setPitch       ( pitch   );
    _ui->widgetEADI->setFPM         ( alpha, beta );
    _ui->widgetEADI->setSlipSkid    ( slipSkid  );
    _ui->widgetEADI->setTurnRate    ( turnRate / 6.0 );
    _ui->widgetEADI->setDots        ( devGS, devLC, true, true );
    _ui->widgetEADI->setFD          ( fd_roll, fd_pitch, true );
    _ui->widgetEADI->setStall       ( _ui->pushButtonStall->isChecked() );
    _ui->widgetEADI->setHeading     ( heading   );
    _ui->widgetEADI->setAirspeed    ( airspeed  );
    _ui->widgetEADI->setMachNo      ( machNo    );
    _ui->widgetEADI->setAltitude    ( altitude  );
    _ui->widgetEADI->setPressure    ( press_coef * pressure, press_mode );
    _ui->widgetEADI->setClimbRate   ( climbRate / 1000.0 );
    _ui->widgetEADI->setAirspeedSel ( sel_ias );
    _ui->widgetEADI->setAltitudeSel ( sel_alt );
    _ui->widgetEADI->setHeadingSel  ( hdg );
    //_ui->widgetEADI->setIdentifier  ( "ILAX" , true );
    //_ui->widgetEADI->setDistance    ( dme    , true );
    _ui->widgetEADI->setVfe         (  85.0 );
    _ui->widgetEADI->setVne         ( 158.0 );

    // EHSI
    _ui->widgetEHSI->setHeading    ( heading   );
    _ui->widgetEHSI->setCourse     ( crs );
    _ui->widgetEHSI->setBearing    ( adf  , true );
    _ui->widgetEHSI->setDeviation  ( vor  , cdi );
    _ui->widgetEHSI->setDistance   ( dme  , true );
    _ui->widgetEHSI->setHeadingSel ( hdg );

    // Basic Six
    _ui->widgetSix->getAI()  ->setRoll      ( roll      );
    _ui->widgetSix->getAI()  ->setPitch     ( pitch     );
    _ui->widgetSix->getALT() ->setAltitude  ( altitude  );
    _ui->widgetSix->getALT() ->setPressure  ( pressure  );
    _ui->widgetSix->getASI() ->setAirspeed  ( airspeed  );
    _ui->widgetSix->getHI()  ->setHeading   ( heading   );
    _ui->widgetSix->getTC()  ->setSlipSkid  ( slipSkid * 15.0 );
    _ui->widgetSix->getTC()  ->setTurnRate  ( turnRate  );
    _ui->widgetSix->getVSI() ->setClimbRate ( climbRate );

    // redrawing widgets

    _ui->widgetEADI->redraw();
    _ui->widgetEHSI->redraw();

    _ui->widgetSix->getAI()  ->redraw();
    _ui->widgetSix->getALT() ->redraw();
    _ui->widgetSix->getASI() ->redraw();
    _ui->widgetSix->getHI()  ->redraw();
    _ui->widgetSix->getTC()  ->redraw();
    _ui->widgetSix->getVSI() ->redraw();

    // incrementing number of steps

    _steps++;
}
