
#include "vtkPolyData.h"
#include "PolygonsRepair.h"
#include "CGAL_to_VTK.h"

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/boost/graph/graph_traits_Polyhedron_3.h>

#include <CGAL/Polygon_mesh_processing/stitch_borders.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Polyhedron_3<K> Polyhedron;

namespace PMP = CGAL::Polygon_mesh_processing;

vtkPolyData* PolygonsStitchBorder(vtkPolyData *pInData, vtkPolyData *pOutData)
{
	Polyhedron poly;

	vtk_polydata_to_Polyhedron(poly, pInData);

	PMP::stitch_borders(poly);

	if (pOutData == nullptr)
	{
		pOutData = vtkPolyData::New();
	}

	Polyhedron_to_vtk_polydata(poly, pOutData);

	return pOutData;
}

vtkPolyData* CheckStitchBorder(vtkPolyData *pInData, vtkPolyData *pOutData)
{
	Polyhedron poly;

	vtk_polydata_to_Polyhedron(poly, pInData);

	PMP::stitch_borders(poly);

	if (pOutData == nullptr)
	{
		pOutData = vtkPolyData::New();
	}

	Polyhedron_to_vtk_polydata(poly, pOutData);

	return pOutData;
}