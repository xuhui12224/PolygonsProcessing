

#ifndef _Polygons_Repair_H_
#define _Polygons_Repair_H_

#include <CGAL_to_VTKConfigure.h>

class vtkPolyData;

CGAL_VTK_EXPORT vtkPolyData* PolygonsFillHole(vtkPolyData *pInData, vtkPolyData *pOutData = nullptr);

CGAL_VTK_EXPORT vtkPolyData* PolygonsStitchBorder(vtkPolyData *pInData, vtkPolyData *pOutData = nullptr);

CGAL_VTK_EXPORT vtkPolyData* PolygonsConnectedComponents(vtkPolyData *pInData, vtkPolyData *pOutData = nullptr);

CGAL_VTK_EXPORT vtkPolyData* PolygonsRefineFair(vtkPolyData *pInData, vtkPolyData *pOutData = nullptr);

CGAL_VTK_EXPORT vtkPolyData* PolygonsSoupToMesh(vtkPolyData *pInData, vtkPolyData *pOutData = nullptr);

#endif