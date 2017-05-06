

#ifndef _CGAL_to_VTK_Configure_H_
#define _CGAL_to_VTK_Configure_H_

#ifdef CGAL_TO_VTK_DLL
#define CGAL_VTK_EXPORT __declspec(dllexport)
#else
#define CGAL_VTK_EXPORT __declspec(dllimport)
#endif

#endif
