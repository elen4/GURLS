/*
 * The GURLS Package in C++
 *
 * Copyright (C) 2011-1013, IIT@MIT Lab
 * All rights reserved.
 *
 * authors:  M. Santoro
 * email:   msantoro@mit.edu
 * website: http://cbcl.mit.edu/IIT@MIT/IIT@MIT.html
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *     * Redistributions of source code must retain the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials
 *       provided with the distribution.
 *     * Neither the name(s) of the copyright holders nor the names
 *       of its contributors or of the Massacusetts Institute of
 *       Technology or of the Italian Institute of Technology may be
 *       used to endorse or promote products derived from this software
 *       without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */


#ifndef _GURLS_NORML2_H_
#define _GURLS_NORML2_H_


#include "gurls++/norm.h"
#include "gurls++/gmath.h"
#include "gurls++/optmatrix.h"

#include <limits>

namespace gurls {

/**
 * \ingroup Norms
 * \brief NormL2 is the sub-class of Norm that spheriphies the data according to the l2 norm.
 */

template <typename T>
class NormL2: public Norm<T>
{
public:
    /**
     * Spheriphies the data according to the l2 norm.
     * \param X input data matrix
     * \param Y not used
     * \param opt not used
     * \return spheriphied input data matrix
     */
    GurlsOptionsList* execute(const gMat2D<T>& X, const gMat2D<T>& Y, const GurlsOptionsList& opt)  throw(gException);
};

template<typename T>
GurlsOptionsList* NormL2<T>::execute(const gMat2D<T>& X, const gMat2D<T>& /*Y*/, const GurlsOptionsList& /*opt*/) throw(gException)
{
    const unsigned long m = X.rows();
    const unsigned long n = X.cols();


    gMat2D<T>* retX = new gMat2D<T>(m, n);
    copy(retX->getData(), X.getData(), retX->getSize());
    T *rx_it = retX->getData();

    const T epsilon = std::numeric_limits<T>::epsilon();
    const T one = (T)1.0;
    T norm2;

//    for j = 1:size(X,1)
    for(unsigned long j=0; j<m; ++j, ++rx_it)
    {
//        X(j,:) = X(j,:)/(norm(X(j,:)) + eps);
        norm2 = nrm2(n, rx_it, m) + epsilon;
        scal(n, one/norm2, rx_it, m);
    }

    GurlsOptionsList* norm = new GurlsOptionsList("norm");
    norm->addOpt("X", new OptMatrix<gMat2D<T> >(*retX));

    return norm;
}

}

#endif //_GURLS_NORML2_H_
