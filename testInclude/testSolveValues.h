/********************************************************************* 
  CombLayer : MNCPX Input builder
 
 * File:   testInclude/testSolveValues.h
*
 * Copyright (c) 2004-2013 by Stuart Ansell
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. 
 *
 ****************************************************************************/
#ifndef testSolveValues_h
#define testSolveValues_h 

/*!
  \class testSolveValues
  \brief Tests the Surface system
  \author S. Ansell
  \date February 2011
  \version 1.0

  Test all the solving of a polynominal system
*/

class testSolveValues 
{
private:

  //Tests 
  int testGetSolutions();
 
public:

  testSolveValues();
  ~testSolveValues();

  int applyTest(const int);
    
};

#endif
