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
    This is the OpenFOAM DictionaryTest tutorial from buaaymh.

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    // Initialise OF case
    #include "setRootCase.H"
    #include "createTime.H"
    #include "createMesh.H"

     // Initialise the dictionary object
     IOdictionary testDict
     (
          IOobject
          (
               "fluidProperties", // name of the file
               mesh.time().constant(), // path to where the file is
               mesh, // reference to the mesh needed by the constructor
               IOobject::MUST_READ // indicate that reading this dictionary is compulsory
          )
     );

    word simulationType;
    testDict.lookup("simulationType") >> simulationType;

    scalar gamma(testDict.lookupOrDefault<scalar>("gamma", 1.4));
    scalar R(testDict.lookupOrDefault<scalar>("R", 0.0));
    scalar PrDyna(testDict.lookupOrDefault<scalar>("PrDyna", 0.0));
    scalar PrTurb(testDict.lookupOrDefault<scalar>("PrTurb", 0.0));

    Info << "Gas information:" << nl
         << nl
         << "simulationType: "  << simulationType << nl
         << "gamma: "           << gamma << nl
         << "R: "               << R << nl
         << "PrDyna: "          << PrDyna << nl
         << "PrTurb: "          << PrTurb << nl
         << endl;

    const dictionary& freeStream = testDict.subDict("freeStream");
    vector refU    = freeStream.lookup<vector>("refU");
    scalar refPres = freeStream.lookup<scalar>("refPres");
    scalar refT    = freeStream.lookup<scalar>("refT");
    scalar refVisc = freeStream.lookup<scalar>("refVisc");

    Info << "Free stream information:" << nl
         << nl
         << "refPres: "  << refU << nl
         << "refPres: "  << refPres << nl
         << "refPres: "  << refT << nl
         << "refPres: "  << refVisc << nl
         << endl;

    const dictionary& scheme = mesh.schemesDict();
    label nIter = scheme.subDict("vrSchemes").lookupOrDefault<label>("nIter", 1);
    List<scalar> weightList = scheme.subDict("vrSchemes").lookup<List<scalar>>("weightList");
    word flux = scheme.subDict("divSchemes").lookupOrDefault<word>("flux", "roe");
    Info << "Scheme information:" << nl
         << nl
         << "nIter: "       << nIter << nl
         << "weightList: "  << weightList << nl
         << "flux: "        << flux << nl
         << endl;

    const dictionary& solution = mesh.solutionDict();
    label maxIter = solution.subDict("GMRES").lookupOrDefault<label>("maxIter", 10);
    label nKrylov = solution.subDict("GMRES").lookupOrDefault<label>("nKrylov", 10);
    scalar tolerance = solution.subDict("GMRES").lookupOrDefault<scalar>("tolerance", 1e-2);
    scalar relTol = solution.subDict("GMRES").lookupOrDefault<scalar>("relTol", 1e-2);
    Info << "Solution information:" << nl
         << nl
         << "maxIter: "   << maxIter << nl
         << "nKrylov: "   << nKrylov << nl
         << "tolerance: " << tolerance << nl
         << "relTol: "    << relTol << nl
         << endl;

    scalar startTime = runTime.controlDict().lookupOrDefault<scalar>("startTime", 1.0);
    scalar endTime = runTime.controlDict().lookupOrDefault<scalar>("endTime", 1.0);
    scalar deltaT = runTime.controlDict().lookupOrDefault<scalar>("deltaT", 1.0);
    scalar maxCo = runTime.controlDict().lookupOrDefault<scalar>("maxCo", 1.0);
    Info << "Time information:" << nl
         << nl
         << "startTime: "   << startTime << nl
         << "endTime: "     << endTime << nl
         << "deltaT: "      << deltaT << nl
         << "maxCo: "       << maxCo << nl
         << endl;

    Info<< "End\n" << endl;

    return 0;
}

// ************************************************************************* //