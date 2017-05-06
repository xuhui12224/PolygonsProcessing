#include "PolygonsRepair.h"
#include "CGAL_to_VTK.h"

#include "vtkPolyData.h"

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/boost/graph/graph_traits_Surface_mesh.h>

#include <CGAL/Polygon_mesh_processing/self_intersections.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Polyhedron_3<Kernel>     Polyhedron;
typedef boost::graph_traits<Polyhedron>::face_descriptor face_descriptor;

namespace PMP = CGAL::Polygon_mesh_processing;

vtkPolyData* CheckSelfIntersection(vtkPolyData *pInData, vtkPolyData *pOutData = nullptr)
{
	Polyhedron poly;

	vtk_polydata_to_Polyhedron(poly, pInData);

	bool intersecting = PMP::does_self_intersect(poly,
		PMP::parameters::vertex_point_map(get(CGAL::vertex_point, poly)));

	std::vector<std::pair<face_descriptor, face_descriptor> > intersected_tris;
	PMP::self_intersections(poly,
		std::back_inserter(intersected_tris),
		PMP::parameters::vertex_point_map(get(CGAL::vertex_point, poly)));

	if (pOutData == nullptr)
	{
		pOutData = vtkPolyData::New();
	}

	Polyhedron_to_vtk_polydata(poly, pOutData);

	return pOutData;
}
