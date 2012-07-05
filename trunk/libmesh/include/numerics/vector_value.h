// The libMesh Finite Element Library.
// Copyright (C) 2002-2012 Benjamin S. Kirk, John W. Peterson, Roy H. Stogner

// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA



#ifndef __vector_value_h__
#define __vector_value_h__

// Local includes
#include "type_vector.h"

// C++ includes

namespace libMesh
{


template <typename T>
struct MakeNumber<VectorValue<T> >
{
  typedef VectorValue<typename MakeNumber<T>::type > type;
};




/**
 * This class defines a vector in LIBMESH_DIM dimensional Real or Complex
 * space.  The typedef RealVectorValue always defines a real-valued vector,
 * and NumberVectorValue defines a real or complex-valued vector depending
 * on how the library was configured.
 *
 * \author Benjamin S. Kirk, 2003.
 */
template <typename T>
class VectorValue : public TypeVector<T>
{
public:

  /**
   * Empty constructor.
   * Gives the vector 0 in \p LIBMESH_DIM dimensional T space.
   */
  VectorValue ();

  /**
   * Constructor-from-scalars.  By default sets higher dimensional
   * entries to 0.
   */
  template <typename Scalar>
  VectorValue (const Scalar x,
	       const Scalar y=0,
               typename
                 boostcopy::enable_if_c<ScalarTraits<Scalar>::value,
                                        const Scalar>::type z=0);

  /**
   * Copy-constructor.
   */
  template <typename T2>
  VectorValue (const VectorValue<T2>& p);

  /**
   * Copy-constructor.
   */
  template <typename T2>
  VectorValue (const TypeVector<T2>& p);

#ifdef LIBMESH_USE_COMPLEX_NUMBERS
  /**
   * Constructor that takes two \p TypeVector<Real>
   * representing the real and imaginary part as
   * arguments.
   */
  VectorValue (const TypeVector<Real>& p_re,
	       const TypeVector<Real>& p_im);
#endif

  /**
   * Assignment-from-scalar operator.  Used only to zero out vectors.
   */
  template <typename Scalar>
  typename boostcopy::enable_if_c<
    ScalarTraits<Scalar>::value,
    VectorValue&>::type
  operator = (const Scalar& p)
  { libmesh_assert(p == Scalar(0)); this->zero(); return *this; }


private:


};



/**
 * Useful typedefs to allow transparent switching
 * between Real and Complex data types.
 */
typedef VectorValue<Real>   RealVectorValue;
typedef VectorValue<Number> NumberVectorValue;
typedef RealVectorValue     RealGradient;
typedef NumberVectorValue   Gradient;



//------------------------------------------------------
// Inline functions

template <typename T>
inline
VectorValue<T>::VectorValue () :
  TypeVector<T> ()
{
}


template <typename T>
template <typename Scalar>
inline
VectorValue<T>::VectorValue (const Scalar x,
	                     const Scalar y,
                             typename
                              boostcopy::enable_if_c<ScalarTraits<Scalar>::value,
                                                     const Scalar>::type z) :
  TypeVector<T> (x,y,z)
{
}



template <typename T>
template <typename T2>
inline
VectorValue<T>::VectorValue (const VectorValue<T2>& p) :
  TypeVector<T> (p)
{
}



template <typename T>
template <typename T2>
inline
VectorValue<T>::VectorValue (const TypeVector<T2>& p) :
  TypeVector<T> (p)
{
}


#ifdef LIBMESH_USE_COMPLEX_NUMBERS
template <typename T>
inline
VectorValue<T>::VectorValue (const TypeVector<Real>& p_re,
			     const TypeVector<Real>& p_im) :
  TypeVector<T> (Complex (p_re(0), p_im(0)),
		 Complex (p_re(1), p_im(1)),
		 Complex (p_re(2), p_im(2)))
{
}
#endif

} // namespace libMesh

#endif // #define __vector_value_h__