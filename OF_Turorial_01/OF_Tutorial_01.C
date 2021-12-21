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
    OF_Tutorial_01

Description
    This is the OpenFOAM InfoTest tutorial from buaaymh.

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"

using namespace Foam;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    // Initialise OF case
    #include "setRootCase.H"

    // Similar to std::cout, std::nl and std::endl in C++, you just need to
    // replace them with Foam::Info, Foam::nl and Foam::endl(multi-processors).
    Info << "Hello , OpenFOAM learner!" << nl
		 << "You don't need a mesh or anything to run it, just a bare OpenFOAM case will do." << nl
		 << tab << "this is to test the info demo." << nl << endl;

    Info<< "End\n" << endl;

    return 0;
}

// ************************************************************************* //