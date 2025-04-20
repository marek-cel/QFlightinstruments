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
#ifndef QFI_TC_H
#define QFI_TC_H

////////////////////////////////////////////////////////////////////////////////

#include <QGraphicsView>
#include <QGraphicsSvgItem>

#include <qfi/qfi_defs.h>

////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Turn Coordinator widget class.
 */
class QFIAPI qfi_TC : public QGraphicsView
{
    Q_OBJECT

public:

    /** Constructor. */
    explicit qfi_TC( QWidget *parent = Q_NULLPTR );

    /** Destructor. */
    virtual ~qfi_TC();

    /** Reinitiates widget. */
    void reinit();

    /** Refreshes (redraws) widget. */
    void redraw();

    /** @param turn rate [deg/s] */
    void setTurnRate( double turnRate );

    /** @param slip/skid ball angle [deg] */
    void setSlipSkid( double slipSkid );

protected:

    /** */
    void resizeEvent( QResizeEvent *event );

private:

    QGraphicsScene *_scene;

    QGraphicsSvgItem *_itemBack;
    QGraphicsSvgItem *_itemBall;
    QGraphicsSvgItem *_itemFace_1;
    QGraphicsSvgItem *_itemFace_2;
    QGraphicsSvgItem *_itemMark;
    QGraphicsSvgItem *_itemCase;

    double _turnRate;
    double _slipSkid;

    double _scaleX;
    double _scaleY;

    const int _originalHeight;
    const int _originalWidth;

    QPointF _originalMarkCtr;
    QPointF _originalBallCtr;

    const int _backZ;
    const int _ballZ;
    const int _face1Z;
    const int _face2Z;
    const int _markZ;
    const int _caseZ;

    void init();

    void reset();

    void updateView();
};

////////////////////////////////////////////////////////////////////////////////

#endif // QFI_TC_H
