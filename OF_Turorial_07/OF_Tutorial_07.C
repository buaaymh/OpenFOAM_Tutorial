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
    OF_Tutorial_07

Description
    This is the OpenFOAM WallDistTest tutorial from buaaymh.

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "wallDist.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
     // Initialise OF case
     #include "setRootCase.H"
     #include "createTime.H"
     #include "createMesh.H"

     Info << "Mesh read in = "
          << runTime.cpuTimeIncrement()
          << " s\n" << endl;

     Info<< "Time now = " << runTime.timeName() << endl << endl;

     // Wall distance
     const volScalarField& y = wallDist::New(mesh).y();
     y.write();

     Info<< "\nEnd\n" << endl;

     return 0;
}

// ************************************************************************* //