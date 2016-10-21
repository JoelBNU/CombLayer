/********************************************************************* 
  CombLayer : MCNP(X) Input builder
 
 * File:   constructInc/FrontBackCut.h
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
#ifndef attachSystem_FrontBackCut_h
#define attachSystem_FrontBackCut_h

class Simulation;

namespace attachSystem
{
  
/*!
  \class FrontBackCut
  \version 1.0
  \author S. Ansell
  \date September 2016
  \brief FrontBackCut unit  
  
  System to add this to components that need to be cut
*/

class FrontBackCut 
{
 private:
  
  bool activeFront;             ///< Front cut is active
  HeadRule frontCut;            ///< Front cut
  HeadRule frontDivider;        ///< Front divider

  bool activeBack;             ///< Back cut is active
  HeadRule backCut;            ///< Back cut
  HeadRule backDivider;        ///< Back divider


 public:

  FrontBackCut();
  FrontBackCut(const FrontBackCut&);
  FrontBackCut& operator=(const FrontBackCut&);
  virtual ~FrontBackCut();

  void setFront(const attachSystem::FixedComp&,const long int);
  void setBack(const attachSystem::FixedComp&,const long int);

  void setFrontDivider(const std::string&);
  void setBackDivider(const std::string&);
  void setFrontDivider(const HeadRule&);
  void setBackDivider(const HeadRule&);


  /// Flag accessor
  bool frontActive() const { return activeFront; }
  /// Flag accessor
  bool backActive() const { return activeBack; }
  std::string frontRule() const;
  std::string backRule() const;
  
};

}

#endif
 