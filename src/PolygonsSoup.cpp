
#include "PolygonsRepair.h"
#include "CGAL_to_VTK.h"

#include "vtkPolyData.h"

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/IO/Polyhedron_iostream.h>
#include <CGAL/boost/graph/graph_traits_Polyhedron_3.h>
#include <CGAL/IO/OFF_reader.h>
#include <CGAL/Polygon_mesh_processing/orient_polygon_soup.h>
#include <CGAL/Polygon_mesh_processing/polygon_soup_to_polygon_mesh.h>
#include <CGAL/Polygon_mesh_processing/orientation.h>

#include <vector>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Polyhedron_3<Kernel>     Polyhedron;
typedef boost::graph_traits<Polyhedron>::face_descriptor face_descriptor;

namespace PMP = CGAL::Polygon_mesh_processing;

vtkPolyData* PolygonsSoupToMesh(vtkPolyData *pInData, vtkPolyData *pOutData = nullptr)
{
	Polyhedron poly;

	vtk_polydata_to_Polyhedron(poly, pInData);

	std::vector<K::Point_3> points;
	std::vector< std::vector<std::size_t> > polygons;
	
	PMP::orient_polygon_soup(points, polygons);

	Polyhedron mesh;
	PMP::polygon_soup_to_polygon_mesh(points, polygons, mesh);

	if (CGAL::is_closed(mesh) && (!PMP::is_outward_oriented(mesh)))
	{
		PMP::reverse_face_orientations(mesh);
	}
		
	if (pOutData == nullptr)
	{
		pOutData = vtkPolyData::New();
	}

	Polyhedron_to_vtk_polydata(poly, pOutData);

	return pOutData;
}
