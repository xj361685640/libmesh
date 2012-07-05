// $Id: linear_implicit_system.h,v 1.4 2006-03-29 20:01:47 roystgnr Exp $

// The libMesh Finite Element Library.
// Copyright (C) 2002-2005  Benjamin S. Kirk, John W. Peterson
  
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



#ifndef __linear_implicit_system_h__
#define __linear_implicit_system_h__

// C++ includes

// Local Includes
#include "implicit_system.h"


// Forward Declarations
template <typename T> class LinearSolver;


/**
 * This class provides a specific system class.  It aims
 * at implicit systems, offering nothing more than just
 * the essentials needed to solve a system.  Note
 * that still additional vectors/matrices may be added,
 * as offered in the parent class \p ExplicitSystem.
 */

// ------------------------------------------------------------
// LinearImplicitSystem class definition

class LinearImplicitSystem : public ImplicitSystem
{
public:

  /**
   * Constructor.  Optionally initializes required
   * data structures.
   */
  LinearImplicitSystem (EquationSystems& es,
			const std::string& name,
			const unsigned int number);

  /**
   * Destructor.
   */
  virtual ~LinearImplicitSystem ();

  /**
   * The type of system.
   */
  typedef LinearImplicitSystem sys_type;

  /**
   * The type of the parent.
   */
  typedef ImplicitSystem Parent;
  
  /**
   * @returns a clever pointer to the system.
   */
  sys_type & system () { return *this; }
  
  /**
   * Clear all the data structures associated with
   * the system. 
   */
  virtual void clear ();

  /**
   * Reinitializes the member data fields associated with
   * the system, so that, e.g., \p assemble() may be used.
   */
  virtual void reinit ();
   
//   /**
//    * Prepares \p matrix and \p _dof_map for matrix assembly.
//    * Does not actually assemble anything.  For matrix assembly,
//    * use the \p assemble() in derived classes.
//    * @e Should be overloaded in derived classes.
//    */
//   virtual void assemble () { ImplicitSystem::assemble(); }
 
  /**
   * Assembles & solves the linear system Ax=b. 
   */
  virtual void solve ();
 
  /**
   * @returns \p "LinearImplicit".  Helps in identifying
   * the system type in an equation system file.
   */
  virtual std::string system_type () const { return "LinearImplicit"; }

  /**
   * The \p LinearSolver defines the interface used to
   * solve the linear_implicit system.  This class handles all the
   * details of interfacing with various linear algebra packages
   * like PETSc or LASPACK.
   */
  AutoPtr<LinearSolver<Number> > linear_solver;
  
  /**
   * Returns  the number of iterations 
   * taken for the most recent linear solve.
   */
  unsigned int n_linear_iterations() const { return _n_linear_iterations; }

  /**
   * Returns the final residual for the linear system solve.
   */
  Real final_linear_residual() const { return _final_linear_residual; }
  
protected:
  
  /**
   * The number of linear iterations required to solve the linear
   * system Ax=b.
   */
  unsigned int _n_linear_iterations;

  /**
   * The final residual for the linear system Ax=b.
   */
  Real _final_linear_residual;
};



// ------------------------------------------------------------
// LinearImplicitSystem inline methods


#endif