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
#ifndef QFI_FONTS_H
#define QFI_FONTS_H

////////////////////////////////////////////////////////////////////////////////

#include <QFont>

#include <qfi/qfi_defs.h>

////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Fonts class.
 */
class QFIAPI qfi_Fonts
{
public:

    static inline const QFont& small()
    {
        if ( !_inited ) init();
        return _small;
    }

    static inline const QFont& xsmall()
    {
        if ( !_inited ) init();
        return _xsmall;
    }

    static inline const QFont& medium()
    {
        if ( !_inited ) init();
        return _medium;
    }

private:

    static QFont _xsmall;
    static QFont _small;
    static QFont _medium;

    static bool _inited;

    static void init();
};

////////////////////////////////////////////////////////////////////////////////

#endif // QFI_FONTS_H
