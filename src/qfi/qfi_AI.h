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
#ifndef QFI_AI_H
#define QFI_AI_H

////////////////////////////////////////////////////////////////////////////////

#include <QGraphicsView>
#include <QGraphicsSvgItem>

#include <qfi/qfi_defs.h>

////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Attitude Indicator widget class.
 */
class QFIAPI qfi_AI : public QGraphicsView
{
    Q_OBJECT

public:

    /** Constructor. */
    explicit qfi_AI( QWidget *parent = Q_NULLPTR );

    /** Destructor. */
    virtual ~qfi_AI();

    /** Reinitiates widget. */
    void reinit();

    /** Refreshes (redraws) widget. */
    void redraw();

    /** @param roll angle [deg] */
    void setRoll( double roll );

    /** @param pitch angle [deg] */
    void setPitch( double pitch );

protected:

    /** */
    void resizeEvent( QResizeEvent *event );

private:

    QGraphicsScene *_scene;

    QGraphicsSvgItem *_itemBack;
    QGraphicsSvgItem *_itemFace;
    QGraphicsSvgItem *_itemRing;
    QGraphicsSvgItem *_itemCase;

    double _roll;
    double _pitch;

    double _faceDeltaX_new;
    double _faceDeltaX_old;
    double _faceDeltaY_new;
    double _faceDeltaY_old;

    double _scaleX;
    double _scaleY;

    const int _originalHeight;
    const int _originalWidth;

    const double _originalPixPerDeg;

    QPointF _originalAdiCtr;

    const int _backZ;
    const int _faceZ;
    const int _ringZ;
    const int _caseZ;

    void init();

    void reset();

    void updateView();
};

////////////////////////////////////////////////////////////////////////////////

#endif // QFI_AI_H
