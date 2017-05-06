
#ifndef _CGAL_TO_VTK_H_
#define _CGAL_TO_VTK_H_

#include "vtkPolyData.h"
#include "vtkPoints.h"
#include "vtkCellArray.h"

#include <CGAL/basic.h>
#include <CGAL/Inverse_index.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polyhedron_incremental_builder_3.h>

namespace CGAL
{
	template <typename P>
	vtkPolyData* Polyhedron_to_vtk_polydata(const P& tr3, vtkPolyData* polydata = 0)
	{
		typedef typename P::Vertex_const_iterator					VCI;
		typedef typename P::Facet_const_iterator					FCI;
		typedef typename P::Halfedge_around_facet_const_circulator	HFCC;

		typedef typename P::Point_3									Point;

		vtkPoints* const vtk_points = vtkPoints::New();
		vtkCellArray* const vtk_cells = vtkCellArray::New();

		for (VCI vi = tr3.vertices_begin(); vi != tr3.vertices_end(); ++vi)
		{
			Point p = vi->point();
			vtk_points->InsertNextPoint(CGAL::to_double(p.x()), CGAL::to_double(p.y()), CGAL::to_double(p.z()));
		}

		typedef Inverse_index< VCI> Index;
		Index index(tr3.vertices_begin(), tr3.vertices_end());

		for (FCI fi = tr3.facets_begin(); fi != tr3.facets_end(); ++fi)
		{
			HFCC hc = fi->facet_begin();
			HFCC hc_end = hc;
			std::size_t n = circulator_size(hc);

			CGAL_assertion(n >= 3);

			vtkIdType *pIds = new vtkIdType[n];

			for (std::size_t i = 0; i < n; i++)
			{
				pIds[i] = index[VCI(hc->vertex())];
				++hc;
			}

			vtk_cells->InsertNextCell(n, pIds);
		}

		if (!polydata)
		{
			polydata = vtkPolyData::New();
		}

		polydata->SetPoints(vtk_points);
		vtk_points->Delete();

		polydata->SetPolys(vtk_cells);
		vtk_cells->Delete();

		return polydata;
	}

	template <typename P>
	bool vtk_polydata_to_Polyhedron(P& tr3, vtkPolyData* polydata)
	{
		typedef typename P::HalfedgeDS				HDS;
		typedef typename P::Point_3					Point;

		vtkPoints* vtk_points = vtkPoints::New();
		vtk_points = polydata->GetPoints();

		Polyhedron_incremental_builder_3<HDS> B(tr3.hds());
		B.begin_surface(polydata->GetNumberOfPoints(), polydata->GetPolys()->GetNumberOfCells());

		typedef typename HDS::Traits     Traits;
		typedef typename Traits::Point_3 Point;

		for (int i = 0; i < polydata->GetNumberOfPoints(); i++)
		{
			double *p = polydata->GetPoint(i);
			Point pt(p[0], p[1], p[2]);
			B.add_vertex(pt);
		}

		vtkIdList *ids = vtkIdList::New();
		polydata->GetPolys()->InitTraversal();
		while (polydata->GetPolys()->GetNextCell(ids))
		{
			B.begin_facet();
			for (int i = 0; i < ids->GetNumberOfIds(); i++)
			{
				B.add_vertex_to_facet(ids->GetId(i));
			}
			B.end_facet();
		}

		if (B.error())
		{
			B.rollback();
			return false;
		}

		B.end_surface();

		if (B.check_unconnected_vertices())
		{
			if (!B.remove_unconnected_vertices())
			{
				B.rollback();
				return false;
			}
		}
		return true;
	}
}


#endif