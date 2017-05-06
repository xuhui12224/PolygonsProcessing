

#ifndef _Polygons_Check_H_
#define _Polygons_Check_H_

#include <CGAL_to_VTKConfigure.h>

class vtkPolyData;

CGAL_VTK_EXPORT vtkPolyData* CheckHoles(vtkPolyData *pInData, vtkPolyData *pOutData = nullptr);

CGAL_VTK_EXPORT vtkPolyData* CheckBorder(vtkPolyData *pInData, vtkPolyData *pOutData = nullptr);

CGAL_VTK_EXPORT vtkPolyData* CheckConnectedComponents(vtkPolyData *pInData, vtkPolyData *pOutData = nullptr);

CGAL_VTK_EXPORT vtkPolyData* CheckSelfIntersection(vtkPolyData *pInData, vtkPolyData *pOutData = nullptr);

#endif