
#include <vtkPolyData.h>
#include <vtkSTLReader.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>

#include "PolygonsRepair.h"

int TestFillHole(int argc, char *argv[])
{
	if (argc != 2)
	{
		cout << "Required parameters: Filename" << endl;
		return EXIT_FAILURE;
	}

	std::string inputFilename = argv[1];

	vtkSTLReader *reader = vtkSTLReader::New();
	reader->SetFileName(inputFilename.c_str());
	reader->Update();

	vtkPolyData *pInputData = vtkPolyData::New();
	pInputData = reader->GetOutput();

	vtkPolyData *pOutData = vtkPolyData::New();

	PolygonsFillHole(pInputData, pOutData);

	// Visualize
	vtkPolyDataMapper *mapper1 = vtkPolyDataMapper::New();
	mapper1->SetInputData(pInputData);

	vtkActor *actor1 = vtkActor::New();
	actor1->SetMapper(mapper1);
	actor1->GetProperty()->EdgeVisibilityOn();

	vtkRenderer *renderer1 = vtkRenderer::New();
	renderer1->AddActor(actor1);
	renderer1->SetBackground(.3, .6, .3);
	renderer1->SetViewport(0.0, 0.0, 0.5, 1.0);

	// Visualize
	vtkPolyDataMapper *mapper2 = vtkPolyDataMapper::New();
	mapper2->SetInputData(pOutData);

	vtkActor *actor2 = vtkActor::New();
	actor2->SetMapper(mapper2);
	actor2->GetProperty()->EdgeVisibilityOn();

	vtkRenderer *renderer2 = vtkRenderer::New();
	renderer2->AddActor(actor2);
	renderer2->SetBackground(.3, .6, .3);
	renderer2->SetViewport(0.5, 0.0, 1.0, 1.0);

	vtkRenderWindow *renderWindow = vtkRenderWindow::New();
	renderWindow->AddRenderer(renderer1);
	renderWindow->AddRenderer(renderer2);
	renderWindow->Render();

	vtkRenderWindowInteractor *rwi = vtkRenderWindowInteractor::New();
	rwi->SetRenderWindow(renderWindow);
	rwi->Start();

	return EXIT_SUCCESS;

}