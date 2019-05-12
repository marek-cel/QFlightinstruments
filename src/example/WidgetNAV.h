/***************************************************************************//**
 * @file example/WidgetNAV.h
 * @author  Marek M. Cel <marekcel@marekcel.pl>
 *
 * @section LICENSE
 *
 * Copyright (C) 2015 Marek M. Cel
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
 * Copyright (C) 2015 Marek M. Cel
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
#ifndef WIDGETNAV_H
#define WIDGETNAV_H

////////////////////////////////////////////////////////////////////////////////

#include <QWidget>

#include <qfi_NAV.h>

#include "LayoutSquare.h"

////////////////////////////////////////////////////////////////////////////////

namespace Ui
{
    class WidgetNAV;
}

////////////////////////////////////////////////////////////////////////////////

class WidgetNAV : public QWidget
{
    Q_OBJECT

public:

    explicit WidgetNAV( QWidget *parent = 0 );

    virtual ~WidgetNAV();

    inline void update()
    {
        m_nav->update();
    }

    inline void setHeading( float heading )
    {
        m_nav->setHeading( heading );
    }

    inline void setHeadingBug( float headingBug )
    {
        m_nav->setHeadingBug( headingBug );
    }

    inline void setCourse( float course )
    {
        m_nav->setCourse( course );
    }

    inline void setBearing( float bearing, bool visible = false )
    {
        m_nav->setBearing( bearing, visible );
    }

    inline void setDeviation( float deviation, bool visible = false )
    {
        m_nav->setDeviation( deviation, visible );
    }

    inline void setDistance( float distance, bool visible = false )
    {
        m_nav->setDistance( distance, visible );
    }

private:

    Ui::WidgetNAV *m_ui;
    qfi_NAV       *m_nav;
    LayoutSquare  *m_layoutSq;

    void setupUi();
};

////////////////////////////////////////////////////////////////////////////////

#endif // WIDGETNAV_H
