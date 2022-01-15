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
    OF_Tutorial_03

Description
    This is the OpenFOAM MeshTest tutorial from buaaymh.

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    // Initialise OF case
    #include "setRootCase.H"
    #include "createTime.H"
    #include "createMesh.H"

    Info << " There are " << mesh.C().size() << " cells here " << nl
         << "  and " << mesh.Cf().size() << " internal faces "
         << nl << endl;

    for (label cellI = 0; cellI < mesh.C().size(); cellI++)
        if (cellI%1 == 0)
            Info << " Number " << cellI << " cell with the center point at " << mesh.C()[cellI] << nl
                << " and it has cells : "  << mesh.cellCells()[cellI] << nl
                << " and it has faces : "  << mesh.cells()[cellI] << nl
                << " and it has points : " << mesh.cellPoints()[cellI] << nl << endl;

    for (label faceI = 0; faceI < mesh.Cf().size(); faceI++)
        if (faceI%5 == 0)
            Info << " The internal face Number " << faceI << " with the center point at " << mesh.Cf()[faceI] << nl
                 << " with the owner face Number " << mesh.owner()[faceI] << nl
                 << " with the neighbour face Number " << mesh.neighbour()[faceI] << nl
                 << " and it has points : " << mesh.faces()[faceI] << nl
                 << endl;

    forAll(mesh.boundary(), patchI)
        Info << "Patch " << patchI << ": " << mesh.boundary()[patchI].name()
             << " is " << "\"" << mesh.boundary()[patchI].type() << "\"" << " and has "
             << mesh.boundary()[patchI].Cf().size() << " faces. Starts at total face "
             << mesh.boundary()[patchI].start() << endl;
    Info << endl;

    label patchID = mesh.boundary().findPatchID("movingWall");
    const fvPatch& patch = mesh.boundary()[patchID];
    const UList<label>& bfaceCells = patch.faceCells();
    const vectorField& Cf = patch.Cf();
    const scalarField& area = patch.magSf();
    Info << "Patch" << "[" << patchID << "] movingWall has :" << endl;
    forAll(patch, faceI)
    {
        Info << "Face" << faceI  << " Cf:" << Cf[faceI] << " area:" << area[faceI]
             << " has cell" << bfaceCells[faceI] << endl; 
    }
    Info << endl;

    word findAPatch("frontAndBack");
    patchID = mesh.boundary().findPatchID(findAPatch);
    const polyPatch& pp = mesh.boundaryMesh()[patchID];
    if (isA<emptyPolyPatch>(pp))
    {
        Info << "The empty patch is [" << patchID << "] which is not been seen." << endl;
    }

    Info<< "End\n" << endl;

    return 0;
}

// ************************************************************************* //