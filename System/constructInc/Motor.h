/********************************************************************* 
  CombLayer : MCNP(X) Input builder
 
 * File:   constructInc/Motor.h
 *
 * Copyright (c) 2004-2016 by Stuart Ansell
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
#ifndef constructSystem_Motor_h
#define constructSystem_Motor_h

class Simulation;

namespace constructSystem
{
  
/*!
  \class Motor
  \version 1.0
  \author S. Ansell
  \date April 2016
  \brief Motor unit  
  
  Produces a sealed inner port with bolts within a space
  Ring axis along Y axis. X/Z parallel to ring.
*/

class Motor :
  public attachSystem::FixedOffset,
  public attachSystem::ContainedComp,
  public attachSystem::CellMap,
  public attachSystem::FrontBackCut
{
 private:
  
  const int motorIndex;         ///< Index of surface offset
  int cellIndex;                ///< Cell index  

  double length;                ///< length out of port
  double radius;                ///< radius 
  int mat;                      ///< material

  void populate(const FuncDataBase&);
  void createUnitVector(const attachSystem::FixedComp&,const long int);
  void createSurfaces();
  void createObjects(Simulation&);
  void createLinks();
  
 public:

  Motor(const std::string&);
  Motor(const Motor&);
  Motor& operator=(const Motor&);
  virtual ~Motor();

  void createAll(Simulation&,const attachSystem::FixedComp&,
		 const long int);
};

}

#endif
 
