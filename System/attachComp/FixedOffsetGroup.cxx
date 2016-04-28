/********************************************************************* 
  CombLayer : MCNP(X) Input builder
 
 * File:   attachComp/FixedOffsetGroup.cxx
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
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cmath>
#include <complex>
#include <list>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <memory>

#include "Exception.h"
#include "FileReport.h"
#include "GTKreport.h"
#include "NameStack.h"
#include "RegMethod.h"
#include "OutputLog.h"
#include "BaseVisit.h"
#include "BaseModVisit.h"
#include "support.h"
#include "MatrixBase.h"
#include "Matrix.h"
#include "Vec3D.h"
#include "Quaternion.h"
#include "Surface.h"
#include "surfIndex.h"
#include "surfRegister.h"
#include "surfEqual.h"
#include "Rules.h"
#include "HeadRule.h"
#include "LinkUnit.h"
#include "FixedComp.h"
#include "varList.h"
#include "Code.h"
#include "FuncDataBase.h"
#include "FixedGroup.h"
#include "FixedOffsetGroup.h"

namespace attachSystem
{

void
offset::copy(double& XS,double& YS,double& ZS,
             double& XYA,double& ZA) const
  /*!
    Copy data to external variables
    \param XS :: XStep value
    \param YS :: YStep value    
    \param ZS :: ZStep value
    \param XYA :: XYAngle value
    \param ZA :: ZAngle value
  */
{
  XS=xStep;
  YS=yStep;
  ZS=zStep;
  XYA=xyAngle;
  ZA=zAngle;
  return;
}
  
FixedOffsetGroup::FixedOffsetGroup(const std::string& mainKey,
				   const std::string& KN,
				   const size_t NL) :
  FixedGroup(mainKey,KN,NL),xStep(0.0),yStep(0.0),zStep(0.0),
  xyAngle(0.0),zAngle(0.0)
 /*!
    Constructor 
    \param KN :: KeyName
    \param NL :: Number of links
  */
{}

FixedOffsetGroup::FixedOffsetGroup(const std::string& mainKey,
				   const std::string& AKey,
				   const size_t ANL,
				   const std::string& BKey,
				   const size_t BNL) :
  FixedGroup(mainKey,AKey,ANL,BKey,BNL),
  xStep(0.0),yStep(0.0),zStep(0.0),
  xyAngle(0.0),zAngle(0.0)
 /*!
    Constructor 
    \param mainKey :: KeyName [main system]
    \param AKey :: Key unit
    \param ANL :: A Number of links
    \param BKey :: Key unit
    \param BNL :: B Number of links
  */
{}

FixedOffsetGroup::FixedOffsetGroup(const std::string& mainKey,
                                   const std::string& AKey,
                                   const size_t ANL,
                                   const std::string& BKey,
                                   const size_t BNL,
                                   const std::string& CKey,
                                   const size_t CNL) :
  FixedGroup(mainKey,AKey,ANL,BKey,BNL,CKey,CNL),
  xStep(0.0),yStep(0.0),zStep(0.0),
  xyAngle(0.0),zAngle(0.0)
 /*!
    Constructor 
    \param mainKey :: KeyName [main system]
    \param AKey :: Key unit
    \param ANL :: A Number of links
    \param BKey :: Key unit
    \param BNL :: B Number of links
    \param CKey :: Key unit
    \param CNL :: B Number of links
  */
{}


FixedOffsetGroup::FixedOffsetGroup(const FixedOffsetGroup& A) : 
  FixedGroup(A),
  xStep(A.xStep),yStep(A.yStep),zStep(A.zStep),
  xyAngle(A.xyAngle),zAngle(A.zAngle),GOffset(A.GOffset)
  /*!
    Copy constructor
    \param A :: FixedOffsetGroup to copy
  */
{}

FixedOffsetGroup&
FixedOffsetGroup::operator=(const FixedOffsetGroup& A)
  /*!
    Assignment operator
    \param A :: FixedOffsetGroup to copy
    \return *this
  */
{
  if (this!=&A)
    {
      FixedGroup::operator=(A);
      xStep=A.xStep;
      yStep=A.yStep;
      zStep=A.zStep;
      xyAngle=A.xyAngle;
      zAngle=A.zAngle;
      GOffset=A.GOffset;
    }
  return *this;
}

void
FixedOffsetGroup::populateOffset(const FuncDataBase& Control,
                                 const std::string& keyItem,
                                 offset& GO)
  /*!
    Populate the variables
    \param Control :: Control data base
   */
{
  ELog::RegMethod RegA("FixedOffsetGroup","populate");

  
  GO.xStep=Control.EvalDefVar<double>(keyItem+"XStep",0.0);
  GO.yStep=Control.EvalDefVar<double>(keyItem+"YStep",0.0);
  GO.zStep=Control.EvalDefVar<double>(keyItem+"ZStep",0.0);
  GO.xyAngle=Control.EvalDefVar<double>(keyItem+"XYAngle",0.0);
  GO.zAngle=Control.EvalDefVar<double>(keyItem+"ZAngle",0.0);
  
  return;
}

void
FixedOffsetGroup::populate(const FuncDataBase& Control)
  /*!
    Populate the variables
    \param Control :: Control data base
   */
{
  ELog::RegMethod RegA("FixedOffsetGroup","populate");

  for(FTYPE::value_type& FCmc : FMap)
    {
      offset GO;
      populateOffset(Control,FCmc.second->getKeyName(),GO);
      GOffset.emplace(FCmc.first,GO);
    }
  
 
  xStep=Control.EvalDefVar<double>(keyName+"XStep",0.0);
  yStep=Control.EvalDefVar<double>(keyName+"YStep",0.0);
  zStep=Control.EvalDefVar<double>(keyName+"ZStep",0.0);
  xyAngle=Control.EvalDefVar<double>(keyName+"XYAngle",0.0);
  zAngle=Control.EvalDefVar<double>(keyName+"ZAngle",0.0);
  
  return;
}
  
void
FixedOffsetGroup::applyOffset()
  /*!
    Apply the rotation/step offset
  */
{
  ELog::RegMethod RegA("FixedOffsetGroup","applyOffset");

  for(FTYPE::value_type& FCmc : FMap)
    {
      std::map<std::string,offset>::const_iterator mc=GOffset.find(FCmc.first);
      if (mc==GOffset.end())
        throw ColErr::InContainerError<std::string>
          (FCmc.first,"Offset not found");
      const offset& GO=mc->second;      
      FCmc.second->applyShift(xStep+GO.xStep,yStep+GO.yStep,zStep+GO.zStep);
      FCmc.second->applyAngleRotate(xyAngle+GO.xyAngle,zAngle+GO.zAngle);
    }
  return;
}

 
}  // NAMESPACE attachSystem
