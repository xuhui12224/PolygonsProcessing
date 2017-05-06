
#include "PolygonsRepair.h"
#include "CGAL_to_VTK.h"

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/boost/graph/graph_traits_Polyhedron_3.h>

#include <CGAL/Polygon_mesh_processing/triangulate_hole.h>

#include <boost/foreach.hpp>

#include "vtkPolyData.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Polyhedron_3<Kernel>     Polyhedron;

typedef Polyhedron::Halfedge_handle    Halfedge_handle;
typedef Polyhedron::Facet_handle       Facet_handle;
typedef Polyhedron::Vertex_handle      Vertex_handle;
namespace PMP = CGAL::Polygon_mesh_processing;

vtkPolyData* PolygonsFillHole(vtkPolyData *pInData, vtkPolyData *pOutData)
{
	Polyhedron poly;

	vtk_polydata_to_Polyhedron(poly, pInData);

	// Incrementally fill the holes
	unsigned int nb_holes = 0;
	BOOST_FOREACH(Halfedge_handle h, halfedges(poly))
	{
		if (h->is_border())
		{
			std::vector<Facet_handle>  patch_facets;
			std::vector<Vertex_handle> patch_vertices;
			bool success = CGAL::cpp11::get<0>(
				PMP::triangulate_refine_and_fair_hole(
				poly,
				h,
				std::back_inserter(patch_facets),
				std::back_inserter(patch_vertices),
				PMP::parameters::vertex_point_map(get(CGAL::vertex_point, poly)).geom_traits(Kernel())));

			++nb_holes;
		}
	}

	if (pOutData == nullptr)
	{
		pOutData = vtkPolyData::New();
	}

	Polyhedron_to_vtk_polydata(poly, pOutData);

	return pOutData;
}

vtkPolyData* CheckFillHole(vtkPolyData *pInData, vtkPolyData *pOutData)
{
	Polyhedron poly;

	vtk_polydata_to_Polyhedron(poly, pInData);

	// Incrementally fill the holes
	unsigned int nb_holes = 0;
	BOOST_FOREACH(Halfedge_handle h, halfedges(poly))
	{
		if (h->is_border())
		{
			std::vector<Facet_handle>  patch_facets;
			std::vector<Vertex_handle> patch_vertices;
			bool success = CGAL::cpp11::get<0>(
				PMP::triangulate_refine_and_fair_hole(
				poly,
				h,
				std::back_inserter(patch_facets),
				std::back_inserter(patch_vertices),
				PMP::parameters::vertex_point_map(get(CGAL::vertex_point, poly)).
				geom_traits(Kernel())));

			++nb_holes;
		}
	}

	if (pOutData == nullptr)
	{
		pOutData = vtkPolyData::New();
	}

	Polyhedron_to_vtk_polydata(poly, pOutData);

	return pOutData;
}

