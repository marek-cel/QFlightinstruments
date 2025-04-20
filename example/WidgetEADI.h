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
#ifndef WIDGETEADI_H
#define WIDGETEADI_H

////////////////////////////////////////////////////////////////////////////////

#include <QWidget>

#include <qfi/qfi_EADI.h>

#include "LayoutSquare.h"

////////////////////////////////////////////////////////////////////////////////

namespace Ui
{
    class WidgetEADI;
}

////////////////////////////////////////////////////////////////////////////////

class WidgetEADI : public QWidget
{
    Q_OBJECT

public:

    explicit WidgetEADI( QWidget *parent = Q_NULLPTR );

    virtual ~WidgetEADI();

    inline void redraw() { _eadi->redraw(); }

    /** */
    inline void setFltMode( qfi_EADI::FltMode fltMode )
    {
        _eadi->setFltMode( fltMode );
    }

    /** */
    inline void setSpdMode( qfi_EADI::SpdMode spdMode )
    {
        _eadi->setSpdMode( spdMode );
    }

    /** */
    inline void setLNAV( qfi_EADI::LNAV lnav )
    {
        _eadi->setLNAV( lnav );
    }

    /** */
    inline void setVNAV( qfi_EADI::VNAV vnav )
    {
        _eadi->setVNAV( vnav );
    }

    inline void setRoll( double roll )
    {
        _eadi->setRoll( roll );
    }

    inline void setPitch( double pitch )
    {
        _eadi->setPitch( pitch );
    }

    inline void setFPM( double aoa, double sideslip )
    {
        _eadi->setFPM( aoa, sideslip );
    }

    inline void setSlipSkid( double slipSkid )
    {
        _eadi->setSlipSkid( slipSkid );
    }

    /**
     * @param normalized turn rate (range from -1.0 to 1.0),
     * hash marks positions are set to be -0.5 and 0.5 */
    inline void setTurnRate( double turnRate )
    {
        _eadi->setTurnRate( turnRate );
    }

    /**
     * @param normalized horizontal deviation dot position (range from -1.0 to 1.0)
     * @param normalized vertical deviation dot position (range from -1.0 to 1.0)
     * @param deviation horizontal dot visibility
     * @param deviation vertical dot visibility */
    inline void setDots( double dotH, double dotV, bool visibleH, bool visibleV )
    {
        _eadi->setDots( dotH, dotV, visibleH, visibleV );
    }

    /**
     * @param FD roll angle [deg]
     * @param FD pitch angle [deg]
     * @param FD visibility */
    inline void setFD( double roll, double pitch, bool visible = true )
    {
        _eadi->setFD( roll, pitch, visible );
    }

    /** @param stall flag */
    inline void setStall( bool stall )
    {
        _eadi->setStall( stall );
    }

    inline void setAltitude( double altitude )
    {
        _eadi->setAltitude( altitude );
    }

    inline void setPressure( double pressure, qfi_EADI::PressureMode pressMode )
    {
        _eadi->setPressure( pressure, pressMode );
    }

    inline void setAirspeed( double airspeed )
    {
        _eadi->setAirspeed( airspeed );
    }

    inline void setMachNo( double machNo )
    {
        _eadi->setMachNo( machNo );
    }

    inline void setHeading( double heading )
    {
        _eadi->setHeading( heading );
    }

    inline void setClimbRate( double climbRate )
    {
        _eadi->setClimbRate( climbRate );
    }

    /** @param airspeed (dimensionless numeric value) */
    inline void setAirspeedSel( double airspeed )
    {
        _eadi->setAirspeedSel( airspeed );
    }

    /** @param altitude (dimensionless numeric value) */
    inline void setAltitudeSel( double altitude )
    {
        _eadi->setAltitudeSel( altitude );
    }

    /** @param heading [deg] */
    inline void setHeadingSel( double heading )
    {
        _eadi->setHeadingSel( heading );
    }

    //inline void setIdentifier( const QString &ident, bool isVisible )
    //{
    //    _eadi->setIdent( ident, isVisible );
    //}

    //inline void setDistance( double dist, bool isVisible )
    //{
    //    _eadi->setDistance( dist, isVisible );
    //}

    inline void setVfe( double vfe )
    {
        _eadi->setVfe( vfe );
    }

    inline void setVne( double vne )
    {
        _eadi->setVne( vne );
    }

private:

    Ui::WidgetEADI *_ui;
    qfi_EADI       *_eadi;
    LayoutSquare   *_layoutSq;

    void setupUi();
};

////////////////////////////////////////////////////////////////////////////////

#endif // WIDGETEADI_H
