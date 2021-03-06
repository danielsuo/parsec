/*=========================================================================

  Program:   CMake - Cross-Platform Makefile Generator
  Module:    $RCSfile: cmCursesDummyWidget.cxx,v $
  Language:  C++
  Date:      $Date: 2012/03/29 17:21:09 $
  Version:   $Revision: 1.1.1.1 $

  Copyright (c) 2002 Kitware, Inc., Insight Consortium.  All rights reserved.
  See Copyright.txt or http://www.cmake.org/HTML/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#include "cmCursesDummyWidget.h"

cmCursesDummyWidget::cmCursesDummyWidget(int width, int height, 
                                           int left, int top) :
  cmCursesWidget(width, height, left, top)
{
  this->Type = cmCacheManager::INTERNAL;
}


bool cmCursesDummyWidget::HandleInput(int&, cmCursesMainForm*, WINDOW* )
{
  return false;
}

