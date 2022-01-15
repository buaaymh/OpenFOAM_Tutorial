/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2019 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Application
    OF_Tutorial_06

Description
    This is the OpenFOAM ParallelTest tutorial from buaaymh.

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
     // Initialise OF case
     #include "setRootCase.H"
     #include "createTime.H"
     #include "createMesh.H"

     Pout << "Hello from processor " << Pstream::myProcNo() << "! I am working on "
          << mesh.C().size() << " cells" << endl;

     scalar meshVolume(0.);
     forAll(mesh.V(), cellI) meshVolume += mesh.V()[cellI];

     Pout << "Mesh volume on this processor: " << meshVolume << endl;
     reduce(meshVolume, sumOp<scalar>());
     Info << "Total mesh volume on all processors: " << meshVolume
          << " over " << returnReduce(mesh.C().size(), sumOp<label>())
          << " cells" << endl;

     // Spreading a value across all processors is done using a scatter operation.
     Pstream::scatter(meshVolume);
     Pout << "Mesh volume on this processor is now " << meshVolume << endl;

     // It is often useful to check the distribution of something across all
     // processors. This may be done using a list, with each element of it
     // being written to by only one processor.
     List<label> nInternalFaces (Pstream::nProcs()), nBoundaries (Pstream::nProcs());
     nInternalFaces[Pstream::myProcNo()] = mesh.Cf().size();
     nBoundaries[Pstream::myProcNo()] = mesh.boundary().size();

     // The list may then be gathered on the head node as
     Pstream::gatherList(nInternalFaces);
     Pstream::gatherList(nBoundaries);
     // Scattering a list is also possbile
     Pstream::scatterList(nInternalFaces);
     Pstream::scatterList(nBoundaries);

     // It can also be useful to do things on the head node only
     // (in this case this is meaningless since we are using Info, which already
     // checks this and executes on the head node).
     // Note how the gathered lists hold information for all processors now.
     if (Pstream::master())
     {
          forAll(nInternalFaces,i)
               Info << "Processor " << i << " has " << nInternalFaces[i]
                    << " internal faces and " << nBoundaries[i] << " boundary patches" << endl;
     }

     // As the mesh is decomposed, interfaces between processors are turned
     // into patches, meaning each subdomain sees a processor boundary as a
     // boundary condition.
     forAll(mesh.boundary(),patchI)
          Pout << "Patch " << patchI << " named " << mesh.boundary()[patchI].name() << endl;

     // When looking for processor patches, it is useful to check their type,
     // similarly to how one can check if a patch is of empty type
     forAll(mesh.boundary(),patchI)
     {
          const polyPatch& pp = mesh.boundaryMesh()[patchI];
          if (isA<processorPolyPatch>(pp))
          {
               Pout << "Patch " << patchI << " named " << mesh.boundary()[patchI].name()
                    << " is definitely a processor boundary!" << endl;
               forAll(mesh.boundary()[patchI].Cf(), faceI)
               {
                    Pout << "face " << faceI << " " << mesh.boundary()[patchI].Cf()[faceI] << endl;
               }
          }
               
     }

     volScalarField p // note that pressure is a scalar field
	(
		IOobject
		(
		    "p", // name of the field
		    runTime.timeName(), // name of the current time, i.e. the time folder to read from
		    mesh,
		    IOobject::MUST_READ, // always gets imported, will throw an error if the field is missing
		    IOobject::AUTO_WRITE // will get saved automatically when the controlDict parameters will request it
		),
		mesh // initialises the field to match the size of the mesh with default (0) values
	);

     runTime++;
     forAll(p, iCell)
          p[iCell] = Pstream::myProcNo();
     runTime.write();
     
     runTime++;
     p.correctBoundaryConditions();
     forAll(mesh.boundary(), patchI)
     {
          if(mesh.boundary()[patchI].coupled())
          {
               const UList<label>& bfaceCells = mesh.boundary()[patchI].faceCells();
               const scalarField neig = p.boundaryField()[patchI].patchNeighbourField();
               forAll(bfaceCells, faceI)
                    p[bfaceCells[faceI]] = neig[faceI];
               Pout << "Processor" << Pstream::myProcNo() << " has exchanged!" << endl;
          }
     }
     runTime.write();

     Info<< "\nEnd\n" << endl;

     return 0;
}

// ************************************************************************* //