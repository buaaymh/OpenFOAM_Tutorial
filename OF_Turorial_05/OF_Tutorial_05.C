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
    OF_Tutorial_02

Description
    This is the OpenFOAM FieldTest tutorial from buaaymh.

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
     // Initialise OF case
     #include "setRootCase.H"
     #include "createTime.H"
     #include "createMesh.H"

     Info<< "Reading field p\n" << endl;
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

     Info<< "Reading field U\n" << endl;
	volVectorField U // note that velocity is a vector field
	(
		IOobject
		(
		    "U",
		    runTime.timeName(),
		    mesh,
		    IOobject::MUST_READ,
		    IOobject::AUTO_WRITE
		),
		mesh
	);

     Info<< "\nStarting time loop\n" << endl;
     while (runTime.loop())
     {
          Info<< "Time = " << runTime.timeName() << nl << endl;
          for (label cellI=0; cellI<mesh.C().size(); cellI++)
		{
               const vector& center = mesh.C()[cellI];
               p[cellI] = Foam::sin(2*Foam::constant::mathematical::pi*
                                    center.x());
          }
          p.correctBoundaryConditions();
          U = fvc::grad(p)*dimensionedScalar("tmp",dimTime,1.);
          U.correctBoundaryConditions();
          runTime.write();
     }

     Info<< "End\n" << endl;

     return 0;
}

// ************************************************************************* //