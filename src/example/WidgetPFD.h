/***************************************************************************//**
 * @file example/WidgetPFD.h
 * @author  Marek M. Cel <marekcel@marekcel.pl>
 * @author Dave Culp <daveculp@cox.net>
 *
 * @section LICENSE
 *
 * Copyright (C) 2018 Marek M. Cel, Dave Culp
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
 * Copyright (C) 2018 Marek M. Cel, Dave Culp
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
#ifndef WIDGETPFD_H
#define WIDGETPFD_H

////////////////////////////////////////////////////////////////////////////////

#include <QWidget>

#include <qfi_PFD.h>

#include "LayoutSquare.h"

////////////////////////////////////////////////////////////////////////////////

namespace Ui
{
    class WidgetPFD;
}

////////////////////////////////////////////////////////////////////////////////

class WidgetPFD : public QWidget
{
    Q_OBJECT

public:

    explicit WidgetPFD( QWidget *parent = 0 );

    virtual ~WidgetPFD();

    inline void update()
    {
        m_pfd->update();
    }

    inline void setRoll( float roll )
    {
        m_pfd->setRoll( roll );
    }

    inline void setPitch( float pitch )
    {
        m_pfd->setPitch( pitch );
    }

    inline void setFlightPathMarker( float aoa, float sideslip )
    {
        m_pfd->setFlightPathMarker( aoa, sideslip );
    }

    inline void setSlipSkid( float slipSkid )
    {
        m_pfd->setSlipSkid( slipSkid );
    }

    inline void setDevH( float devH )
    {
        m_pfd->setBarH( devH );
        m_pfd->setDotH( devH );
    }

    inline void setDevV( float devV )
    {
        m_pfd->setBarV( devV );
        m_pfd->setDotV( devV );
    }

    inline void setAltitude( float altitude )
    {
        m_pfd->setAltitude( altitude );
    }

    inline void setPressure( float pressure )
    {
        m_pfd->setPressure( pressure, qfi_PFD::IN );
    }

    inline void setAirspeed( float airspeed )
    {
        m_pfd->setAirspeed( airspeed );
    }

    inline void setMachNo( float machNo )
    {
        m_pfd->setMachNo( machNo );
    }

    inline void setHeading( float heading )
    {
        m_pfd->setHeading( heading );
    }

    inline void setTurnRate( float turnRate )
    {
        m_pfd->setTurnRate( turnRate );
    }

    inline void setClimbRate( float climbRate )
    {
        m_pfd->setClimbRate( climbRate );
    }

    inline void setIdentifier( const QString &ident, bool isVisible )
    {
        m_pfd->setIdent( ident, isVisible );
    }

    inline void setDistance( float dist, bool isVisible )
    {
        m_pfd->setDistance( dist, isVisible );
    }

private:

    Ui::WidgetPFD *m_ui;
    qfi_PFD       *m_pfd;
    LayoutSquare  *m_layoutSq;

    void setupUi();
};

////////////////////////////////////////////////////////////////////////////////

#endif // WIDGETPFD_H
