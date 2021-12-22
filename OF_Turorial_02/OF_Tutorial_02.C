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

    const word dictName("testProperties");

    // Create and input-output object
    IOobject yourDictObject
    (
        dictName, // name of the file
        mesh.time().constant(), // path to where the file is
        mesh, // reference to the mesh needed by the constructor
        IOobject::MUST_READ // indicate that reading this dictionary is compulsory
    );
    // Initialise the dictionary object
    dictionary testDict = IOdictionary(yourDictObject);

    word outputWord;
    testDict.lookup("myName") >> outputWord;

    scalar gamma(testDict.lookupOrDefault<scalar>("gamma", 1.4));
    scalar PI(testDict.lookupOrDefault<scalar>("PI", 3.1415));
    bool yourBool(testDict.lookupOrDefault<Switch>("yourBool", true));
    List<scalar> outputList (testDict.lookup("yourList"));
    vector yourVector (testDict.lookupOrDefault<vector>("yourVector", vector::zero));
    tensor yourTensor (testDict.lookupOrDefault<tensor>("yourTensor", tensor::zero));

    Info << "What you got here:" << nl
         << nl
         << "myName: "         << outputWord << nl
         << "gamma: "          << gamma << nl
         << "PI: "             << PI << nl
         << "yourBool: "       << yourBool << nl
         << "yourList: "       << outputList << nl
         << "yourVector: "     << yourVector << nl
         << "yourTensor: "     << yourTensor << nl
         << endl;

    Info<< "End\n" << endl;

    return 0;
}

// ************************************************************************* //