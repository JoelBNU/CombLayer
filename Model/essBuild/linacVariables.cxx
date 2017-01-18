/********************************************************************* 
  CombLayer : MCNP(X) Input builder
 
 * File:   essBuild/linacVariables.cxx
 *
 * Copyright (c) 2017 by Konstantin Batkov
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
#include <iterator>
#include <memory>

#include "Exception.h"
#include "FileReport.h"
#include "NameStack.h"
#include "RegMethod.h"
#include "GTKreport.h"
#include "OutputLog.h"
#include "support.h"
#include "stringCombine.h"
#include "MatrixBase.h"
#include "Matrix.h"
#include "Vec3D.h"
#include "Code.h"
#include "varList.h"
#include "FuncDataBase.h"
#include "variableSetup.h"
#include "essVariables.h"

namespace setVariable
{


void
EssLinacVariables(FuncDataBase& Control)
  /*!
    Create all the linac variables
    \param Control :: DataBase
  */
{
  ELog::RegMethod RegA("essVariables[F]","EssLinacVariables");

  Control.addVariable("LinacLength",300);
  Control.addVariable("LinacWidth",300);
  Control.addVariable("LinacHeight",300);
  Control.addVariable("LinacWallThick",1);
  Control.addVariable("LinacMainMat","Void");
  Control.addVariable("LinacWallMat","SS316L");

  Control.addVariable("LinacBeamDumpSteelMat","SS316L"); // check it !!!
  Control.addVariable("LinacBeamDumpConcreteMat","Concrete"); // check it !!!

  Control.addVariable("LinacBeamDumpFrontWallLength",4*5.0); // doc SPLTDISH0001
  Control.addVariable("LinacBeamDumpFrontWallHeight",50.0); // doc SPLTDISH0001
  Control.addVariable("LinacBeamDumpFrontWallDepth",50.0); // doc SPLTDISH0001
  Control.addVariable("LinacBeamDumpFrontWallWidth",40.0); // doc SPLTDISH0001

  Control.addVariable("LinacBeamDumpFrontInnerWallDepth",15.0); // doc SPLTDISH0001

  Control.addVariable("LinacBeamDumpFloorLength",100.0); // doc SPLTDISH0001
  Control.addVariable("LinacBeamDumpFloorDepth",5*5.0); // doc SPLTDISH0001
  
  Control.addVariable("LinacBeamDumpPlate25Length",35.0); // doc SPLTDISH0001
  Control.addVariable("LinacBeamDumpPlate25Depth",3.0); // doc SPLTDISH0001

  Control.addVariable("LinacBeamDumpBackWallLength",20.0);  // email Lali 3 Nov 2016
  Control.Parse("LinacBeamDumpFrontInnerWallDepth+LinacBeamDumpFloorDepth+LinacBeamDumpPlate25Depth");
  Control.addVariable("LinacBeamDumpBackWallDepth");

  Control.addVariable("LinacBeamDumpWidth",100);
  Control.addVariable("LinacBeamDumpHeight",50);
  Control.addVariable("LinacBeamDumpWallThick",1);
  Control.addVariable("LinacBeamDumpMainMat","Void");
  Control.addVariable("LinacBeamDumpWallMat","SS316L");

  return;
}

}  // NAMESPACE setVariable